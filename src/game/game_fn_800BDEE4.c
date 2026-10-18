typedef struct RuntimeState {
    unsigned char pad[0xAC];
    int pool_index;
    int slot_index;
} RuntimeState;

typedef struct Slot {
    int index;
    int object_id;
    int start_frame;
    int last_frame;
    int count;
    unsigned char flags;
    unsigned char pad15[3];
} Slot;

extern void *fn_8015C28C(int);
extern int fn_800BD944(void);
extern int fn_80201B54(int);
extern int fn_800BD194(int, RuntimeState *);
extern int OSSendMessage(unsigned char *, int, int);
extern Slot lbl_80320DF0[];
extern unsigned char lbl_805E2B1C[];
extern int lbl_8064D5A8;

int fn_800BDEE4(int object, RuntimeState *runtime)
{
    int result = 0;
    int object_id;
    int slot_index;
    unsigned char *resource;

    resource = (unsigned char *)fn_8015C28C(2);
    if (resource != 0 &&
        (signed char)resource[0x8143] != 0 &&
        (signed char)resource[0x8142] != 0 &&
        fn_800BD944() != 0) {
        object_id = fn_80201B54(object);
        if (runtime->slot_index < 0 && runtime->pool_index < 0)
            fn_800BD194(object, runtime);

        slot_index = runtime->slot_index;
        if ((lbl_80320DF0[slot_index].flags & 2) == 0) {
            result = OSSendMessage(lbl_805E2B1C, object_id, 0);
            if (result != 0) {
                if (lbl_80320DF0[slot_index].index == -1)
                    lbl_80320DF0[slot_index].index = -2;
                lbl_80320DF0[slot_index].flags |= 2;
                lbl_80320DF0[slot_index].last_frame = lbl_8064D5A8;
            }
        }
    }
    return result;
}
