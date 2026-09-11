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

extern float fn_80200BDC(void);
extern void fn_8020088C(EventNode *);

void fn_802011D4(EventNode *source)
{
    EventNode event;

    event.kind = source->kind;
    event.field_04 = source->field_04;
    event.field_08 = source->field_08;
    event.field_0c = 0;
    event.field_10 = -1;
    event.time = fn_80200BDC();
    event.field_1c = source->field_1c;
    fn_8020088C(&event);
}
