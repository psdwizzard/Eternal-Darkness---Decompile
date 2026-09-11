typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct EntryData {
    u8 pad[0x18];
    int gameFlag;
} EntryData;

typedef struct Entry {
    u8 pad0[4];
    struct Entry *next;
    u8 pad8[8];
    int uniqueId;
    u8 pad14[0x10];
    EntryData *data;
    u8 pad28[0xC];
    void *object;
} Entry;

typedef struct Manager {
    u8 pad0[4];
    Entry *head;
} Manager;

extern char lbl_802FC8F0[];
extern float lbl_80651590;

extern Manager *fn_802014AC(void);
extern int fn_8011FB4C(void *object);
extern int fn_8011EB04(void *object);
extern int fn_8011EB1C(void *object);
extern void fn_8011F114(Vec3 *position, void *object);
extern int fn_80128EAC(void *object);
extern int fn_80128F40(void *object);
extern void fn_800ED4BC(Vec3 *position, int mode, const char *format, ...);

void fn_802013C4(int group)
{
    Entry *entry;

    for (entry = fn_802014AC()->head; entry != 0; entry = entry->next) {
        int objectGroup;
        int geom;
        int type;
        int anim;
        int dopeFrame;
        Vec3 position;

        if (entry->data == 0) {
            continue;
        }
        objectGroup = fn_8011FB4C(entry->object);
        if (objectGroup != group) {
            continue;
        }
        geom = fn_8011EB04(entry->object);
        type = fn_8011EB1C(entry->object);
        fn_8011F114(&position, entry->object);
        anim = fn_80128EAC(entry->object);
        dopeFrame = fn_80128F40(entry->object) >> 17;
        position.z += lbl_80651590;
        fn_800ED4BC(&position, 3, lbl_802FC8F0, geom, type,
                    entry->data->gameFlag, entry->uniqueId, objectGroup,
                    anim, dopeFrame);
    }
}
