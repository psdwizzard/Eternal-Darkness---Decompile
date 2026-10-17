typedef struct Object {
    unsigned char pad[0x44];
    unsigned int flags;
} Object;

extern void *fn_80156938(Object *);
extern void *fn_80201BC8(void *);
extern unsigned int fn_80157034(Object *);
extern void fn_80185078(unsigned char *, const signed short *, const signed short *);
extern void fn_801850CC(unsigned char *);

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    unsigned char r, g, b, a;
} Color;

extern void fn_800EBA80(int, Vec3 *, Color *, unsigned char, float);

extern unsigned int lbl_80651BC8;
extern unsigned short lbl_80651BCC;
extern unsigned int lbl_80651BD0;
extern unsigned short lbl_80651BD4;
extern int lbl_8064D084;
extern float lbl_80650480;

extern Color lbl_802FC5BC[];

typedef struct QueryResult {
    unsigned char pad[8];
    Vec3 pos;
    unsigned char pad2[20];
} QueryResult;

extern int fn_8011F6A4(void *, int, int, int, void *, int);

typedef struct LinkList {
    unsigned char count;
    unsigned char pad1[5];
    unsigned short active;
    int firstQuery[16];
    int secondQuery[16];
    unsigned char *links[16];
} LinkList;

void fn_80148FE8(Object *object, Object *target)
{
    QueryResult result;
    Vec3 firstPos;
    Vec3 secondPos;
    signed short first[3];
    signed short second[3];
    Color colorA;
    Color colorB;
    int i;
    int count;
    LinkList *list;
    void *base;

    base = fn_80201BC8(fn_80156938(target));
    list = fn_80156938(object);
    count = list->count;
    if ((int)fn_80157034(target) == 0) {
        for (i = 0; i < count; i++) {
            *(unsigned int *)&first[0] = lbl_80651BC8;
            *(unsigned short *)&first[2] = lbl_80651BCC;
            *(unsigned int *)&second[0] = lbl_80651BD0;
            *(unsigned short *)&second[2] = lbl_80651BD4;
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
                    colorA = lbl_802FC5BC[5];
                    fn_800EBA80(2, &firstPos, &colorA, 0x40, lbl_80650480);
                    colorB = lbl_802FC5BC[8];
                    fn_800EBA80(2, &secondPos, &colorB, 0x40, lbl_80650480);
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
