#pragma once

#include "base.h"
#include "structure/math/modulo.h"

#include <vector>
#include <string>

namespace altruct {
namespace math {

/**
 * Prime sieve of Eratosthenes up to `n`
 *
 * Performs Eratosthenes prime sieving and stores the result in the provided
 * arrays. Array `p` contains all the primes up to `n`, whereas array `q`
 * contains flags whether the number at the given index is prime or not. If
 * null pointer is passed for one of those arrays, the corresponding output
 * won't be stored. At least one of `p` or `q` needs to be non-null.
 *
 * If only `p` is specified, `p` needs to be of size at least `n`.
 * If both `p` and `q` are specified, `p` needs to be of size at least `pi(n)`.
 * `q` if specified, needs to be of size at least `n`.
 *
 * Complexity: O(n log log n)
 *
 * @param p - array to store primes up to `n`, or null if not required
 * @param q - array to store prime flags up to `n`, or null if not required
 * @param n - performs sieving for numbers up to `n` (exclusive)
 * @return - number of primes up to `n`
 */
int primes(int *p, char *q, int n);

/**
 * Prime Pi (Number of primes) up to `n`
 *
 * Stores the number of primes up to `i` for each integer `i` less than `n`.
 *
 * Complexity: O(n)
 *
 * @param pi - array to store the number of primes
 * @param n - calculates number of primes up to `n` (exclusive)
 * @param p - array of prime numbers up to `n`
 * @param m - number of prime numbers up to `n`
 */
void prime_pi(int *pi, int n, const int *p, int m);

/**
 * Euler's Phi (Number of coprimes; Totient) up to `n`
 *
 * Stores the number of numbers coprime to `i` up to `i` for each integer `i`
 * less than `n`.
 *
 * Complexity: O(n log log n)
 *
 * @param phi - array to store the number of coprimes
 * @param n - calculate number of coprimes up to `n` (exclusive)
 * @param p - array of prime numbers up to `n`
 * @param m - number of prime numbers up to `n`
 */
void euler_phi(int *phi, int n, const int *p, int m);

/**
 * Moebius Mu (+/-1 if squarefree, 0 otherwise) up to `n`
 *
 * Moebius Mu for each integer `i` is defined as:
 *    0 if `i` is not a square-free positive integer
 *   +1 if `i` is a square-free positive integer with an even number of prime factors
 *   -1 if `i` is a square-free positive integer with an odd number of prime factors
 *
 * Complexity: O(n log log n)
 *
 * @param mu - array to store the result
 * @param n - calculate moebius mu up to `n` (exclusive)
 */
void moebius_mu(int *mu, int n, const int* p = 0, int m = 0);

/**
 * Segmented PrimeQ in range `[b, e)`
 *
 * Stores whether `i` is prime for each integer `i` in range `[b, e)`.
 * Prime numbers up to `sqrt(e)` should be provided. I.e. `p[m-1] >= sqrt(e-1)`.
 *
 * Complexity: O((e - b) log log e)
 *
 * @param q - array to store the result
 * @param b, e - range `[b, e)`
 * @param p - array of prime numbers up to `sqrt(e)`
 * @param m - number of prime numbers up to `sqrt(e)`
 */
void segmented_q(char* q, int64_t b, int64_t e, const int *p, int m);

/**
 * Segmented Euler's Phi (Number of coprimes; Totient) in range `[b, e)`
 *
 * Stores the number of numbers coprime to `i` up to `i` for each integer `i`
 * in range `[b, e)`.
 * Prime numbers up to `sqrt(e)` should be provided. I.e. `p[m-1] >= sqrt(e-1)`.
 *
 * Complexity: O((e - b) log log e)
 *
 * @param phi - array to store the number of coprimes
 * @param tmp - temporary array
 * @param b, e - calculate number of coprimes in range `[b, e)`
 * @param p - array of prime numbers up to `sqrt(e)`
 * @param m - number of prime numbers up to `sqrt(e)`
 */
void segmented_phi(int64_t *phi, int64_t *tmp, int64_t b, int64_t e, const int *p, int m);

/**
 * Segmented Moebius Mu (+/-1 if squarefree, 0 otherwise) in range `[b, e)`
 *
 * Moebius Mu for each integer `i` is defined as:
 *    0 if `i` is not a square-free positive integer
 *   +1 if `i` is a square-free positive integer with an even number of prime factors
 *   -1 if `i` is a square-free positive integer with an odd number of prime factors
 * Prime numbers up to `sqrt(e)` should be provided. I.e. `p[m-1] >= sqrt(e-1)`.
 *
 * Complexity: O((e - b) log log e)
 *
 * @param mu - array to store the result
 * @param b, e - calculate number of coprimes in range `[b, e)`
 * @param p - array of prime numbers up to `sqrt(e)`
 * @param m - number of prime numbers up to `sqrt(e)`
 */
void segmented_mu(int64_t *mu, int64_t b, int64_t e, const int *p, int m);

/**
 * Divisor Sigma 0 (Number of divisors) up to `n`
 *
 * Complexity: O(n log n)
 *
 * @param ds0 - array to store the result
 * @param n - calculate number of divisors up to `n` (exclusive)
 */
void divisor_sigma0(int *ds0, int n);

/**
 * Divisor Sigma 1 (Sum of divisors) up to `n`
 *
 * Complexity: O(n log n)
 *
 * @param ds1 - array to store the result
 * @param n - calculate sum of divisors up to `n` (exclusive)
 */
void divisor_sigma1(int64_t *ds1, int n);

/**
 * Biggest prime factor for integers up to `n`
 *
 * Sotres the biggest prime factor for integers up to n to the array `bpf`.
 * Output array `bpf` needs to be of size `n`.
 *
 * Complexity: O(n log log n)
 *
 * @param bpf - array to store the biggest prime factors for integers up to `n`
 * @param n - factors numbers up to `n` (exclusive)
 * @param p - array of prime numbers up to `n`
 * @param m - number of prime numbers up to `n`
 */
void factor(int *bpf, int n, const int *p, int m);

/**
 * Prime factorization of integer `n`
 *
 * Stores the prime factors and their exponents to the map `mf`. This
 * function requires a prime factors array for integers up to `n` inclusive
 * to be provided. That array can be precalculated with the `factor` function.
 *
 * Complexity: O(log n / log log n)
 *
 * @param mf - map to store prime factors and the corresponding exponents
 * @param n - integer to factor
 * @param pf - array of prime factors for integers up to `n` inclusive
 */
template<typename M>
void factor_integer_to_map(M &mf, int n, const int *pf) {
    while (n > 1) {
        int p = pf[n], e = 0;
        while (n % p == 0) {
            n /= p, e++;
        }
        mf[p] += e;
    }
}

/**
 * Prime factorization of integer `n`
 *
 * Stores the prime factors and their exponents to the vector `vf`. This
 * function requires a prime factors array for integers up to `n` inclusive
 * to be provided. That array can be precalculated with the `factor` function.
 *
 * Complexity: O(log n / log log n)
 *
 * @param vf - vector to store prime factors and the corresponding exponents
 * @param n - integer to factor
 * @param pf - array of prime factors for integers up to `n` inclusive
 */
void factor_integer(std::vector<std::pair<int, int>> &vf, int n, const int *pf);

/**
 * Prime factorization of the product of integers `vn`
 *
 * Stores the prime factors and their exponents to the vector `vf`. This
 * function requires a prime factors array for integers up to `n` inclusive
 * to be provided, where `n` is the largest element in `vn`. That array can
 * be precalculated with the `factor` function.
 *
 * Complexity: O(k log n / log log n)
 *
 * @param vf - vector to store prime factors and the corresponding exponents
 * @param vn - integers whose product to factor
 * @param pf - array of prime factors for integers up to `n` inclusive
 */
void factor_integer(std::vector<std::pair<int, int>> &vf, std::vector<int> vn, const int *pf);

/**
 * Calculates divisors from a factorization.
 *
 * Stores the divisors to the vector `vd`. Only divisors up to `maxd` are stored.
 *
 * @param vd - vector to store divisors
 * @param vf - prime factorization of the original number
 * @param maxd - maximum divisor to store, 0 for all divisors
 * @param d - reserved
 * @param i - reserved
 */
template<typename D, typename P>
void divisors(std::vector<D> &vd, const std::vector<std::pair<P, int>> &vf, D maxd = 0, D d = 1, int i = 0) {
	if (i >= (int)vf.size()) {
		vd.push_back(d);
		return;
	}
	const auto &f = vf[i];
	for (int e = 0; e <= f.second; e++) {
		divisors(vd, vf, maxd, d, i + 1);
		if (maxd > 0 && d > maxd / f.first) break;
		d *= f.first;
	}
}

/**
 * Extracts prime factors from a factorization.
 *
 * Extracts the first element `p` of each pair `(p, e)`.
 */
template<typename P>
std::vector<P> prime_factors(const std::vector<std::pair<P, int>> &vf) {
	std::vector<P> vp;
	vp.reserve(vf.size());
	for (const auto& f : vf) {
		vp.push_back(f.first);
	}
	return vp;
}

/**
* Extracts prime exponents from a factorization.
*
* Extracts the second element `e` of each pair `(p, e)`.
*/
template<typename P>
std::vector<int> prime_exponents(const std::vector<std::pair<P, int>> &vf) {
	std::vector<int> ve;
	ve.reserve(vf.size());
	for (const auto& f : vf) {
		ve.push_back(f.second);
	}
	return ve;
}

/**
 * Calculates number of divisors from a factorization.
 */
template<typename P>
int divisor_sigma0(const std::vector<std::pair<P, int>> &vf) {
	int r = 1;
	for (const auto& f : vf) {
		r *= f.second + 1;
	}
	return r;
}

/**
 * Calculates Euler Phi from a factorization.
 */
template<typename P>
P euler_phi(const std::vector<std::pair<P, int>> &vf) {
	P r = 1;
	for (const auto& f : vf) {
		r *= powT(f.first, f.second - 1) * (f.first - 1);
	}
	return r;
}

/**
 * Calculates Carmichael Lambda from a factorization.
 */
template<typename P>
P carmichael_lambda(const std::vector<std::pair<P, int>> &vf) {
	P r = 1;
	for (const auto& f : vf) {
		int e = (f.first == 2 && f.second > 2) ? f.second - 1 : f.second;
		r = lcm<P>(r, powT(f.first, e - 1) * (f.first - 1));
	}
	return r;
}

/**
 * Calculates the number of representations of n as a sum of 2 squares from a factorization of `n`.
 *
 * E.g. some unique representations:
 *   4 = 0^2 + 2^2
 *   5 = 1^2 + 2^2
 *   8 = 2^2 + 2^2
 *   25 = 3^2 + 4^2 = 0^2 + 5^2
 *
 * @param unique_only - if true, the sign and order won't be taken into account
 *                      i.e. (1, 2) is considered the same as (-2, -1)
 */
template<typename P>
P squares_r(const std::vector<std::pair<P, int>> &vf, bool unique_only) {
	P B = 1; int s = 1, q = 1;
	for (const auto& f : vf) {
		if (f.first % 4 == 1) {
			B *= f.second + 1;
		} else if (f.first % 4 == 3) {
			if (f.second % 2 == 1) B = 0;
		} else if (f.first == 2) {
			if (f.second % 2 == 1) s = -1;
		}
		if (f.second % 2 == 1) q = 0;
	}
	if (!unique_only) return B * 4;
	if (B % 2 == 1) B -= s;
	return B / 2 + q;
}

/**
 * Miller-Rabin primality test.
 *
 * Probabilistic primality test with accuracy `4^-k`, where `k` is the number of bases tested.
 *
 * Complexity: O(p^(1/2)) <= O(n^(1/4)), where `p` is the smallest prime factor of `n`.
 *
 * @param n - number to test for primality
 * @param bases - a null-terminated array of bases to test against.
 * @return - true means `n` is probably prime, false means `n` is certainly composite.
 */
template<typename T>
bool miller_rabin(const T& n, const T* bases) {
	if (n == 0 || n == 1) return 0;
	if (n == 2 || n == 3) return 1;
	if ((n % 2) == 0) return 0;
	typedef moduloX<T> modx;
	T d = n - 1; int r = 0; // n-1 = 2^r * d
	while (d % 2 == 0) d /= 2, r++;
	for (int i = 0; bases[i] && bases[i] < n; i++) {
		modx x = powT(modx(bases[i], n), d);
		if (x == 1 || x == n - 1) continue;
		for (int i = 1; i < r; i++) {
			x *= x;
			if (x == 1 || x == n - 1) break;
		}
		if (x != n - 1) return false; // composite
	}
	return true; // probably prime
}

/**
 * Miller-Rabin primality test.
 *
 * Selects the appropriate bases based on the input size so that the test is
 * deterministic. See `miller_rabin` above.
 */
template<typename T>
bool miller_rabin(const T& n) {
	// 10^3, 2^10
	static T bases1[] = { 2, 0 };
	if (n < 2047) return miller_rabin(n, bases1);
	// 10^6, 2^23
	static T bases2[] = { 31, 73, 0 };
	if (n < 9080191) return miller_rabin(n, bases2);
	// 10^9, 2^32
	static T bases3[] = { 2, 7, 61, 0 };
	if (n < 4759123141LL) return miller_rabin(n, bases3);
	// 10^12, 2^40
	static T bases4[] = { 2, 13, 23, 1662803, 0 };
	if (n < 1122004669633LL) return miller_rabin(n, bases4);
	// 10^15, 2^48
	static T bases7[] = { 2, 3, 5, 7, 11, 13, 17, 0 };
	if (n < 341550071728321LL) return miller_rabin(n, bases7);
	// 10^18, 2^61
	static T bases9[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 0 };
	if (n < 3825123056546413051LL) return miller_rabin(n, bases9);
	// fallback to bases9 for larger numbers too
	return miller_rabin(n, bases9);
}

/**
 * Pollard's Rho factorization algorithm.
 *
 * Attempts to find a non-trivial, not necessarily prime factor of `n`.
 *
 * Before running this algorithm one should make sure that `n` is not a prime.
 * See the `miller_rabin` primality test above.
 *
 * In case the factorization fails (returned value is same as the input value `n`),
 * one should try with different `k` and `a`. See `pollard_rho_repeated` below.
 *
 * Complexity: O(p^(1/2)) <= O(n^(1/4)), where `p` is the smallest prime factor of `n`.
 *
 * @param n - number to factor
 * @param k - initial value
 * @param a - parameter of the polynomial g(x) = x^2 + a
 * @param max_inner_iter - maximum allowed number of iterations
 * @return d - a nontrivial factor of `n`, or `n` if factorization failed
 */
template<typename I>
I pollard_rho(const I& n, const I& k = 2, const I& a = 1, I max_inner_iter = 1000000) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n % 2 == 0) return 2;
	typedef moduloX<I> modx;
	auto g = [a](const modx& x){ return x*x + a; };
	modx x = modx(k, n), y = modx(k, n); I d = 1;
	while (d == 1 && max_inner_iter-- > 0) {
		x = g(x);
		y = g(g(y));
		d = gcd(absT((x - y).v), n);
	}
	return (d == 1) ? n : d;
}

