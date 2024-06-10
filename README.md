# (C bindings for) DirectX Shader Compiler

_**NOTE**: These are bindings for [DirectX Shader Compiler](https://github.com/microsoft/DirectXShaderCompiler)
developed by Microsoft Corporation. I do not own DirectX Shader Compiler in any
way._

_**NOTE2**: This `README.md` file does not provide any documentation for
DirectX Shader Compiler itself. Refer to [the documentation](https://github.com/microsoft/DirectXShaderCompiler/tree/main/docs)._

_**NOTE3**: The codebase introduces some concepts found in MIT licensed
[The RAD Debugger Project](https://github.com/EpicGamesExt/raddebugger), such
as context cracking._

Bindings are for **Version: dxcompiler.dll: 1.7 - 1.7.2212.40 (e043f4a12); dxil.dll: 1.7(101.7.2212.36)**!

This repository aims to provide C bindings for DirectX Shader Compiler. At the
moment, the bindings are completely handcrafted.

Due to the nature of these bindings, it is possible to use them _instead of_
the original library.

## Repository tour

### Concept

_The_ bindings mimic how Microsoft exposes C bindings for their C++ interfaces.
COM objects follow a specific memory layout to ensure interoperability. Each
COM object typically includes:

- _Virtual method table pointer_: Stored at the beginning.
- _Object data_: Stored right after _virtual method table pointer_.

For bindings, I implement a _virtual method table pointer_ for every `class`.
Then, I create a `struct` that corresponds to the original one, naming it
appropriately and including a pointer to the virtual method table pointer.
Consider this example:
```c
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
Then, you let the implementation initialize the `struct`, and as a consequence,
`lpVtbl` gets initialized as well.

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

The `struct`'s themselves did not require doing any sort of mappings inbetween
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

### C && C++ integration

To use this library in any C && C++ codebase, simply include `dxc.h` and link
your program against `dxcompiler.lib`. `dxcompiler.lib` is bundled together
with `dxc.h`.
```c
#define COBJMACROS // NOTE(mwalky): Optional, but convinient
#include "dxc/dxc.h"

#pragma comment(lib, "third_party/dxc/dxcompiler.lib")
```
Examples can be found in `code/samples/samples_main.c` and
`code/samples/samples_main.cpp`.
