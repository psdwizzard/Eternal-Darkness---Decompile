typedef struct Context Context;

extern void fn_8016AA34(Context *context, const char *name);
extern double fn_8016A694(void *context, int index);
extern void fn_8016A5B0(Context *context, int count);
extern void *memcpy(void *destination, const void *source, unsigned long size);

int fn_80048068(Context *context, void *destination, const char *name)
{
    double value;

    fn_8016AA34(context, name);
    value = fn_8016A694(context, 1);
    fn_8016A5B0(context, -2);
    memcpy(destination, &value, sizeof(value));
    return sizeof(value);
}
