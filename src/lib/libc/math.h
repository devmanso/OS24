#ifndef MATH_H
#define MATH_H

#define INF (1.0 / 0.0)  // Represents infinity
#define NAN (0.0 / 0.0)  // Represents NaN (Not a Number)

int is_inf(double x);
int is_nan(double x);

#define S21_INF INF
#define S21_NAN NAN

#define E 2.718281828459045
#define PI 3.141592653589793

#define S21_E E
#define S21_PI PI

int abs(int x);
long double acos(double x);
long double asin(double x);
long double atan(double x);
long double ceil(double x);
long double cos(double x);
long double exp(double x);
long double fabs(double x);
long double floor(double x);
long double fmod(double x, double y);
long double log(double x);
long double pow(double base, double exp);
long double sin(double x);
long double sqrt(double x);
long double tan(double x);
long double trunc(double x);

long double sinh(double x);
long double cosh(double x);
long double tanh(double x);
long double atan2(double y, double x);
long double modf(double x, double *iptr);
long double log10(double x);
long double frexp(double x, int *eptr);
long double ldexp(double x, int exp);

#endif