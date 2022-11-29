
using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    [DllImport("user32.dll")]
    public static extern int MessageBoxA(int handle, String message, String caption, int type);

    public static void Main()
    {
        MessageBoxA(0, "This is ANSI message box", "Message", 0);
        MessageBoxA(0, "This is ANSI message box", "Message", 1);
        MessageBoxA(0, "This is ANSI message box", "Message", 2);
        MessageBoxA(0, "This is ANSI message box", "Message", 3);
        MessageBoxA(0, "This is ANSI message box", "Message", 4);
    }
}


/*
    C:\Sugriv\WinDev2022\03-DotNet\03-PInvoke\02-Win32DllWin32Function\01-ANSI>csc PInvoke.cs 
*/

