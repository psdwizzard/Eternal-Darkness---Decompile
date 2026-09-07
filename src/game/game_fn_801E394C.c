int fn_801E394C(signed char* text)
{
    int length = 0;

    if (text != 0 && *text != 0) {
        do {
            text++;
            length++;
        } while (*text != 0);
    }
    return length;
}
