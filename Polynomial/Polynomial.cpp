#include "stdafx.h"
int main()
{
    std::cout << "Input numbers(coef exp),end with 0 -1: " << std::endl;
    List<double> A;
    List<double> B;
    A.Input(std::cin);
    B.Input(std::cin);
    // get two polynomials
    List<double> C((A.getMaxExp() >= B.getMaxExp() ? A : B));
    C.sortExp();
    // the other polynomial
    C.Add((A.getMaxExp() >= B.getMaxExp() ? B : A));
    C.sortExp();
    // output result
    A.Output(std::cout);
    B.Output(std::cout);
    C.Output(std::cout);
    system("pause");
    return 0;
}