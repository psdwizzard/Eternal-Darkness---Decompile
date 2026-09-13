typedef unsigned short u16;

typedef struct Object {
    unsigned char pad[0x2BC];
    float value;
    float decrement;
    unsigned char pad2[0xE];
    u16 state;
} Object;

extern float lbl_806500A0;
extern float lbl_806500C4;
extern float lbl_806500C8;

void fn_80120B58(Object* object)
{
    if ((object->state & 2) && !(object->state & 0x200)) {
        float value = object->value;
        float decrement = object->decrement;
        float minimum = lbl_806500A0;
        object->value = value - decrement;
        if (object->value <= minimum) {
            object->value = minimum;
            object->state = 0;
        }
    }

    if (object->state & 1) {
        float value = object->value;
        float increment = lbl_806500C4;
        float maximum = lbl_806500C8;
        object->value = value + increment;
        if (maximum == object->value) {
            object->value = maximum;
        }
    }
}
