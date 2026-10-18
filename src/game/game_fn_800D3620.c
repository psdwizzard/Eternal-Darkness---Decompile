typedef unsigned int u32;
typedef struct Vec3 { u32 x, y, z; } Vec3;
typedef struct State State;

extern const Vec3 lbl_80248AE4;
extern void* fn_80201B94(int);
extern int fn_80201C48(void*);
extern int fn_80201B54(int);
extern void fn_80201DD8(void*, int);
extern void fn_8011F114(Vec3*, State*);
extern void fn_8012B690(State*, const Vec3*, Vec3*);
extern void PSVECAdd(Vec3*, Vec3*, Vec3*);
extern void fn_8020123C(int, int, int, void*);

int fn_800D3620(void* arg0, void* arg1)
{
    State* state;
    int object;
    int id;
    int value;
    void* resource;
    Vec3 first;
    Vec3 second;

    state = arg0;
    object = (int)arg1;
    resource = fn_80201B94(object);
    value = fn_80201C48(resource);
    id = fn_80201B54(object);
    fn_80201DD8(resource, 0);
    fn_8011F114(&first, state);
    fn_8012B690(state, &lbl_80248AE4, &second);
    PSVECAdd(&first, &second, &second);
    fn_8020123C(157, id, value, &second);
    fn_8020123C(160, id, value, 0);
    return 1;
}
