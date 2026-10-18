int strncmp(const char* left, const char* right, unsigned long count)
{
    const unsigned char* a = (const unsigned char*)left - 1;
    const unsigned char* b = (const unsigned char*)right - 1;
    unsigned int ac;
    unsigned int bc;
    unsigned long n = count + 1;

    while (--n != 0) {
        ac = *++a;
        bc = *++b;
        if (ac != bc) {
            return ac - bc;
        }
        if (ac == 0) {
            break;
        }
    }
    return 0;
}
