using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
    public static void Main()
    {
        // code
        // RCW - runtime callable wrapper  
        // CMyMathClass is a wrapper around CMyMath to DotNet understandable
        CMyMathClass objCMyMathClass = new CMyMathClass(); // tlbimp is DotNet utility
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;
        int num1, num2, sum, subtract;

        num1 = 165;
        num2 = 135;

        sum = objIMyMath.SumOfTwoIntegers(num1, num2); // midl ne 3rd parameter baher kadhala ani ikade .Net ne to sum madhe ghetla
        Console.WriteLine("Sum of " + num1 + " and " + num2 + " is " + sum);

        subtract = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Subtraction of " + num1 + " and " + num2 + " is " + subtract);
    }
}

