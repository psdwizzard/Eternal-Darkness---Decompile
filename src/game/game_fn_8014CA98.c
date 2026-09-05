typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern const Vec3 lbl_8023A728;
extern const double lbl_806504F0;
extern void *fn_80156938(void *);
extern void *fn_80201BC8(void *);
extern short fn_801FE9DC(void*);
extern void fn_8012B690(void*, const Vec3*, Vec3*);
extern void fn_801FDEB4(void*, Vec3*);

void fn_8014CA98(void* first, void* second)
{
    Vec3 value;
    Vec3 result;
    void* runtime;
    void* owner;

    owner = fn_80201BC8(fn_80156938(second));
    runtime = fn_80156938(first);
    if (runtime != 0) {
        value = lbl_8023A728;
        value.y = (float)-fn_801FE9DC(runtime);
        fn_8012B690(owner, &value, &result);
        fn_801FDEB4(runtime, &result);
    }
}
