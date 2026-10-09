typedef unsigned char u8;
typedef unsigned int u32;

typedef struct NOTE Note;
struct NOTE {
    Note* next;
    Note* prev;
    u32 voiceId;
    int endTime;
    u8 section;
    u8 pad11[3];
};

typedef struct SEQ_INSTANCE Sequence;
struct SEQ_INSTANCE {
    Sequence* next;
    Sequence* prev;
    u8 state;
    u8 index;
    u8 pad0A[2];
    u32 publicId;
    u8 pad010[0xE64 - 0x10];
    Note* noteUsed[2];
    Note* noteKeyOff;
    u8 padE70[0xEDA - 0xE70];
    u8 syncCrossFlags;
    u8 padEDB;
    u32* syncSeqIdPtr;
    u8 padEE0[0x1868 - 0xEE0];
};

typedef struct SequenceStorage {
    u8 pad[0x1400];
    Sequence instances[8];
} SequenceStorage;

extern SequenceStorage lbl_8060C020;
extern Sequence* lbl_8064D394;
extern Sequence* lbl_8064D398;
extern Sequence* lbl_8064D39C;
extern void fn_801B244C(Sequence*);
extern int fn_801C21E8(u32);

/* Preserve the public handle's high bit when converting to a sequence index. */
static inline u32 resolve_handle(u32 handle)
{
    u32 key = handle & 0x7FFFFFFF;
    u32 id;
    Sequence* search = lbl_8064D39C;
    while (search != 0) {
        if (search->publicId == key) {
            id = __rlwimi(search->index, handle, 0, 0, 0);
            return id;
        }
        search = search->next;
    }
    search = lbl_8064D398;
    while (search != 0) {
        if (search->publicId == key) {
            id = __rlwimi(search->index, handle, 0, 0, 0);
            return id;
        }
        search = search->next;
    }
    id = -1;
    return id;
}

void fn_801B3770(register u32 handle)
{
    register SequenceStorage* entries = &lbl_8060C020;
    u32 i;
    Note* note;
    register u8* cursor;
    register Sequence* node;
    register u32 offset;
    register u32 flag;
    handle = resolve_handle(handle);
    if (handle == 0xFFFFFFFFU) {
        return;
    }
    /* ASM: rlwinm. and bne test the handle flag without the separate comparison emitted by C. */
    asm {
        rlwinm. flag, handle, 0, 0, 0
        bne deferred_path
    }
    {
        u8 state;
        offset = handle * sizeof(Sequence);
        /* ASM: add retains the base-plus-index address in the sequence pointer; C splits its live range before the state load. */
        asm { add node, entries, offset }
        state = *((u8*)node + 0x1408);
        node = (Sequence*)((u8*)node + 0x1400);
        switch (state) {
        case 1:
            if (node->prev != 0) {
                node->prev->next = node->next;
            } else {
                lbl_8064D39C = node->next;
            }
            i = 0;
            /* ASM: addi preserves the zero-displacement address operation; C emits mr for this cursor initialization. */
            asm { addi cursor, node, 0 }
            do {
                note = ((Sequence*)cursor)->noteUsed[0];
                while (note) {
                    fn_801C21E8(note->voiceId);
                    note = note->next;
                }
                cursor += sizeof(Note*);
            } while (++i < 2);
            {
                register SequenceStorage* links;
                Note* link;
                /* ASM: add preserves base-plus-index addressing; C selects an indexed load after folding the field displacement. */
                asm { add links, entries, offset }
                link = links->instances[0].noteKeyOff;
                while (link) {
                    fn_801C21E8(link->voiceId);
                    link = link->next;
                }
            }
            fn_801B244C(node);
            break;
        case 2:
            if (node->prev != 0) {
                node->prev->next = node->next;
            } else {
                lbl_8064D398 = node->next;
            }
            break;
        }
        if (node->next != 0) {
            node->next->prev = node->prev;
        }
        node->state = 0;
        {
            Sequence* free = lbl_8064D394;
            if (free != 0) {
                free->prev = node;
            }
        }
        node->next = lbl_8064D394;
        node->prev = 0;
        lbl_8064D394 = node;
    }
    return;
deferred_path:
    {
        u8* entry = (u8*)entries + (handle & 0x7FFFFFFF) * sizeof(Sequence);
        u8 state = entry[0x1408];
        Sequence* deferred = (Sequence*)(entry + 0x1400);
        if (state != 0) {
            deferred->syncSeqIdPtr = 0;
        }
    }
}
