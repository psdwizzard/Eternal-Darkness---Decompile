char* strcat(char* destination, const char* source)
{
    const char* s = source - 1;
    char* end = destination - 1;
    unsigned int ch;

    do {
        ch = (unsigned char)*++end;
    } while (ch != 0);
    --end;
    do {
        ch = (unsigned char)*++s;
        *++end = ch;
    } while (ch != 0);
    return destination;
}
