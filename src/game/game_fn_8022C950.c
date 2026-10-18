/* Copy characters until the next source character is the terminator. */
void Strcpy(char *destination, const char *source)
{
    do {
        *destination = *source;
        ++destination;
        ++source;
    } while ((signed char)*source != 0);
}
