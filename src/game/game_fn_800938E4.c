typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec800938E4 {
    float x, y, z;
} Vec800938E4;

typedef struct State800938E4 {
    u8 pad0[0x150];
    short timer;
} State800938E4;

typedef struct Data800938E4 {
    u8 pad0[0x8C];
    State800938E4 *state;
    void *value90;
} Data800938E4;

extern void *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void fn_8011F114(Vec800938E4 *, void *);
extern void *fn_80201C48(void *);
extern int fn_80201B54(void *);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void *fn_801294DC(void *, int, int, int);
extern void *fn_801A717C(void);
extern void *fn_80072354(void *);
extern void fn_801A7460(void *, int);
extern void fn_801A74A0(void *, int);
extern void fn_801A74A8(void *, int);
extern void fn_801A74C8(void *, int);
extern void fn_801A7560(void *, int);
extern void fn_801A7538(void *, int);
extern void fn_801A7518(void *, int);
extern void fn_801A7550(void *, int);
extern void fn_801A7558(void *, int);
extern void fn_801A764C(void *, void *);
extern void fn_801292E0(void *, int *, int *);
extern void fn_801287C4(void *, void *, void *, int);
extern u32 fn_80201C2C(void *);
extern u32 fn_80205288(void *);
extern int fn_80201C24(void);
extern void fn_801A7680(void *, int);
extern void fn_80129334(void *, int, int *, int);
extern void fn_801A7478(void *, void *);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_8009376C(void);
extern void fn_800C3ADC(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);
extern char lbl_8031D588[];

enum Kind800938E4 { KindInvalid = -1, KindFour = 4 };

int fn_800938E4(void *object, void *resource)
{
    Data800938E4 *data = fn_80201B8C(object);
    void *related;
    int offset;
    void *object2 = fn_80201B94(object);
    Vec800938E4 positionCopy;
    Vec800938E4 position;
    State800938E4 *state;
    int owner;
    int success;
    int callback;
    enum Kind800938E4 selection;
    void *actor;
    void *created;
    u8 (*table)[0x34];
    int dummy;
    int count;
    int frames;

    fn_8011F114(&position, resource);
    positionCopy = position;
    success = 0;
    related = fn_80201C48(object2);
    owner = fn_80201B54(object);
    state = data->state;
    if (state->timer < 1) {
        Vec800938E4 temp;
        /* Reusing 'created' for the lookup result keeps MWCC's allocation. */
        created = fn_80201814((int)related);
        state->timer = 0;
        if (created != 0) {
            {
                void *relatedData = fn_80201BC8(created);
                fn_8011F114(&temp, relatedData);
            }
            selection = 4;
            if (selection != -1) {
                created = fn_801294DC(resource, 4, 0, 6);
                if (created != 0) {
                    actor = fn_801A717C();
                    table = (u8 (*)[0x34])fn_80072354(data->value90);
                    fn_801A7460(actor, 4);
                    fn_801A74A0(actor, owner);
                    fn_801A74A8(actor, (int)related);
                    fn_801A74C8(actor, 1);
                    fn_801A7560(actor, 0x100A84);
                    {
                        /* The sign bit selects the alternate fields eight bytes later. */
                        enum Kind800938E4 selector = 0;
                        offset = ((unsigned)selector >> 28) & 8;
                        fn_801A7538(actor, (*table)[offset + 0x2B]);
                        fn_801A7518(actor, (*table)[offset + 0x2A]);
                    }
                    fn_801A7550(actor, 12);
                    fn_801A7558(actor, 7);
                    fn_801A764C(actor, &positionCopy);
                    fn_801292E0(resource, &count, &dummy);
                    fn_801287C4(created, fn_8003B8A0, actor, 4);
                    callback = 5;
                    do {
                        fn_801287C4(created, fn_8009376C, actor, callback);
                        callback += 2;
                    } while (callback < 25);
                    if (fn_80201C2C(object) != 0 && fn_80205288(object) != 0) {
                        int link = fn_80201C24();
                        fn_801A7680(actor, link);
                        fn_80129334(resource, 1, &frames, -1);
                        fn_801A7478(actor, lbl_8031D588);
                        fn_801287C4(created, fn_800C3ADC, actor, frames - 1);
                    }
                    fn_80128C28(created, fn_80204230, actor);
                    fn_80128C44(created, fn_802042A4, actor);
                    fn_80201D2C(object, 6);
                    fn_80201D14(object, 1);
                    success = 1;
                }
            }
        }
    }
    return success;
}
