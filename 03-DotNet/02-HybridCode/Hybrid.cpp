/*
    C:\Sugriv\WinDev2022\03-DotNet\02-HybridCode>cl.exe /clr Hybrid.cpp
    // /clr switch - safe and unsafe

    this /clr support is from version 13 and above compiler cl.exe
*/

#include <stdio.h>
#using <MSCorLib.dll>
using namespace System;

int main(void)
{
    printf("This line is from native cpp\n");
    Console::WriteLine("This line is from DotNet managed cpp");

    return 0;
}

