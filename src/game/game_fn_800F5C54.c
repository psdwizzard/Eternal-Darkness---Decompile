unsigned int fn_800F5C54(double value)
{
    unsigned int result = 0;
    if (value >= 0.0) {
        result--;
        if (value < 4294967296.0) {
            double converted = value;
            if (value >= 2147483648.0) {
                converted = value - 2147483648.0;
            }
            result = (int)converted;
            if (value >= 2147483648.0) {
                result += 0x80000000;
            }
        }
    }
    return result;
}
