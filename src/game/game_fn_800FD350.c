char* strncat(char* destination, const char* source, unsigned long count)
{
    const char* s = source - 1;
    char* end = destination - 1;
    unsigned long n;
    unsigned int ch;

    do {
        ch = (unsigned char)*++end;
    } while (ch != 0);
    --end;
    n = count + 1;

    while (--n != 0) {
        ch = (unsigned char)*++s;
        *++end = ch;
        if (ch == 0) {
            --end;
            break;
        }
    }
    end[1] = 0;
    return destination;
}