/**
 * Pollard's Rho factorization algorithm.
 *
 * Pollard's Rho algorithm applied iteratively with `k` and `a` being increased in each iteration.
 * By trying different `k` and `a` parameters, the algorithm significantly reduces a chance of
 * factorization failure.
 */
template<typename I>
I pollard_rho_repeated(const I& n, const I& max_iter = 20, const I& max_inner_iter = 1000000) {
	for (I k = 2; k <= max_iter; k++) {
		I d = pollard_rho(n, k, k, max_inner_iter);
		if (d != n) return d;
	}
	return n;
}

/**
 * Factors integer `n` using a general-purpose factoring algorithm.
 */
template<typename I>
std::vector<std::pair<I, int>> factor_integer(const I& n, int max_iter = 20) {
	std::vector<std::pair<I, int>> vf;
	if (n == 0 || n == 1) return vf;
	std::vector<I> q = { n };
	while (!q.empty()) {
		I a = q.back(); q.pop_back();
		if (a == 1) {
			continue;
		}
		if (miller_rabin<I>(a)) {
			// a prime factor found
			int e = 1;
			for (auto& b : q) {
				while (b % a == 0) b /= a, e++;
			}
			vf.push_back({ a, e });
			continue;
		}
		// `a` is composite
		I d = pollard_rho_repeated<I>(a, max_iter);
		if (d == 1 || d == a) {
			// failed to factor the composite
			vf.push_back({ a, 1 });
			continue;
		}
		// a non-trivial factorization `a = d * e`
		q.push_back(d);
		q.push_back(a / d);
	}
	return vf;
}

