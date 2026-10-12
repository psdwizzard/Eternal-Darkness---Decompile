typedef unsigned char u8;
typedef unsigned int u32;

/* Keep the owner opaque: the callees use different layout views. */
typedef struct Owner Owner;

typedef struct SlotState {
    u32 age : 31;
    u32 flag : 1;
} SlotState;

typedef struct Slot {
    Owner* owner;
    u8 pad_004[0x760];
    SlotState state;
} Slot;

typedef struct OwnerLayout {
    u8 pad_000[0x2A4];
    Slot* slot;
} OwnerLayout;

extern u8 lbl_80500500[];
extern int lbl_8064CF1C;
extern void fn_80125DE0(Owner*);
extern void fn_80126118(Owner*, u8*);
extern void fn_80125DD0(void);

void fn_80125ECC(Owner* owner)
{
    u32 age;
    Slot* candidate;
    u32 index;
    SlotState* state;
    int i = 0;
    u32 oldest_age = 0;
    int chosen = 0;
    Slot* slot;

    if (((OwnerLayout*)owner)->slot == 0) {
        for (; i < 44; i++) {
            index = lbl_8064CF1C;
            candidate = (Slot*)(lbl_80500500 + index * 0x768);
            state = &candidate->state;
            age = state->age;

            if (age > oldest_age && !candidate->state.flag) {
                chosen = index;
                oldest_age = age;
            }
            state->age++;
            if (candidate->owner == 0) {
                chosen = index;
                i = 44;
            }
            lbl_8064CF1C++;
            if (lbl_8064CF1C >= 44)
                lbl_8064CF1C = 0;
        }
        slot = (Slot*)(lbl_80500500 + chosen * 0x768);
        if (slot->owner != 0)
            fn_80125DE0(slot->owner);
        fn_80126118(owner, (u8*)slot);
        fn_80125DD0();
    }
    ((OwnerLayout*)owner)->slot->state.age = 0;
}
