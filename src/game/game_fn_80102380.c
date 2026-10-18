extern double __ieee754_log(double value);

double log(double value)
{
    return __ieee754_log(value);
}
