// Copyright (c) 2024 M. Walky
// Licensed under the MIT license (https://opensource.org/license/mit/)

#ifndef DXC_H
#define DXC_H

////////////////////////////////
//~ mwalky: MSVC Cracking

#if defined(_MSC_VER)

#define DXC_COMPILER_MSVC 1
#if defined(_WIN32)
#define DXC_OS_WINDOWS 1
#else
#error _MSC_VER is defined, but _WIN32 is not. This setup is not supported.
#endif

#if defined(_M_AMD64)
#define DXC_ARCH_X64 1
#elif defined(_M_IX86)
#define DXC_ARCH_X86 1
#elif defined(_M_ARM64)
#define DXC_ARCH_ARM64 1
#elif defined(_M_ARM)
#define DXC_ARCH_ARM32 1
#else
#error Target architecture is not supported. _MSC_VER is defined, but one of {_M_AMD64, _M_IX86, _M_ARM64, _M_ARM} is not.
#endif

#if _MSC_VER >= 1920
#define DXC_COMPILER_MSVC_YEAR 2019
#elif _MSC_VER >= 1910
#define DXC_COMPILER_MSVC_YEAR 2017
#elif _MSC_VER >= 1900
#define DXC_COMPILER_MSVC_YEAR 2015
#elif _MSC_VER >= 1800
#define DXC_COMPILER_MSVC_YEAR 2013
#elif _MSC_VER >= 1700
#define DXC_COMPILER_MSVC_YEAR 2012
#elif _MSC_VER >= 1600
#define DXC_COMPILER_MSVC_YEAR 2010
#elif _MSC_VER >= 1500
#define DXC_COMPILER_MSVC_YEAR 2008
#elif _MSC_VER >= 1400
#define DXC_COMPILER_MSVC_YEAR 2005
#else
#define DXC_COMPILER_MSVC_YEAR 0
#endif

////////////////////////////////
//~ mwalky: Clang Cracking

#elif defined(__clang__)

#define DXC_COMPILER_CLANG 1

#if defined(__APPLE__) && defined(__MACH__)
#define DXC_OS_MAC 1
#elif defined(__gnu_linux__)
#define DXC_OS_LINUX 1
#else
#error __clang__ is defined, but one of {__APPLE__, __gnu_linux__} is not. This setup is not supported.
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define DXC_ARCH_X64 1
#elif defined(i386) || defined(__i386) || defined(__i386__)
#define DXC_ARCH_X86 1
#elif defined(__aarch64__)
#define DXC_ARCH_ARM64 1
#elif defined(__arm__)
#define DXC_ARCH_ARM32 1
#else
#error Target architecture is not supported. __clang__ is defined, but one of {__amd64__, __amd64, __x86_64__, __x86_64, i386, __i386, __i386__, __aarch64__, __arm__} is not.
#endif

////////////////////////////////
//~ mwalky: GCC Cracking

#elif defined(__GNUC__) || defined(__GNUG__)

#define DXC_COMPILER_GCC 1

#if defined(__gnu_linux__)
#define DXC_OS_LINUX 1
#else
#error __GNUC__ or __GNUG__ is defined, but __gnu_linux__ is not. This setup is not supported.
#endif

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#define DXC_ARCH_X64 1
#elif defined(i386) || defined(__i386) || defined(__i386__)
#define DXC_ARCH_X86 1
#elif defined(__aarch64__)
#define DXC_ARCH_ARM64 1
#elif defined(__arm__)
#define DXC_ARCH_ARM32 1
#else
#error Target architecture is not supported. __GNU_C__ or __GNUG__ is defined, but one of {__amd64__, __amd64, __x86_64__, __x86_64, i386, __i386, __i386__, __aarch64__, __arm__} is not.
#endif

#else
#error Compiler is not supported. _MSC_VER, __clang__, __GNUC__, or __GNUG__ must be defined.
#endif

#if defined(DXC_ARCH_X64)
#define DXC_ARCH_64BIT 1
#elif defined(DXC_ARCH_X86)
#define DXC_ARCH_32BIT 1

#endif

////////////////////////////////
//~ mwalky: Language Cracking

#if defined(__cplusplus)
#define DXC_LANG_CPP 1
#else
#define DXC_LANG_C 1
#endif

////////////////////////////////
//~ mwalky: Zero-ing All Undefined Options

#if !defined(DXC_ARCH_32BIT)
#define DXC_ARCH_32BIT 0
#endif
#if !defined(DXC_ARCH_64BIT)
#define DXC_ARCH_64BIT 0
#endif
#if !defined(DXC_ARCH_X64)
#define DXC_ARCH_X64 0
#endif
#if !defined(DXC_ARCH_X86)
#define DXC_ARCH_X86 0
#endif
#if !defined(DXC_ARCH_ARM64)
#define DXC_ARCH_ARM64 0
#endif
#if !defined(DXC_ARCH_ARM32)
#define DXC_ARCH_ARM32 0
#endif
#if !defined(DXC_COMPILER_MSVC)
#define DXC_COMPILER_MSVC 0
#endif
#if !defined(DXC_COMPILER_GCC)
#define DXC_COMPILER_GCC 0
#endif
#if !defined(DXC_COMPILER_CLANG)
#define DXC_COMPILER_CLANG 0
#endif
#if !defined(DXC_OS_WINDOWS)
#define DXC_OS_WINDOWS 0
#endif
#if !defined(DXC_OS_LINUX)
#define DXC_OS_LINUX 0
#endif
#if !defined(DXC_OS_MAC)
#define DXC_OS_MAC 0
#endif
#if !defined(DXC_LANG_CPP)
#define DXC_LANG_CPP 0
#endif
#if !defined(DXC_LANG_C)
#define DXC_LANG_C 0
#endif

////////////////////////////////
//~ mwalky: Macros

//- mwalky: Linking Keywords

#if DXC_LANG_CPP
#define dxc_no_name_mangle extern "C"
#else
#define dxc_no_name_mangle
#endif

#if DXC_OS_WINDOWS
#define dxc_exported dxc_no_name_mangle __declspec(dllexport)
#else
#define dxc_exported dxc_no_name_mangle
#endif

#if DXC_OS_WINDOWS
#define dxc_imported dxc_no_name_mangle __declspec(dllimport)
#else
#define dxc_imported dxc_no_name_mangle
#endif

//- mwalky: Keywords

#define dxc_global static
#define dxc_internal static

////////////////////////////////
//~ mwalky: Inlined `dxcapi.h`

// NOTE(mwalky): This library has been modified for _dxc_ codebase.

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// dxcapi.h                                                                  //
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
// This file is distributed under the University of Illinois Open Source     //
// License. See LICENSE.TXT for details.                                     //
//                                                                           //
// Provides declarations for the DirectX Compiler API entry point.           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#ifndef __DXC_API__
#define __DXC_API__

#ifdef _WIN32
#ifndef DXC_API_IMPORT
#define DXC_API_IMPORT __declspec(dllimport)
#endif
#else
#ifndef DXC_API_IMPORT
#define DXC_API_IMPORT __attribute__ ((visibility ("default")))
#endif
#endif

#ifdef _WIN32

#ifndef CROSS_PLATFORM_UUIDOF
// Warning: This macro exists in WinAdapter.h as well
#define CROSS_PLATFORM_UUIDOF(interface, spec)                                 \
  struct __declspec(uuid(spec)) interface;
#endif

#else

#include <dlfcn.h>
#include "WinAdapter.h"
#endif

//~ mwalky: _dxc_ Modification: `ifdef`d `IMalloc`

#if DXC_LANG_C
typedef struct IMalloc IMalloc;
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
struct IMalloc;

//~ mwalky: _dxc_ Modification: `typedef`d `IDxcIncludeHandler`

#if DXC_LANG_C
typedef struct IDxcIncludeHandler IDxcIncludeHandler;
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
struct IDxcIncludeHandler;

typedef HRESULT (__stdcall *DxcCreateInstanceProc)(
    _In_ REFCLSID   rclsid,
    _In_ REFIID     riid,
    _Out_ LPVOID*   ppv
);

typedef HRESULT(__stdcall *DxcCreateInstance2Proc)(
  _In_ IMalloc    *pMalloc,
  _In_ REFCLSID   rclsid,
  _In_ REFIID     riid,
  _Out_ LPVOID*   ppv
  );

/// <summary>
/// Creates a single uninitialized object of the class associated with a specified CLSID.
/// </summary>
/// <param name="rclsid">
/// The CLSID associated with the data and code that will be used to create the object.
/// </param>
/// <param name="riid">
/// A reference to the identifier of the interface to be used to communicate
/// with the object.
/// </param>
/// <param name="ppv">
/// Address of pointer variable that receives the interface pointer requested
/// in riid. Upon successful return, *ppv contains the requested interface
/// pointer. Upon failure, *ppv contains NULL.</param>
/// <remarks>
/// While this function is similar to CoCreateInstance, there is no COM involvement.
/// </remarks>

//~ mwalky: _dxc_ Modification: `ifdef`d `extern "C"`

#if DXC_LANG_CPP
extern "C"
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
DXC_API_IMPORT HRESULT __stdcall DxcCreateInstance(
  _In_ REFCLSID   rclsid,
  _In_ REFIID     riid,
  _Out_ LPVOID*   ppv
  );

//~ mwalky: _dxc_ Modification: `ifdef`d `extern "C"`

#if DXC_LANG_CPP
extern "C"
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
DXC_API_IMPORT HRESULT __stdcall DxcCreateInstance2(
  _In_ IMalloc    *pMalloc,
  _In_ REFCLSID   rclsid,
  _In_ REFIID     riid,
  _Out_ LPVOID*   ppv
);

// For convenience, equivalent definitions to CP_UTF8 and CP_UTF16.
#define DXC_CP_UTF8 65001
#define DXC_CP_UTF16 1200
#define DXC_CP_UTF32 12000
// Use DXC_CP_ACP for: Binary;  ANSI Text;  Autodetect UTF with BOM
#define DXC_CP_ACP 0

#ifdef _WIN32
#define DXC_CP_WIDE DXC_CP_UTF16
#else
#define DXC_CP_WIDE DXC_CP_UTF32
#endif

// This flag indicates that the shader hash was computed taking into account source information (-Zss)
#define DXC_HASHFLAG_INCLUDES_SOURCE  1

// Hash digest type for ShaderHash
typedef struct DxcShaderHash {
  UINT32 Flags; // DXC_HASHFLAG_*
  BYTE HashDigest[16];
} DxcShaderHash;

#define DXC_FOURCC(ch0, ch1, ch2, ch3) (                     \
  (UINT32)(UINT8)(ch0)        | (UINT32)(UINT8)(ch1) << 8  | \
  (UINT32)(UINT8)(ch2) << 16  | (UINT32)(UINT8)(ch3) << 24   \
  )
#define DXC_PART_PDB                      DXC_FOURCC('I', 'L', 'D', 'B')
#define DXC_PART_PDB_NAME                 DXC_FOURCC('I', 'L', 'D', 'N')
#define DXC_PART_PRIVATE_DATA             DXC_FOURCC('P', 'R', 'I', 'V')
#define DXC_PART_ROOT_SIGNATURE           DXC_FOURCC('R', 'T', 'S', '0')
#define DXC_PART_DXIL                     DXC_FOURCC('D', 'X', 'I', 'L')
#define DXC_PART_REFLECTION_DATA          DXC_FOURCC('S', 'T', 'A', 'T')
#define DXC_PART_SHADER_HASH              DXC_FOURCC('H', 'A', 'S', 'H')
#define DXC_PART_INPUT_SIGNATURE          DXC_FOURCC('I', 'S', 'G', '1')
#define DXC_PART_OUTPUT_SIGNATURE         DXC_FOURCC('O', 'S', 'G', '1')
#define DXC_PART_PATCH_CONSTANT_SIGNATURE DXC_FOURCC('P', 'S', 'G', '1')

