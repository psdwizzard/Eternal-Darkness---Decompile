typedef unsigned int u32;

typedef struct PacketTemplate {
    u32 word0;
    u32 word1;
    u32 word2;
} PacketTemplate;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_80205868(void*, int, const PacketTemplate*, int);
extern const char lbl_8024FF00[];
extern const PacketTemplate lbl_8023A988;

int fn_80176D14(void* state)
{
    PacketTemplate packet;
    int first;
    int second;
    void* object;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    object = fn_80201814(first);
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            packet = lbl_8023A988;
            fn_80205868(object, second, &packet, 0x2000);
        }
    }
    return 0;
}
