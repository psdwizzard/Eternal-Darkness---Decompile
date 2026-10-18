typedef unsigned int u32;
typedef int s32;

typedef struct QueueRecord {
    s32 type;
    u32 field_4;
    u32 field_8;
    u32 field_C;
} QueueRecord;

extern unsigned char lbl_80607CD0[];
extern void* lbl_8064D2D0;
extern void* lbl_8064D2D8;
extern void fn_8015D7D4(u32, void*, u32, u32, void*);
extern void OSSendMessage(void*, void*, int);
extern void OSReceiveMessage(void*, void*, int);
extern void VIWaitForRetrace(void);

int fn_801AA4A0(void* arg)
{
    QueueRecord* record;
    int wait = 1;

    for (;;) {
        OSReceiveMessage(lbl_8064D2D8, &record, 1);
        if (record->type == 2)
            break;
        if (record->type == 1) {
            wait = 0;
            continue;
        }
        fn_8015D7D4(record->field_4, lbl_80607CD0, record->field_8,
                    record->field_C, arg);
        if (wait)
            VIWaitForRetrace();
    }
    OSSendMessage(lbl_8064D2D0, 0, 1);
    return 0;
}
