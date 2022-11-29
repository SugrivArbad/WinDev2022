
using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    [DllImport("user32.dll", CharSet = CharSet.Unicode)]    // entrypoint attribute
    public static extern int MessageBoxW(int handle, String message, String caption, int type);

    public static void Main()
    {
        MessageBoxW(0, "This is Unicode message box", "Message", 0);
        //MessageBoxW(0, "This is Unicode message box", "Message", 1);
        //MessageBoxW(0, "This is Unicode message box", "Message", 2);
        //MessageBoxW(0, "This is Unicode message box", "Message", 3);
        //MessageBoxW(0, "This is Unicode message box", "Message", 4);
    }
}


/*
    C:\Sugriv\WinDev2022\03-DotNet\03-PInvoke\02-Win32DllWin32Function\01-ANSI>csc PInvoke.cs 
*/

