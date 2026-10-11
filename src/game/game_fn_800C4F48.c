typedef struct Item4F48 {
    unsigned char padding[0x84];
    int variant;
    unsigned char padding88[0x0D];
    unsigned char kind;
} Item4F48;

typedef struct ItemRef4F48 {
    Item4F48 *item;
} ItemRef4F48;

typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

extern int fn_80201B54(int *object);
extern void *fn_80201B8C(unsigned char *object);
extern void fn_8010F3DC(unsigned int mask);
extern void fn_800C510C(void);
extern void fn_80201D2C(Object80201D2C *object, int value);
extern void fn_80201D14(Object80201D14 *object, unsigned char value);

void fn_800C4F48(void *context, void *object, void *event, int *result)
{
    Item4F48 *item;

    fn_80201B54(context);
    item = ((ItemRef4F48 *)fn_80201B8C(context))->item;
    switch ((unsigned int)item->kind) {
    case 12:
        switch (item->variant) {
        case 1: fn_8010F3DC(0x800); break;
        case 2: fn_8010F3DC(0x2000); break;
        case 3: fn_8010F3DC(0x1000); break;
        }
        break;
    case 3:
        switch (item->variant) {
        case 1: fn_8010F3DC(2); break;
        case 2: fn_8010F3DC(8); break;
        case 3: fn_8010F3DC(4); break;
        case 4: fn_8010F3DC(1); break;
        }
        break;
    case 4:
        switch (item->variant) {
        case 1: fn_8010F3DC(0x100); break;
        case 2: fn_8010F3DC(0x400); break;
        case 3: fn_8010F3DC(0x200); break;
        }
        break;
    case 5:
        switch (item->variant) {
        case 1: fn_8010F3DC(0x20); break;
        case 2: fn_8010F3DC(0x80); break;
        case 3: fn_8010F3DC(0x40); break;
        }
        break;
    case 6:
        fn_8010F3DC(0x10);
        break;
    case 7:
        /* This kind has no mask to set. */
        break;
    }
    fn_800C510C();
    fn_80201D2C(context, 1);
    fn_80201D14(context, 1);
}
