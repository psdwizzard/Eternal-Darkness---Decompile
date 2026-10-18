typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct GameState {
    u8 byte_00;
    u8 byte_01;
    u8 pad_02[2];
    u16 half_04;
    u8 pad_06[6];
    s32 word_0C;
    u8 pad_10[4];
    s32 word_14;
    s32 word_18;
    s32 word_1C;
    s32 word_20;
    u8 pad_24[2];
    u8 byte_26;
    u8 byte_27;
    u8 pad_28[2];
    u16 half_2A;
    float float_2C;
    s32 word_30;
    s32 word_34;
    u8 pad_38[0x5C];
    s32 word_94;
    u8 pad_98[0x10];
    s32 word_A8;
    u8 pad_AC[0x10];
    u8 byte_BC;
    u8 pad_BD[3];
    void* object_C0;
} GameState;

typedef struct CreatedObject {
    u8 pad_00[8];
    s32 word_08;
    u8 pad_0C[0x3C];
    s32 word_48;
} CreatedObject;

typedef struct PairSource {
    s32 first;
    u8 pad_04[8];
    s32 second;
} PairSource;

extern const char lbl_8023BEF8[];
extern GameState lbl_803020E4;
extern PairSource lbl_802FC5BC;
extern void* lbl_8064C618;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80187A34(void*, s32);
extern void fn_801878E0(void*);
extern CreatedObject* fn_80149E04(void);
extern void fn_80147E88(GameState*);
extern void fn_801498AC(GameState*, CreatedObject*);
extern void fn_80187968(GameState*);
extern int fn_80201B44();
extern int fn_801E8328();

s32 fn_800159B0(void* script)
{
    s32 mode;
    s32 third;
    float fourth;
    s32 fifth;
    CreatedObject* object;
    void* current;

    if (lua_gettop(script) != 5) {
        luaO_verror(script, lbl_8023BEF8, 5, lua_gettop(script));
        return 0;
    }

    mode = (s32)lua_tonumber(script, 1);
    lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (float)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);

    switch (mode) {
    case 0:
        if (lbl_803020E4.object_C0 != 0) {
            current = *(void**)((u8*)lbl_803020E4.object_C0 + 0x88);
            lbl_8064C618 = current;
            if (current != 0) {
                fn_80187A34(current, 1);
            }
        }
        break;
    case 1:
        if (lbl_803020E4.object_C0 != 0) {
            current = *(void**)((u8*)lbl_803020E4.object_C0 + 0x88);
            lbl_8064C618 = current;
            if (current != 0) {
                fn_801878E0(current);
            }
        }
        break;
    case 2:
        object = lbl_803020E4.object_C0 = fn_80149E04();
        if (object != 0) {
            fn_80147E88(&lbl_803020E4);
            fn_801498AC(&lbl_803020E4, object);
            lbl_803020E4.byte_BC = 4;
            object->word_08 = 0;
            object->word_48 = 1;
            lbl_803020E4.word_94 = 0;
            fn_80187968(&lbl_803020E4);

            lbl_803020E4.byte_01 = 0x10;
            lbl_803020E4.half_04 = 6;
            lbl_803020E4.word_14 = 1;
            lbl_803020E4.word_18 = 1;
            lbl_803020E4.word_1C = 0;
            lbl_803020E4.word_20 = 1;
            lbl_803020E4.word_30 = lbl_802FC5BC.first;
            lbl_803020E4.word_34 = lbl_802FC5BC.second;
            lbl_803020E4.half_2A = 600;
            lbl_803020E4.byte_26 = third;
            lbl_803020E4.float_2C = fourth;
            lbl_803020E4.byte_27 = fifth;
            lbl_803020E4.word_A8 = fn_80201B44();
            fn_801E8328(0x11);
        }
        break;
    }

    return 0;
}