// Some option arguments are defined here for continuity with D3DCompile interface
#define DXC_ARG_DEBUG L"-Zi"
#define DXC_ARG_SKIP_VALIDATION L"-Vd"
#define DXC_ARG_SKIP_OPTIMIZATIONS L"-Od"
#define DXC_ARG_PACK_MATRIX_ROW_MAJOR L"-Zpr"
#define DXC_ARG_PACK_MATRIX_COLUMN_MAJOR L"-Zpc"
#define DXC_ARG_AVOID_FLOW_CONTROL L"-Gfa"
#define DXC_ARG_PREFER_FLOW_CONTROL L"-Gfp"
#define DXC_ARG_ENABLE_STRICTNESS L"-Ges"
#define DXC_ARG_ENABLE_BACKWARDS_COMPATIBILITY L"-Gec"
#define DXC_ARG_IEEE_STRICTNESS L"-Gis"
#define DXC_ARG_OPTIMIZATION_LEVEL0 L"-O0"
#define DXC_ARG_OPTIMIZATION_LEVEL1 L"-O1"
#define DXC_ARG_OPTIMIZATION_LEVEL2 L"-O2"
#define DXC_ARG_OPTIMIZATION_LEVEL3 L"-O3"
#define DXC_ARG_WARNINGS_ARE_ERRORS L"-WX"
#define DXC_ARG_RESOURCES_MAY_ALIAS L"-res_may_alias"
#define DXC_ARG_ALL_RESOURCES_BOUND L"-all_resources_bound"
#define DXC_ARG_DEBUG_NAME_FOR_SOURCE L"-Zss"
#define DXC_ARG_DEBUG_NAME_FOR_BINARY L"-Zsb"

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

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcBlobEncoding, "7241d424-2646-4191-97c0-98e96e42fc68")
struct IDxcBlobEncoding : public IDxcBlob {
public:
  virtual HRESULT GetEncoding(_Out_ BOOL *pKnown,
                                                _Out_ UINT32 *pCodePage) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Notes on IDxcBlobWide and IDxcBlobUtf8
// These guarantee null-terminated text and eithre utf8 or the native wide char encoding.
// GetBufferSize() will return the size in bytes, including null-terminator
// GetStringLength() will return the length in characters, excluding the null-terminator
// Name strings will use IDxcBlobWide, while other string output blobs,
// such as errors/warnings, preprocessed HLSL, or other text will be based
// on the -encoding option.

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// The API will use this interface for output name strings
CROSS_PLATFORM_UUIDOF(IDxcBlobWide, "A3F84EAB-0FAA-497E-A39C-EE6ED60B2D84")
struct IDxcBlobWide : public IDxcBlobEncoding {
public:
  virtual LPCWSTR GetStringPointer(void) = 0;
  virtual SIZE_T GetStringLength(void) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcBlobUtf8, "3DA636C9-BA71-4024-A301-30CBF125305B")
struct IDxcBlobUtf8 : public IDxcBlobEncoding {
public:
  virtual LPCSTR GetStringPointer(void) = 0;
  virtual SIZE_T GetStringLength(void) = 0;
};

// Define legacy name IDxcBlobUtf16 as IDxcBlobWide for Win32
#ifdef _WIN32
typedef IDxcBlobWide IDxcBlobUtf16;
#endif

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcIncludeHandler, "7f61fc7d-950d-467f-b3e3-3c02fb49187c")
struct IDxcIncludeHandler : public IUnknown {
  virtual HRESULT LoadSource(
    _In_z_ LPCWSTR pFilename,                                 // Candidate filename.
    _COM_Outptr_result_maybenull_ IDxcBlob **ppIncludeSource  // Resultant source object for included file, nullptr if not found.
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//~ mwalky: _dxc_ Modification: `typedef`d `DxcBuffer`

#if DXC_LANG_C
typedef struct DxcBuffer DxcBuffer;
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Structure for supplying bytes or text input to Dxc APIs.
// Use Encoding = 0 for non-text bytes, ANSI text, or unknown with BOM.
typedef struct DxcBuffer {
  LPCVOID Ptr;
  SIZE_T Size;
  UINT Encoding;
} DxcText;

//~ mwalky: _dxc_ Modification: `typedef`d `DxcDefine`

#if DXC_LANG_C
typedef struct DxcDefine DxcDefine;
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
struct DxcDefine {
  LPCWSTR Name;
  _Maybenull_ LPCWSTR Value;
};

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcCompilerArgs, "73EFFE2A-70DC-45F8-9690-EFF64C02429D")
struct IDxcCompilerArgs : public IUnknown {
  // Pass GetArguments() and GetCount() to Compile
  virtual LPCWSTR* GetArguments() = 0;
  virtual UINT32 GetCount() = 0;

