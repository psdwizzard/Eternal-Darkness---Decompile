typedef struct EffectState {
    unsigned char pad[0xC];
    int value;
    int primary;
    int secondary;
} EffectState;

extern unsigned int fn_80036D5C(void*);
extern void fn_80036DA4(void*, unsigned int);
extern void *fn_80201814();
extern void fn_8012B344(void*);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern unsigned long long fn_8020123C();
extern void fn_8008DF64(void*, void*, void*, void*);

void fn_8008E71C(void* object, int object_id, EffectState* state,
                 void* resource, void* arg5, void* arg6)
{
    unsigned int masked = fn_80036D5C(object) & 0x00100000;
    int target = state->primary != 0 ? state->primary : state->secondary;

    if (masked != 0) {
        void* linked = fn_80201814(state->secondary);
        fn_8012B344(resource);
        fn_80201D34(object, 73);
        fn_80201D1C(object, 1);
        if (linked != 0) {
            fn_80036DA4(linked, fn_80036D5C(linked) | 0x00080000);
        }
    } else {
        fn_8020123C(126, object_id, target, 0);
        fn_8020123C(122, object_id, state->value, 0);
        state->primary = 0;
        state->value = 0;
        fn_8008DF64(object, resource, arg5, arg6);
    }
}
