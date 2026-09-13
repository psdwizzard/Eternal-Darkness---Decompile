extern unsigned long long fn_8020123C(int type, int owner, int target,
                                     int argument);

int fn_80204810(void *object, int event)
{
    fn_8020123C((unsigned char)event, (unsigned int)event >> 8,
                (unsigned int)event >> 8, 0);
    return 1;
}
