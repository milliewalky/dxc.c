# (C bindings for) DirectX Shader Compiler

Bindings are for **Version: dxcompiler.dll: 1.7 - 1.7.2212.40 (e043f4a12); dxil.dll: 1.7(101.7.2212.36)**!

This repository aims to provide C bindings for DirectX Shader Compiler. At the
moment, the bindings are completely handcrafted.

Due to the nature of these bindings, it is possible to use them _instead of_
the original library.

## Repository tour

### Concept

The bindings mimic how Microsoft exposes C bindings for their C++ interfaces,
and contrary to [d3d12ma.c](https://github.com/milliewalky/d3d12ma.c), they
_really_ do. _Virtual tables_ were implemented for every `class` exposed in
`dxcapi.h`. Then, corresponding `struct`s were created that followed the names
of the original ones, and these included a pointer to the virtual method table
defined in the first step. Consider this example:
```c
//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// IDxcBlob is an alias of ID3D10Blob and ID3DBlob
CROSS_PLATFORM_UUIDOF(IDxcBlob, "8BA5FB08-5195-40e2-AC58-0D989C3A0102")
struct IDxcBlob : public IUnknown {
public:
  virtual LPVOID GetBufferPointer(void) = 0;
  virtual SIZE_T GetBufferSize(void) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

// ...

typedef struct IDxcBlobVTable IDxcBlobVTable;
struct IDxcBlobVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 LPVOID (*GetBufferPointer)(void *pSelf);
 SIZE_T (*GetBufferSize)(void *pSelf);
};

#if DXC_LANG_C

typedef struct IDxcBlob IDxcBlob;
struct IDxcBlob
{
 IDxcBlobVTable *lpVtbl;
};

#endif // DXC_LANG_C
```
Then, you let the implementation initialise `DXC_LANG_C`-`ifdef`'d `struct` in
your C program and as a consequence, `lpVtbl` gets initialised as well.

Additionally, this library supports `COBJMACROS`, allowing you to write, for
example:
```c
IDxcBlob_GetBufferPointer(pSelf)
```
Instead of:
```c
pSelf->lpVtbl->GetBufferPointer(pSelf)
```
Which _may_ be convinient.

The `struct`s themselves did not require doing any sort of mappings inbetween
the bindings ane the original implementation.

### Top-level directories

- `data/third_party/dxc`: Small binary files which are used when building,
  either to embed within build artifacts, or to package with them. Here
  specifically: `dxc`, which contains DirectX Shader Compiler binaries.
- `code`: All source code.
  - `dxc`: Bindings to DirectX Shader Compiler.
  - `samples`: Basic samples that use the compiler to create shader reflection.
    _The_ samples encompass both C and C++ code cases.
  - `third_party/dxc`: Third party libraries, but at this moment and here
    specifically: DirectX Shader Compiler headers. Whereas `dxcapi.h` is not
    necessary per se, `d3d12shader.h` might be useful.

After setting up the codebase and building, the following directories will
also exist:

- `build`: All build artifacts. Not checked in to version control.
- `local`: Local files, used for local build configuration input files.
  At this very moment, this directory is completetly obsolete.

## Example usage

```c
IDxcUtils *utils = 0;
IDxcCompiler3 *compiler = 0;
IDxcIncludeHandler *include_handler = 0;

DxcCreateInstance(&CLSID_DxcUtils, &IID_IDxcUtils, &utils); // NOTE(mwalky): or `(void **)(&<var>)` 
DxcCreateInstance(&CLSID_DxcCompiler, &IID_IDxcCompiler3, &compiler);
IDxcUtils_CreateDefaultIncludeHandler(utils, &include_handler);
 
IDxcBlobEncoding *blob_encoding = 0; 
DxcBuffer src = {0};
{
 IDxcUtils_LoadFile(utils, "shader.hlsl", 0, &blob_encoding);
 src.Ptr =  IDxcBlobEncoding_GetBufferPointer(blob_encoding);
 src.Size = IDxcBlobEncoding_GetBufferSize(blob_encoding);
 BOOL known = 0;
 IDxcBlobEncoding_GetEncoding(blob_encoding, &known, &src.Encoding);
}
LPCWSTR args[] =
{
 L"-HV",
 L"2021",
};
IDxcCompilerArgs *compiler_args = 0;
IDxcUtils_BuildArguments(utils,
                         "shader.hlsl",
                         "CS_EntryPoint",
                         "cs_6_5",
                         args,
                         _countof(args),
                         0,
                         0,
                         &compiler_args);

IDxcResult *result = 0;
IDxcCompiler3_Compile(compiler,
                      &src,
                      IDxcCompilerArgs_GetArguments(compiler_args),
                      IDxcCompilerArgs_GetCount(compiler_args),
                      include_handler,
                      &IID_IDxcResult,
                      &result);
```

## C && C++ integration

To use this library in any C && C++ codebase, simply include `dxc.h` and link
your program against `dxcompiler.lib`. `dxcompiler.lib` is bundled together
with `dxc.h`.
```c
// NOTE(mwalky): perhaps `main.c`

#pragma comment(lib, "user32")
#pragma comment(lib, "third_party/dxc/dxcompiler.lib") // NOTE(mwalky) provided by dxc, bundled with the code in this repository

#include "windows.h"
#include "initguid.h" // NOTE(mwalky): for GUIDs

#define COBJMACROS // NOTE(mwalky): Optional, but convinient
#include "dxc/dxc.h"

int
main(void)
{
 return 0;
}

```
Examples can be found in `code/samples/samples_reflection_main.c` and
`code/samples/samples_reflection_main.cpp`.

## Disclaimers

These are bindings for [DirectX Shader Compiler](https://github.com/microsoft/DirectXShaderCompiler)
developed by Microsoft Corporation. I do not own DirectX Shader Compiler in any
way.

This `README.md` file does not provide any documentation for
DirectX Shader Compiler itself. Refer to [the documentation](https://github.com/microsoft/DirectXShaderCompiler/tree/main/docs).

The codebase introduces some concepts found in MIT licensed
[The RAD Debugger Project](https://github.com/EpicGamesExt/raddebugger), such
as context cracking.
