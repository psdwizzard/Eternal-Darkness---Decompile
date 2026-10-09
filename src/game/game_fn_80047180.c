typedef struct Config {
    unsigned char pad_00[0x20];
    unsigned int flags;
} Config;

typedef struct Entry Entry;

typedef struct Owner {
    void *pad_00;
    Entry *entry;
    unsigned char pad_08[0xBC];
    Config *config;
} Owner;

typedef struct Object Object;

extern int fn_80071258(void);
extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *object, int type);
extern void *fn_8006D444(void *object);
extern int fn_8006D2C8(Owner *owner, int kind);

int fn_80047180(void)
{
    int result = 1;
    Owner *owner;

    if (fn_80071258() != 0) {
        owner = fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
        result = 0;
        if (fn_8006D2C8(owner, 0xA) != 0) {
            owner->config->flags |= 0x2000;
        }
    }
    return result;
}
