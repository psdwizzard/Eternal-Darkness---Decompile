typedef unsigned char u8;
typedef unsigned int u32;

typedef union Color800A41CC {
    u32 value;
    u8 channel[4];
} Color800A41CC;

typedef struct Object800A41CC {
    u8 pad0[0x24c];
    int children[4];
} Object800A41CC;

typedef struct Runtime800A41CC {
    u8 pad0[0x94];
    int state;
    u8 pad98[7];
    u8 type;
} Runtime800A41CC;

extern void* fn_80201890(int);
extern void *fn_80201814(int);
extern void *fn_80201B8C();
extern unsigned short fn_8012DBE8(void*, int, Color800A41CC*);
extern void fn_8006A478(void*);
extern int fn_80201B5C(void*);
extern void fn_800CAC5C(int, int, int*, int*, int*);
extern unsigned long long fn_8020123C();
extern void fn_80201D44(void*, int);
extern void fn_802015A4(void*);
extern void fn_80201D34(void*, int);
extern void fn_80201D1C(void*, int);
extern int fn_801E8328();
extern int fn_800A4368(Object800A41CC*, int);

void fn_800A41CC(Object800A41CC* object, void* context)
{
    int child;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        child = object->children[i];
        if (child != 0) {
            void* model;
            void* entity;
            Runtime800A41CC* runtime;
            Color800A41CC color;
            int remove;
            int value;
            int first;
            int second;

            remove = 0;
            model = fn_80201890(child);
            entity = fn_80201814(child);
            runtime = ((Runtime800A41CC*)fn_80201B8C(entity));
            fn_8012DBE8(model, 15, &color);

            if (runtime->type == 3 && runtime->state == 2) {
                fn_8006A478(entity);
            }

            if (fn_80201B5C(entity) == 40) {
                if (color.channel[3] <= 0x80) {
                    remove = 1;
                } else {
                    fn_800CAC5C(runtime->type, 1, &first, &second, &value);
                    fn_8020123C(0xf0, context, child, value);
                }
            } else if (fn_80201B5C(entity) == 0) {
                if (color.channel[3] <= 0x80) {
                    remove = 1;
                } else {
                    fn_800CAC5C(runtime->type, 1, &first, &second, &value);
                    fn_80201D44(entity, value);
                    fn_802015A4(entity);
                }
            }

            if (remove != 0) {
                fn_80201D34(entity, 0);
                fn_80201D1C(entity, 1);
                fn_801E8328(2, entity);
            } else {
                fn_8020123C(8, context, child, 0);
            }
            fn_800A4368(object, child);
        }
    }
}
