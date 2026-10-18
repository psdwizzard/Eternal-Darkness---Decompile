extern double __ieee754_pow(double value);

double pow(double value)
{
    return __ieee754_pow(value);
}
