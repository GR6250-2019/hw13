// pwlinear.h - Fit a piecewise linear curve.
#pragma once
#include<cmath>
using namespace std;

namespace fms {

	// Given a p.w. linear curve find the Carr-Madan coefficients.
	// Curve is determined by the points (x[i], y[i]), 0 <= i < n.
	// Array f is filled with (f(a), f''(x[1]) ... f''(x[n-2]), f'(a))
	// f(x) = f(a) 
	//        + sum_{i > 0, x[i] < a} f''(x[i]) max{x[i] - x, 0}
	//        + sum_{i < n-1, x[i] > a} f''(x[i]) max{x - x[i], 0}
	//        + f'(a)(x - a).
	// Return i such that x[i] < a < x[i+1]
	template<class X = double>
	inline size_t pwlinear_coefficients(const X& a, size_t n, const X* x, const X* y, X* f)
	{
		//!!! implement
		int a_fl = 0;
		for (int i = 1; x[i] < a; i++) {
			a_fl++;
		}

		//x[a_fl]< a <x[a_fl+1]

		//y[a_fl]=f(a)+f'(a)(x[a_fl]-a)
		//y[a_fl+1]=f(a)+f'(a)(x[a_fl+1]-a)
		//because both of the sum are 0 in when taking y[a_fl] and y[a_cl]

		f[n - 1] = (y[a_fl + 1] - y[a_fl]) / (x[a_fl + 1] - x[a_fl]);//f'(a) based on the formula when f(a
		f[0] = y[a_fl] - f[n - 1] * (x[a_fl] - a);//f(a)=f(x)-f'(a)(x-a)

		X sum_11;
		X sum_12;

		for (int i = a_fl - 1; i >= 0; i--) {
			sum_11 = f[0] + f[n - 1] * (x[i] - a);
			sum_12 = 0;
			for (int j = i + 1; j < a_fl + 1; j++) {
				sum_12 += f[j] * (x[j] - x[i]);
			}

			f[i + 1] = (y[i] - sum_11 - sum_12) / (x[i + 1] - x[i]);
		}
		X sum_21;
		X sum_22;
		for (int i = a_fl + 2; i < n - 1; i++) {
			sum_21 = f[0] + f[n - 1] * (x[i] - a);
			sum_22 = 0;
			for (int j = i - 1; j > a_fl; j--) {
				sum_22 += f[j] * (x[i] - x[j]);
			}
			f[i - 1] = (y[i] - sum_21 - sum_22) / (x[i] - x[i - 1]);

		}
		return a_fl;
	}

	// Expected value of payoff.
	// E[f(X)] = f(a) + f'(a)(E[X] - a) 
	//           + sum_{x[i] < a} f''(x[i]) p[i]
	//           + sum_{a < x[i]} f''(x[i]) c[i].
	// The array f[] contains the coefficents from the function above.
	// Assume E[X] = a so the second term is 0.
	template<class X = double>
	inline X pwlinear_value(size_t n, const X* f, size_t i, const X* p, const X* c)
	{
		double value = f[0];
		for (size_t j = 0; j < i; j++) {
			value += f[j] * p[j];
		}
		for (size_t j = i; j < n - 1; j++) {
			value += f[j] * c[j];
		}
		return 0; //!!! implement

	}
}

