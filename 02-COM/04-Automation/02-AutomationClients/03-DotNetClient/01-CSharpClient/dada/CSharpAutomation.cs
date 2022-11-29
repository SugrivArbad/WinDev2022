using System;

public class program
{
    public static void Main()
    {
        try
        {
            string param = null;
            if (param == null)
            {
                throw new ArgumentNullException(param.ToString());
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex);
        }
    }
}
