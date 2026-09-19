extern const double lbl_80239CD0[3];

unsigned int fn_800F5C54(double value)
{
    if (value < lbl_80239CD0[0]) {
        return 0;
    }
    if (value < lbl_80239CD0[1]) {
        if (value < lbl_80239CD0[2]) {
            return (int)value;
        }
        return (int)(value - lbl_80239CD0[2]) + 0x80000000;
    }
    return 0xFFFFFFFF;
}
