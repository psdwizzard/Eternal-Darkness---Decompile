typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Runtime {
    unsigned char pad[0x8C];
    void* resource;
} Runtime;

extern Vec3 lbl_80239660;
extern int lbl_8064C55C;
extern int lbl_8064C56C;
extern int lbl_806519C8;
extern int lbl_8064EC3C;
extern int lbl_8064EC40;
extern float lbl_8064EC30;

extern int fn_80201C48(void*);
extern void *fn_80201B8C();
extern void fn_802045AC(void*, Vec3*);
extern int fn_800CA7D4(void*, void*, void*, void*, int, int);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern int fn_80178E94(void*, Vec3*);
extern int fn_800DE298(void*);
extern void* fn_8012C62C(void*, int, int*, int*, int*, int);
extern unsigned long long fn_8020123C();
extern int fn_800BE2CC(void*, void*, Vec3*);
extern void fn_800BE390(void*, void*);
extern int fn_8012AFC4(void*);
extern void fn_80129928(void*, Vec3*);
extern void fn_8012976C(void*, int, int, Vec3*, float);

void fn_8008F064(void* object, void* actor, void* owner, void* distance_ctx,
                 void* unused, void* status)
{
    Runtime* runtime;
    void* resource;
    int distance;
    Vec3 position = lbl_80239660;
    Vec3 hit;

    fn_80201C48(status);
    if (lbl_8064C55C == 0) {
        runtime = ((Runtime*)fn_80201B8C(object));
        resource = runtime->resource;
        fn_802045AC(object, &position);
        if (fn_800CA7D4(owner, object, resource, actor, 45, 5)) {
            fn_80201D34(object, 9);
            fn_80201D1C(object, 1);
            return;
        }

        distance = fn_80178E94(distance_ctx, &position);
        if (distance < 350 && lbl_8064C56C == 0 && fn_800DE298(object)) {
            int a;
            int b;
            int c;
            lbl_8064C56C = 1;
            c = lbl_806519C8;
            b = lbl_8064EC3C;
            a = lbl_8064EC40;
            fn_8012C62C(actor, 15, &a, &b, &c, 4);
        }
        if (distance < 75) {
            fn_8020123C(23, owner, owner, 0);
        } else if (fn_800BE2CC(object, resource, &hit)) {
            if ((unsigned int)fn_80178E94(distance_ctx, &hit) < 80) {
                fn_800BE390(object, resource);
            } else if (fn_8012AFC4(actor)) {
                fn_80129928(actor, &hit);
            } else {
                fn_8012976C(actor, 3, 33, &hit, lbl_8064EC30);
            }
        }
    }
}
