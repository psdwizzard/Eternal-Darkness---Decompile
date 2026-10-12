typedef unsigned char u8;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct InteractionState {
    u32 flags;
    u8 pad04[0xBC];
    s32 actor;
} InteractionState;

typedef struct ObjectData {
    u8 pad00[0x8C];
    InteractionState *interaction;
    s32 entry_index;
} ObjectData;

typedef struct Entry {
    char data[0xE0];
} Entry;

extern void *fn_80201B8C(u8 *);
extern Entry *fn_80072354(s32);
extern void *fn_80201B94(u8 *);
extern s32 fn_80201B44(void);
extern s32 fn_80201B54(s32 *);
extern void *fn_80036D5C(void *);
typedef struct Object80201C48 Object80201C48;
extern void *fn_80201C48(Object80201C48 *);
extern u32 fn_8015C910(void);
extern s32 fn_800460EC(void);
extern s32 fn_800CAF7C(void *);
extern void *fn_801E2004(s32);
extern s32 fn_8003BFC8(void *);
extern s32 fn_80201B64(s32 *);
extern s32 fn_800CC650(s32, s32, s32, s32);
extern s32 lbl_8064D5A8;
extern s32 lbl_8064C598;

s32 fn_800CC4DC(s32 object)
{
    ObjectData *data;
    Entry *entry;
    s32 relation;
    s32 result;
    s32 actor;
    s32 allowed;

    data = fn_80201B8C((u8 *)object);
    entry = fn_80072354(data->entry_index);
    relation = (s32)fn_80201B94((u8 *)object);
    result = 0;
    actor = fn_80201B44();
    fn_80201B54((s32 *)object);
    if (!((u32)fn_80036D5C((void *)object) & 8)) {
        if ((u32)relation != 0) {
            s32 owner = (s32)fn_80201C48((Object80201C48 *)relation);
            if (owner != 0 && owner == actor)
                allowed = 1;
            else if (owner == 0)
                allowed = 1;
            else
                allowed = 0;
        } else {
            allowed = 1;
        }
        if (!(lbl_8064D5A8 & 0x1F) && fn_8015C910() == 0 &&
            fn_800460EC() == 0 && allowed != 0 &&
            (!((data->interaction->flags >> 22) & 1) ||
             data->interaction->actor != actor) &&
            lbl_8064C598 != 0 && fn_800CAF7C((void *)object) != 0 &&
            ((s32)fn_801E2004(actor) != 4 || fn_8003BFC8((void *)object) == 0)) {
            s32 kind = fn_80201B64((s32 *)object);
            if (kind != 8 && kind != 9 && kind != 31)
                result = fn_800CC650(object, 8, 23, *(s16 *)(entry->data + 0x90));
        }
    }
    return result;
}
