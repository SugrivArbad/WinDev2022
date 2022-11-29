Imports System.Windows.Forms
Imports AutomationServerTypeLibForDotNet

Public Class VBAutomation
    Inherits Form
    Public Sub New()
        Dim objCMyMathClass As New CMyMathClass
        Dim objIMyMath As Object = objCMyMathClass
        Dim num1, num2, sum, subtract As Integer

        num1 = 265
        num2 = 235

        sum = objIMyMath.SumOfTwoIntegers(num1, num2)
        Dim str = String.Format("Sum of {0} and {1} is {2}", num1, num2, sum)
        MsgBox(str)

        subtract = objIMyMath.SubtractionOfTwoIntegers(num1, num2)
        str = String.Format("Subtraction of {0} and {1} is {2}", num1, num2, subtract)
        MsgBox(str)
        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomation())
    End Sub
End Class

