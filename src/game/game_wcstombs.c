/* MSL wcstombs: convert 16-bit wide characters to UTF-8. */
typedef unsigned short wchar_t;
typedef unsigned long size_t;

extern int unicode_to_UTF8(char *output, wchar_t character);
extern char *strncpy(char *destination, const char *source, size_t count);

size_t wcstombs(char *destination, const wchar_t *source, size_t limit)
{
    char encoded[6];
    size_t count;
    size_t total = 0;
    const wchar_t *current;

    if (!destination || !source) {
        return 0;
    }

    current = source;
    while (total <= limit) {
        if (*current == 0) {
            destination[total] = 0;
            break;
        }
        count = unicode_to_UTF8(encoded, *current++);
        if (total + count > limit) {
            break;
        }
        strncpy(destination + total, encoded, count);
        total += count;
    }
    return total;
}
