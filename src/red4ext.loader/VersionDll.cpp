#include "stdafx.hpp"
#include "VersionDll.hpp"

decltype(&GetFileVersionInfoA) _GetFileVersionInfoA;
decltype(&GetFileVersionInfoExA) _GetFileVersionInfoExA;
decltype(&GetFileVersionInfoExW) _GetFileVersionInfoExW;
decltype(&GetFileVersionInfoSizeA) _GetFileVersionInfoSizeA;
decltype(&GetFileVersionInfoSizeExA) _GetFileVersionInfoSizeExA;
decltype(&GetFileVersionInfoSizeExW) _GetFileVersionInfoSizeExW;
decltype(&GetFileVersionInfoSizeW) _GetFileVersionInfoSizeW;
decltype(&GetFileVersionInfoW) _GetFileVersionInfoW;
decltype(&VerFindFileA) _VerFindFileA;
decltype(&VerFindFileW) _VerFindFileW;
decltype(&VerInstallFileA) _VerInstallFileA;
decltype(&VerInstallFileW) _VerInstallFileW;
decltype(&VerLanguageNameA) _VerLanguageNameA;
decltype(&VerLanguageNameW) _VerLanguageNameW;
decltype(&VerQueryValueA) _VerQueryValueA;
decltype(&VerQueryValueW) _VerQueryValueW;

INT APIENTRY GetFileVersionInfoByHandle(int a1, int64_t a2, int64_t a3, int64_t a4);
decltype(&GetFileVersionInfoByHandle) _GetFileVersionInfoByHandle;

BOOL APIENTRY GetFileVersionInfoA(_In_ LPCSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen,
                                  _Out_writes_bytes_(dwLen) LPVOID lpData)
{
    return _GetFileVersionInfoA(lptstrFilename, dwHandle, dwLen, lpData);
}

INT APIENTRY GetFileVersionInfoByHandle(int a1, int64_t a2, int64_t a3, int64_t a4)
{
    return _GetFileVersionInfoByHandle(a1, a2, a3, a4);
}

