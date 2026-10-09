typedef signed short s16;
typedef signed int s32;

typedef struct Entry80201814 Entry80201814;

extern int fn_80038308(void *object, int channel, s16 *value);
extern int fn_80038464(void *object, int channel, s16 *value);
extern int fn_800389E0(void *object, int channel, s32 value, int propagate);
extern Entry80201814 *fn_80201814(int id);
extern int fn_80201B44(void);

void fn_800C3C6C(s16 amount)
{
    Entry80201814 *object;
    s16 current;
    s16 maximum;

    object = fn_80201814(fn_80201B44());
    fn_80038308(object, 3, &current);
    fn_80038464(object, 3, &maximum);
    current -= amount;
    fn_800389E0(object, 3, current, 1);
}
