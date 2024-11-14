#include "math.h"

int abs(int x) {
    return x >= 0 ? x : -x;
}


long double acos(double x) {
    long double result = S21_NAN;
    if (x>= -1 && x <= 1) {
        result = S21_PI / 2 - asin(x);
    }
    return result;
}


static const double ASIN_EPS = 1e-16l;

long double asin_x_0_05(double x) {
    int i = 3;
    double numerator = x;
    double div_result = 1;
    double result = x;
    double divisor = 1;

    do {
        divisor *= i - 1;
        numerator *= x * x * (i - 2);
        div_result = numerator / (divisor * i);
        result += div_result;
        i += 2;
    } while (div_result > ASIN_EPS);
    return result;
}

long double asin(double x) {
    long double result;

    if (x >= -1 - ASIN_EPS && x <= 1 + ASIN_EPS) {
        int sign;
        if (x >= 0) {
            sign = 1;
        } else {
            x *= -1;
            sign = -1;
        }
        if (x < 0.5) {
            result = asin_x_0_05(x);
        } else {
            result = S21_PI / 2 - 2 * asin_x_0_05(pow((1 - x) / 2, 0.5));
        }
        result *= sign;
    } else {
        result = S21_NAN;
    }
    return result;
}


long double atan(double x) {
    long double result = S21_NAN;
    int sign;

    if (x >= 0) {
        sign = 1;
    } else {
        x *= -1;
        sign = -1;
    }

    if (!is_nan(x)) {
        if (!is_inf(x) && x < 1e7) {
            result = asin(x / pow(1 + x * x, 0.5)) * sign;
        } else {
            result = S21_PI / 2 * sign;
        }
    }

    return result;
}

#include <string.h>

long double ceil(double x) {
    long unsigned input;
    memcpy(&input, &x, 8);
    int exponent = ((input >> 52) & 0x7ff) - 1023;
    if (exponent >= 0) {
        int fractional_bits = 52 - exponent;
        if (fractional_bits > 0) {
            long unsigned integral_mask = 0xffffffffffffffff << fractional_bits;
            long unsigned output = input & integral_mask;
            memcpy(&x, &output, 8);
            if (x > 0 && output != input) x += 1.0;
        }
    } else {
        x = x > 0;
    }
    return x;
}

static const double COS_EPS = 1e-6l;

long double cos(double x) {
    double result = 0;
    if (!is_inf(x) && !is_nan(x)) {
        x = fmod(x, 2 * S21_PI);
        double i = 1;
        double step = 1;
        result = 1;
        while (fabs(step) > COS_EPS) {
            step *= -x * x / ((2 * i - 1) * (2 * i));
            result += step;
            i++;
        }
    } else {
        result = S21_NAN;
    }
    return result;
}

/**
 * Implementation of exp function from math lib.
 * Uses Tailor series for calculation and aproximation of result
**/


static const long double EXP_EPS = 1e-100;

long double exp(double x) {
    long double res = 1;
    if (is_nan(x)) {
        res = x < 0 ? -S21_NAN : S21_NAN;
    } else if (is_inf(x)) {
        res = x < 0 ? 0 : S21_INF;
    } else {
        long double num = x;
        long double fact = 1;
        long double step = 1;
        while (fabs(step) > EXP_EPS) {
            step *= num / fact;
            res += step;
            fact++;
        }
    }
    return res;
}
long double fabs(double x) {
    return x < 0 ? -x : x;
}

#include <string.h>

long double floor(double x) {
    unsigned long input;
    memcpy(&input, &x, 8);
    long exponent = ((input >> 52) & 0x7ff) - 1023;
    if (exponent >= 0) {
        long fractional_bits = 52 - exponent;
        if (fractional_bits > 0) {
            unsigned long integral_mask = 0xffffffffffffffff << fractional_bits;
            unsigned long output = input & integral_mask;
            memcpy(&x, &output, 8);
            if (x < 0 && output != input) x -= 1.0;
        }
    } else {
        x = x < 0 ? -1 : 0;
    }
    return x;
}

long double fmod(double x, double y) {
    long double result = S21_NAN;
    if (!is_inf(x) && !is_nan(x) && !is_nan(y) && !is_inf(y) && y != 0) {
        double quotient = trunc(x / y);
        long double without_trace = y * quotient;
        result = x - without_trace;
    } else if (!is_inf(x) && is_inf(y)) {
        result = x;
    }

    return result;
}
/**
 * Implementation of log function from math library
 * Uses Newton-Raphson method for calculation and approximation of result
**/

long double log(double x) {
    long double res = 1;
    if (is_nan(x)) {
        res = x < 0 ? -S21_NAN : S21_NAN;
    } else if (is_inf(x)) {
        res = x < 0 ? -S21_NAN : S21_INF;
    } else if (x < 0) {
        res = S21_NAN;
    } else if (x == 0) {
        res = -S21_INF;
    } else {
        long double num = x;
        long double p = 0;
        int invert = num < 1.0l;
        if (invert) num = 1.0l / num;
        while (num > S21_E) {
            num /= S21_E;
            p++;
        }
        for (int i = 0; i < 256; i++) {
            res = res + 2 * (num - exp(res)) / (num + exp(res));
        }
        res += p;
        if (invert) res = -res;
    }
    return res;
}

