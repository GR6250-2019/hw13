// xllproject.cpp
#include <cmath>
#include "pwlinear.h"
#include "hw13.h"

using namespace fms;
using namespace xll;

AddIn xai_project(
    Document(L"hw13")
    .Documentation(
        L"This will generate a Sandcastle Helpfile Builder project file. "
        L"Start Excel with the add-in loaded and run (Alt-F8) the macro MAKE.SHFB. "
    )
);

AddIn xai_xllproject(
    Document(CATEGORY)
    .Category(CATEGORY)
    .Documentation(
        L"Documentation for the " CATEGORY L" category. "
        L"</para>"
        L"The function XLL.PWLINEAR.VALUE(x, y, f, p, c) computes the value "
        L"of a piecwise linear payoff determinded by x and y "
        L"using put prices (x &lt; f) and call prices (x &gt; f). "
        L"<para>"
        L"We assume f is the par forward value of the underlying. "
    )
);

//!!! Implement XLL.PWLINEAR.VALUE as described above.
AddIn xai_pwlinear_value(
    Function(XLL_DOUBLE, L"?xll_pwlinear_value", CATEGORY L".PWLINEAR.VALUE")
    .Arg(XLL_FP, L"x", L"are an array of x-values. ")
    .Arg(XLL_FP, L"y", L"is an array of y-values. ")
    .Arg(XLL_DOUBLE, L"f", L"is the put-call seperator. ")
    .Arg(XLL_FP, L"p", L"are an array of put prices. ")
    .Arg(XLL_FP, L"c", L"is an array of call prices. ")
    .Category(CATEGORY)
    .FunctionHelp(L"Return value of a piecewise linear payoff using put and call prices.")
    .Documentation(L"Clever documentation goes here." )
);
double WINAPI xll_pwlinear_value(_FP12* px, _FP12* py, double f, _FP12* pp, _FP12* pc)
{
#pragma XLLEXPORT
    double value = std::numeric_limits<double>::epsilon();

    try {
        auto n = size(*px);
        ensure(n == size(*py));
        ensure(n == size(*pp));
        ensure(n == size(*pc));
        std::vector<double> F(n);
        
        auto i = pwlinear_coefficients(f, n, px->array, py->array, &F[0]);
        value = pwlinear_value(n, &F[0], i, pp->array, pc->array);
    }
    catch (const std::exception & ex) {
        XLL_ERROR(ex.what());
    }

    return value;
}

#ifdef _DEBUG

test test_pwlinear_value([] {
    // !!!put tests here!!!

    });

#endif