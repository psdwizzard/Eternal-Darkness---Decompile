/* Return the string length, treating a null pointer as an empty string. */
unsigned long Strlen(const char *text)
{
    unsigned long length = 0;

    if (text == 0) {
        return 0;
    }

    while ((signed char)*text != 0) {
        ++text;
        ++length;
    }
    return length;
}
