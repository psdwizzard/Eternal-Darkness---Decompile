typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct ActorPrimary {
    u32 *values;
    char pad4[0xC];
    u32 flags;
    u32 choices;
} ActorPrimary;

typedef struct Actor {
    ActorPrimary *primary;
    void *secondary;
} Actor;

typedef struct Slot {
    int depth;
    void *model;
    char pad8[0x1C];
    Actor *actor;
    int owner;
} Slot;

typedef struct MenuState {
    int owner;
    int unused4;
    int text;
    u32 action;
    u32 flags;
    void *sound;
} MenuState;

typedef struct FadeState {
    char pad0[0x6C];
    void *handle;
} FadeState;

typedef struct TextState {
    u32 flags;
} TextState;

typedef struct Entry Entry;
typedef struct OwnerRecord OwnerRecord;

typedef struct SlotTable {
    Slot previous[6];
    Slot current[6];
    Slot previousShadow[6];
    Slot shadow[6];
    Slot extra[32];
    void *lists[6];
} SlotTable;

extern SlotTable lbl_80330D80;
extern MenuState lbl_80332140;
extern u32 lbl_80331748[];
extern FadeState lbl_8024B3E4;
extern u32 *lbl_8064C4E0;
extern void *lbl_8064C4E4;
extern void *lbl_8064C504;
extern int lbl_8064CCA8;
extern int lbl_8064CCB0;
extern float lbl_8064CCB8;
extern int lbl_8064CCC4;
extern void *lbl_8064CCC8;
extern int lbl_8064CCD0;
extern int lbl_8064CCD4;
extern int lbl_8064CCDC;
extern int lbl_8064CD70;
extern void *lbl_8064CDB0;
extern void *lbl_8064CDB4;
extern int lbl_8064CDC8;
extern float lbl_8064FE74;

extern void fn_80027730(u32, int);
extern void *fn_8004914C(void);
extern void *fn_8004918C(void);
extern int fn_80070A6C(u32);
extern void fn_800CC140(int, int, int, u32, int);
extern int fn_800CC2D8(void *, int);
extern int fn_8010A32C(int, int, int);
extern int fn_8010B194(int);
/* Retail passes owner and mode to this callee, which ignores its inputs. */
extern void fn_8010F218();
extern void fn_80117EF0(void);
extern void fn_8012B324(void *);
extern void fn_8012C478(void *, int, int);
extern void fn_80144C40(void);
extern int fn_80155D9C(int);
extern u32 fn_80157888(Actor *);
extern u32 fn_80157894(Actor *);
extern u32 fn_801578A0(Actor *);
extern u32 fn_801578AC(Actor *);
extern short fn_801578E8(Actor *);
extern short fn_801578F4(Actor *);
extern short fn_8015790C(Actor *);
extern u16 fn_80157994(Actor *);
extern int fn_801579EC(Actor *);
extern u8 fn_80157AB8(Actor *);
extern void fn_80157AC4(Actor *, u32);
extern u32 fn_80157C98(Actor *, u32, u32);
extern int fn_8015821C(Actor *);
extern int fn_80158390(OwnerRecord *, u32 ***, int);
extern u32 fn_80158550(OwnerRecord *, int);
extern OwnerRecord *fn_80158598(int, int);
extern void fn_8016B400(int, void *, void *);
extern int fn_801A98F4(int, void *);
extern int fn_801B05E8(int, u8, u8, u8, void *, u8, int, int);
extern void *fn_801E5D20(void *);
extern void fn_801E5FB0(void *);
extern void *fn_801E6CA0(void *, u32, u32, u32, int);
extern int fn_801E79FC(u32 *, u32);
extern void fn_801E8B24(void *, int, int);
extern void fn_801E8B6C(void *, short);
extern int fn_801E8D24(void *);
extern int fn_801E8D34(void *);
extern int fn_801E8D3C(void *);
extern Entry *fn_80201814(int);
extern Entry *fn_80201B3C(void);
extern int fn_80201B44(void);
extern Actor *fn_80201C24(Entry *);
extern void *fn_802053B0(Entry *, Actor *);