/**
 * Factors integer `n` by trial division.
 */
template<typename I>
std::vector<std::pair<I, int>> factor_integer_slow(I n) {
	std::vector<std::pair<I, int>> vf;
	for (I i = 2; i <= n / i; i += 1) {
		if (n % i != 0) continue;
		int e = 0; while (n % i == 0) n /= i, e++;
		vf.push_back({ i, e });
	}
	if (n > 1) vf.push_back({ n, 1 });
	return vf;
}

/**
 * Factors out all factors `p` out of `n`.
 */
template<typename I, typename P>
I factor_out(I n, P p) {
    while (n % p == 0) n /= p;
    return n;
}

/**
 * Jointly reduces the given lists of numerators and denominators.
 *
 *    n     n_0 * ... * n_l1
 *   --- = ------------------
 *    d     d_0 * ... * d_l2
 */
template<typename I, typename P, typename G>
void fraction_reduce(std::vector<I>& numerators, std::vector<P>& denominators, G gcd) {
    for (auto& d : denominators) {
        for (size_t i = 0; d > 1 && i < numerators.size();) {
            auto g = gcd(numerators[i], d);
            if (g > 1) {
                d /= g, numerators[i] /= g;
            } else {
                i++;
            }
        }
    }
}

/**
 * Gives the vector of digits of `n` in base `b`.
 *
 * @param n - number to extract the digits of
 * @param b - base
 * @param len - zeros are added if necessary to fill the `len` digits
 */
template<typename I, typename B>
std::vector<B> integer_digits(const I& n, const B& b, int len = 0) {
	std::vector<B> vd;
	for (I t = n; t > 0; t /= b) {
		vd.push_back(castOf<B, I>(t % b));
	}
    while ((int)vd.size() < len) {
		vd.push_back(0);
	}
	return vd;
}

/**
 * Converts the vector of digits to a lowercase string.
 * Only bases up to 36 are supported.
 */
template<typename B>
std::string integer_string(const std::vector<B>& digits) {
    static char* c = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::string s;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        s += c[*it];
    }
    return s;
}

/**
 * Gives the string representation of `n` in base `b`.
 *
 * @param n - number to extract the digits of
 * @param b - base up to 36
 * @param len - zeros are added if necessary to fill the `len` digits
 */
template<typename I, typename B>
std::string integer_string(const I& n, const B& b, int len = 0) {
    return integer_string(integer_digits(n, b, len));
}

} // math
} // altruct
