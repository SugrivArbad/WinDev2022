using System;
using System.Windows.Forms;

public class CSharpWindow : Form
{
    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }

    public CSharpWindow()
    {
        Text = "MyCSharpWindow";    // 2nd pararmeter of messagebox
        BackColor = System.Drawing.Color.Black;    //System.Color.Drawing.Black;
        ResizeRedraw = true;
    }
}

/*
    C:\Sugriv\WinDev2022\03-DotNet\04-Window\01-Window> csc.exe /t:winexe CSharpWindow.cs
*/

