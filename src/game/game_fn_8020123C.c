typedef unsigned long long u64;

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
extern u64 fn_8020088C(EventNode *);

u64 fn_8020123C(int kind, int arg1, int arg2, int arg3)
{
    EventNode event;

    event.kind = kind;
    event.field_04 = arg1;
    event.field_08 = arg2;
    event.field_0c = -1;
    event.field_10 = -1;
    event.time = fn_80200BDC();
    event.field_1c = arg3;
    event.sequence = lbl_8064C3C0++;
    return fn_8020088C(&event);
}
