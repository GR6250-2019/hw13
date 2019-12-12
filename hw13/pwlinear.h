// pwlinear.h - Fit a piecewise linear curve.
#pragma once

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
		//start with i such that x[i] < a < x[i+1]

		size_t xhat=0; 
		int i;
		for (i = 0; (size_t)i <n-1 ; i++) {
			if (x[i] < a && x[i + 1]>a) {
				xhat = i;
			}
			else if (x[i] == a) {
				xhat = i;
			}
		}

		X fppsum;
		int j;
		//start from xhat and go to zero to find double
		//derivates
		X fpa = (y[xhat] - y[xhat + 1]) / (x[xhat + 1] - x[xhat]);
		X fa = y[xhat] - fpa * (x[xhat] - a);
		X tempsum;
		for (i = xhat-1; i >=0; i--) {
			tempsum = fpa * (x[i] - a) + fa;
			fppsum = 0;
			for (j = i+1; (size_t)j < xhat; j++) {
				fppsum += f[j ] * (x[j] - x[i]);
			}
			f[i + 1] = (y[i] - tempsum - fppsum) / (x[i + 1] - x[i]);
		}

		//start from xhat +1 and go to n to find double
		//derivates
		for (i = xhat +2; (size_t)i <=n-1 ; i++) {
			tempsum = fpa * (x[i] - a) + fa;
			fppsum = 0;
			for (j = i-1; (size_t)j > xhat+1; j--) {
				fppsum += f[j] * (x[i] - x[j]);
			}
			f[i -1] = (y[i] - tempsum - fppsum) / (x[i ] - x[i-1]);
		}
		f[0] = fa;
		f[n - 1] = fpa;
		return xhat;
	}

	// Expected value of payoff.
	// E[f(X)] = f(a) + f'(a)(E[X] - a) 
	//           + sum_{x[i] < a} f''(x[i]) p[i]
	//           + sum_{a < x[i]} f''(x[i]) c[i].
	// The array f[] contains the coefficents from the function above.
	// Assume E[X] = a so the second term is 0.
	// Array f is filled with (f(a), f''(x[1]) ... f''(x[n-2]), f'(a))

	template<class X = double>
	inline X pwlinear_value(size_t n, const X* f, size_t i, const X* p, const X* c)
	{
		X ev = f[0];
		int j;
		for (j = 0; (size_t)j < n-1; j++) {
			if ((size_t)j < i) {
				ev += f[j] * p[j];
			}
			else if ((size_t)j > i) {
				ev += f[j] * c[j];
			}
		}
		return ev;
		
	}
}
