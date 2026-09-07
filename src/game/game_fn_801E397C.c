void fn_801E397C(signed char* destination, signed char* source)
{
    if (destination == 0) {
        return;
    }
    if (source == 0) {
        return;
    }

    do {
        *destination++ = *source;
    } while (*++source != 0);
}
