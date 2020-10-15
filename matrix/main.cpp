#include <iostream>
#include "TMatrix.h"

int main()
{
    TMatrix<int> mtr(2);
    mtr(1,1) = 5;


    TMatrix<int> mtr2(2);
    mtr2 = mtr;


    std::cout<<mtr2<<std::endl;

    return 0;
}
