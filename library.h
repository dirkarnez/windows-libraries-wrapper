



#include <iostream>
#include <memory>
#include <windows.h>

struct tLibraryDeleter
{
  typedef HMODULE pointer;
  void operator()(HMODULE h) { FreeLibrary(h); std::cout << "yoyoyooy"<< std::endl; }
};

/*
int main() {
     auto a =  std::unique_ptr<HMODULE, tLibraryDeleter>(::LoadLibraryA("kernel32.dll"));
    //
    return 0;
}
*/