int is_inf(double x) {
    return x == INF || x == -INF;
}

int is_nan(double x) {
    // A NaN value is not equal to itself
    return x != x;
}

long double sinh(double x)
{
    return (exp(x) - exp(-x)) / 2;
}

long double cosh(double x)
{
    return (exp(x) + exp(-x)) / 2;
}

long double tanh(double x)
{
    return sinh(x) / cosh(x);
}

long double atan2(double y, double x)
{
    // Placeholder for atan2 implementation
    return atan(y / x);  // This is a simplified version; replace with actual implementation
}

long double modf(double x, double *iptr)
{
    // Placeholder for modf implementation
    *iptr = (double)((int)x);
    return x - *iptr;
}

long double log10(double x)
{
    // Placeholder for log10 implementation
    return log(x) / log(10);
}

long double log2(double x) {
    return log(x) / log(2);
}

long double frexp(double x, int *eptr)
{
    // Placeholder for frexp implementation
    *eptr = (int)floor(log2(x));
    return x / (1 << *eptr);
}

long double ldexp(double x, int exp)
{
    // Placeholder for ldexp implementation
    return x * (1 << exp);
}

static const double POW_EPS = 1e-100l;

long double pow(double base, double _exp) {
    long double res = 1;
    if (fabs(_exp) <= POW_EPS) {
        res = 1.0l;
    } else if (fabs(base) <= POW_EPS && _exp > 0) {
        res = 0.0l;
    } else if (fabs(base - 1.0) <= POW_EPS) {
        res = 1.0l;
    } else if (is_nan(base) || is_nan(_exp)) {
        res = S21_NAN;
    } else if (base < 0 && fabs(fmod(_exp, 1.0)) > POW_EPS) {
        res = -S21_NAN;
    } else if (is_inf(base) && base < 0 && fabs(fmod(_exp, 2.0)) > POW_EPS) {
        res = -S21_INF;
    } else if (is_inf(base) && base < 0 && fmod(_exp, 2.0) <= POW_EPS && _exp > 0) {
        res = S21_INF;
    } else if (is_inf(base) && base < 0 && _exp < 0) {
        res = 0.0l;
    } else if (is_inf(base) && base < 0 && _exp > 0) {
        res = S21_INF;
    } else if (is_inf(base) && base > 0 && _exp < 0) {
        res = 0.0l;
    } else if (is_inf(base) && base > 0 && _exp > 0) {
        res = S21_INF;
    } else if (fabs(base) <= POW_EPS && base >= 0 && _exp < 0) {
        res = S21_INF;
    } else if (fabs(base) <= POW_EPS && base >= 0) {
        res = 0.0l;
    } else if (base < 0 && fabs(base) - 1 <= POW_EPS && is_inf(_exp)) {
        res = 1.0l;
    } else if ((fabs(base) - 1 < POW_EPS && is_inf(_exp) && _exp < 0) ||
               (fabs(base) - 1 > POW_EPS && is_inf(_exp) && _exp > 0)) {
        res = S21_INF;
    } else if ((fabs(base) - 1 > POW_EPS && is_inf(_exp) && _exp < 0) ||
               (fabs(base) - 1 < POW_EPS && is_inf(_exp) && _exp > 0)) {
        res = 0.0l;

    } else {
        int neg_base = base < 0;
        int neg_pow = _exp < 0;
        if (neg_base) base = -base;
        if (neg_pow) _exp = -_exp;
        res = exp(_exp * log(base));
        if (neg_base && fabs(fmod(_exp, 2.0)) > POW_EPS) res = -res;
        if (neg_pow) res = 1. / res;
    }
    return res;
}

static const double SIN_EPS = 1e-6l;

long double sin(double x) {
    x = fmod(x, 2 * S21_PI);

    int i = 1;
    double numerator = x;
    double divisor = 1;
    double div_result = 1;
    double result = x;

    do {
        divisor *= ((i << 1) * ((i << 1) + 1));
        numerator *= -1 * x * x;
        div_result = numerator / divisor;
        result += div_result;
        i++;
    } while (fabs(div_result) > SIN_EPS);

    return result;
}

/**
 * Implementation of sqrt function from math library.
**/

static const long double SQRT_EPS = 1e-20l;

long double sqrt(double x) {
    long double res = 0;
    if (x < 0) {
        res = -S21_NAN;
    } else if (is_nan(x)) {
        res = S21_NAN;
    } else if (is_inf(x) || x <= SQRT_EPS) {
        res = x;
    } else {
        res = exp(log(x) / 2.);
    }
    return res;
}

long double tan(double x) {
    long double res;
    if (is_nan(x) || is_inf(x))
        res = S21_NAN;
    else
        res = sin(x) / cos(x);
    return res;
}
#include <string.h>

long double trunc(double x) {
    long unsigned input;
    memcpy(&input, &x, 8);
    int exponent = ((input >> 52) & 0x7ff) - 1023;
    if (exponent >= 0) {
        int fractional_bits = 52 - exponent;
        if (fractional_bits > 0) {
            long unsigned integral_mask = 0xffffffffffffffff << fractional_bits;
            long unsigned output = input & integral_mask;
            memcpy(&x, &output, 8);
        }
    } else {
        x = x < 0 ? -0.0 : 0.0;
    }
    return x;
}
