typedef unsigned char u8;

typedef struct AttributeBlock {
    u8 positions[2][0x18];
    u8 colors[2][0x10];
    u8 texcoords[2][0x10];
} AttributeBlock;

typedef struct Data {
    u8 pad00[8];
    AttributeBlock attributes;
    u8 pad78[0x7C];
    u8 flags;
} Data;

typedef struct RuntimeState {
    u8 pad00[0x20];
    Data *data;
} RuntimeState;

extern int fn_80201ADC(void);
extern void *fn_80201BC8(void *);
extern void *fn_80201B8C(unsigned char *);
extern void *fn_8011FB4C(void *);
extern int fn_80048628(void);
extern void DCFlushRange(void *, unsigned int);
extern void fn_80027150(void *, void *, void *);
extern void fn_801ECC4C(void);
extern void fn_801EA9F8(void);
extern int lbl_8064D18C;
extern int lbl_8064D738;

void fn_800CE5A8(void *object)
{
    /* The accessor is defined with an int return, containing an object address. */
    void *current = (void *)fn_80201ADC();
    void *other;
    Data *data;
    int group;
    AttributeBlock *attributes;

    if (current != 0) {
        other = fn_80201BC8(current);
        if (other != 0) {
            data = ((RuntimeState *)fn_80201B8C(object))->data;
            /* This accessor returns void * in its definition; this field is an ID. */
            group = (int)fn_8011FB4C(other);
            if (group == lbl_8064D18C &&
                (fn_80048628() == 0 || !(data->flags & 0x40))) {
                attributes = &data->attributes;
                DCFlushRange(attributes->positions[lbl_8064D738], 0x18);
                DCFlushRange(attributes->texcoords[lbl_8064D738], 0x10);
                DCFlushRange(attributes->colors[lbl_8064D738], 0x10);
                fn_80027150(attributes->positions[lbl_8064D738],
                            attributes->colors[lbl_8064D738],
                            attributes->texcoords[lbl_8064D738]);
                fn_801ECC4C();
                fn_801EA9F8();
            }
        }
    }
}
