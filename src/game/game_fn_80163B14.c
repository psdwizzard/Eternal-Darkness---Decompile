extern double strtod(signed char*, signed char**);
extern int isspace(int);

int luaO_str2d(signed char* text, double* result)
{
    signed char* end;
    double value = strtod(text, &end);

    if (end == text) {
        return 0;
    }
    while (isspace((unsigned char)*end)) {
        end++;
    }
    if (*end != 0) {
        return 0;
    }
    *result = value;
    return 1;
}
