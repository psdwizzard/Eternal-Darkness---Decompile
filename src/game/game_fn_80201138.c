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

extern int fn_80201B54(void *);
extern float fn_80200BDC(void);
extern void fn_8020088C(EventNode *);

void fn_80201138(int kind, void *context, int value, int id, int arg4,
                 float delay)
{
    EventNode event;

    event.kind = kind;
    event.field_04 = fn_80201B54(context);
    event.field_08 = fn_80201B54(context);
    event.field_0c = value;
    event.field_10 = id;
    event.time = delay + fn_80200BDC();
    event.field_1c = arg4;
    fn_8020088C(&event);
}
