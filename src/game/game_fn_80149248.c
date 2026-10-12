typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Descriptor {
    u8 pad00[0x90];
    void* create;
    u32 createData;
    void* destroy;
    u32 destroyData;
    void* query;
    u32 queryData;
    u8 padA8[0x14];
    u8 enabled;
} Descriptor;

typedef struct LinkList {
    u8 count;
    u8 pad1[5];
    unsigned short active;
    void* firstQuery[16];
    void* secondQuery[16];
    void* links[16];
} LinkList;

typedef struct Effect {
    union {
        Descriptor descriptor;
        struct {
            u8 pad00[6];
            unsigned short duration;
            u8 pad08[0xC];
            u8 type;
            u8 pad15;
            u8 active;
            u8 pad17;
            u32 flags;
            u8 pad1C[0x8C];
            int owner;
            u8 padAC[0x10];
            u8 enabled;
            u8 state;
        } fields;
    } header;
    LinkList* resource;
} Effect;

extern void* fn_80201BC8(void*);
extern void* fn_80149360(void);
extern void* fn_80149E04(void);
extern void fn_80148B18(Descriptor*, u8*);
/* This entry accepts an object; the caller also supplies a configuration
 * address in the unused argument register, as in the original ABI call. */
extern void fn_80149220();
extern void fn_801493D4(void*, short*, void*, void*, u8*);
extern void fn_80148FE8(void*, void*);
extern int fn_80201B54(int*);
extern int fn_801E8328(u32, u32);
extern int lbl_80650484;

void fn_80149248(int* object, int count)
{
    Effect* effect;
    int configuration;

    fn_80201BC8(object);
    effect = fn_80149360();
    if (effect != 0) {
        effect->resource = fn_80149E04();
        if (effect->resource != 0) {
            configuration = lbl_80650484;
            fn_80148B18(&effect->header.descriptor, (u8*)effect->resource);
            effect->resource->firstQuery[0] = (void*)9;
            effect->resource->secondQuery[0] = (void*)10;
            effect->resource->count = count;
            if (count > 1) {
                effect->resource->firstQuery[1] = (void*)11;
                effect->resource->secondQuery[1] = (void*)12;
            }
            fn_80149220(effect, &configuration);
            effect->header.descriptor.query = fn_801493D4;
            effect->header.descriptor.enabled = 4;
            effect->header.descriptor.destroy = fn_80148FE8;
            effect->header.fields.duration = 100;
            effect->header.fields.active = 1;
            effect->header.fields.state = 1;
            effect->header.fields.type = 2;
            effect->header.fields.flags = 1;
            effect->header.fields.owner = fn_80201B54(object);
            fn_801E8328(17, (u32)effect);
        }
    }
}
