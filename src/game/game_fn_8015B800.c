typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Entry { s16 id; s16 active; u8 pad[0x14]; } Entry;
typedef struct Shared { int primary; int secondary; s16 requested; u8 padA[2]; void* slots[2]; } Shared;

extern Shared lbl_805B6FE0;
extern Entry lbl_805B6F80[];
extern u8 lbl_805DB240[];
extern u8 lbl_805E27DC[];
extern u8 lbl_805E7560[];
extern int lbl_8064D144;
extern void fn_80158E7C(int);
extern int fn_80158E88(s16);
extern int fn_80158ECC(int);
extern void fn_80158F6C(s16, int);
extern int fn_8015A12C(void);
extern int fn_8015E51C(void);
extern int fn_8015E548(int);
extern void fn_80159DD0(s16, int);
extern void fn_8015DEC4(void);
extern void fn_8015DF24(void);
extern void fn_8020D250(void*, int, int);
extern int fn_8020D318(void*, u32*, int);
extern void fn_802101F4(void*, int);

static s16 slot_id(int slot)
{
    return *(s16*)((u8*)lbl_805B6FE0.slots[slot] + 0x8140);
}

static s8 slot_busy(int slot)
{
    return *(s8*)((u8*)lbl_805B6FE0.slots[slot] + 0x8142);
}

/* NonMatching: unsigned queue storage is required for the -1/-2 sentinel
 * tests, while the signed cast below reproduces retail's cmpwi for message 1.
 * The remaining object-level differences are documented in the assignment
 * objdiff evidence and durable result. */
void fn_8015B800(void)
{
    u32 message;
    int action;
    int current;
    int selection = -1;
    int state = 0;
    int found;

    fn_80158E7C(5);
    for (;;) {
        fn_8020D318(lbl_805E27DC, &message, 1);
        if (message == 0xFFFFFFFF) {
            fn_8020D250(lbl_805DB240, 43, 1);
            do fn_8020D318(lbl_805E27DC, &message, 1); while (message != 0xFFFFFFFE);
            message = 0;
            state = 0;
            selection = -1;
            continue;
        }
        fn_80158E7C(6);
        if ((int)message == 1) state = 0;
        current = lbl_805B6FE0.secondary;
        action = 0;
        if (!slot_busy(lbl_805B6FE0.primary)) {
            found = fn_80158E88(slot_id(lbl_805B6FE0.primary));
            if (found == -1 || lbl_805B6F80[found].active == 0)
                action = 11;
            else
                action = 10;
        } else if (fn_8015E51C()) action = 9;
        else if (fn_8015E548(3)) action = 8;
        else if (lbl_805B6FE0.requested != -1) {
            if (current != -1 && !slot_busy(current)) {
                found = fn_80158E88(lbl_805B6FE0.requested);
                if (found == -1 || lbl_805B6F80[found].active == 0)
                    action = 7;
                else
                    action = 6;
            }
        } else if (current != -1 && slot_id(current) != -1 && !slot_busy(current)) {
            found = fn_80158E88(slot_id(lbl_805B6FE0.primary));
            if (found == -1 || lbl_805B6F80[found].active == 0)
                action = 5;
            else
                action = 4;
        } else if (fn_8015E548(2)) action = 3;
        if (!action) {
            selection = fn_8015A12C();
            if (selection != -1) action = 2;
        }
        if (action) {
            if (action > state && state) {
                lbl_8064D144 = 1;
                continue;
            }
            if (state == action) continue;
            state = action;
            switch (action) {
            case 2: fn_802101F4(lbl_805E7560, 11); fn_80159DD0(lbl_805B6F80[selection].id, selection); break;
            case 3: fn_802101F4(lbl_805E7560, 21); if (current != -1) fn_80158F6C(slot_id(current), current); break;
            case 4: fn_802101F4(lbl_805E7560, 11); if (current != -1) fn_80158ECC(slot_id(current)); break;
            case 5: fn_802101F4(lbl_805E7560, 21); if (current != -1) fn_80158F6C(lbl_805B6FE0.requested, current); break;
            case 6: fn_802101F4(lbl_805E7560, 11); fn_80158ECC(lbl_805B6FE0.requested); break;
            case 7: fn_802101F4(lbl_805E7560, 21); fn_8015DF24(); break;
            case 8: fn_802101F4(lbl_805E7560, 21); fn_8015DF24(); break;
            case 9: fn_802101F4(lbl_805E7560, 11); fn_8015DF24(); break;
            case 10: fn_802101F4(lbl_805E7560, 11); fn_8015DEC4(); break;
            case 11: fn_802101F4(lbl_805E7560, 11); fn_80158F6C(slot_id(lbl_805B6FE0.primary), lbl_805B6FE0.primary); break;
            default: fn_802101F4(lbl_805E7560, 11); fn_80158ECC(slot_id(lbl_805B6FE0.primary)); break;
            }
        } else fn_80158E7C(7);
    }
}
