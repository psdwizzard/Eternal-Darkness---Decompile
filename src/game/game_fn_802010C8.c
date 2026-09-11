extern int fn_80201B64(void *object);
extern void fn_80201138(int kind, void *context, int value, int id,
                        int arg4, float time);

void fn_802010C8(int kind, void *context, int arg2, float time)
{
    fn_80201138(kind, context, fn_80201B64(context), -1, arg2, time);
}
