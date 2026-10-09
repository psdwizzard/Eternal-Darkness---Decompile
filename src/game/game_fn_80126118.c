typedef unsigned char u8;

typedef struct Owner {
    u8 pad[0x3C];
    void* header;
} Owner;

typedef struct RuntimeState RuntimeState;
typedef struct StateEntry StateEntry;

/* Layout of the owner's pointers into the supplied working storage. */
typedef struct OwnerLayout {
    u8 pad_0[0x23C];
    StateEntry* states;
    StateEntry** state_by_id;
    u8 pad_244[0x4C];
    RuntimeState* runtime_state;
    u8 pad_294[0x10];
    void* storage;
} OwnerLayout;

extern void* memset(void*, int, unsigned long);
extern void fn_8012C0A8(u8*);
extern void fn_8012BE94(Owner*, void*);
extern void fn_8012BFE4(u8*);
extern void fn_8012FEC8(RuntimeState*);
extern void (*lbl_8064CF18)(Owner*);

void fn_80126118(Owner* owner, u8* storage)
{
    OwnerLayout* layout = (OwnerLayout*)owner;

    memset(storage, 0, 0x768);
    layout->storage = storage;
    layout->states = (StateEntry*)(storage + 4);
    layout->state_by_id = (StateEntry**)(storage + 0x6C4);
    layout->runtime_state = (RuntimeState*)(storage + 0x70C);
    *(Owner**)storage = owner;

    if (owner->header != 0) {
        fn_8012C0A8((u8*)owner);
        fn_8012BE94(owner, owner->header);
        fn_8012BFE4((u8*)owner);
    }
    fn_8012FEC8(layout->runtime_state);
    if (lbl_8064CF18 != 0) {
        lbl_8064CF18(owner);
    }
}
