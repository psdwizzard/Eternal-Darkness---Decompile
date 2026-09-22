typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Pair { u32 first; u32 second; } Pair;
typedef struct State { void* inherited; u16 flags; u16 pad; } State;
typedef struct Context { u8 pad[0x17C]; State state[24]; } Context;

extern void fn_80125ECC(void*);
extern void fn_8012BFE4(u8*);
extern void fn_8012C478(u8*, int, int);
extern void fn_8012CAC4(u8*, int, void*);

/* NonMatching: honest reconstruction of the complete state-clone path. */
void fn_8012C804(u8* dst, u8* src, int index)
{
    int i;
    int index_offset;
    int offset;
    u8* selected_object;
    u8* graph;
    u8* src_object;
    u16 entry;
    u16 flags;
    void* inherited;

    fn_80125ECC(dst);
    index_offset = index * 4;

    for (i = 0; i < 24; i++) {
        ((Context*)dst)->state[i].flags = 0;
        ((Context*)dst)->state[i].inherited = 0;
    }

    graph = *(u8**)(*(u8**)(*(u8**)(dst + 0x240) + index_offset) + 4);
    for (offset = 0, i = 0; offset < *(u16*)(graph + 6); i += 2, offset++) {
        entry = *(u16*)(*(u8**)(graph + 8) + i);
        if (entry & 0x8000) {
            int child = entry & 0x7FFF;
            src_object = (*(u8***)(src + 0x240))[child];
            if (*(u16*)(src_object + 8) & 1) {
                fn_8012C478(dst, child, 1);
            } else {
                s8 slot = *(s8*)(*(u8**)((*(u8***)(dst + 0x240))[child] + 4) + 0xD);
                if (slot != -1) {
                    *(u16*)(dst + 0x180 + slot * 8) |= 1;
                }
            }
        } else if (((Context*)src)->state[entry].flags & 1) {
            ((Context*)dst)->state[entry].flags |= 1;
        }
    }

    {
        s8 slot = *(s8*)(graph + 0xC);
        if (slot != -1) {
            Context* context = (Context*)dst;
            context->state[slot].flags |= 1;
        }
    }

    for (offset = 0, i = 0; offset < 18; i += 4, offset++) {
        src_object = *(u8**)(*(u8**)(src + 0x240) + i);
        if (src_object != 0) {
            flags = *(u16*)(src_object + 0xA);
            selected_object = *(u8**)(*(u8**)(dst + 0x240) + i);
            if (flags & 0x3F) {
                *(u16*)(selected_object + 0xA) = flags;
                *(u32*)(selected_object + 0x3C) = *(u32*)(src_object + 0x3C);
                *(u16*)(selected_object + 0x40) = *(u16*)(src_object + 0x40);
                *(u32*)(selected_object + 0x54) = *(u32*)(src_object + 0x54);
                *(u16*)(selected_object + 0x58) = *(u16*)(src_object + 0x58);
                *(Pair*)(selected_object + 0x6C) = *(Pair*)(src_object + 0x6C);
            }
        }
    }

    fn_8012BFE4(dst);

    inherited = 0;
    graph = *(u8**)(*(u8**)(*(u8**)(src + 0x240) + index_offset) + 4);
    for (offset = 0, i = 0; offset < *(u16*)(graph + 6); i += 2, offset++) {
        entry = *(u16*)(*(u8**)(graph + 8) + i);
        if (!(entry & 0x8000)) {
            inherited = ((State*)(src + 0x17C))[entry].inherited;
            break;
        }
    }
    if (inherited != 0) {
        *(u16*)(selected_object + 8) = *(u16*)((u8*)inherited + 8);
        *(u32*)(selected_object + 0x2C) = *(u32*)((u8*)inherited + 0x2C);
    }

    fn_8012CAC4(dst, index, selected_object);
    *(float*)(dst + 0x278) = *(float*)(src + 0x278);
}
