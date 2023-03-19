#include <iostream>
#include <memory>
#include <windows.h>

struct tLibraryDeleter
{
  typedef HMODULE pointer;
  void operator()(HMODULE h)
  {
    FreeLibrary(h);
    std::cout << "Released" << std::endl;
  }
};

int main()
{
  {
    auto user32 = std::unique_ptr<HMODULE, tLibraryDeleter>(::LoadLibraryA("user32.dll"));

    typedef int(__stdcall * MessageBoxA_t)(HWND, LPCSTR, LPCSTR, UINT);
    MessageBoxA_t MessageBoxA = reinterpret_cast<MessageBoxA_t>(::GetProcAddress(user32.get(), "MessageBoxA"));

    if (MessageBoxA != NULL)
    {
      //(*MessageBoxA)
      MessageBoxA(NULL, "I'm a MessageBox", "Hello", MB_OK);
    }
  }

  {
    auto shcore = std::unique_ptr<HMODULE, tLibraryDeleter>(::LoadLibraryA("shcore.dll"));

    enum ProcessDpiAwareness
    {
      ProcessDpiUnaware = 0,
      ProcessSystemDpiAware = 1,
      ProcessPerMonitorDpiAware = 2
    };
    typedef HRESULT(__stdcall * SetProcessDpiAwareness_t)(ProcessDpiAwareness);

    SetProcessDpiAwareness_t SetProcessDpiAwareness = reinterpret_cast<SetProcessDpiAwareness_t>(::GetProcAddress(shcore.get(), "SetProcessDpiAwareness"));

    if (SetProcessDpiAwareness != NULL)
    {
      std::cout << ((SetProcessDpiAwareness(ProcessPerMonitorDpiAware) == S_OK) ? "OK" : "NOT OK") << std::endl;
    }
  }

  return 0;
}