  // Add additional arguments or defines here, if desired.
  virtual HRESULT AddArguments(
    _In_opt_count_(argCount) LPCWSTR *pArguments,       // Array of pointers to arguments to add
    _In_ UINT32 argCount                                // Number of arguments to add
  ) = 0;
  virtual HRESULT AddArgumentsUTF8(
    _In_opt_count_(argCount)LPCSTR *pArguments,         // Array of pointers to UTF-8 arguments to add
    _In_ UINT32 argCount                                // Number of arguments to add
  ) = 0;
  virtual HRESULT AddDefines(
      _In_count_(defineCount) const DxcDefine *pDefines, // Array of defines
      _In_ UINT32 defineCount                            // Number of defines
  ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//////////////////////////
// Legacy Interfaces
/////////////////////////

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// NOTE: IDxcUtils replaces IDxcLibrary
CROSS_PLATFORM_UUIDOF(IDxcLibrary, "e5204dc7-d18c-4c3c-bdfb-851673980fe7")
struct IDxcLibrary : public IUnknown {
  virtual HRESULT SetMalloc(_In_opt_ IMalloc *pMalloc) = 0;
  virtual HRESULT CreateBlobFromBlob(
    _In_ IDxcBlob *pBlob, UINT32 offset, UINT32 length, _COM_Outptr_ IDxcBlob **ppResult) = 0;
  virtual HRESULT CreateBlobFromFile(
    _In_z_ LPCWSTR pFileName, _In_opt_ UINT32* codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;
  virtual HRESULT CreateBlobWithEncodingFromPinned(
    _In_bytecount_(size) LPCVOID pText, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;
  virtual HRESULT CreateBlobWithEncodingOnHeapCopy(
    _In_bytecount_(size) LPCVOID pText, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;
  virtual HRESULT CreateBlobWithEncodingOnMalloc(
    _In_bytecount_(size) LPCVOID pText, IMalloc *pIMalloc, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;
  virtual HRESULT CreateIncludeHandler(
    _COM_Outptr_ IDxcIncludeHandler **ppResult) = 0;
  virtual HRESULT CreateStreamFromBlobReadOnly(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IStream **ppStream) = 0;
  virtual HRESULT GetBlobAsUtf8(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

  // Renamed from GetBlobAsUtf16 to GetBlobAsWide
  virtual HRESULT GetBlobAsWide(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

#ifdef _WIN32
  // Alias to GetBlobAsWide on Win32
  inline HRESULT GetBlobAsUtf16(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) {
    return this->GetBlobAsWide(pBlob, pBlobEncoding);
  }
#endif
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// NOTE: IDxcResult replaces IDxcOperationResult
CROSS_PLATFORM_UUIDOF(IDxcOperationResult, "CEDB484A-D4E9-445A-B991-CA21CA157DC2")
struct IDxcOperationResult : public IUnknown {
  virtual HRESULT GetStatus(_Out_ HRESULT *pStatus) = 0;

  // GetResult returns the main result of the operation.
  // This corresponds to:
  // DXC_OUT_OBJECT - Compile() with shader or library target
  // DXC_OUT_DISASSEMBLY - Disassemble()
  // DXC_OUT_HLSL - Compile() with -P
  // DXC_OUT_ROOT_SIGNATURE - Compile() with rootsig_* target
  virtual HRESULT GetResult(_COM_Outptr_result_maybenull_ IDxcBlob **ppResult) = 0;

  // GetErrorBuffer Corresponds to DXC_OUT_ERRORS.
  virtual HRESULT GetErrorBuffer(_COM_Outptr_result_maybenull_ IDxcBlobEncoding **ppErrors) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// NOTE: IDxcCompiler3 replaces IDxcCompiler and IDxcCompiler2
CROSS_PLATFORM_UUIDOF(IDxcCompiler, "8c210bf3-011f-4422-8d70-6f9acb8db617")
struct IDxcCompiler : public IUnknown {
  // Compile a single entry point to the target shader model
  virtual HRESULT Compile(
    _In_ IDxcBlob *pSource,                       // Source text to compile
    _In_opt_z_ LPCWSTR pSourceName,               // Optional file name for pSource. Used in errors and include handlers.
    _In_opt_z_ LPCWSTR pEntryPoint,               // entry point name
    _In_z_ LPCWSTR pTargetProfile,                // shader profile to compile
    _In_opt_count_(argCount) LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,                         // Number of arguments
    _In_count_(defineCount)
      const DxcDefine *pDefines,                  // Array of defines
    _In_ UINT32 defineCount,                      // Number of defines
    _In_opt_ IDxcIncludeHandler *pIncludeHandler, // user-provided interface to handle #include directives (optional)
    _COM_Outptr_ IDxcOperationResult **ppResult   // Compiler output status, buffer, and errors
  ) = 0;

  // Preprocess source text
  virtual HRESULT Preprocess(
    _In_ IDxcBlob *pSource,                       // Source text to preprocess
    _In_opt_z_ LPCWSTR pSourceName,               // Optional file name for pSource. Used in errors and include handlers.
    _In_opt_count_(argCount) LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,                         // Number of arguments
    _In_count_(defineCount)
      const DxcDefine *pDefines,                  // Array of defines
    _In_ UINT32 defineCount,                      // Number of defines
    _In_opt_ IDxcIncludeHandler *pIncludeHandler, // user-provided interface to handle #include directives (optional)
    _COM_Outptr_ IDxcOperationResult **ppResult   // Preprocessor output status, buffer, and errors
  ) = 0;

  // Disassemble a program.
  virtual HRESULT Disassemble(
    _In_ IDxcBlob *pSource,                         // Program to disassemble.
    _COM_Outptr_ IDxcBlobEncoding **ppDisassembly   // Disassembly text.
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// NOTE: IDxcCompiler3 replaces IDxcCompiler and IDxcCompiler2
CROSS_PLATFORM_UUIDOF(IDxcCompiler2, "A005A9D9-B8BB-4594-B5C9-0E633BEC4D37")
struct IDxcCompiler2 : public IDxcCompiler {
  // Compile a single entry point to the target shader model with debug information.
  virtual HRESULT CompileWithDebug(
    _In_ IDxcBlob *pSource,                       // Source text to compile
    _In_opt_z_ LPCWSTR pSourceName,               // Optional file name for pSource. Used in errors and include handlers.
    _In_opt_z_ LPCWSTR pEntryPoint,               // Entry point name
    _In_z_ LPCWSTR pTargetProfile,                // Shader profile to compile
    _In_opt_count_(argCount) LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,                         // Number of arguments
    _In_count_(defineCount)
      const DxcDefine *pDefines,                  // Array of defines
    _In_ UINT32 defineCount,                      // Number of defines
    _In_opt_ IDxcIncludeHandler *pIncludeHandler, // user-provided interface to handle #include directives (optional)
    _COM_Outptr_ IDxcOperationResult **ppResult,  // Compiler output status, buffer, and errors
    _Outptr_opt_result_z_ LPWSTR *ppDebugBlobName,// Suggested file name for debug blob. (Must be CoTaskMemFree()'d!)
    _COM_Outptr_opt_ IDxcBlob **ppDebugBlob       // Debug blob
  ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcLinker, "F1B5BE2A-62DD-4327-A1C2-42AC1E1E78E6")
struct IDxcLinker : public IUnknown {
public:
  // Register a library with name to ref it later.
  virtual HRESULT RegisterLibrary(
    _In_opt_ LPCWSTR pLibName,          // Name of the library.
    _In_ IDxcBlob *pLib                 // Library blob.
  ) = 0;

  // Links the shader and produces a shader blob that the Direct3D runtime can
  // use.
  virtual HRESULT Link(
    _In_opt_ LPCWSTR pEntryName,        // Entry point name
    _In_ LPCWSTR pTargetProfile,        // shader profile to link
    _In_count_(libCount)
        const LPCWSTR *pLibNames,       // Array of library names to link
    _In_ UINT32 libCount,               // Number of libraries to link
    _In_opt_count_(argCount) const LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,               // Number of arguments
    _COM_Outptr_
        IDxcOperationResult **ppResult  // Linker output status, buffer, and errors
  ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/////////////////////////
// Latest interfaces. Please use these
////////////////////////

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// NOTE: IDxcUtils replaces IDxcLibrary
CROSS_PLATFORM_UUIDOF(IDxcUtils, "4605C4CB-2019-492A-ADA4-65F20BB7D67F")
struct IDxcUtils : public IUnknown {
  // Create a sub-blob that holds a reference to the outer blob and points to its memory.
  virtual HRESULT CreateBlobFromBlob(
    _In_ IDxcBlob *pBlob, UINT32 offset, UINT32 length, _COM_Outptr_ IDxcBlob **ppResult) = 0;

  // For codePage, use 0 (or DXC_CP_ACP) for raw binary or ANSI code page

  // Creates a blob referencing existing memory, with no copy.
  // User must manage the memory lifetime separately.
  // (was: CreateBlobWithEncodingFromPinned)
  virtual HRESULT CreateBlobFromPinned(
    _In_bytecount_(size) LPCVOID pData, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

  // Create blob, taking ownership of memory allocated with supplied allocator.
  // (was: CreateBlobWithEncodingOnMalloc)
  virtual HRESULT MoveToBlob(
    _In_bytecount_(size) LPCVOID pData, IMalloc *pIMalloc, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

  ////
  // New blobs and copied contents are allocated with the current allocator

  // Copy blob contents to memory owned by the new blob.
  // (was: CreateBlobWithEncodingOnHeapCopy)
  virtual HRESULT CreateBlob(
    _In_bytecount_(size) LPCVOID pData, UINT32 size, UINT32 codePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

  // (was: CreateBlobFromFile)
  virtual HRESULT LoadFile(
    _In_z_ LPCWSTR pFileName, _In_opt_ UINT32* pCodePage,
    _COM_Outptr_ IDxcBlobEncoding **pBlobEncoding) = 0;

  virtual HRESULT CreateReadOnlyStreamFromBlob(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IStream **ppStream) = 0;

  // Create default file-based include handler
  virtual HRESULT CreateDefaultIncludeHandler(
    _COM_Outptr_ IDxcIncludeHandler **ppResult) = 0;

  // Convert or return matching encoded text blobs
  virtual HRESULT GetBlobAsUtf8(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobUtf8 **pBlobEncoding) = 0;

  // Renamed from GetBlobAsUtf16 to GetBlobAsWide
  virtual HRESULT GetBlobAsWide(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobWide **pBlobEncoding) = 0;

#ifdef _WIN32
  // Alias to GetBlobAsWide on Win32
  inline HRESULT GetBlobAsUtf16(
    _In_ IDxcBlob *pBlob, _COM_Outptr_ IDxcBlobWide **pBlobEncoding) {
    return this->GetBlobAsWide(pBlob, pBlobEncoding);
  }
#endif

  virtual HRESULT GetDxilContainerPart(
    _In_ const DxcBuffer *pShader,
    _In_ UINT32 DxcPart,
    _Outptr_result_nullonfailure_ void **ppPartData,
    _Out_ UINT32 *pPartSizeInBytes) = 0;

  // Create reflection interface from serialized Dxil container, or DXC_PART_REFLECTION_DATA.
  // TBD: Require part header for RDAT?  (leaning towards yes)
  virtual HRESULT CreateReflection(
    _In_ const DxcBuffer *pData, REFIID iid, void **ppvReflection) = 0;

  virtual HRESULT BuildArguments(
    _In_opt_z_ LPCWSTR pSourceName,               // Optional file name for pSource. Used in errors and include handlers.
    _In_opt_z_ LPCWSTR pEntryPoint,               // Entry point name. (-E)
    _In_z_ LPCWSTR pTargetProfile,                // Shader profile to compile. (-T)
    _In_opt_count_(argCount) LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,                         // Number of arguments
    _In_count_(defineCount)
      const DxcDefine *pDefines,                  // Array of defines
    _In_ UINT32 defineCount,                      // Number of defines
    _COM_Outptr_ IDxcCompilerArgs **ppArgs        // Arguments you can use with Compile() method
  ) = 0;

  // Takes the shader PDB and returns the hash and the container inside it
  virtual HRESULT GetPDBContents(
    _In_ IDxcBlob *pPDBBlob, _COM_Outptr_ IDxcBlob **ppHash, _COM_Outptr_ IDxcBlob **ppContainer) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// For use with IDxcResult::[Has|Get]Output dxcOutKind argument
// Note: text outputs returned from version 2 APIs are UTF-8 or UTF-16 based on -encoding option
typedef enum DXC_OUT_KIND {
  DXC_OUT_NONE = 0,
  DXC_OUT_OBJECT = 1,         // IDxcBlob - Shader or library object
  DXC_OUT_ERRORS = 2,         // IDxcBlobUtf8 or IDxcBlobWide
  DXC_OUT_PDB = 3,            // IDxcBlob
  DXC_OUT_SHADER_HASH = 4,    // IDxcBlob - DxcShaderHash of shader or shader with source info (-Zsb/-Zss)
  DXC_OUT_DISASSEMBLY = 5,    // IDxcBlobUtf8 or IDxcBlobWide - from Disassemble
  DXC_OUT_HLSL = 6,           // IDxcBlobUtf8 or IDxcBlobWide - from Preprocessor or Rewriter
  DXC_OUT_TEXT = 7,           // IDxcBlobUtf8 or IDxcBlobWide - other text, such as -ast-dump or -Odump
  DXC_OUT_REFLECTION = 8,     // IDxcBlob - RDAT part with reflection data
  DXC_OUT_ROOT_SIGNATURE = 9, // IDxcBlob - Serialized root signature output
  DXC_OUT_EXTRA_OUTPUTS  = 10,// IDxcExtraResults - Extra outputs
  DXC_OUT_REMARKS = 11,       // IDxcBlobUtf8 or IDxcBlobWide - text directed at stdout
  DXC_OUT_TIME_REPORT = 12,   // IDxcBlobUtf8 or IDxcBlobWide - text directed at stdout
  DXC_OUT_TIME_TRACE = 13,   // IDxcBlobUtf8 or IDxcBlobWide - text directed at stdout

  DXC_OUT_LAST = DXC_OUT_TIME_TRACE, // Last value for a counter

  DXC_OUT_NUM_ENUMS,
  DXC_OUT_FORCE_DWORD = 0xFFFFFFFF
} DXC_OUT_KIND;

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: commented out `static_assert` below

//static_assert(DXC_OUT_NUM_ENUMS == DXC_OUT_LAST + 1,
//              "DXC_OUT_* Enum added and last value not updated.");

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcResult, "58346CDA-DDE7-4497-9461-6F87AF5E0659")
struct IDxcResult : public IDxcOperationResult {
  virtual BOOL HasOutput(_In_ DXC_OUT_KIND dxcOutKind) = 0;
  virtual HRESULT GetOutput(_In_ DXC_OUT_KIND dxcOutKind,
    _In_ REFIID iid, _COM_Outptr_opt_result_maybenull_ void **ppvObject,
    _COM_Outptr_ IDxcBlobWide **ppOutputName) = 0;

  virtual UINT32 GetNumOutputs() = 0;
  virtual DXC_OUT_KIND GetOutputByIndex(UINT32 Index) = 0;
  virtual DXC_OUT_KIND PrimaryOutput() = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Special names for extra output that should get written to specific streams
#define DXC_EXTRA_OUTPUT_NAME_STDOUT L"*stdout*"
#define DXC_EXTRA_OUTPUT_NAME_STDERR L"*stderr*"

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcExtraOutputs, "319b37a2-a5c2-494a-a5de-4801b2faf989")
struct IDxcExtraOutputs : public IUnknown {

  virtual UINT32 GetOutputCount() = 0;
  virtual HRESULT GetOutput(_In_ UINT32 uIndex,
    _In_ REFIID iid, _COM_Outptr_opt_result_maybenull_ void **ppvObject,
    _COM_Outptr_opt_result_maybenull_ IDxcBlobWide **ppOutputType,
    _COM_Outptr_opt_result_maybenull_ IDxcBlobWide **ppOutputName) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcCompiler3, "228B4687-5A6A-4730-900C-9702B2203F54")
struct IDxcCompiler3 : public IUnknown {
  // Compile a single entry point to the target shader model,
  // Compile a library to a library target (-T lib_*),
  // Compile a root signature (-T rootsig_*), or
  // Preprocess HLSL source (-P)
  virtual HRESULT Compile(
    _In_ const DxcBuffer *pSource,                // Source text to compile
    _In_opt_count_(argCount) LPCWSTR *pArguments, // Array of pointers to arguments
    _In_ UINT32 argCount,                         // Number of arguments
    _In_opt_ IDxcIncludeHandler *pIncludeHandler, // user-provided interface to handle #include directives (optional)
    _In_ REFIID riid, _Out_ LPVOID *ppResult      // IDxcResult: status, buffer, and errors
  ) = 0;

  // Disassemble a program.
  virtual HRESULT Disassemble(
    _In_ const DxcBuffer *pObject,                // Program to disassemble: dxil container or bitcode.
    _In_ REFIID riid, _Out_ LPVOID *ppResult      // IDxcResult: status, disassembly text, and errors
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

static const UINT32 DxcValidatorFlags_Default = 0;
static const UINT32 DxcValidatorFlags_InPlaceEdit = 1;  // Validator is allowed to update shader blob in-place.
static const UINT32 DxcValidatorFlags_RootSignatureOnly = 2;
static const UINT32 DxcValidatorFlags_ModuleOnly = 4;
static const UINT32 DxcValidatorFlags_ValidMask = 0x7;

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcValidator, "A6E82BD2-1FD7-4826-9811-2857E797F49A")
struct IDxcValidator : public IUnknown {
  // Validate a shader.
  virtual HRESULT Validate(
    _In_ IDxcBlob *pShader,                       // Shader to validate.
    _In_ UINT32 Flags,                            // Validation flags.
    _COM_Outptr_ IDxcOperationResult **ppResult   // Validation output status, buffer, and errors
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcValidator2, "458e1fd1-b1b2-4750-a6e1-9c10f03bed92")
struct IDxcValidator2 : public IDxcValidator {
  // Validate a shader.
  virtual HRESULT ValidateWithDebug(
    _In_ IDxcBlob *pShader,                       // Shader to validate.
    _In_ UINT32 Flags,                            // Validation flags.
    _In_opt_ DxcBuffer *pOptDebugBitcode,         // Optional debug module bitcode to provide line numbers
    _COM_Outptr_ IDxcOperationResult **ppResult   // Validation output status, buffer, and errors
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcContainerBuilder, "334b1f50-2292-4b35-99a1-25588d8c17fe")
struct IDxcContainerBuilder : public IUnknown {
  virtual HRESULT Load(_In_ IDxcBlob *pDxilContainerHeader) = 0;                // Loads DxilContainer to the builder
  virtual HRESULT AddPart(_In_ UINT32 fourCC, _In_ IDxcBlob *pSource) = 0;      // Part to add to the container
  virtual HRESULT RemovePart(_In_ UINT32 fourCC) = 0;                           // Remove the part with fourCC
  virtual HRESULT SerializeContainer(_Out_ IDxcOperationResult **ppResult) = 0; // Builds a container of the given container builder state
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcAssembler, "091f7a26-1c1f-4948-904b-e6e3a8a771d5")
struct IDxcAssembler : public IUnknown {
  // Assemble dxil in ll or llvm bitcode to DXIL container.
  virtual HRESULT AssembleToContainer(
    _In_ IDxcBlob *pShader,                       // Shader to assemble.
    _COM_Outptr_ IDxcOperationResult **ppResult   // Assembly output status, buffer, and errors
    ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcContainerReflection, "d2c21b26-8350-4bdc-976a-331ce6f4c54c")
struct IDxcContainerReflection : public IUnknown {
  virtual HRESULT Load(_In_ IDxcBlob *pContainer) = 0; // Container to load.
  virtual HRESULT GetPartCount(_Out_ UINT32 *pResult) = 0;
  virtual HRESULT GetPartKind(UINT32 idx, _Out_ UINT32 *pResult) = 0;
  virtual HRESULT GetPartContent(UINT32 idx, _COM_Outptr_ IDxcBlob **ppResult) = 0;
  virtual HRESULT FindFirstPartKind(UINT32 kind, _Out_ UINT32 *pResult) = 0;
  virtual HRESULT GetPartReflection(UINT32 idx, REFIID iid, void **ppvObject) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcOptimizerPass, "AE2CD79F-CC22-453F-9B6B-B124E7A5204C")
struct IDxcOptimizerPass : public IUnknown {
  virtual HRESULT GetOptionName(_COM_Outptr_ LPWSTR *ppResult) = 0;
  virtual HRESULT GetDescription(_COM_Outptr_ LPWSTR *ppResult) = 0;
  virtual HRESULT GetOptionArgCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetOptionArgName(UINT32 argIndex, _COM_Outptr_ LPWSTR *ppResult) = 0;
  virtual HRESULT GetOptionArgDescription(UINT32 argIndex, _COM_Outptr_ LPWSTR *ppResult) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcOptimizer, "25740E2E-9CBA-401B-9119-4FB42F39F270")
struct IDxcOptimizer : public IUnknown {
  virtual HRESULT GetAvailablePassCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetAvailablePass(UINT32 index, _COM_Outptr_ IDxcOptimizerPass** ppResult) = 0;
  virtual HRESULT RunOptimizer(IDxcBlob *pBlob,
    _In_count_(optionCount) LPCWSTR *ppOptions, UINT32 optionCount,
    _COM_Outptr_ IDxcBlob **pOutputModule,
    _COM_Outptr_opt_ IDxcBlobEncoding **ppOutputText) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

static const UINT32 DxcVersionInfoFlags_None = 0;
static const UINT32 DxcVersionInfoFlags_Debug = 1; // Matches VS_FF_DEBUG
static const UINT32 DxcVersionInfoFlags_Internal = 2; // Internal Validator (non-signing)

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcVersionInfo, "b04f5b50-2059-4f12-a8ff-a1e0cde1cc7e")
struct IDxcVersionInfo : public IUnknown {
  virtual HRESULT GetVersion(_Out_ UINT32 *pMajor, _Out_ UINT32 *pMinor) = 0;
  virtual HRESULT GetFlags(_Out_ UINT32 *pFlags) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcVersionInfo2, "fb6904c4-42f0-4b62-9c46-983af7da7c83")
struct IDxcVersionInfo2 : public IDxcVersionInfo {
  virtual HRESULT GetCommitInfo(
    _Out_ UINT32 *pCommitCount,           // The total number commits.
    _Outptr_result_z_ char **pCommitHash  // The SHA of the latest commit. (Must be CoTaskMemFree()'d!)
  ) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcVersionInfo3, "5e13e843-9d25-473c-9ad2-03b2d0b44b1e")
struct IDxcVersionInfo3 : public IUnknown {
  virtual HRESULT GetCustomVersionString(
    _Outptr_result_z_ char **pVersionString // Custom version string for compiler. (Must be CoTaskMemFree()'d!)
  ) = 0;
};

#endif // DXC_LANG_CPP

//~ mwalky: _dxc_ Modification: `typedef`d `DxcArgPair`

#if DXC_LANG_C
typedef struct DxcArgPair DxcArgPair;
#endif // DXC_LANG_C

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
struct DxcArgPair {
  const WCHAR *pName;
  const WCHAR *pValue;
};

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcPdbUtils, "E6C9647E-9D6A-4C3B-B94C-524B5A6C343D")
struct IDxcPdbUtils : public IUnknown {
  virtual HRESULT Load(_In_ IDxcBlob *pPdbOrDxil) = 0;

  virtual HRESULT GetSourceCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetSource(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobEncoding **ppResult) = 0;
  virtual HRESULT GetSourceName(_In_ UINT32 uIndex, _Outptr_result_z_ BSTR *pResult) = 0;

  virtual HRESULT GetFlagCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetFlag(_In_ UINT32 uIndex, _Outptr_result_z_ BSTR *pResult) = 0;

  virtual HRESULT GetArgCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetArg(_In_ UINT32 uIndex, _Outptr_result_z_ BSTR *pResult) = 0;

  virtual HRESULT GetArgPairCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetArgPair(_In_ UINT32 uIndex, _Outptr_result_z_ BSTR *pName, _Outptr_result_z_ BSTR *pValue) = 0;

  virtual HRESULT GetDefineCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetDefine(_In_ UINT32 uIndex, _Outptr_result_z_ BSTR *pResult) = 0;

  virtual HRESULT GetTargetProfile(_Outptr_result_z_ BSTR *pResult) = 0;
  virtual HRESULT GetEntryPoint(_Outptr_result_z_ BSTR *pResult) = 0;
  virtual HRESULT GetMainFileName(_Outptr_result_z_ BSTR *pResult) = 0;

  virtual HRESULT GetHash(_COM_Outptr_ IDxcBlob **ppResult) = 0;
  virtual HRESULT GetName(_Outptr_result_z_ BSTR *pResult) = 0;

  virtual BOOL IsFullPDB() = 0;
  virtual HRESULT GetFullPDB(_COM_Outptr_ IDxcBlob **ppFullPDB) = 0;

  virtual HRESULT GetVersionInfo(_COM_Outptr_ IDxcVersionInfo **ppVersionInfo) = 0;

  virtual HRESULT SetCompiler(_In_ IDxcCompiler3 *pCompiler) = 0;
  virtual HRESULT CompileForFullPDB(_COM_Outptr_ IDxcResult **ppResult) = 0;
  virtual HRESULT OverrideArgs(_In_ DxcArgPair *pArgPairs, UINT32 uNumArgPairs) = 0;
  virtual HRESULT OverrideRootSignature(_In_ const WCHAR *pRootSignature) = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

CROSS_PLATFORM_UUIDOF(IDxcPdbUtils2, "4315D938-F369-4F93-95A2-252017CC3807")
struct IDxcPdbUtils2 : public IUnknown {
  virtual HRESULT Load(_In_ IDxcBlob *pPdbOrDxil) = 0;

  virtual HRESULT GetSourceCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetSource(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobEncoding **ppResult) = 0;
  virtual HRESULT GetSourceName(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetLibraryPDBCount(UINT32 *pCount) = 0;
  virtual HRESULT GetLibraryPDB(_In_ UINT32 uIndex, _COM_Outptr_ IDxcPdbUtils2 **ppOutPdbUtils, _COM_Outptr_opt_result_maybenull_ IDxcBlobWide **ppLibraryName) = 0;

  virtual HRESULT GetFlagCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetFlag(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetArgCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetArg(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetArgPairCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetArgPair(_In_ UINT32 uIndex, _COM_Outptr_result_maybenull_ IDxcBlobWide **ppName, _COM_Outptr_result_maybenull_ IDxcBlobWide **ppValue) = 0;

  virtual HRESULT GetDefineCount(_Out_ UINT32 *pCount) = 0;
  virtual HRESULT GetDefine(_In_ UINT32 uIndex, _COM_Outptr_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetTargetProfile(_COM_Outptr_result_maybenull_ IDxcBlobWide **ppResult) = 0;
  virtual HRESULT GetEntryPoint(_COM_Outptr_result_maybenull_ IDxcBlobWide **ppResult) = 0;
  virtual HRESULT GetMainFileName(_COM_Outptr_result_maybenull_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetHash(_COM_Outptr_result_maybenull_ IDxcBlob **ppResult) = 0;
  virtual HRESULT GetName(_COM_Outptr_result_maybenull_ IDxcBlobWide **ppResult) = 0;

  virtual HRESULT GetVersionInfo(_COM_Outptr_result_maybenull_ IDxcVersionInfo **ppVersionInfo) = 0;

  virtual HRESULT GetCustomToolchainID(_Out_ UINT32 *pID) = 0;
  virtual HRESULT GetCustomToolchainData(_COM_Outptr_result_maybenull_ IDxcBlob **ppBlob) = 0;

  virtual HRESULT GetWholeDxil(_COM_Outptr_result_maybenull_ IDxcBlob **ppResult) = 0;

  virtual BOOL IsFullPDB() = 0;
  virtual BOOL IsPDBRef() = 0;
};

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//~ mwalky: _dxc_ Modification: `ifdef`d C++-specific code

#if DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Note: __declspec(selectany) requires 'extern'
// On Linux __declspec(selectany) is removed and using 'extern' results in link error.
#ifdef _MSC_VER
#define CLSID_SCOPE __declspec(selectany) extern
#else
#define CLSID_SCOPE
#endif

CLSID_SCOPE const CLSID CLSID_DxcCompiler = {
    0x73e22d93,
    0xe6ce,
    0x47f3,
    {0xb5, 0xbf, 0xf0, 0x66, 0x4f, 0x39, 0xc1, 0xb0}};

// {EF6A8087-B0EA-4D56-9E45-D07E1A8B7806}
CLSID_SCOPE const GUID CLSID_DxcLinker = {
    0xef6a8087,
    0xb0ea,
    0x4d56,
    {0x9e, 0x45, 0xd0, 0x7e, 0x1a, 0x8b, 0x78, 0x6}};

// {CD1F6B73-2AB0-484D-8EDC-EBE7A43CA09F}
CLSID_SCOPE const CLSID CLSID_DxcDiaDataSource = {
    0xcd1f6b73,
    0x2ab0,
    0x484d,
    {0x8e, 0xdc, 0xeb, 0xe7, 0xa4, 0x3c, 0xa0, 0x9f}};

// {3E56AE82-224D-470F-A1A1-FE3016EE9F9D}
CLSID_SCOPE const CLSID CLSID_DxcCompilerArgs = {
    0x3e56ae82,
    0x224d,
    0x470f,
    {0xa1, 0xa1, 0xfe, 0x30, 0x16, 0xee, 0x9f, 0x9d}};

// {6245D6AF-66E0-48FD-80B4-4D271796748C}
CLSID_SCOPE const GUID CLSID_DxcLibrary = {
    0x6245d6af,
    0x66e0,
    0x48fd,
    {0x80, 0xb4, 0x4d, 0x27, 0x17, 0x96, 0x74, 0x8c}};

CLSID_SCOPE const GUID CLSID_DxcUtils = CLSID_DxcLibrary;

// {8CA3E215-F728-4CF3-8CDD-88AF917587A1}
CLSID_SCOPE const GUID CLSID_DxcValidator = {
    0x8ca3e215,
    0xf728,
    0x4cf3,
    {0x8c, 0xdd, 0x88, 0xaf, 0x91, 0x75, 0x87, 0xa1}};

// {D728DB68-F903-4F80-94CD-DCCF76EC7151}
CLSID_SCOPE const GUID CLSID_DxcAssembler = {
    0xd728db68,
    0xf903,
    0x4f80,
    {0x94, 0xcd, 0xdc, 0xcf, 0x76, 0xec, 0x71, 0x51}};

// {b9f54489-55b8-400c-ba3a-1675e4728b91}
CLSID_SCOPE const GUID CLSID_DxcContainerReflection = {
    0xb9f54489,
    0x55b8,
    0x400c,
    {0xba, 0x3a, 0x16, 0x75, 0xe4, 0x72, 0x8b, 0x91}};

// {AE2CD79F-CC22-453F-9B6B-B124E7A5204C}
CLSID_SCOPE const GUID CLSID_DxcOptimizer = {
    0xae2cd79f,
    0xcc22,
    0x453f,
    {0x9b, 0x6b, 0xb1, 0x24, 0xe7, 0xa5, 0x20, 0x4c}};

// {94134294-411f-4574-b4d0-8741e25240d2}
CLSID_SCOPE const GUID CLSID_DxcContainerBuilder = {
    0x94134294,
    0x411f,
    0x4574,
    {0xb4, 0xd0, 0x87, 0x41, 0xe2, 0x52, 0x40, 0xd2}};

// {54621dfb-f2ce-457e-ae8c-ec355faeec7c}
CLSID_SCOPE const GUID CLSID_DxcPdbUtils = {
    0x54621dfb,
    0xf2ce,
    0x457e,
    {0xae, 0x8c, 0xec, 0x35, 0x5f, 0xae, 0xec, 0x7c}};

#endif

//~ mwalky: _dxc_ Modification: `endif`d C++-specific code

#endif // DXC_LANG_CPP

//~ ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

DEFINE_GUID(IID_IDxcBlob,                 0x8ba5fb08, 0x5195, 0x40e2, 0xac, 0x58, 0x0d, 0x98, 0x9c, 0x3a, 0x01, 0x02);
DEFINE_GUID(IID_IDxcBlobEncoding,         0x7241d424, 0x2646, 0x4191, 0x97, 0xc0, 0x98, 0xe9, 0x6e, 0x42, 0xfc, 0x68);
DEFINE_GUID(IID_IDxcBlobWide,             0xa3f84eab, 0x0faa, 0x497e, 0xa3, 0x9c, 0xee, 0x6e, 0xd6, 0x0b, 0x2d, 0x84);
DEFINE_GUID(IID_IDxcBlobUtf8,             0x3da636c9, 0xba71, 0x4024, 0xa3, 0x01, 0x30, 0xcb, 0xf1, 0x25, 0x30, 0x5b);
DEFINE_GUID(IID_IDxcIncludeHandler,       0x7f61fc7d, 0x950d, 0x467f, 0xb3, 0xe3, 0x3c, 0x02, 0xfb, 0x49, 0x18, 0x7c);
DEFINE_GUID(IID_IDxcCompilerArgs,         0x73effe2a, 0x70dc, 0x45f8, 0x96, 0x90, 0xef, 0xf6, 0x4c, 0x02, 0x42, 0x9d);
DEFINE_GUID(IID_IDxcLibrary,              0xe5204dc7, 0xd18c, 0x4c3c, 0xbd, 0xfb, 0x85, 0x16, 0x73, 0x98, 0x0f, 0xe7);
DEFINE_GUID(IID_IDxcOperationResult,      0xcedb484a, 0xd4e9, 0x445a, 0xb9, 0x91, 0xca, 0x21, 0xca, 0x15, 0x7d, 0xc2);
DEFINE_GUID(IID_IDxcCompiler,             0x8c210bf3, 0x011f, 0x4422, 0x8d, 0x70, 0x6f, 0x9a, 0xcb, 0x8d, 0xb6, 0x17);
DEFINE_GUID(IID_IDxcCompiler2,            0xa005a9d9, 0xb8bb, 0x4594, 0xb5, 0xc9, 0x0e, 0x63, 0x3b, 0xec, 0x4d, 0x37);
DEFINE_GUID(IID_IDxcLinker,               0xf1b5be2a, 0x62dd, 0x4327, 0xa1, 0xc2, 0x42, 0xac, 0x1e, 0x1e, 0x78, 0xe6);
DEFINE_GUID(IID_IDxcUtils,                0x4605c4cb, 0x2019, 0x492a, 0xad, 0xa4, 0x65, 0xf2, 0x0b, 0xb7, 0xd6, 0x7f);
DEFINE_GUID(IID_IDxcResult,               0x58346cda, 0xdde7, 0x4497, 0x94, 0x61, 0x6f, 0x87, 0xaf, 0x5e, 0x06, 0x59);
DEFINE_GUID(IID_IDxcExtraOutputs,         0x319b37a2, 0xa5c2, 0x494a, 0xa5, 0xde, 0x48, 0x01, 0xb2, 0xfa, 0xf9, 0x89);
DEFINE_GUID(IID_IDxcCompiler3,            0x228b4687, 0x5a6a, 0x4730, 0x90, 0x0c, 0x97, 0x02, 0xb2, 0x20, 0x3f, 0x54);
DEFINE_GUID(IID_IDxcValidator,            0xa6e82bd2, 0x1fd7, 0x4826, 0x98, 0x11, 0x28, 0x57, 0xe7, 0x97, 0xf4, 0x9a);
DEFINE_GUID(IID_IDxcValidator2,           0x458e1fd1, 0xb1b2, 0x4750, 0xa6, 0xe1, 0x9c, 0x10, 0xf0, 0x3b, 0xed, 0x92);
DEFINE_GUID(IID_IDxcContainerBuilder,     0x334b1f50, 0x2292, 0x4b35, 0x99, 0xa1, 0x25, 0x58, 0x8d, 0x8c, 0x17, 0xfe);
DEFINE_GUID(IID_IDxcAssembler,            0x091f7a26, 0x1c1f, 0x4948, 0x90, 0x4b, 0xe6, 0xe3, 0xa8, 0xa7, 0x71, 0xd5);
DEFINE_GUID(IID_IDxcContainerReflection,  0xd2c21b26, 0x8350, 0x4bdc, 0x97, 0x6a, 0x33, 0x1c, 0xe6, 0xf4, 0xc5, 0x4c);
DEFINE_GUID(IID_IDxcOptimizerPass,        0xae2cd79f, 0xcc22, 0x453f, 0x9b, 0x6b, 0xb1, 0x24, 0xe7, 0xa5, 0x20, 0x4c);
DEFINE_GUID(IID_IDxcOptimizer,            0x25740e2e, 0x9cba, 0x401b, 0x91, 0x19, 0x4f, 0xb4, 0x2f, 0x39, 0xf2, 0x70);
DEFINE_GUID(IID_IDxcVersionInfo,          0xb04f5b50, 0x2059, 0x4f12, 0xa8, 0xff, 0xa1, 0xe0, 0xcd, 0xe1, 0xcc, 0x7e);
DEFINE_GUID(IID_IDxcVersionInfo2,         0xfb6904c4, 0x42f0, 0x4b62, 0x9c, 0x46, 0x98, 0x3a, 0xf7, 0xda, 0x7c, 0x83);
DEFINE_GUID(IID_IDxcVersionInfo3,         0x5e13e843, 0x9d25, 0x473c, 0x9a, 0xd2, 0x03, 0xb2, 0xd0, 0xb4, 0x4b, 0x1e);
DEFINE_GUID(IID_IDxcPdbUtils,             0xe6c9647e, 0x9d6a, 0x4c3b, 0xb9, 0x4c, 0x52, 0x4b, 0x5a, 0x6c, 0x34, 0x3d);
DEFINE_GUID(IID_IDxcPdbUtils2,            0x4315d938, 0xf369, 0x4f93, 0x95, 0xa2, 0x25, 0x20, 0x17, 0xcc, 0x38, 0x07);

#if DXC_LANG_C

DEFINE_GUID(CLSID_DxcCompiler,            0x73e22d93, 0xe6ce, 0x47f3, 0xb5, 0xbf, 0xf0, 0x66, 0x4f, 0x39, 0xc1, 0xb0);
DEFINE_GUID(CLSID_DxcLinker,              0xef6a8087, 0xb0ea, 0x4d56, 0x9e, 0x45, 0xd0, 0x7e, 0x1a, 0x8b, 0x78, 0x06);
DEFINE_GUID(CLSID_DxcDiaDataSource,       0xcd1f6b73, 0x2ab0, 0x484d, 0x8e, 0xdc, 0xeb, 0xe7, 0xa4, 0x3c, 0xa0, 0x9f);
DEFINE_GUID(CLSID_DxcCompilerArgs,        0x3e56ae82, 0x224d, 0x470f, 0xa1, 0xa1, 0xfe, 0x30, 0x16, 0xee, 0x9f, 0x9d);
DEFINE_GUID(CLSID_DxcLibrary,             0x6245d6af, 0x66e0, 0x48fd, 0x80, 0xb4, 0x4d, 0x27, 0x17, 0x96, 0x74, 0x8c);
DEFINE_GUID(CLSID_DxcUtils,               0x6245d6af, 0x66e0, 0x48fd, 0x80, 0xb4, 0x4d, 0x27, 0x17, 0x96, 0x74, 0x8c);
DEFINE_GUID(CLSID_DxcValidator,           0x8ca3e215, 0xf728, 0x4cf3, 0x8c, 0xdd, 0x88, 0xaf, 0x91, 0x75, 0x87, 0xa1);
DEFINE_GUID(CLSID_DxcAssembler,           0xd728db68, 0xf903, 0x4f80, 0x94, 0xcd, 0xdc, 0xcf, 0x76, 0xec, 0x71, 0x51);
DEFINE_GUID(CLSID_DxcContainerReflection, 0xb9f54489, 0x55b8, 0x400c, 0xba, 0x3a, 0x16, 0x75, 0xe4, 0x72, 0x8b, 0x91);
DEFINE_GUID(CLSID_DxcOptimizer,           0xae2cd79f, 0xcc22, 0x453f, 0x9b, 0x6b, 0xb1, 0x24, 0xe7, 0xa5, 0x20, 0x4c);
DEFINE_GUID(CLSID_DxcContainerBuilder,    0x94134294, 0x411f, 0x4574, 0xb4, 0xd0, 0x87, 0x41, 0xe2, 0x52, 0x40, 0xd2);
DEFINE_GUID(CLSID_DxcPdbUtils,            0x54621dfb, 0xf2ce, 0x457e, 0xae, 0x8c, 0xec, 0x35, 0x5f, 0xae, 0xec, 0x7c);

#endif // DXC_LANG_C


////////////////////////////////
//~ mwalky: Forward declarations

typedef struct IDxcPdbUtils2 IDxcPdbUtils2;

////////////////////////////////
//~ mwalky: Blob Types

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

////////////////////////////////
//~ mwalky: BlobEncoding Types

typedef struct IDxcBlobEncodingVTable IDxcBlobEncodingVTable;
struct IDxcBlobEncodingVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 LPVOID (*GetBufferPointer)(void *pSelf);
 SIZE_T (*GetBufferSize)(void *pSelf);

 HRESULT (*GetEncoding)(void *pSelf, BOOL *pKnown, UINT32 *pCodePage);
};

#if DXC_LANG_C

typedef struct IDxcBlobEncoding IDxcBlobEncoding;
struct IDxcBlobEncoding
{
 IDxcBlobEncodingVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: BlobWide Types

typedef struct IDxcBlobWideVTable IDxcBlobWideVTable;
struct IDxcBlobWideVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 LPVOID (*GetBufferPointer)(void *pSelf);
 SIZE_T (*GetBufferSize)(void *pSelf);

 HRESULT (*GetEncoding)(void *pSelf, BOOL *pKnown, UINT32 *pCodePage);

 LPCWSTR (*GetStringPointer)(void *pSelf);
 SIZE_T (*GetStringLength)(void *pSelf);
};

#if DXC_LANG_C

typedef struct IDxcBlobWide IDxcBlobWide;
struct IDxcBlobWide
{
 IDxcBlobWideVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: BlobUtf8 Types

typedef struct IDxcBlobUtf8VTable IDxcBlobUtf8VTable;
struct IDxcBlobUtf8VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 LPVOID (*GetBufferPointer)(void *pSelf);
 SIZE_T (*GetBufferSize)(void *pSelf);

 HRESULT (*GetEncoding)(void *pSelf, BOOL *pKnown, UINT32 *pCodePage);

 LPCSTR (*GetStringPointer)(void *pSelf);
 SIZE_T (*GetStringLength)(void *pSelf);
};

#if DXC_LANG_C

typedef struct IDxcBlobUtf8 IDxcBlobUtf8;
struct IDxcBlobUtf8
{
 IDxcBlobUtf8VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: IncludeHandler Types

typedef struct IDxcIncludeHandlerVTable IDxcIncludeHandlerVTable;
struct IDxcIncludeHandlerVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*LoadSource)(void *pSelf, LPCWSTR pFilename, IDxcBlob **ppIncludeSource);
};

#if DXC_LANG_C

typedef struct IDxcIncludeHandler IDxcIncludeHandler;
struct IDxcIncludeHandler
{
 IDxcIncludeHandlerVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: CompilerArgs Types

typedef struct IDxcCompilerArgsVTable IDxcCompilerArgsVTable;
struct IDxcCompilerArgsVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 LPCWSTR* (*GetArguments)(void *pSelf);
 UINT32 (*GetCount)(void *pSelf);
 HRESULT (*AddArguments)(void *pSelf, LPCWSTR *pArguments, UINT32 argCount);
 HRESULT (*AddArgumentsUTF8)(void *pSelf, LPCSTR *pArguments, UINT32 argCount);
 HRESULT (*AddDefines)(void *pSelf, const DxcDefine *pDefines, UINT32 defineCount);
};

#if DXC_LANG_C

typedef struct IDxcCompilerArgs IDxcCompilerArgs;
struct IDxcCompilerArgs
{
 IDxcCompilerArgsVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Library Types

typedef struct IDxcLibraryVTable IDxcLibraryVTable;
struct IDxcLibraryVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*SetMalloc)(void *pSelf, IMalloc *pMalloc);
 HRESULT (*CreateBlobFromBlob)(void *pSelf, IDxcBlob *pBlob, UINT32 offset, UINT32 length, IDxcBlob **ppResult);
 HRESULT (*CreateBlobFromFile)(void *pSelf, LPCWSTR pFileName, UINT32 *codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateBlobWithEncodingFromPinned)(void *pSelf, LPCVOID pText, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateBlobWithEncodingOnHeapCopy)(void *pSelf, LPCVOID pText, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateBlobWithEncodingOnMalloc)(void *pSelf, LPCVOID pText, IMalloc *pIMalloc, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateIncludeHandler)(void *pSelf, IDxcIncludeHandler **ppResult);
 HRESULT (*CreateStreamFromBlobReadOnly)(void *pSelf, IDxcBlob *pBlob, IStream **ppStream);
 HRESULT (*GetBlobAsUtf8)(void *pSelf, IDxcBlob *pBlob, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*GetBlobAsWide)(void *pSelf, IDxcBlob *pBlob, IDxcBlobEncoding **pBlobEncoding);
};

#if DXC_LANG_C

typedef struct IDxcLibrary IDxcLibrary;
struct IDxcLibrary
{
 IDxcLibraryVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: OperationResult Types

typedef struct IDxcOperationResultVTable IDxcOperationResultVTable;
struct IDxcOperationResultVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetStatus)(void *pSelf, HRESULT *pStatus);
 HRESULT (*GetResult)(void *pSelf, IDxcBlob **ppResult);
 HRESULT (*GetErrorBuffer)(void *pSelf, IDxcBlobEncoding **ppErrors);
};

#if DXC_LANG_C

typedef struct IDxcOperationResult IDxcOperationResult;
struct IDxcOperationResult
{
 IDxcOperationResultVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Compiler Types

typedef struct IDxcCompilerVTable IDxcCompilerVTable;
struct IDxcCompilerVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Compile)(void *pSelf, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult);
 HRESULT (*Preprocess)(void *pSelf, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult);
 HRESULT (*Disassemble)(void *pSelf, IDxcBlob *pSource, IDxcBlobEncoding **ppDisassembly);
};

#if DXC_LANG_C

typedef struct IDxcCompiler IDxcCompiler;
struct IDxcCompiler
{
 IDxcCompilerVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Compiler2 Types

typedef struct IDxcCompiler2VTable IDxcCompiler2VTable;
struct IDxcCompiler2VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Compile)(void *pSelf, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult);
 HRESULT (*Preprocess)(void *pSelf, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult);
 HRESULT (*Disassemble)(void *pSelf, IDxcBlob *pSource, IDxcBlobEncoding **ppDisassembly);

 HRESULT (*CompileWithDebug)(void *pSelf, IDxcBlob *pSource, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcIncludeHandler *pIncludeHandler, IDxcOperationResult **ppResult, LPWSTR *ppDebugBlobName, IDxcBlob **ppDebugBlob);
};

#if DXC_LANG_C

typedef struct IDxcCompiler2 IDxcCompiler2;
struct IDxcCompiler2
{
 IDxcCompiler2VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Linker Types

typedef struct IDxcLinkerVTable IDxcLinkerVTable;
struct IDxcLinkerVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*RegisterLibrary)(void *pSelf, LPCWSTR pLibName, IDxcBlob *pLib);
 HRESULT (*Link)(void *pSelf, LPCWSTR pEntryName, LPCWSTR pTargetProfile, const LPCWSTR *pLibNames, UINT32 libCount, const LPCWSTR *pArguments, UINT32 argCount, IDxcOperationResult **ppResult);
};

#if DXC_LANG_C

typedef struct IDxcLinker IDxcLinker;
struct IDxcLinker
{
 IDxcLinkerVTable *lpVtbl;
};

#endif // DXC_LANG_C

// NOTE(mwalky): Supposedly I should be using the interface below rather than the one above

////////////////////////////////
//~ mwalky: Utils Types

typedef struct IDxcUtilsVTable IDxcUtilsVTable;
struct IDxcUtilsVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*CreateBlobFromBlob)(void *pSelf, IDxcBlob *pBlob, UINT32 offset, UINT32 length, IDxcBlob **ppResult);
 HRESULT (*CreateBlobFromPinned)(void *pSelf, LPCVOID pData, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*MoveToBlob)(void *pSelf, LPCVOID pData, IMalloc *pIMalloc, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateBlob)(void *pSelf, LPCVOID pData, UINT32 size, UINT32 codePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*LoadFile)(void *pSelf, LPCWSTR pFileName, UINT32 *pCodePage, IDxcBlobEncoding **pBlobEncoding);
 HRESULT (*CreateReadOnlyStreamFromBlob)(void *pSelf, IDxcBlob *pBlob, IStream **ppStream);
 HRESULT (*CreateDefaultIncludeHandler)(void *pSelf, IDxcIncludeHandler **ppResult);
 HRESULT (*GetBlobAsUtf8)(void *pSelf, IDxcBlob *pBlob, IDxcBlobUtf8 **pBlobEncoding);
 HRESULT (*GetBlobAsWide)(void *pSelf, IDxcBlob *pBlob, IDxcBlobWide **pBlobEncoding);
 HRESULT (*GetDxilContainerPart)(void *pSelf, const DxcBuffer *pShader, UINT32 DxcPart, void **ppPartData, UINT32 *pPartSizeInBytes);
 HRESULT (*CreateReflection)(void *pSelf, const DxcBuffer *pData, REFIID iid, void **ppvReflection);
 HRESULT (*BuildArguments)(void *pSelf, LPCWSTR pSourceName, LPCWSTR pEntryPoint, LPCWSTR pTargetProfile, LPCWSTR *pArguments, UINT32 argCount, const DxcDefine *pDefines, UINT32 defineCount, IDxcCompilerArgs **ppArgs);
 HRESULT (*GetPDBContents)(void *pSelf, IDxcBlob *pPDBBlob, IDxcBlob **ppHash, IDxcBlob **ppContainer);
};

#if DXC_LANG_C

typedef struct IDxcUtils IDxcUtils;
struct IDxcUtils
{
 IDxcUtilsVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Result Types

typedef struct IDxcResultVTable IDxcResultVTable;
struct IDxcResultVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetStatus)(void *pSelf, HRESULT *pStatus);
 HRESULT (*GetResult)(void *pSelf, IDxcBlob **ppResult);
 HRESULT (*GetErrorBuffer)(void *pSelf, IDxcBlobEncoding **ppErrors);

 BOOL (*HasOutput)(void *pSelf, DXC_OUT_KIND dxcOutKind);
 HRESULT (*GetOutput)(void *pSelf, DXC_OUT_KIND dxcOutKind, REFIID iid, void **ppvObject, IDxcBlobWide **ppOutputName);
 UINT32 (*GetNumOutputs)(void *pSelf);
 DXC_OUT_KIND (*GetOutputByIndex)(void *pSelf, UINT32 Index);
 DXC_OUT_KIND (*PrimaryOutput)(void *pSelf);
};

#if DXC_LANG_C

typedef struct IDxcResult IDxcResult;
struct IDxcResult
{
 IDxcResultVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: ExtraOutputs Types

typedef struct IDxcExtraOutputsVTable IDxcExtraOutputsVTable;
struct IDxcExtraOutputsVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 UINT32 (*GetOutputCount)(void *pSelf);
 HRESULT (*GetOutput)(void *pSelf, UINT32 uIndex, REFIID iid, void **ppvObject, IDxcBlobWide **ppOutputType, IDxcBlobWide **ppOutputName);
};

#if DXC_LANG_C

typedef struct IDxcExtraOutputs IDxcExtraOutputs;
struct IDxcExtraOutputs
{
 IDxcExtraOutputsVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Compiler3 Types

typedef struct IDxcCompiler3VTable IDxcCompiler3VTable;
struct IDxcCompiler3VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Compile)(void *pSelf, const DxcBuffer *pSource, LPCWSTR *pArguments, UINT32 argCount, IDxcIncludeHandler *pIncludeHandler, REFIID riid, LPVOID *ppResult);
 HRESULT (*Disassemble)(void *pSelf, const DxcBuffer *pObject, REFIID riid, LPVOID *ppResult);
};

#if DXC_LANG_C

typedef struct IDxcCompiler3 IDxcCompiler3;
struct IDxcCompiler3
{
 IDxcCompiler3VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Validator Types

typedef struct IDxcValidatorVTable IDxcValidatorVTable;
struct IDxcValidatorVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Validate)(void *pSelf, IDxcBlob *pShader, UINT32 Flags, IDxcOperationResult **ppResult);
};

#if DXC_LANG_C

typedef struct IDxcValidator IDxcValidator;
struct IDxcValidator
{
 IDxcValidatorVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Validator2 Types

typedef struct IDxcValidator2VTable IDxcValidator2VTable;
struct IDxcValidator2VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Validate)(void *pSelf, IDxcBlob *pShader, UINT32 Flags, IDxcOperationResult **ppResult);

 HRESULT (*ValidateWithDebug)(void *pSelf, IDxcBlob *pShader, UINT32 Flags, DxcBuffer *pOptDebugBitcode, IDxcOperationResult **ppResult);
};

#if DXC_LANG_C

typedef struct IDxcValidator2 IDxcValidator2;
struct IDxcValidator2
{
 IDxcValidator2VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: ContainerBuilder Types

typedef struct IDxcContainerBuilderVTable IDxcContainerBuilderVTable;
struct IDxcContainerBuilderVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Load)(void *pSelf, IDxcBlob *pDxilContainerHeader);
 HRESULT (*AddPart)(void *pSelf, UINT32 fourCC, IDxcBlob *pSource);
 HRESULT (*RemovePart)(void *pSelf, UINT32 fourCC);
 HRESULT (*SerializeContainer)(void *pSelf, IDxcOperationResult **ppResult);
};

#if DXC_LANG_C

typedef struct IDxcContainerBuilder IDxcContainerBuilder;
struct IDxcContainerBuilder
{
 IDxcContainerBuilderVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Assembler Types

typedef struct IDxcAssemblerVTable IDxcAssemblerVTable;
struct IDxcAssemblerVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*AssembleToContainer)(void *pSelf, IDxcBlob *pShader, IDxcOperationResult **ppResult);
};

#if DXC_LANG_C

typedef struct IDxcAssembler IDxcAssembler;
struct IDxcAssembler
{
 IDxcAssemblerVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: ContainerReflection Types

typedef struct IDxcContainerReflectionVTable IDxcContainerReflectionVTable;
struct IDxcContainerReflectionVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Load)(void *pSelf, IDxcBlob *pContainer);
 HRESULT (*GetPartCount)(void *pSelf, UINT32 *pResult);
 HRESULT (*GetPartKind)(void *pSelf, UINT32 idx, UINT32 *pResult);
 HRESULT (*GetPartContent)(void *pSelf, UINT32 idx, IDxcBlob **ppResult);
 HRESULT (*FindFirstPartKind)(void *pSelf, UINT32 kind, UINT32 *pResult);
 HRESULT (*GetPartReflection)(void *pSelf, UINT32 idx, REFIID iid, void **ppvObject);
};

#if DXC_LANG_C

typedef struct IDxcContainerReflection IDxcContainerReflection;
struct IDxcContainerReflection
{
 IDxcContainerReflectionVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: OptimizerPass Types

typedef struct IDxcOptimizerPassVTable IDxcOptimizerPassVTable;
struct IDxcOptimizerPassVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetOptionName)(void *pSelf, LPWSTR *ppResult);
 HRESULT (*GetDescription)(void *pSelf, LPWSTR *ppResult);
 HRESULT (*GetOptionArgCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetOptionArgName)(void *pSelf, UINT32 argIndex, LPWSTR *ppResult);
 HRESULT (*GetOptionArgDescription)(void *pSelf, UINT32 argIndex, LPWSTR *ppResult);
};

#if DXC_LANG_C

typedef struct IDxcOptimizerPass IDxcOptimizerPass;
struct IDxcOptimizerPass
{
 IDxcOptimizerPassVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Optimizer Types

typedef struct IDxcOptimizerVTable IDxcOptimizerVTable;
struct IDxcOptimizerVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetAvailablePassCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetAvailablePass)(void *pSelf, UINT32 index, IDxcOptimizerPass **ppResult);
 HRESULT (*RunOptimizer)(void *pSelf, IDxcBlob *pBlob, LPCWSTR *ppOptions, UINT32 optionCount, IDxcBlob **pOutputModule, IDxcBlobEncoding **ppOutputText);
};

#if DXC_LANG_C

typedef struct IDxcOptimizer IDxcOptimizer;
struct IDxcOptimizer
{
 IDxcOptimizerVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: VersionInfo Types

typedef struct IDxcVersionInfoVTable IDxcVersionInfoVTable;
struct IDxcVersionInfoVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetVersion)(void *pSelf, UINT32 *pMajor, UINT32 *pMinor);
 HRESULT (*GetFlags)(void *pSelf, UINT32 *pFlags);
};

#if DXC_LANG_C

typedef struct IDxcVersionInfo IDxcVersionInfo;
struct IDxcVersionInfo
{
 IDxcVersionInfoVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: VersionInfo2 Types

typedef struct IDxcVersionInfo2VTable IDxcVersionInfo2VTable;
struct IDxcVersionInfo2VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetVersion)(void *pSelf, UINT32 *pMajor, UINT32 *pMinor);
 HRESULT (*GetFlags)(void *pSelf, UINT32 *pFlags);
 HRESULT (*GetCommitInfo)(void *pSelf, UINT32 *pCommitCount, char **pCommitHash);
};

#if DXC_LANG_C

typedef struct IDxcVersionInfo2 IDxcVersionInfo2;
struct IDxcVersionInfo2
{
 IDxcVersionInfo2VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: VersionInfo3 Types

typedef struct IDxcVersionInfo3VTable IDxcVersionInfo3VTable;
struct IDxcVersionInfo3VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*GetCustomVersionString)(void *pSelf, char **pVersionString);
};

#if DXC_LANG_C

typedef struct IDxcVersionInfo3 IDxcVersionInfo3;
struct IDxcVersionInfo3
{
 IDxcVersionInfo3VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: PdbUtils Types

typedef struct IDxcPdbUtilsVTable IDxcPdbUtilsVTable;
struct IDxcPdbUtilsVTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Load)(void *pSelf, IDxcBlob *pPdbOrDxil);
 HRESULT (*GetSourceCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetSource)(void *pSelf, UINT32 uIndex, IDxcBlobEncoding **ppResult);
 HRESULT (*GetSourceName)(void *pSelf, UINT32 uIndex, BSTR *pResult);
 HRESULT (*GetFlagCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetFlag)(void *pSelf, UINT32 uIndex, BSTR *pResult);
 HRESULT (*GetArgCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetArg)(void *pSelf, UINT32 uIndex, BSTR *pResult);
 HRESULT (*GetArgPairCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetArgPair)(void *pSelf, UINT32 uIndex, BSTR *pName, BSTR *pValue);
 HRESULT (*GetDefineCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetDefine)(void *pSelf, UINT32 uIndex, BSTR *pResult);
 HRESULT (*GetTargetProfile)(void *pSelf, BSTR *pResult);
 HRESULT (*GetEntryPoint)(void *pSelf, BSTR *pResult);
 HRESULT (*GetMainFileName)(void *pSelf, BSTR *pResult);
 HRESULT (*GetHash)(void *pSelf, IDxcBlob **ppResult);
 HRESULT (*GetName)(void *pSelf, BSTR *pResult);
 BOOL (*IsFullPDB)(void *pSelf);
 HRESULT (*GetFullPDB)(void *pSelf, IDxcBlob **ppFullPDB);
 HRESULT (*GetVersionInfo)(void *pSelf, IDxcVersionInfo **ppVersionInfo);
 HRESULT (*SetCompiler)(void *pSelf, IDxcCompiler3 *compiler);
 HRESULT (*CompileForFullPDB)(void *pSelf, IDxcResult **ppResult);
 HRESULT (*OverrideArgs)(void *pSelf, DxcArgPair *pArgPairs, UINT32 uNumArgPairs);
 HRESULT (*OverrideRootSignature)(void *pSelf, const WCHAR *pRootSignature);
};

#if DXC_LANG_C

typedef struct IDxcPdbUtils IDxcPdbUtils;
struct IDxcPdbUtils
{
 IDxcPdbUtilsVTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: PdbUtils2 Types

typedef struct IDxcPdbUtils2VTable IDxcPdbUtils2VTable;
struct IDxcPdbUtils2VTable
{
 HRESULT (*QueryInterface)(void *pSelf, REFIID riid, void **ppvObject);
 ULONG (*AddRef)(void *pSelf);
 ULONG (*Release)(void *pSelf);

 HRESULT (*Load)(void *pSelf, IDxcBlob *pPdbOrDxil);
 HRESULT (*GetSourceCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetSource)(void *pSelf, UINT32 uIndex, IDxcBlobEncoding **ppResult);
 HRESULT (*GetSourceName)(void *pSelf, UINT32 uIndex, IDxcBlobWide **ppResult);
 HRESULT (*GetLibraryPDBCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetLibraryPDB)(void *pSelf, UINT32 uIndex, IDxcPdbUtils2 **ppOutPdbUtils, IDxcBlobWide **ppLibraryName);
 HRESULT (*GetFlagCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetFlag)(void *pSelf, UINT32 uIndex, IDxcBlobWide **ppResult);
 HRESULT (*GetArgCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetArg)(void *pSelf, UINT32 uIndex, IDxcBlobWide **ppResult);
 HRESULT (*GetArgPairCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetArgPair)(void *pSelf, UINT32 uIndex, IDxcBlobWide **ppName, IDxcBlobWide **ppValue);
 HRESULT (*GetDefineCount)(void *pSelf, UINT32 *pCount);
 HRESULT (*GetDefine)(void *pSelf, UINT32 uIndex, IDxcBlobWide **ppResult);
 HRESULT (*GetTargetProfile)(void *pSelf, IDxcBlobWide **ppResult);
 HRESULT (*GetEntryPoint)(void *pSelf, IDxcBlobWide **ppResult);
 HRESULT (*GetMainFileName)(void *pSelf, IDxcBlobWide **ppResult);
 HRESULT (*GetHash)(void *pSelf, IDxcBlob **ppResult);
 HRESULT (*GetName)(void *pSelf, IDxcBlobWide **ppResult);
 HRESULT (*GetVersionInfo)(void *pSelf, IDxcVersionInfo **ppVersionInfo);
 HRESULT (*GetCustomToolchainID)(void *pSelf, UINT32 *pID);
 HRESULT (*GetCustomToolchainData)(void *pSelf, IDxcBlob **ppBlob);
 HRESULT (*GetWholeDxil)(void *pSelf, IDxcBlob **ppResult);
 BOOL (*IsFullPDB)(void *pSelf);
 BOOL (*IsPDBRef)(void *pSelf);
};

#if DXC_LANG_C

typedef struct IDxcPdbUtils2 IDxcPdbUtils2;
struct IDxcPdbUtils2
{
 IDxcPdbUtils2VTable *lpVtbl;
};

#endif // DXC_LANG_C

////////////////////////////////
//~ mwalky: Top-Level API

#if DXC_LANG_C

#ifdef COBJMACROS

////////////////////////////////
//~ mwalky: Blob Top-Level API

#define IDxcBlob_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcBlob_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcBlob_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcBlob_GetBufferPointer(pSelf) (pSelf)->lpVtbl->GetBufferPointer(pSelf)
#define IDxcBlob_GetBufferSize(pSelf) (pSelf)->lpVtbl->GetBufferSize(pSelf)

////////////////////////////////
//~ mwalky: BlobEncoding Top-Level API

#define IDxcBlobEncoding_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcBlobEncoding_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcBlobEncoding_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcBlobEncoding_GetBufferPointer(pSelf) (pSelf)->lpVtbl->GetBufferPointer(pSelf)
#define IDxcBlobEncoding_GetBufferSize(pSelf) (pSelf)->lpVtbl->GetBufferSize(pSelf)

#define IDxcBlobEncoding_GetEncoding(pSelf, pKnown, pCodePage) (pSelf)->lpVtbl->GetEncoding(pSelf, pKnown, pCodePage)

////////////////////////////////
//~ mwalky: BlobWide Top-Level API

#define IDxcBlobWide_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcBlobWide_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcBlobWide_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcBlobWide_GetBufferPointer(pSelf) (pSelf)->lpVtbl->GetBufferPointer(pSelf)
#define IDxcBlobWide_GetBufferSize(pSelf) (pSelf)->lpVtbl->GetBufferSize(pSelf)

#define IDxcBlobWide_GetEncoding(pSelf, pKnown, pCodePage) (pSelf)->lpVtbl->GetEncoding(pSelf, pKnown, pCodePage)

#define IDxcBlobWide_GetStringPointer(pSelf) (pSelf)->lpVtbl->GetStringPointer(pSelf)
#define IDxcBlobWide_GetStringLength(pSelf) (pSelf)->lpVtbl->GetStringLength(pSelf)

////////////////////////////////
//~ mwalky: BlobUtf8 Top-Level API

#define IDxcBlobUtf8_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcBlobUtf8_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcBlobUtf8_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcBlobUtf8_GetBufferPointer(pSelf) (pSelf)->lpVtbl->GetBufferPointer(pSelf)
#define IDxcBlobUtf8_GetBufferSize(pSelf) (pSelf)->lpVtbl->GetBufferSize(pSelf)

#define IDxcBlobUtf8_GetEncoding(pSelf, pKnown, pCodePage) (pSelf)->lpVtbl->GetEncoding(pSelf, pKnown, pCodePage)

#define IDxcBlobUtf8_GetStringPointer(pSelf) (pSelf)->lpVtbl->GetStringPointer(pSelf)
#define IDxcBlobUtf8_GetStringLength(pSelf) (pSelf)->lpVtbl->GetStringLength(pSelf)

////////////////////////////////
//~ mwalky: IncludeHandler Top-Level API

#define IDxcIncludeHandler_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcIncludeHandler_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcIncludeHandler_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcIncludeHandler_LoadSource(pSelf, pFilename, ppIncludeSource) (pSelf)->lpVtbl->LoadSource(pSelf, pFilename, ppIncludeSource)

////////////////////////////////
//~ mwalky: CompilerArgs Top-Level API

#define IDxcCompilerArgs_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcCompilerArgs_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcCompilerArgs_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcCompilerArgs_GetArguments(pSelf) (pSelf)->lpVtbl->GetArguments(pSelf)
#define IDxcCompilerArgs_GetCount(pSelf) (pSelf)->lpVtbl->GetCount(pSelf)
#define IDxcCompilerArgs_AddArguments(pSelf, pArguments, argCount) (pSelf)->lpVtbl->AddArguments(pSelf, pArguments, argCount)
#define IDxcCompilerArgs_AddArgumentsUTF8(pSelf, pArguments, argCount) (pSelf)->lpVtbl->AddArgumentsUTF8(pSelf, pArguments, argCount)
#define IDxcCompilerArgs_AddDefines(pSelf, pDefines, defineCount) (pSelf)->lpVtbl->AddDefines(pSelf, pDefines, defineCount)

////////////////////////////////
//~ mwalky: Library Top-Level API

#define IDxcLibrary_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcLibrary_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcLibrary_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcLibrary_SetMalloc(pSelf, pMalloc) (pSelf)->lpVtbl->SetMalloc(pSelf, pMalloc)
#define IDxcLibrary_CreateBlobFromBlob(pSelf, pBlob, offset, length, ppResult) (pSelf)->lpVtbl->CreateBlobFromBlob(pSelf, pBlob, offset, length, ppResult)
#define IDxcLibrary_CreateBlobFromFile(pSelf, pFileName, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlobFromFile(pSelf, pFileName, codePage, pBlobEncoding)
#define IDxcLibrary_CreateBlobWithEncodingFromPinned(pSelf, pText, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlobWithEncodingFromPinned(pSelf, pText, size, codePage, pBlobEncoding)
#define IDxcLibrary_CreateBlobWithEncodingOnHeapCopy(pSelf, pText, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlobWithEncodingOnHeapCopy(pSelf, pText, size, codePage, pBlobEncoding)
#define IDxcLibrary_CreateBlobWithEncodingOnMalloc(pSelf, pText, pIMalloc, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlobWithEncodingOnMalloc(pSelf, pText, pIMalloc, size, codePage, pBlobEncoding)
#define IDxcLibrary_CreateIncludeHandler(pSelf, ppResult) (pSelf)->lpVtbl->CreateIncludeHandler(pSelf, ppResult)
#define IDxcLibrary_CreateStreamFromBlobReadOnly(pSelf, pBlob, ppStream) (pSelf)->lpVtbl->CreateStreamFromBlobReadOnly(pSelf, pBlob, ppStream)
#define IDxcLibrary_GetBlobAsUtf8(pSelf, pBlob, pBlobEncoding) (pSelf)->lpVtbl->GetBlobAsUtf8(pSelf, pBlob, pBlobEncoding)
#define IDxcLibrary_GetBlobAsWide(pSelf, pBlob, pBlobEncoding) (pSelf)->lpVtbl->GetBlobAsWide(pSelf, pBlob, pBlobEncoding)

////////////////////////////////
//~ mwalky: OperationResult Top-Level API

#define IDxcOperationResult_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcOperationResult_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcOperationResult_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcOperationResult_GetStatus(pSelf, pStatus) (pSelf)->lpVtbl->GetStatus(pSelf, pStatus)
#define IDxcOperationResult_GetResult(pSelf, ppResult) (pSelf)->lpVtbl->GetResult(pSelf, ppResult)
#define IDxcOperationResult_GetErrorBuffer(pSelf, ppErrors) (pSelf)->lpVtbl->GetErrorBuffer(pSelf, ppErrors)

////////////////////////////////
//~ mwalky: Compiler Top-Level API

#define IDxcCompiler_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcCompiler_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcCompiler_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcCompiler_Compile(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult) (pSelf)->lpVtbl->Compile(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult)
#define IDxcCompiler_Preprocess(pSelf, pSource, pSourceName, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult) (pSelf)->lpVtbl->Preprocess(pSelf, pSource, pSourceName, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult)
#define IDxcCompiler_Disassemble(pSelf, pSource, ppDisassembly) (pSelf)->lpVtbl->Disassemble(pSelf, pSource, ppDisassembly)

////////////////////////////////
//~ mwalky: Compiler2 Top-Level API

#define IDxcCompiler2_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcCompiler2_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcCompiler2_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcCompiler2_Compile(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult) (pSelf)->lpVtbl->Compile(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult)
#define IDxcCompiler2_Preprocess(pSelf, pSource, pSourceName, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult) (pSelf)->lpVtbl->Preprocess(pSelf, pSource, pSourceName, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult)
#define IDxcCompiler2_Disassemble(pSelf, pSource, ppDisassembly) (pSelf)->lpVtbl->Disassemble(pSelf, pSource, ppDisassembly)

#define IDxcCompiler2_CompileWithDebug(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult, ppDebugBlobName, ppDebugBlob) (pSelf)->lpVtbl->CompileWithDebug(pSelf, pSource, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, pIncludeHandler, ppResult, ppDebugBlobName, ppDebugBlob)

////////////////////////////////
//~ mwalky: Linker Top-Level API

#define IDxcLinker_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcLinker_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcLinker_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcLinker_RegisterLibrary(pSelf, pLibName, pLib) (pSelf)->lpVtbl->RegisterLibrary(pSelf, pLibName, pLib)
#define IDxcLinker_Link(pSelf, pEntryName, pTargetProfile, pLibNames, libCount, pArguments, argCount, ppResult) (pSelf)->lpVtbl->Link(pSelf, pEntryName, pTargetProfile, pLibNames, libCount, pArguments, argCount, ppResult)

// NOTE(mwalky): Supposedly I should be using the interface below rather than the one above

////////////////////////////////
//~ mwalky: Utils Top-Level API

#define IDxcUtils_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcUtils_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcUtils_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcUtils_CreateBlobFromBlob(pSelf, pBlob, offset, length, ppResult) (pSelf)->lpVtbl->CreateBlobFromBlob(pSelf, pBlob, offset, length, ppResult)
#define IDxcUtils_CreateBlobFromPinned(pSelf, pData, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlobFromPinned(pSelf, pData, size, codePage, pBlobEncoding)
#define IDxcUtils_MoveToBlob(pSelf, pData, pIMalloc, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->MoveToBlob(pSelf, pData, pIMalloc, size, codePage, pBlobEncoding)
#define IDxcUtils_CreateBlob(pSelf, pData, size, codePage, pBlobEncoding) (pSelf)->lpVtbl->CreateBlob(pSelf, pData, size, codePage, pBlobEncoding)
#define IDxcUtils_LoadFile(pSelf, pFileName, pCodePage, pBlobEncoding) (pSelf)->lpVtbl->LoadFile(pSelf, pFileName, pCodePage, pBlobEncoding)
#define IDxcUtils_CreateReadOnlyStreamFromBlob(pSelf, pBlob, ppStream) (pSelf)->lpVtbl->CreateReadOnlyStreamFromBlob(pSelf, pBlob, ppStream)
#define IDxcUtils_CreateDefaultIncludeHandler(pSelf, ppResult) (pSelf)->lpVtbl->CreateDefaultIncludeHandler(pSelf, ppResult)
#define IDxcUtils_GetBlobAsUtf8(pSelf, pBlob, pBlobEncoding) (pSelf)->lpVtbl->GetBlobAsUtf8(pSelf, pBlob, pBlobEncoding)
#define IDxcUtils_GetBlobAsWide(pSelf, pBlob, pBlobEncoding) (pSelf)->lpVtbl->GetBlobAsWide(pSelf, pBlob, pBlobEncoding)
#define IDxcUtils_GetDxilContainerPart(pSelf, pShader, DxcPart, ppPartData, pPartSizeInBytes) (pSelf)->lpVtbl->GetDxilContainerPart(pSelf, pShader, DxcPart, ppPartData, pPartSizeInBytes)
#define IDxcUtils_CreateReflection(pSelf, pData, iid, ppvReflection) (pSelf)->lpVtbl->CreateReflection(pSelf, pData, iid, ppvReflection)
#define IDxcUtils_BuildArguments(pSelf, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, ppArgs) (pSelf)->lpVtbl->BuildArguments(pSelf, pSourceName, pEntryPoint, pTargetProfile, pArguments, argCount, pDefines, defineCount, ppArgs)
#define IDxcUtils_GetPDBContents(pSelf, pPDBBlob, ppHash, ppContainer) (pSelf)->lpVtbl->GetPDBContents(pSelf, pPDBBlob, ppHash, ppContainer)

////////////////////////////////
//~ mwalky: Result Top-Level API

#define IDxcResult_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcResult_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcResult_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcResult_GetStatus(pSelf, pStatus) (pSelf)->lpVtbl->GetStatus(pSelf, pStatus)
#define IDxcResult_GetResult(pSelf, ppResult) (pSelf)->lpVtbl->GetResult(pSelf, ppResult)
#define IDxcResult_GetErrorBuffer(pSelf, ppErrors) (pSelf)->lpVtbl->GetErrorBuffer(pSelf, ppErrors)

#define IDxcResult_HasOutput(pSelf, dxcOutKind) (pSelf)->lpVtbl->HasOutput(pSelf, dxcOutKind)
#define IDxcResult_GetOutput(pSelf, dxcOutKind, iid, ppvObject, ppOutputName) (pSelf)->lpVtbl->GetOutput(pSelf, dxcOutKind, iid, ppvObject, ppOutputName)
#define IDxcResult_GetNumOutputs(pSelf) (pSelf)->lpVtbl->GetNumOutputs(pSelf)
#define IDxcResult_GetOutputByIndex(pSelf, Index) (pSelf)->lpVtbl->GetOutputByIndex(pSelf, Index)
#define IDxcResult_PrimaryOutput(pSelf) (pSelf)->lpVtbl->PrimaryOutput(pSelf)

////////////////////////////////
//~ mwalky: ExtraOutputs Top-Level API

#define IDxcExtraOutputs_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcExtraOutputs_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcExtraOutputs_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcExtraOutputs_GetOutputCount(pSelf) (pSelf)->lpVtbl->GetOutputCount(pSelf)
#define IDxcExtraOutputs_GetOutput(pSelf, uIndex, iid, ppvObject, ppOutputType, ppOutputName) (pSelf)->lpVtbl->GetOutput(pSelf, uIndex, iid, ppvObject, ppOutputType, ppOutputName)

////////////////////////////////
//~ mwalky: Compiler3 Top-Level API

#define IDxcCompiler3_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcCompiler3_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcCompiler3_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcCompiler3_Compile(pSelf, pSource, pArguments, argCount, pIncludeHandler, riid, ppResult) (pSelf)->lpVtbl->Compile(pSelf, pSource, pArguments, argCount, pIncludeHandler, riid, ppResult)
#define IDxcCompiler3_Disassemble(pSelf, pObject, riid, ppResult) (pSelf)->lpVtbl->Disassemble(pSelf, pObject, riid, ppResult)

////////////////////////////////
//~ mwalky: Validator Top-Level API

#define IDxcValidator_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcValidator_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcValidator_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcValidator_Validate(pSelf, pShader, Flags, ppResult) (pSelf)->lpVtbl->Validate(pSelf, pShader, Flags, ppResult)

////////////////////////////////
//~ mwalky: Validator2 Top-Level API

#define IDxcValidator2_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcValidator2_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcValidator2_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcValidator2_Validate(pSelf, pShader, Flags, ppResult) (pSelf)->lpVtbl->Validate(pSelf, pShader, Flags, ppResult)

#define IDxcValidator2_ValidateWithDebug(pSelf, pShader, Flags, pOptDebugBitcode, ppResult) (pSelf)->lpVtbl->ValidateWithDebug(pSelf, pShader, Flags, pOptDebugBitcode, ppResult)

////////////////////////////////
//~ mwalky: ContainerBuilder Top-Level API

#define IDxcContainerBuilder_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcContainerBuilder_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcContainerBuilder_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcContainerBuilder_Load(pSelf, pDxilContainerHeader) (pSelf)->lpVtbl->Load(pSelf, pDxilContainerHeader)
#define IDxcContainerBuilder_AddPart(pSelf, fourCC, pSource) (pSelf)->lpVtbl->AddPart(pSelf, fourCC, pSource)
#define IDxcContainerBuilder_RemovePart(pSelf, fourCC) (pSelf)->lpVtbl->RemovePart(pSelf, fourCC)
#define IDxcContainerBuilder_SerializeContainer(pSelf, ppResult) (pSelf)->lpVtbl->SerializeContainer(pSelf, ppResult)

////////////////////////////////
//~ mwalky: Assembler Top-Level API

#define IDxcAssembler_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcAssembler_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcAssembler_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcAssembler_AssembleToContainer(pSelf, pShader, ppResult) (pSelf)->lpVtbl->AssembleToContainer(pSelf, pShader, ppResult)

////////////////////////////////
//~ mwalky: ContainerReflection Top-Level API

#define IDxcContainerReflection_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcContainerReflection_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcContainerReflection_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcContainerReflection_Load(pSelf, pContainer) (pSelf)->lpVtbl->Load(pSelf, pContainer)
#define IDxcContainerReflection_GetPartCount(pSelf, pResult) (pSelf)->lpVtbl->GetPartCount(pSelf, pResult)
#define IDxcContainerReflection_GetPartKind(pSelf, idx, pResult) (pSelf)->lpVtbl->GetPartKind(pSelf, idx, pResult)
#define IDxcContainerReflection_GetPartContent(pSelf, idx, ppResult) (pSelf)->lpVtbl->GetPartContent(pSelf, idx, ppResult)
#define IDxcContainerReflection_FindFirstPartKind(pSelf, kind, pResult) (pSelf)->lpVtbl->FindFirstPartKind(pSelf, kind, pResult)
#define IDxcContainerReflection_GetPartReflection(pSelf, idx, iid, ppvObject) (pSelf)->lpVtbl->GetPartReflection(pSelf, idx, iid, ppvObject)

////////////////////////////////
//~ mwalky: OptimizerPass Top-Level API

#define IDxcOptimizerPass_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcOptimizerPass_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcOptimizerPass_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcOptimizerPass_GetOptionName(pSelf, ppResult) (pSelf)->lpVtbl->GetOptionName(pSelf, ppResult)
#define IDxcOptimizerPass_GetDescription(pSelf, ppResult) (pSelf)->lpVtbl->GetDescription(pSelf, ppResult)
#define IDxcOptimizerPass_GetOptionArgCount(pSelf, pCount) (pSelf)->lpVtbl->GetOptionArgCount(pSelf, pCount)
#define IDxcOptimizerPass_GetOptionArgName(pSelf, argIndex, ppResult) (pSelf)->lpVtbl->GetOptionArgName(pSelf, argIndex, ppResult)
#define IDxcOptimizerPass_GetOptionArgDescription(pSelf, argIndex, ppResult) (pSelf)->lpVtbl->GetOptionArgDescription(pSelf, argIndex, ppResult)

////////////////////////////////
//~ mwalky: Optimizer Top-Level API

#define IDxcOptimizer_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcOptimizer_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcOptimizer_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcOptimizer_GetAvailablePassCount(pSelf, pCount) (pSelf)->lpVtbl->GetAvailablePassCount(pSelf, pCount)
#define IDxcOptimizer_GetAvailablePass(pSelf, index, ppResult) (pSelf)->lpVtbl->GetAvailablePass(pSelf, index, ppResult)
#define IDxcOptimizer_RunOptimizer(pSelf, pBlob, ppOptions, optionCount, pOutputModule, ppOutputText) (pSelf)->lpVtbl->RunOptimizer(pSelf, pBlob, ppOptions, optionCount, pOutputModule, ppOutputText)

////////////////////////////////
//~ mwalky: VersionInfo Top-Level API

#define IDxcVersionInfo_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcVersionInfo_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcVersionInfo_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcVersionInfo_GetVersion(pSelf, pMajor, pMinor) (pSelf)->lpVtbl->GetVersion(pSelf, pMajor, pMinor)
#define IDxcVersionInfo_GetFlags(pSelf, pFlags) (pSelf)->lpVtbl->GetFlags(pSelf, pFlags)

////////////////////////////////
//~ mwalky: VersionInfo2 Top-Level API

#define IDxcVersionInfo2_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcVersionInfo2_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcVersionInfo2_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcVersionInfo2_GetVersion(pSelf, pMajor, pMinor) (pSelf)->lpVtbl->GetVersion(pSelf, pMajor, pMinor)
#define IDxcVersionInfo2_GetFlags(pSelf, pFlags) (pSelf)->lpVtbl->GetFlags(pSelf, pFlags)
#define IDxcVersionInfo2_GetCommitInfo(pSelf, pCommitCount, pCommitHash) (pSelf)->lpVtbl->GetCommitInfo(pSelf, pCommitCount, pCommitHash)

////////////////////////////////
//~ mwalky: VersionInfo3 Top-Level API

#define IDxcVersionInfo3_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcVersionInfo3_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcVersionInfo3_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcVersionInfo3_GetCustomVersionString(pSelf, pVersionString) (pSelf)->lpVtbl->GetCustomVersionString(pSelf, pVersionString)

////////////////////////////////
//~ mwalky: PdbUtils Top-Level API

#define IDxcPdbUtils_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcPdbUtils_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcPdbUtils_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcPdbUtils_Load(pSelf, pPdbOrDxil) (pSelf)->lpVtbl->Load(pSelf, pPdbOrDxil)
#define IDxcPdbUtils_GetSourceCount(pSelf, pCount) (pSelf)->lpVtbl->GetSourceCount(pSelf, pCount)
#define IDxcPdbUtils_GetSource(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetSource(pSelf, uIndex, ppResult)
#define IDxcPdbUtils_GetSourceName(pSelf, uIndex, pResult) (pSelf)->lpVtbl->GetSourceName(pSelf, uIndex, pResult)
#define IDxcPdbUtils_GetFlagCount(pSelf, pCount) (pSelf)->lpVtbl->GetFlagCount(pSelf, pCount)
#define IDxcPdbUtils_GetFlag(pSelf, uIndex, pResult) (pSelf)->lpVtbl->GetFlag(pSelf, uIndex, pResult)
#define IDxcPdbUtils_GetArgCount(pSelf, pCount) (pSelf)->lpVtbl->GetArgCount(pSelf, pCount)
#define IDxcPdbUtils_GetArg(pSelf, uIndex, pResult) (pSelf)->lpVtbl->GetArg(pSelf, uIndex, pResult)
#define IDxcPdbUtils_GetArgPairCount(pSelf, pCount) (pSelf)->lpVtbl->GetArgPairCount(pSelf, pCount)
#define IDxcPdbUtils_GetArgPair(pSelf, uIndex, pName, pValue) (pSelf)->lpVtbl->GetArgPair(pSelf, uIndex, pName, pValue)
#define IDxcPdbUtils_GetDefineCount(pSelf, pCount) (pSelf)->lpVtbl->GetDefineCount(pSelf, pCount)
#define IDxcPdbUtils_GetDefine(pSelf, uIndex, pResult) (pSelf)->lpVtbl->GetDefine(pSelf, uIndex, pResult)
#define IDxcPdbUtils_GetTargetProfile(pSelf, pResult) (pSelf)->lpVtbl->GetTargetProfile(pSelf, pResult)
#define IDxcPdbUtils_GetEntryPoint(pSelf, pResult) (pSelf)->lpVtbl->GetEntryPoint(pSelf, pResult)
#define IDxcPdbUtils_GetMainFileName(pSelf, pResult) (pSelf)->lpVtbl->GetMainFileName(pSelf, pResult)
#define IDxcPdbUtils_GetHash(pSelf, ppResult) (pSelf)->lpVtbl->GetHash(pSelf, ppResult)
#define IDxcPdbUtils_GetName(pSelf, pResult) (pSelf)->lpVtbl->GetName(pSelf, pResult)
#define IDxcPdbUtils_IsFullPDB(pSelf) (pSelf)->lpVtbl->IsFullPDB(pSelf)
#define IDxcPdbUtils_GetFullPDB(pSelf, ppFullPDB) (pSelf)->lpVtbl->GetFullPDB(pSelf, ppFullPDB)
#define IDxcPdbUtils_GetVersionInfo(pSelf, ppVersionInfo) (pSelf)->lpVtbl->GetVersionInfo(pSelf, ppVersionInfo)
#define IDxcPdbUtils_SetCompiler(pSelf, compiler) (pSelf)->lpVtbl->SetCompiler(pSelf, compiler)
#define IDxcPdbUtils_CompileForFullPDB(pSelf, ppResult) (pSelf)->lpVtbl->CompileForFullPDB(pSelf, ppResult)
#define IDxcPdbUtils_OverrideArgs(pSelf, pArgPairs, uNumArgPairs) (pSelf)->lpVtbl->OverrideArgs(pSelf, pArgPairs, uNumArgPairs)
#define IDxcPdbUtils_OverrideRootSignature(pSelf, pRootSignature) (pSelf)->lpVtbl->OverrideRootSignature(pSelf, pRootSignature)

////////////////////////////////
//~ mwalky: PdbUtils2 Top-Level API

#define IDxcPdbUtils2_QueryInterface(pSelf, riid, ppvObject) (pSelf)->lpVtbl->QueryInterface(pSelf, riid, ppvObject)
#define IDxcPdbUtils2_AddRef(pSelf) (pSelf)->lpVtbl->AddRef(pSelf)
#define IDxcPdbUtils2_Release(pSelf) (pSelf)->lpVtbl->Release(pSelf)

#define IDxcPdbUtils2_Load(pSelf, pPdbOrDxil) (pSelf)->lpVtbl->Load(pSelf, pPdbOrDxil)
#define IDxcPdbUtils2_GetSourceCount(pSelf, pCount) (pSelf)->lpVtbl->GetSourceCount(pSelf, pCount)
#define IDxcPdbUtils2_GetSource(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetSource(pSelf, uIndex, ppResult)
#define IDxcPdbUtils2_GetSourceName(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetSourceName(pSelf, uIndex, ppResult)
#define IDxcPdbUtils2_GetLibraryPDBCount(pSelf, pCount) (pSelf)->lpVtbl->GetLibraryPDBCount(pSelf, pCount)
#define IDxcPdbUtils2_GetLibraryPDB(pSelf, uIndex, ppOutPdbUtils, ppLibraryName) (pSelf)->lpVtbl->GetLibraryPDB(pSelf, uIndex, ppOutPdbUtils, ppLibraryName)
#define IDxcPdbUtils2_GetFlagCount(pSelf, pCount) (pSelf)->lpVtbl->GetFlagCount(pSelf, pCount)
#define IDxcPdbUtils2_GetFlag(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetFlag(pSelf, uIndex, ppResult)
#define IDxcPdbUtils2_GetArgCount(pSelf, pCount) (pSelf)->lpVtbl->GetArgCount(pSelf, pCount)
#define IDxcPdbUtils2_GetArg(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetArg(pSelf, uIndex, ppResult)
#define IDxcPdbUtils2_GetArgPairCount(pSelf, pCount) (pSelf)->lpVtbl->GetArgPairCount(pSelf, pCount)
#define IDxcPdbUtils2_GetArgPair(pSelf, uIndex, ppName, ppValue) (pSelf)->lpVtbl->GetArgPair(pSelf, uIndex, ppName, ppValue)
#define IDxcPdbUtils2_GetDefineCount(pSelf, pCount) (pSelf)->lpVtbl->GetDefineCount(pSelf, pCount)
#define IDxcPdbUtils2_GetDefine(pSelf, uIndex, ppResult) (pSelf)->lpVtbl->GetDefine(pSelf, uIndex, ppResult)
#define IDxcPdbUtils2_GetTargetProfile(pSelf, ppResult) (pSelf)->lpVtbl->GetTargetProfile(pSelf, ppResult)
#define IDxcPdbUtils2_GetEntryPoint(pSelf, ppResult) (pSelf)->lpVtbl->GetEntryPoint(pSelf, ppResult)
#define IDxcPdbUtils2_GetMainFileName(pSelf, ppResult) (pSelf)->lpVtbl->GetMainFileName(pSelf, ppResult)
#define IDxcPdbUtils2_GetHash(pSelf, ppResult) (pSelf)->lpVtbl->GetHash(pSelf, ppResult)
#define IDxcPdbUtils2_GetName(pSelf, ppResult) (pSelf)->lpVtbl->GetName(pSelf, ppResult)
#define IDxcPdbUtils2_GetVersionInfo(pSelf, ppVersionInfo) (pSelf)->lpVtbl->GetVersionInfo(pSelf, ppVersionInfo)
#define IDxcPdbUtils2_GetCustomToolchainID(pSelf, pID) (pSelf)->lpVtbl->GetCustomToolchainID(pSelf, pID)
#define IDxcPdbUtils2_GetCustomToolchainData(pSelf, ppBlob) (pSelf)->lpVtbl->GetCustomToolchainData(pSelf, ppBlob)
#define IDxcPdbUtils2_GetWholeDxil(pSelf, ppResult) (pSelf)->lpVtbl->GetWholeDxil(pSelf, ppResult)
#define IDxcPdbUtils2_IsFullPDB(pSelf) (pSelf)->lpVtbl->IsFullPDB(pSelf)
#define IDxcPdbUtils2_IsPDBRef(pSelf) (pSelf)->lpVtbl->IsPDBRef(pSelf)

#endif // COBJMACROS

#endif // DXC_LANG_C

#endif // DXC_H
