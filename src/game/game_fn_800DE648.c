typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *fn_80201BC8();
#define FN_80201E78_RETURN Vec3
#define FN_80201E78_PARAMETERS void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);
extern float fn_8012B7D0(void *, Vec3);
extern void fn_8012B7A0(void *);

/* EABI passes these by-value vectors through caller-owned copies. */
void fn_800DE648(void *first, Vec3 target, void *object)
{
    void *info = fn_80201BC8(object);
    {
        Vec3 returned = fn_80201E78(object);

        fn_8012B7D0(first, returned);
        fn_8012B7A0(first);
    }
    fn_8012B7D0(info, target);
    fn_8012B7A0(info);
}