void fn_8010C3F4(int owner, int mode)
{
    unsigned char *base = (unsigned char *)&lbl_80330D80;
    register void **lists = (void **)(base + 0x9A0);
    OwnerRecord *record;
    int row;
    register Actor **currentActor;
    register Actor **shadowActor;
    register Actor *selectedShadow;
    register Slot *shadowBank;
    u32 flags;
    TextState *text;
    u32 primaryFlags;
    u32 value;
    u32 selection;
    int otherOffset;
    Actor *selectedActor;
    Actor *actor;
    int currentOffset;
    int cursor;
    int ready;
    int script;
    u32 mask;
    int alternateScript;
    int index;
    void *object;
    int context;
    int otherCursor;

    row = fn_801E8D24(lists[1]) * 2;
    cursor = fn_801E8D24(((void **)(base + 0x9A0))[0]) + row;
    fn_80144C40();
    if ((lbl_80332140.flags & 1) && lbl_8064CCC4 > 0) {
        register Slot *currentBank;
        register Slot *shadowBank;
        currentBank = (Slot *)(base + 0x108);
        shadowBank = (Slot *)(base + 0x318);

        /* ASM: mr keeps the two slot-bank bases distinct. MWCC otherwise
         * combines their offsets with the index before loading fields. */
        asm {
            mr currentBank, currentBank
            mr shadowBank, shadowBank
        }
        selectedActor = currentBank[cursor].actor;
        if (shadowBank[cursor].actor != 0) {
            selectedActor = shadowBank[cursor].actor;
        }
        flags = fn_80157894(selectedActor);
        if ((flags & 1) || ((fn_80157888(selectedActor) & 1) &&
            (fn_80157AB8(selectedActor) == 0 || !(flags & 0x100)))) {
            lbl_8064CDC8 = 2;
            owner = lbl_80332140.owner;
            lbl_8064CD70 = 1;
            lbl_80331748[0xAC / 4] = lbl_80332140.action | 0x80000000;
            actor = fn_80201C24(fn_80201814(owner));
            index = fn_801579EC(actor);
            if (index != 0) {
                owner = index;
                actor = fn_80201C24(fn_80201814(owner));
            }
            primaryFlags = fn_80157888(actor);
            flags = fn_80157894(actor);
            if (!(flags & 1) && (primaryFlags & 1) &&
                (fn_80157AB8(actor) == 0 || !(flags & 0x100))) {
                record = fn_80158598(fn_80201B44(), 0);
                if (fn_80158550(record, owner) == 0) {
                    index = fn_80158390(record, (u32 ***)actor, 1);
                    if (index >= 0) {
                        value = actor->primary->values[index];
                        fn_80155D9C(0);
                        fn_800CC140(fn_80201B44(), owner, 0, value, 0);
                        lbl_8064CD70 = 1;
                        fn_80155D9C(1);
                    }
                }
            }
        } else {
            void *message = fn_801E6CA0(lbl_8064C504, 0, 6, 0, 1);
            /* ASM: li clears retail's unused third argument register;
             * the actual C callee only accepts two arguments. */
            asm { li r5, 0 }
            fn_80027730((u32)message, 0);
        }
        return;
    }

    switch (lbl_8064CCD4) {
    case 4:
        ready = 1;
        text = fn_801E5D20(lbl_8024B3E4.handle);
        {
            register Slot *bank = (Slot *)(base + 0x108);
            register Actor *selected;
            /* ASM: mr preserves the bank base before indexing; MWCC
             * otherwise folds the bank and field offsets together. */
            asm { mr bank, bank }
            currentActor = (Actor **)&bank[cursor];
            /* ASM: lwzu loads the actor and retains its field address.
             * MWCC keeps the slot base and emits repeated offset loads
             * for the equivalent C pointer update and dereference. */
            asm { lwzu selected, 0x24(currentActor) }
            alternateScript = fn_801578F4(selected);
        }
        if (text != 0 && (text->flags & 0x10) && !(text->flags & 0x4000)) {
            ready = 0;
        }
        if (text != 0 && !(text->flags & 8)) {
            ready = 0;
        }
        fn_8010F218(owner, mode);
        if (ready) {
            if (fn_80157894(*currentActor) & 0x20) {
                script = fn_801578E8(*currentActor);
                if (script != 0) {
                    fn_801E5FB0(lbl_8024B3E4.handle);
                    lbl_8024B3E4.handle = 0;
                    fn_801A98F4(0x222, (void *)100);
                    fn_80155D9C(0);
                    {
                        register Slot *bank = (Slot *)(base + 0x108);
                        /* ASM: mr prevents MWCC from reusing the full slot
                         * pointer where retail recomputes bank plus index. */
                        asm { mr bank, bank }
                        fn_8016B400(script, (void *)bank[cursor].owner, 0);
                    }
                    lbl_8064CCD0 = 2;
                    fn_80155D9C(1);
                }
            }
            if (alternateScript != 0) {
                fn_801E5FB0(lbl_8024B3E4.handle);
                lbl_8024B3E4.handle = 0;
                fn_801A98F4(0x222, (void *)100);
                fn_80155D9C(0);
                {
                    register Slot *bank = (Slot *)(base + 0x108);
                    /* ASM: mr preserves bank-plus-index addressing, which
                     * MWCC otherwise folds into the field load. */
                    asm { mr bank, bank }
                    fn_8016B400(alternateScript, (void *)bank[cursor].owner, 0);
                }
                lbl_8064CCD0 = 2;
                fn_80155D9C(1);
            }
        }
        break;
    case 2: {
        register void **otherLists;
        otherLists = (void **)(base + 0x9A0);
        /* ASM: mr preserves the secondary list base; MWCC folds the C
         * address into the offsets of the subsequent list loads. */
        asm { mr otherLists, otherLists }
        row = fn_801E8D24(otherLists[4]) * 2;
        otherCursor = fn_801E8D24(otherLists[3]) + row;
        currentOffset = fn_801E8D3C(lists[1]) * 2;
        otherOffset = fn_801E8D3C(otherLists[4]) * 2;
        fn_801E5FB0(lbl_8064CCC8);
        lbl_8064CCC8 = 0;
        if (otherCursor + otherOffset != cursor + currentOffset) {
            fn_801A98F4(0x222, (void *)100);
            fn_80155D9C(0);
            fn_8016B400(lbl_8064CCA8, 0, 0);
            lbl_8064CCD0 = 2;
            fn_80155D9C(1);
            if (lbl_8064CDC8 == 3) {
                lbl_8064CCD4 = 0;
                fn_80117EF0();
                lbl_8064CCC4 = fn_8010A32C(fn_801E8D3C(lists[1]) * 2, 0, 6);
            }
            fn_801E5FB0(lbl_8024B3E4.handle);
            lbl_8024B3E4.handle = 0;
        }
        break;
    }
    case 1:
        fn_801A98F4(0x222, (void *)100);
        shadowBank = (Slot *)(base + 0x318);
        shadowActor = (Actor **)&shadowBank[cursor];
        /* ASM: lwzu loads the actor while retaining its field address;
         * C makes MWCC retain an index and issue indexed loads instead. */
        asm { lwzu selectedShadow, 0x24(shadowActor) }
        if (selectedShadow != 0) {
            context = shadowBank[cursor].owner;
            script = fn_801578E8(selectedShadow);
            fn_8015790C(*shadowActor);
            /* ASM: stw consumes the callee's already sign-extended r3.
             * A C assignment from its short return adds an extra extsh. */
            asm { stw r3, lbl_8064CCA8(r13) }
        } else {
            register Slot *bank = (Slot *)(base + 0x108);

            currentActor = &bank[cursor].actor;
            context = bank[cursor].owner;
            script = fn_801578E8(bank[cursor].actor);
            fn_8015790C(*currentActor);
            /* ASM: stw saves the sign-extended short already in r3;
             * MWCC inserts a redundant extsh for the C assignment. */
            asm { stw r3, lbl_8064CCA8(r13) }
        }
        switch (fn_801E8D24(((void **)(base + 0x9A0))[2])) {
        case 0: {
            register Slot *bank = (Slot *)(base + 0x108);
            /* ASM: mr preserves the bank base before this indexed test;
             * MWCC combines the bank and field offsets in C. */
            asm { mr bank, bank }
            if (bank[cursor].actor != 0) {
                fn_80155D9C(0);
                fn_8016B400(script, (void *)context, 0);
                lbl_8064CCD0 = 2;
                fn_80155D9C(1);
                lbl_8064CCD4 = 0;
            }
            break;
        }
        case 1:
            if (fn_80070A6C(0x1000) == 0) {
                if (*shadowActor != 0) {
                    value = (*shadowActor)->primary->values[0];
                } else {
                    register Slot *bank = (Slot *)(base + 0x108);
                    /* ASM: mr preserves bank-plus-index addressing;
                     * MWCC otherwise folds both offsets into the load. */
                    asm { mr bank, bank }
                    value = bank[cursor].actor->primary->values[0];
                }
                fn_80155D9C(0);
                fn_800CC140(fn_80201B44(), context, 0, value, 0);
                lbl_8064CD70 = 1;
                fn_80155D9C(1);
                fn_80117EF0();
                lbl_8064CCC4 = fn_8010A32C(fn_801E8D3C(lists[1]) * 2, 0, 6);
            } else {
                void *message = fn_801E6CA0(lbl_8064C504, 0, 0x33, 0, 1);
                /* ASM: li clears retail's unused third argument register;
                 * the actual C callee only accepts two arguments. */
                asm { li r5, 0 }
                fn_80027730((u32)message, 0);
            }
            lbl_8064CCD4 = 0;
            break;
        case 2: {
            register Slot *bank = (Slot *)(base + 0x108);
            /* ASM: mr requires the bank base to remain distinct from
             * the field offset, which MWCC folds in C. */
            asm { mr bank, bank }
            actor = bank[cursor].actor;
            lbl_8064CCD4 = 3;
            lbl_8064CCB0 = 0;
            lbl_8064CCB8 = lbl_8064FE74;
            if (fn_8015821C(actor) == 0x1F && fn_801E79FC(lbl_8064C4E0, 0x10A) == 0) {
                lbl_8064CCDC = fn_801B05E8(0xC, 100, 6, 1, 0, 5, 0, 0);
            } else if (fn_8015821C(actor) == 0x3D) {
                lbl_8064CCDC = fn_801B05E8(0x44, 100, 6, 1, 0, 5, 0, 0);
            }
            fn_801E5FB0(lbl_8064CCC8);
            lbl_8064CCC8 = 0;
            break;
        }
        case 3:
            currentOffset = fn_801E8D3C(((void **)(base + 0x9A0))[0]);
            fn_801E8B24(((void **)(base + 0x9A0))[3], fn_801E8D34(((void **)(base + 0x9A0))[0]), currentOffset);
            currentOffset = fn_801E8D3C(lists[1]);
            fn_801E8B24(((void **)(base + 0x9A0))[4], fn_801E8D34(lists[1]), currentOffset);
            lbl_8064CCD4 = 2;
            fn_801E5FB0(lbl_8064CCC8);
            lbl_8064CCC8 = 0;
            break;
        case 4: {
            register Slot *bank = (Slot *)(base + 0x108);
            /* ASM: mr preserves the bank base while MWCC folds that
             * address into the indexed load in an ordinary C expression. */
            asm { mr bank, bank }
            actor = bank[cursor].actor;
            mask = fn_801578A0(actor);
            selection = fn_801578AC(actor);
            do {
                selection <<= 1;
                if (selection == 0) {
                    selection = 1;
                }
                if (mask & selection) {
                    if (lbl_8064C4E4 != 0) {
                        fn_8012B324(lbl_8064C4E4);
                    }
                    fn_80157AC4(actor, selection);
                    if (fn_80157994(actor) != 0) {
                        fn_80157C98(actor, 0xA0, 0);
                    } else if (fn_802053B0(fn_80201B3C(), actor) != 0) {
                        fn_80157C98(actor, 0x80, 0x20);
                    } else {
                        fn_80157C98(actor, 0x20, 0x80);
                    }
                    fn_8004918C();
                    object = fn_8004914C();
                    if (object != 0) {
                        if ((u8)fn_800CC2D8(object, 0) != 0) {
                            fn_8012C478(object, 0x10, 0);
                        }
                        if ((u8)fn_800CC2D8(object, 1) != 0) {
                            fn_8012C478(object, 0x11, 0);
                        }
                    }
                    break;
                }
            } while (mask != 0);
            break;
        }
        }
        break;
    case 0:
        if (lbl_8064CCC4 > 0) {
            register void **otherLists;
            fn_801A98F4(0x222, (void *)100);
            otherLists = (void **)(base + 0x9A0);

            if (fn_8010B194(fn_801E8D34(otherLists[2])) == 0) {
                fn_801E8B24(otherLists[2], 0, 0);
                fn_801E8B6C(otherLists[2], 0);
            }
            fn_801E5FB0(lbl_8064CCC8);
            lbl_8064CCC8 = 0;
            lbl_8064CCD4 = 1;
            fn_801E5FB0(lbl_8064CDB4);
            lbl_8064CDB4 = 0;
            fn_801E5FB0(lbl_8064CDB0);
            lbl_8064CDB0 = 0;
        }
        break;
    case 3:
    case 5:
        break;
    }
}
