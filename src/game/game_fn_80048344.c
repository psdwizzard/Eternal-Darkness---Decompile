extern void *memcpy(void *destination, const void *source, unsigned long size);
extern void fn_8016A830(void *context, double value);
extern void fn_8016AB20(void *context, const char *name);

int fn_80048344(void *context, const void *source, const char *name) {
    double value;

    memcpy(&value, source, sizeof(value));
    fn_8016A830(context, value);
    fn_8016AB20(context, name);
    return sizeof(value);
}
