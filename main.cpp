#if 1
#include <string>
#include <cassert>
#include <system_error>
#include <memory>

#include "window.h"
#include "button.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main() {
    using namespace std::string_literals;

    auto window = std::make_unique<window_t>(u8"Window"s, 500, 200);
    auto window2 = std::make_unique<window_t>(u8"Window2"s, 500, 200);
    //auto button = std::make_unique<button_t>(1, u8"Text"s, 3, 3, 280, 100, *window);
    //auto button2 = std::make_unique<button_t>(1, u8"Text2"s, 10, 3, 280, 100, *window2);

    window->thread().join();
    window2->thread().join();

    return 0;
}
#else
#include <pshpck16.h>
#include <poppack.h>

#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>
#include <cassert>
#include <type_traits>
#include <unordered_map>
#include <mutex>
#include <filesystem>

#include <Windows.h>
#include <ShlObj.h>
#include <delayimp.h>
#include <winternl.h>

namespace delay_load {
    auto system_path() {
        std::experimental::filesystem::path path;
        wchar_t* buffer;
        assert(SHGetKnownFolderPath(FOLDERID_System, KF_FLAG_DEFAULT, nullptr, &buffer) == S_OK);
        path = buffer;
        CoTaskMemFree(buffer);
        return path;
    }

    template<class T> struct func {
        T* function;

        func(std::experimental::filesystem::path path, std::string name) {
            HMODULE library = ::LoadLibraryW(path.wstring().c_str());
            assert(library != nullptr);
            function = reinterpret_cast<T*>(::GetProcAddress(library, name.c_str()));
            assert(function != nullptr);
        }

        template<class... A> auto operator()(A... args) {
            return function(args...);
        }
    };
}

extern "C" int __stdcall WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData) {
    static delay_load::func<decltype(WSAStartup)> function{ delay_load::system_path() / "Ws2_32.dll", __func__ };
    return function(wVersionRequired, lpWSAData);
}

extern "C" NTSTATUS __stdcall NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength) {
    static delay_load::func<decltype(NtQuerySystemInformation)> function{ delay_load::system_path() / "Ntdll.dll", __func__ };
    return function(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}

extern "C" NTSTATUS __stdcall NtClose(HANDLE Handle) {
    static delay_load::func<decltype(NtClose)> function{ delay_load::system_path() / "Ntdll.dll", __func__ };
    return function(Handle);
}

int main() {
    {
        WSADATA data;
        auto e = WSAStartup(MAKEWORD(2, 2), &data);
        data = {};
        e = WSAStartup(MAKEWORD(2, 2), &data);
    }

    {
        SYSTEM_BASIC_INFORMATION info{};
        auto e = NtQuerySystemInformation(SystemBasicInformation, &info, sizeof(info), nullptr);
        e = NtClose(nullptr);
        e = {};
    }

    {
        SYSTEM_INFO info{};
        GetNativeSystemInfo(&info);
        info = {};
    }

    auto s = typeid(GetLastError).raw_name();
    s = typeid(GetLastError).name();

    return 0;
}
#endif
