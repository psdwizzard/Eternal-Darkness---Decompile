extern double __ieee754_atan2(double first, double second);

double atan2(double first, double second)
{
    return __ieee754_atan2(first, second);
}
