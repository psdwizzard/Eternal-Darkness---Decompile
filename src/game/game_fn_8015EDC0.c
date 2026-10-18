extern const double lbl_80650650;
extern int number_constant(void*, double);
extern int luaK_code1(void*, int, int);

int luaK_number(void* object, double value)
{
    if (value <= lbl_80650650) {
        if ((double)(int)value == value)
            return luaK_code1(object, 6, (int)value);
    }

    return luaK_code1(object, 8, number_constant(object, value));
}
