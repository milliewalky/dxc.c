// Copyright (c) 2024 M. Walky
// Licensed under the MIT license (https://opensource.org/license/mit/)

////////////////////////////////
//~ mwalky: [h]

#include "stdio.h"

#include "windows.h"
#include "initguid.h"

#include "third_party/dxc/d3d12shader.h"

#define COBJMACROS
#include "dxc/dxc.h"

#pragma comment(lib, "third_party/dxc/dxcompiler.lib")

////////////////////////////////
//~ mwalky: Globals

IDxcUtils *utils = 0;
IDxcCompiler3 *compiler = 0;
IDxcIncludeHandler *include_handler = 0;

int
main()
{
 HRESULT error = 0;
 IDxcBlobEncoding *error_blob = 0;
 LPCWSTR error_str = 0;

 DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&utils));
 DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&compiler));
 utils->CreateDefaultIncludeHandler(&include_handler);

 //- mwalky: compile graphics kernels
 {
  DxcBuffer src = {};
  {
   src.Ptr = "cbuffer constant_buffer:register(b0){matrix model;matrix view;matrix projection;float4 color;};struct vs_input{float3 position:POSITION;float3 normal:NORMAL;};struct vs_output{float4 position:SV_POSITION;float3 normal:NORMAL;float4 color:COLOR;};vs_output vs_entry_point(vs_input input){vs_output output;float4 world_position=mul(float4(input.position,1.0f),model);output.position=mul(world_position,view);output.position=mul(output.position,projection);output.normal=mul(input.normal,(float3x3)model);output.color=color;return output;}struct ps_input{float4 position:SV_POSITION;float3 normal:NORMAL;float4 color:COLOR;};float4 ps_entry_point(ps_input input):SV_TARGET{float3 light_dir=normalize(float3(0.0f,1.0f,-1.0f));float diffuse=max(dot(input.normal,light_dir),0.0f);return input.color*diffuse;}";
   src.Size = strlen((const char *)src.Ptr);
   src.Encoding = DXC_CP_ACP;
  }
  printf("Shader `DxcBuffer` -> Ptr: %p, Size: %lld\n", src.Ptr, src.Size);

  LPCWSTR args[] =
  {
   L"-E", L"vs_entry_point",
   L"-T", L"vs_6_5"
  };
  IDxcResult *result = 0;
  compiler->Compile(&src, args, _countof(args), include_handler, IID_IDxcResult, (void **)&result);
  printf("`IDxcCompiler3_Compile` -> %lx\n", error);
  if(FAILED(error))
  {
   result->GetErrorBuffer(&error_blob);
   error_str = (LPCWSTR)error_blob->GetBufferPointer();
   wprintf(L"Oh, failed to compile THIS -> %s\n", error_str);
  }
  else
  {
   IDxcBlob *bytecode = 0;
   result->GetResult(&bytecode);
   
   IDxcBlob *reflection = 0;
   result->GetOutput(DXC_OUT_REFLECTION, IID_IDxcBlob, (void **)(&reflection), 0);
   
   DxcBuffer reflection_data = {};
   if(reflection)
   {
    reflection_data.Ptr = reflection->GetBufferPointer();
    reflection_data.Size = reflection->GetBufferSize();
    printf("Reflection `DxcBuffer` -> Ptr: %p, Size: %lld\n", reflection_data.Ptr, reflection_data.Size);
    ID3D12ShaderReflection *d3d12_reflection = 0;
    utils->CreateReflection(&reflection_data, IID_ID3D12ShaderReflection, (void **)(&d3d12_reflection));

    D3D12_SHADER_DESC shader_desc = {0};
    {
     d3d12_reflection->GetDesc(&shader_desc);
    }
    printf(" ~~~ shader ~~~\n");
    printf(" version             -> %u\n", shader_desc.Version);
    printf(" creator             -> %s\n", shader_desc.Creator);
    printf(" input parameters    -> %u\n", shader_desc.InputParameters);
    printf(" output parameters   -> %u\n", shader_desc.OutputParameters);
    printf(" constant buffers    -> %u\n", shader_desc.ConstantBuffers);
    printf(" bound resources     -> %u\n", shader_desc.BoundResources);

    for (UINT cbuffer_idx = 0; cbuffer_idx < shader_desc.ConstantBuffers; cbuffer_idx += 1)
    {
     ID3D12ShaderReflectionConstantBuffer *cbuffer = d3d12_reflection->GetConstantBufferByIndex(cbuffer_idx);
     D3D12_SHADER_BUFFER_DESC buffer_desc = {0};
     {
      cbuffer->GetDesc(&buffer_desc);
     }
     printf(" constant buffer %u   -> %s\n", cbuffer_idx, buffer_desc.Name);
     printf("  size               -> %u\n", buffer_desc.Size);
     printf("  variables          -> %u\n", buffer_desc.Variables);
     printf("  type               -> %u\n", buffer_desc.Type);

     for (UINT var_idx = 0; var_idx < buffer_desc.Variables; var_idx += 1)
     {
      ID3D12ShaderReflectionVariable *var = cbuffer->GetVariableByIndex(var_idx);
      D3D12_SHADER_VARIABLE_DESC var_desc = {0};
      {
       var->GetDesc(&var_desc);
      }
      printf("  variable %u         -> %s\n", var_idx, var_desc.Name);
      printf("   start offset      -> %u\n", var_desc.StartOffset);
      printf("   size              -> %u\n", var_desc.Size);
     }
    }
   }
  }
 }
 return 0;
}
