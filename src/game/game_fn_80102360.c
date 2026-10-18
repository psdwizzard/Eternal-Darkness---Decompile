extern double __ieee754_exp(double value);

double exp(double value)
{
    return __ieee754_exp(value);
}
