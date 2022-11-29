#pragma once
#include <Windows.h>
#include <iostream>
#include "..\\..\\MyCom.hpp"
#include "MyClassFactoryServer.h"

int main(void)
{
    ISum* pISum = NULL;
    ISubtract* pISubtract = NULL;
    int n1, n2, sum, subtract;
    HRESULT hr;

    std::cout << std::endl << "*********************************************"
              << std::endl << std::endl;

    std::cout << "  My Factory pattern implementation :"
              << std::endl << std::endl;

    hr = MyCoCreateInstance(CLSID_SumSubtract, NULL, IID_ISum, (void**)&pISum);
    if (FAILED(hr))
    {
        std::cerr << "Error : ISum interface cannot be obtained" << std::endl << std::endl;
        return EXIT_FAILURE;
    }

    n1 = 55;
    n2 = 45;
    pISum->SumOfTwoIntegers(n1, n2, &sum);

    std::cout << "\t" << n1 << " + " << n2 << " = " << sum << std::endl << std::endl;

    pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
    if (FAILED(hr))
    {
        std::cerr << "Error : ISubtract interface cannot be obtained" << std::endl << std::endl;
        return EXIT_FAILURE;
    }

    pISubtract->SubtractionOfTwoIntegers(n1, n2, &subtract);

    std::cout << "\t" << n1 << " - " << n2 << " = " << subtract << std::endl << std::endl;

    std::cout << "*********************************************" << std::endl << std::endl;

    if (pISum)
    {
        delete pISum;
        pISum = 0;
    }

    if (pISubtract)
    {
        delete pISubtract;
        pISubtract = 0;
    }
}

