typedef signed char s8;

void fn_801E6F64(s8* destination, const s8* source)
{
    while (source[0] != 0 || source[1] != 0) {
        *destination = *source;
        source++;
        destination++;
    }
    destination[0] = 0;
    destination[1] = 0;
}
