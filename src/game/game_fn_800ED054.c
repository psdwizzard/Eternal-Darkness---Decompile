typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct Owner {
    u8 padA0[0xA0];
    u8 effect[0x10];
    u16 countB0;
    u16 padB2;
    void* dataB4;
} Owner;

typedef struct DebugPath {
    u8 pad[0x7C];
    void* path;
} DebugPath;

extern void fn_800EB6BC(void);
extern void fn_800EB8B8(void* path, Color* color);
extern void fn_800EBA80(int shape, void* position, Color* color, int alpha, float scale);
extern void fn_800EC234(int);
/* Defined (void) but called with an ignored argument, as retail does. */
extern void fn_800EC314();
extern void fn_800EC6FC(int);
extern void fn_800ECBE4(int, int, int);
extern void fn_800ECE44(int);
extern void fn_800ED024();
extern void fn_800ED4BC(Vec3*, int, const char*, ...);
extern int sprintf(char*, const char*, ...);
extern Vec3* fn_8011F130(void*);
extern float fn_8011F6F0(void*);
extern float fn_8011F6F8(void*);
extern int fn_8011FB4C(void*);
extern void fn_80137AF0(void*);
extern void fn_8013BC34(void*, void*);
extern void fn_8014064C(void);
extern void fn_80140A58(void);
extern void fn_80140D38(void);
extern void fn_80141484(void*, int);
extern void fn_80143DF0(void);
extern Owner* fn_8015C28C(int);
extern void fn_801A7958(void*, u16);
extern void fn_801AC2E8(void);
extern void* fn_801E741C(const char*);
extern void fn_801ED468(int);
extern void fn_802013C4(void*);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern void* fn_80201BC8(void*);

extern const char lbl_8024A59C[];
extern Color lbl_802FC5BC[];
extern u8 lbl_8063C6B8[];
extern u8 lbl_8063CD18[];
extern u8 lbl_8063D4EC[];
extern void* lbl_8064C4E4;
extern int lbl_8064CB30;
extern int lbl_8064CB34;
extern int lbl_8064CB38;
extern int lbl_8064CB3C;
extern int lbl_8064CB40;
extern int lbl_8064CB44;
extern int lbl_8064CB54;
extern int lbl_8064CB80;
extern int lbl_8064CB84;
extern int lbl_8064CB88;
extern int lbl_8064CB8C;
extern int lbl_8064CB90;
extern int lbl_8064CBA8;
extern int lbl_8064CBAC;
extern int lbl_8064CBB4;
extern int lbl_8064CBBC;
extern void* lbl_8064D18C;
extern int lbl_8064D6E8;
extern float lbl_8064F898;
extern float lbl_8064F8D4;
extern float lbl_8064F8D8;

/* The format is the literal at lbl_8024A59C + 0x35 in the retail string pool.
 * Spelled as that address, MWCC hoists it out of the actor loop below (retail
 * does not); as a literal it stays in place, as in retail. */
static inline void DrawObjectInfo(Vec3* position, void* object, char* text, float x, float y)
{
    fn_80137AF0(object);
    sprintf(text, "CRad:%4.2f ERad:%4.2f", x, y);
    fn_800ED4BC(position, 3, text);
}

void fn_800ED054(int kind)
{
    char selfText[0x20];
    char text[0x20];

    lbl_8064D6E8 = 1;
    if (lbl_8064CB40 != 0) {
        fn_800EC234(kind);
    }
    if (lbl_8064CB30 != 0) {
        fn_801AC2E8();
    }
    if (lbl_8064CB80 != 0) {
        fn_800EC314(2);
        fn_800EC314(3);
    }
    if (lbl_8064CB84 != 0) {
        fn_80141484(fn_8015C28C(kind)->effect, 0xFF);
    }
    if (lbl_8064CB88 != 0) {
        fn_80143DF0();
    }
    if (lbl_8064CB8C != 0) {
        fn_80140D38();
        fn_80140A58();
    }
    if (lbl_8064CB90 != 0) {
        fn_8014064C();
    }
    if (lbl_8064CBA8 != 0) {
        Vec3* position = fn_8011F130(lbl_8064C4E4);
        float x;
        float y;

        x = lbl_8064C4E4 != 0 ? fn_8011F6F0(lbl_8064C4E4) : lbl_8064F898;
        y = lbl_8064C4E4 != 0 ? fn_8011F6F8(lbl_8064C4E4) : lbl_8064F898;
        fn_801ED468(0x1B);
        DrawObjectInfo(position, lbl_8064C4E4, selfText, x, y);
    }
    if (lbl_8064CBB4 != 0) {
        fn_8013BC34(fn_801E741C(lbl_8024A59C + 0x4B), lbl_8064C4E4);
        fn_8013BC34(fn_801E741C(lbl_8024A59C + 0x57), lbl_8064C4E4);
        fn_8013BC34(fn_801E741C(lbl_8024A59C + 0x63), lbl_8064C4E4);
    }
    if (lbl_8064CBAC != 0) {
        void* object = fn_80201B9C();
        int room = fn_8011FB4C(lbl_8064C4E4);

        while (object != 0) {
            void* actor = fn_80201BC8(object);

            if (actor != 0) {
                Vec3* position = fn_8011F130(actor);
                float x;
                float y;

                x = actor != 0 ? fn_8011F6F0(actor) : lbl_8064F898;
                y = actor != 0 ? fn_8011F6F8(actor) : lbl_8064F898;
                if (actor != 0 && actor != lbl_8064C4E4 && room == fn_8011FB4C(actor)) {
                    DrawObjectInfo(position, actor, text, x, y);
                }
            }
            object = fn_80201BC0(object);
        }
    }
    if (lbl_8064CB34 != 0) {
        fn_800EC6FC(kind);
    }
    if (lbl_8064CB38 != 0) {
        fn_800ECE44(kind);
    }
    if (lbl_8064CB3C != 0) {
        fn_800ED024(kind);
        fn_800ECBE4(kind, 8, 0xFF);
    }
    if (lbl_8064CB44 != 0) {
        Owner* owner = fn_8015C28C(kind);

        fn_801ED468(0x1B);
        fn_801A7958(owner->dataB4, owner->countB0);
    }
    if (lbl_8064CBBC != 0) {
        DebugPath* first = (DebugPath*)(lbl_8063CD18 + 0x110);
        DebugPath* second = (DebugPath*)(lbl_8063C6B8 + 0x110);
        Color color;

        color = lbl_802FC5BC[11];
        fn_800EBA80(2, first, &color, 0x7F, lbl_8064F8D4);
        {
            Color c = lbl_802FC5BC[5];
            fn_800EBA80(2, second, &c, 0x7F, lbl_8064F8D4);
        }
        {
            Color c = lbl_802FC5BC[8];
            fn_800EBA80(2, lbl_8063D4EC, &c, 0x7F, lbl_8064F8D8);
        }
        {
            Color c = lbl_802FC5BC[13];
            fn_800EBA80(2, lbl_8063D4EC + 0xC, &c, 0x7F, lbl_8064F8D8);
        }
        if (first->path != 0) {
            Color c = lbl_802FC5BC[3];
            fn_800EB8B8(first->path, &c);
        }
        if (second->path != 0) {
            Color c = lbl_802FC5BC[3];
            fn_800EB8B8(second->path, &c);
        }
    }
    if (lbl_8064CB54 != 0) {
        fn_802013C4(lbl_8064D18C);
    }
    fn_800EB6BC();
    lbl_8064D6E8 = 0;
}
