unsigned int __count_trailing_zerol(unsigned int value)
{
    unsigned int result = 0;
    int remaining = 32;
    int shift = 16;
    int next_shift = 16;
    unsigned int mask = 0xFFFF;

    while (remaining != 0) {
        if ((value & mask) == 0) {
            result += next_shift;
            value >>= next_shift;
            remaining -= next_shift;
        } else if (mask == 1) {
            break;
        }
        if (shift > 1) {
            shift /= 2;
        }
        if (mask > 1) {
            mask >>= shift;
            next_shift -= shift;
        }
    }
    return result;
}