BOOL APIENTRY GetFileVersionInfoExA(_In_ DWORD dwFlags, _In_ LPCSTR lpwstrFilename, _Reserved_ DWORD dwHandle,
                                    _In_ DWORD dwLen, _Out_writes_bytes_(dwLen) LPVOID lpData)
{
    return _GetFileVersionInfoExA(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

BOOL APIENTRY GetFileVersionInfoExW(_In_ DWORD dwFlags, _In_ LPCWSTR lpwstrFilename, _Reserved_ DWORD dwHandle,
                                    _In_ DWORD dwLen, _Out_writes_bytes_(dwLen) LPVOID lpData)
{
    return _GetFileVersionInfoExW(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

DWORD APIENTRY GetFileVersionInfoSizeA(_In_ LPCSTR lptstrFilename, _Out_opt_ LPDWORD lpdwHandle)
{
    return _GetFileVersionInfoSizeA(lptstrFilename, lpdwHandle);
}

DWORD APIENTRY GetFileVersionInfoSizeExA(_In_ DWORD dwFlags, _In_ LPCSTR lpwstrFilename, _Out_ LPDWORD lpdwHandle)
{
    return _GetFileVersionInfoSizeExA(dwFlags, lpwstrFilename, lpdwHandle);
}

DWORD APIENTRY GetFileVersionInfoSizeExW(_In_ DWORD dwFlags, _In_ LPCWSTR lpwstrFilename, _Out_ LPDWORD lpdwHandle)
{
    return _GetFileVersionInfoSizeExW(dwFlags, lpwstrFilename, lpdwHandle);
}

DWORD APIENTRY GetFileVersionInfoSizeW(_In_ LPCWSTR lptstrFilename, _Out_opt_ LPDWORD lpdwHandle)
{
    return _GetFileVersionInfoSizeW(lptstrFilename, lpdwHandle);
}

BOOL APIENTRY GetFileVersionInfoW(_In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen,
                                  _Out_writes_bytes_(dwLen) LPVOID lpData)
{
    return _GetFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData);
}

DWORD APIENTRY VerFindFileA(_In_ DWORD uFlags, _In_ LPCSTR szFileName, _In_opt_ LPCSTR szWinDir, _In_ LPCSTR szAppDir,
                            _Out_writes_(*puCurDirLen) LPSTR szCurDir, _Inout_ PUINT puCurDirLen,
                            _Out_writes_(*puDestDirLen) LPSTR szDestDir, _Inout_ PUINT puDestDirLen)
{
    return _VerFindFileA(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
}

DWORD APIENTRY VerFindFileW(_In_ DWORD uFlags, _In_ LPCWSTR szFileName, _In_opt_ LPCWSTR szWinDir,
                            _In_ LPCWSTR szAppDir, _Out_writes_(*puCurDirLen) LPWSTR szCurDir,
                            _Inout_ PUINT puCurDirLen, _Out_writes_(*puDestDirLen) LPWSTR szDestDir,
                            _Inout_ PUINT puDestDirLen)
{
    return _VerFindFileW(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
}

DWORD APIENTRY VerInstallFileA(_In_ DWORD uFlags, _In_ LPCSTR szSrcFileName, _In_ LPCSTR szDestFileName,
                               _In_ LPCSTR szSrcDir, _In_ LPCSTR szDestDir, _In_ LPCSTR szCurDir,
                               _Out_writes_(*puTmpFileLen) LPSTR szTmpFile, _Inout_ PUINT puTmpFileLen)
{
    return _VerInstallFileA(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile,
                            puTmpFileLen);
}

DWORD APIENTRY VerInstallFileW(_In_ DWORD uFlags, _In_ LPCWSTR szSrcFileName, _In_ LPCWSTR szDestFileName,
                               _In_ LPCWSTR szSrcDir, _In_ LPCWSTR szDestDir, _In_ LPCWSTR szCurDir,
                               _Out_writes_(*puTmpFileLen) LPWSTR szTmpFile, _Inout_ PUINT puTmpFileLen)
{
    return _VerInstallFileW(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile,
                            puTmpFileLen);
}

DWORD APIENTRY VerLanguageNameA(_In_ DWORD wLang, _Out_writes_(cchLang) LPSTR szLang, _In_ DWORD cchLang)
{
    return _VerLanguageNameA(wLang, szLang, cchLang);
}

DWORD APIENTRY VerLanguageNameW(_In_ DWORD wLang, _Out_writes_(cchLang) LPWSTR szLang, _In_ DWORD cchLang)
{
    return _VerLanguageNameW(wLang, szLang, cchLang);
}

BOOL APIENTRY VerQueryValueA(_In_ LPCVOID pBlock, _In_ LPCSTR lpSubBlock,
                             _Outptr_result_buffer_(_Inexpressible_("buffer can be PWSTR or DWORD*"))
                                 LPVOID* lplpBuffer,
                             _Out_ PUINT puLen)
{
    return _VerQueryValueA(pBlock, lpSubBlock, lplpBuffer, puLen);
}

BOOL APIENTRY VerQueryValueW(_In_ LPCVOID pBlock, _In_ LPCWSTR lpSubBlock,
                             _Outptr_result_buffer_(_Inexpressible_("buffer can be PWSTR or DWORD*"))
                                 LPVOID* lplpBuffer,
                             _Out_ PUINT puLen)
{
    return _VerQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen);
}

bool LoadOriginalDll()
{
    std::filesystem::path versionPath;

    wchar_t* raw = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &raw)))
    {
        return false;
    }

    versionPath = raw;
    CoTaskMemFree(raw);

    constexpr auto VERSION_DLL = "version.dll";
    versionPath /= VERSION_DLL;

    auto handle = LoadLibrary(versionPath.c_str());
    if (!handle)
    {
        return false;
    }

    _GetFileVersionInfoA =
        reinterpret_cast<decltype(_GetFileVersionInfoA)>(GetProcAddress(handle, "GetFileVersionInfoA"));
    _GetFileVersionInfoByHandle =
        reinterpret_cast<decltype(_GetFileVersionInfoByHandle)>(GetProcAddress(handle, "GetFileVersionInfoByHandle"));
    _GetFileVersionInfoExA =
        reinterpret_cast<decltype(_GetFileVersionInfoExA)>(GetProcAddress(handle, "GetFileVersionInfoExA"));
    _GetFileVersionInfoExW =
        reinterpret_cast<decltype(_GetFileVersionInfoExW)>(GetProcAddress(handle, "GetFileVersionInfoExW"));
    _GetFileVersionInfoSizeA =
        reinterpret_cast<decltype(_GetFileVersionInfoSizeA)>(GetProcAddress(handle, "GetFileVersionInfoSizeA"));
    _GetFileVersionInfoSizeExA =
        reinterpret_cast<decltype(_GetFileVersionInfoSizeExA)>(GetProcAddress(handle, "GetFileVersionInfoSizeExA"));
    _GetFileVersionInfoSizeExW =
        reinterpret_cast<decltype(_GetFileVersionInfoSizeExW)>(GetProcAddress(handle, "GetFileVersionInfoSizeExW"));
    _GetFileVersionInfoSizeW =
        reinterpret_cast<decltype(_GetFileVersionInfoSizeW)>(GetProcAddress(handle, "GetFileVersionInfoSizeW"));
    _GetFileVersionInfoW =
        reinterpret_cast<decltype(_GetFileVersionInfoW)>(GetProcAddress(handle, "GetFileVersionInfoW"));
    _VerFindFileA = reinterpret_cast<decltype(_VerFindFileA)>(GetProcAddress(handle, "VerFindFileA"));
    _VerFindFileW = reinterpret_cast<decltype(_VerFindFileW)>(GetProcAddress(handle, "VerFindFileW"));
    _VerInstallFileA = reinterpret_cast<decltype(_VerInstallFileA)>(GetProcAddress(handle, "VerInstallFileA"));
    _VerInstallFileW = reinterpret_cast<decltype(_VerInstallFileW)>(GetProcAddress(handle, "VerInstallFileW"));
    _VerLanguageNameA = reinterpret_cast<decltype(_VerLanguageNameA)>(GetProcAddress(handle, "VerLanguageNameA"));
    _VerLanguageNameW = reinterpret_cast<decltype(_VerLanguageNameW)>(GetProcAddress(handle, "VerLanguageNameW"));
    _VerQueryValueA = reinterpret_cast<decltype(_VerQueryValueA)>(GetProcAddress(handle, "VerQueryValueA"));
    _VerQueryValueW = reinterpret_cast<decltype(_VerQueryValueW)>(GetProcAddress(handle, "VerQueryValueW"));

    return true;
}
