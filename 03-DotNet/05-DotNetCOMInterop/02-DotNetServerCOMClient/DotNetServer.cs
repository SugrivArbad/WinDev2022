using System;

public class DotNetServer
{
    public int SumOfTwoIntegers(int num1, int num2)
    {
        return (num1 + num2);
    }

    public int SubtractionTwoIntegers(int num1, int num2)
    {
        return (num1 - num2);
    }
}

/*
C:\Sugriv\WinDev2022\03-DotNet\05-DotNetCOMInterop\02-DotNetServerCOMClient>csc.exe /t:library DotNetServer.cs


C:\Sugriv\WinDev2022\03-DotNet\05-DotNetCOMInterop\02-DotNetServerCOMClient>ildasm /adv DotNetServer.dll
    view->metadata->show


// run as administrator
C:\Sugriv\WinDev2022\03-DotNet\05-DotNetCOMInterop\02-DotNetServerCOMClient>regasm.exe DotNetServer.dll /tlb
Microsoft .NET Framework Assembly Registration Utility version 4.8.4084.0
for Microsoft .NET Framework version 4.8.4084.0
Copyright (C) Microsoft Corporation.  All rights reserved.

Types registered successfully
Assembly exported to 'C:\Sugriv\WinDev2022\03-DotNet\05-DotNetCOMInterop\02-DotNetServerCOMClient\DotNetServer.tlb', and the type library was registered successfully


// run as administrator
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\oleview.exe"

*/

