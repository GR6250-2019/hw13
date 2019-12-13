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

	inline size_t pwlinear_coef(const X& a, size_t n, const X* x, const X* y, X* f)
	{
		int i;
		int loc=0;
		for (i = 0;i < n-1;i++) {
			loc = 0;
			if (x[i] < a && a < x[i + 1]) {
				loc = i;
			}
			else if (x[i] == a) {
				loc = i;
			}
		}
		f[n - 1] = (y[loc] - y[loc + 1]) / (x[loc] - x[loc + 1]);
		f[0] = y[loc] - f[n - 1] * (x[loc] - a);
		
		X tempds = 0;
		X diff = 0;
		for (i = loc;i > 0;i--) {
			tempds = 0;
			diff = x[i - 1] - x[i];
			
			for (int j = i+1;j <= loc; j++) {
				tempds += f[j] *diff;
			}
			f[i] = ((y[i] - y[i - 1]) - f[n - 1] * (-diff) - tempds) / diff;
		}

		for (i = loc+1; i < n-1; i++) {
			tempds = 0;
			diff = x[i + 1] - x[i];

			for (int j = i - 1;j >= loc+1; j--) {
				tempds += f[j] * diff;
			}
			f[i] = ((y[i+1] - y[i]) - f[n - 1] * diff - tempds) / diff;
		}
	
		return loc;
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
		X result = 0;
		for (int j = 0;j < n-1;j++) {
			if (j == 0) {
				result += f[0];
			}
			else if(j<i) {
				result += f[j] * p[j];
			}
			else if (j > i) {
				result += f[j] * c[j];
			}
			
		}
		return result; //!!! implement
	}
}
