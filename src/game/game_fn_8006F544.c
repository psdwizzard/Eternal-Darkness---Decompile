typedef unsigned char u8;

typedef struct Config {
    void *header;
    int value;
    u8 pad_08[4];
    u8 object_count;
    u8 slot_count;
    u8 pad_0E[0x66];
    void *slots[16];
    int expected;
} Config;

typedef struct Owner {
    u8 pad_00[0x38];
    void *resource;
    u8 pad_3C[0x88];
    Config *config;
} Owner;

typedef struct Runtime {
    u8 pad_00[0x44];
    void *object;
} Runtime;

extern void *fn_80201814();
extern Runtime *fn_80036D38(void);
extern int fn_80201B54();
extern unsigned long long fn_8020123C();
extern void *fn_80155DB4(void *object);
extern void fn_80156FF4(void *object);
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201EB8();
extern void fn_8011FB54(void *object, int value);
extern void *memset(void *dest, int value, unsigned int size);
extern void *lbl_803127F8[32];

/* NonMatching: size-exact behavior-complete reconstruction. Remaining output
 * differences are initial address formation and first-loop register allocation. */
void fn_8006F544(Owner *owner, int enabled)
{
    Config *config;
    void **object_iter;
    void **objects;
    int object;
    u8 object_count;
    int value;
    void *source;

    source = 0;
    if (fn_80201814(owner->resource) != 0) {
        source = fn_80036D38()->object;
    }
    config = owner->config;
    objects = lbl_803127F8;
    config = (Config *)((u8 *)config + 0x48);
    value = config->value;
    object_count = config->object_count;
    {
        Config *slot_config = config;
        u8 slot_count = config->slot_count;
        int slot;
        for (slot = 0; slot < slot_count; slot++) {
            if (slot_config->slots[0] != 0) {
                int id = fn_80201B54(slot_config->slots[0]);
                if (id == slot_config->expected) {
                    fn_8020123C(0x39, source, id, 0);
                    if (enabled != 0) {
                        void *runtime = fn_80155DB4(slot_config->slots[0]);
                        if (runtime != 0) {
                            fn_80156FF4(runtime);
                        }
                    }
                    slot_config->slots[0] = 0;
                    slot_config->expected = 0;
                }
            }
            slot_config = (Config *)((u8 *)slot_config + 4);
        }
    }
    object_iter = objects;
    for (object = 0; object < object_count; object_iter++, object++) {
        if (object_iter != 0 && *object_iter != 0) {
            void *runtime;
            fn_80201B8C(*object_iter);
            runtime = fn_80201BC8(*object_iter);
            if (fn_80201B54(*object_iter) != 0 &&
                fn_80201EB8(*object_iter) == 10000) {
                fn_8011FB54(runtime, value);
            }
        }
    }
    memset(lbl_803127F8, 0, 0x80);
}
