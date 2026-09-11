typedef struct EventNode {
    int kind;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    float time;
    int sequence;
    int field_1c;
} EventNode;

extern int lbl_8064C3C0;

extern float fn_80200BDC(void);
extern void fn_8020088C(EventNode *);

void fn_8020104C(int arg0, int arg1, int arg2, int arg3, float delay)
{
    EventNode event;

    event.kind = arg0;
    event.field_04 = arg1;
    event.field_08 = arg2;
    event.field_0c = -1;
    event.field_10 = -1;
    event.time = delay + fn_80200BDC();
    event.field_1c = arg3;
    event.sequence = lbl_8064C3C0++;
    fn_8020088C(&event);
}
