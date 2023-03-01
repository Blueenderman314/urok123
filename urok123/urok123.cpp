#include <iostream>
#include "Postfix_calc.h"

using namespace std;

int main()
{
    string asdf = "5555 + 41 - 678";
    Postfix_calc calc;
    calc.start(asdf);
    calc.get_result();
}