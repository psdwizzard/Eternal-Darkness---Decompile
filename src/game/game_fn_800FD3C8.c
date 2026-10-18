char* strncpy(char* destination, const char* source, unsigned long count)
{
    const char* s = source - 1;
    char* d = destination - 1;
    unsigned long n = count + 1;
    unsigned int ch;

    while (--n != 0) {
        ch = (unsigned char)*++s;
        *++d = ch;
        if (ch == 0) {
            ch = 0;
            while (--n != 0) {
                *++d = ch;
            }
            return destination;
        }
    }
    return destination;
}
