using System;
using System.Windows.Forms;
using System.Drawing;

public class CSharpWindow : Form
{
    public static void Main()
    {
        Application.Run(new CSharpWindow());
    }

    public CSharpWindow()
    {
        Icon = new Icon("MyIcon.ico");
        Text = "MyCSharpWindow";    // 2nd pararmeter of messagebox
        BackColor = Color.Black;    //System.Color.Drawing.Black;
        ResizeRedraw = true;
        Width = 800;
        Height = 600;

        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);
    }

    protected override void OnPaint(PaintEventArgs pea)     // case WM_PAINT (WPARAM, LPARAM)
    {
        Graphics grfx = pea.Graphics;       // hdc

        StringFormat strFmt = new StringFormat();
        strFmt.Alignment = StringAlignment.Center;       // horizontal center
        strFmt.LineAlignment = StringAlignment.Center;   // vertical center

        grfx.DrawString("Hello World!!!",   // DrawText
            Font,
            new SolidBrush(Color.Green),
            ClientRectangle,
            strFmt);
    }

    void MyKeyDown(object sender, KeyEventArgs e)
    {
        MessageBox.Show("A key is pressed");
    }

    void MyMouseDown(object sender, MouseEventArgs e)
    {
        MessageBox.Show("Mouse is clicked");
    }
}

/*
    C:\Sugriv\WinDev2022\03-DotNet\04-Window\01-Window> csc.exe /t:winexe CSharpWindow.cs
*/

