typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State800938E4 {
    u8 pad0[0x150];
    short timer;
} State800938E4;

typedef struct Data800938E4 {
    u8 pad0[0x8C];
    State800938E4 *state;
    int tableIndex;
} Data800938E4;

/* Layouts shared with the accessor translation units. */
typedef struct { u8 pad[0x84]; u32 value; } Data801A7460;
typedef struct { u8 pad[0x9C]; u32 value; } Data801A74A0;
typedef struct { u8 pad[0x98]; u32 value; } Data801A74A8;
typedef struct { u8 pad[0x7C]; u32 value; } Data801A74C8;
typedef struct { u8 pad[0xA8]; u32 value; } Data801A7560;
typedef struct { u8 pad[0xB6]; unsigned short value; } Data801A7538;
typedef struct { u8 pad[0xB4]; short value; } Data801A7518;
typedef struct { u8 pad[0x8C]; u32 value; } Data801A7550;
typedef struct { u8 pad[0x90]; u32 value; } Data801A7558;
typedef struct { u8 pad[0x68]; u32 value; } Data801A7680;
typedef struct { u8 pad[0xD0]; u32 value; } Data801A7478;
typedef struct { u32 words[3]; } Value;
typedef struct { u8 pad[0x54]; Value value; } PositionData;

extern void *fn_80201B8C(u8 *);
extern void *fn_80201B94(u8 *);
extern void fn_8011F114(Vec3 *, Vec3 *);
typedef struct Object80201C48 Object80201C48;
extern void *fn_80201C48(Object80201C48 *);
extern int fn_80201B54(int *);
typedef struct Entry80201814 Entry80201814;
extern Entry80201814 *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern u8 *fn_801294DC(void *, int, int, int);
extern void *fn_801A717C(void);
typedef struct Entry { char data[0xE0]; } Entry;
extern Entry *fn_80072354(int);
extern void fn_801A7460(Data801A7460 *, u32);
extern void fn_801A74A0(Data801A74A0 *, u32);
extern void fn_801A74A8(Data801A74A8 *, u32);
extern u32 fn_801A74C8(Data801A74C8 *, u32);
extern u32 fn_801A7560(Data801A7560 *, u32);
extern void fn_801A7538(Data801A7538 *, unsigned short);
extern void fn_801A7518(Data801A7518 *, short);
extern void fn_801A7550(Data801A7550 *, u32);
extern void fn_801A7558(Data801A7558 *, u32);
extern void fn_801A764C(PositionData *, const Value *);
extern void fn_801292E0(void *, int *, int *);
typedef struct Queue Queue;
extern void fn_801287C4(Queue *, void *, u32, u32);
typedef struct Object80201C2C Object80201C2C;
extern void *fn_80201C2C(Object80201C2C *);
typedef struct Object80205288 Object80205288;
extern void *fn_80205288(Object80205288 *);
typedef struct Object80201C24 Object80201C24;
extern void *fn_80201C24(Object80201C24 *);
extern void fn_801A7680(Data801A7680 *, u32);
extern int fn_80129334(void *, int, int *, int);
extern void fn_801A7478(Data801A7478 *, u32);
typedef struct Runtime Runtime;
extern void fn_80128C28(Runtime *, u32, u32);
extern void fn_80128C44(Runtime *, u32, u32);
typedef struct Object80201D2C Object80201D2C;
extern void fn_80201D2C(Object80201D2C *, int);
typedef struct Object80201D14 Object80201D14;
extern void fn_80201D14(Object80201D14 *, u8);
extern int fn_8003B8A0(void *, void *);
extern int fn_8009376C(void *, void *);
extern int fn_800C3ADC(void *, void *);
extern int fn_80204230(int, int);
extern int fn_802042A4(int, int);
extern char lbl_8031D588[];

enum Kind800938E4 { KindInvalid = -1, KindFour = 4 };

static inline int IsValidKind(int value)
{
    enum Kind800938E4 kind = value;
    return kind != KindInvalid;
}

static inline void ApplyTableFields(u32 actor, Entry *table, int selectorValue)
{
    enum Kind800938E4 selector = selectorValue;
    /* The sign bit selects the alternate fields eight bytes later. */
    int offset = ((u32)selector >> 28) & 8;
    fn_801A7538((Data801A7538 *)actor, (u8)table->data[offset + 0x2B]);
    fn_801A7518((Data801A7518 *)actor, (u8)table->data[offset + 0x2A]);
}

int fn_800938E4(void *object, void *resource)
{
    void *created;
    int dummy;
    /* Callback queues store the actor address as a 32-bit payload. */
    u32 actor;
    Data800938E4 *data = fn_80201B8C(object);
    void *object2 = fn_80201B94(object);
    Vec3 positionCopy;
    State800938E4 *state;
    Entry *table;
    int count;
    void *related;
    int owner;
    int frames;
    Vec3 position;
    int success;
    void *linkedObject;

    fn_8011F114(&position, resource);
    positionCopy = position;
    success = 0;
    related = fn_80201C48(object2);
    owner = fn_80201B54(object);
    state = data->state;
    if (state->timer < 1) {
        Vec3 temp;
        created = fn_80201814((int)related);
        state->timer = 0;
        if (created != 0) {
            {
                void *relatedData = fn_80201BC8(created);
                fn_8011F114(&temp, relatedData);
            }
            if (IsValidKind(KindFour)) {
                created = fn_801294DC(resource, KindFour, 0, 6);
                if (created != 0) {
                    actor = (u32)fn_801A717C();
                    table = fn_80072354(data->tableIndex);
                    fn_801A7460((Data801A7460 *)actor, 4);
                    fn_801A74A0((Data801A74A0 *)actor, owner);
                    fn_801A74A8((Data801A74A8 *)actor, (int)related);
                    fn_801A74C8((Data801A74C8 *)actor, 1);
                    fn_801A7560((Data801A7560 *)actor, 0x100A84);
                    ApplyTableFields(actor, table, 0);
                    fn_801A7550((Data801A7550 *)actor, 12);
                    fn_801A7558((Data801A7558 *)actor, 7);
                    fn_801A764C((PositionData *)actor, (const Value *)&positionCopy);
                    fn_801292E0(resource, &count, &dummy);
                    fn_801287C4(created, fn_8003B8A0, actor, 4);
                    {
                        int callback = 5;
                        do {
                            fn_801287C4(created, fn_8009376C, actor, callback);
                            callback += 2;
                        } while (callback < 25);
                    }
                    if (fn_80201C2C(object) != 0 && (linkedObject = fn_80205288(object)) != 0) {
                        void *link = fn_80201C24(linkedObject);
                        fn_801A7680((Data801A7680 *)actor, (u32)link);
                        fn_80129334(resource, 1, &frames, -1);
                        fn_801A7478((Data801A7478 *)actor, (u32)lbl_8031D588);
                        fn_801287C4(created, fn_800C3ADC, actor, frames - 1);
                    }
                    fn_80128C28(created, (u32)fn_80204230, actor);
                    fn_80128C44(created, (u32)fn_802042A4, actor);
                    fn_80201D2C(object, 6);
                    fn_80201D14(object, 1);
                    success = 1;
                }
            }
        }
    }
    return success;
}
