typedef struct QueueRecord {
    int type;
    int field_4;
    int field_8;
    int field_C;
} QueueRecord;

extern int lbl_8064D2C4;
extern int lbl_8064D2C8;
extern QueueRecord* lbl_8064D2DC;
extern void* lbl_8064D2D8;
extern void* lbl_8064D2D0;

extern void OSJamMessage(void*, void*, int);
extern void OSSendMessage(void*, void*, int);
extern void OSReceiveMessage(void*, void*, int);
extern void fn_8015D44C(void);

void fn_801AA618(void)
{
    QueueRecord* record;

    lbl_8064D2C4 = (lbl_8064D2C4 + 1) % 1024;
    record = &lbl_8064D2DC[lbl_8064D2C4];
    record->type = 1;
    OSJamMessage(lbl_8064D2D8, record, 1);

    lbl_8064D2C4 = (lbl_8064D2C4 + 1) % 1024;
    record = &lbl_8064D2DC[lbl_8064D2C4];
    record->type = 2;
    OSSendMessage(lbl_8064D2D8, record, 1);

    OSReceiveMessage(lbl_8064D2D0, 0, 1);
    lbl_8064D2C8 = 0;
    fn_8015D44C();
}
