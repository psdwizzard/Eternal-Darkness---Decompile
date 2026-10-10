extern void *fn_80156938(void *);
extern void *fn_80201BC8(void *);
extern int fn_80157034(void *);
extern void fn_80185078(void *, unsigned short *, unsigned short *);
extern void fn_801850CC(void *);
extern void fn_800EBA80(int, float *, unsigned int *, int, float);

extern unsigned int lbl_80651BC8;
extern unsigned short lbl_80651BCC;
extern unsigned int lbl_80651BD0;
extern unsigned short lbl_80651BD4;
extern int lbl_8064D084;
extern float lbl_80650480;

typedef struct DebugColors {
    unsigned char pad[0x14];
    unsigned int first;
    unsigned char pad2[0x8];
    unsigned int second;
} DebugColors;
extern DebugColors lbl_802FC5BC;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct QueryResult {
    unsigned char pad[8];
    Vec3 pos;
    unsigned char pad2[20];
} QueryResult;

extern int fn_8011F6A4(void *, void *, int, int, QueryResult *, int);

typedef struct LinkList {
    unsigned char count;
    unsigned char pad1[5];
    unsigned short active;
    void *firstQuery[16];
    void *secondQuery[16];
    void *links[16];
} LinkList;

void fn_80148FE8(void *object, void *target)
{
    QueryResult result;
    Vec3 firstPos;
    Vec3 secondPos;
    unsigned short first[3];
    unsigned short second[3];
    unsigned int colorA;
    unsigned int colorB;
    int i;
    int count;
    LinkList *list;
    void *base;

    base = fn_80201BC8(fn_80156938(target));
    list = fn_80156938(object);
    count = list->count;
    if (fn_80157034(target) == 0) {
        for (i = 0; i < count; i++) {
            *(unsigned int *)&first[0] = lbl_80651BC8;
            first[2] = lbl_80651BCC;
            *(unsigned int *)&second[0] = lbl_80651BD0;
            second[2] = lbl_80651BD4;
            if (list->links[i] != 0) {
                if (fn_8011F6A4(base, list->firstQuery[i], 15, -1, &result, 1) != -1) {
                    firstPos = result.pos;
                    first[0] = (short)result.pos.x;
                    first[1] = (short)result.pos.y;
                    first[2] = (short)result.pos.z;
                }
                if (fn_8011F6A4(base, list->secondQuery[i], 15, -1, &result, 1) != -1) {
                    secondPos = result.pos;
                    second[0] = (short)result.pos.x;
                    second[1] = (short)result.pos.y;
                    second[2] = (short)result.pos.z;
                }
                if (lbl_8064D084 != 0) {
                    colorA = lbl_802FC5BC.first;
                    fn_800EBA80(2, &firstPos.x, &colorA, 0x40, lbl_80650480);
                    colorB = lbl_802FC5BC.second;
                    fn_800EBA80(2, &secondPos.x, &colorB, 0x40, lbl_80650480);
                }
                fn_80185078(list->links[i], first, second);
            }
        }
    } else {
        list->active = 1;
        for (i = 0; i < count; i++) {
            if (list->links[i] != 0) {
                fn_801850CC(list->links[i]);
            }
        }
    }
}
