typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Pair {
    u32 first;
    u32 second;
} Pair;
typedef struct Object {
    u8 type;
    u8 mode;
    u8 pad02;
    signed char delta;
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[10];
    Pair pair;
    u16 value1C;
    u16 value1E;
    u8 value20;
    u8 value21;
    u8 value22;
    u8 value23;
    u8 value24;
    u8 pad25[3];
    u8 value28;
    u8 value29;
    u8 pad2A;
    u8 value2B;
    u8 value2C;
    u8 pad2D[3];
    u16 value30;
    u8 pad32[14];
    float value40;
} Object;

extern const u32 lbl_80650B78;
extern const u32 lbl_80650B7C;
extern float lbl_80650B80;

void fn_80196578(Object* object)
{
    u16 hundred = 100;
    signed char delta = -30;
    u8 one_eighty = 180;
    u8 ten = 10;
    u8 sixty = 60;
    u8 one = 1;
    u16 five = 5;
    u8 zero = 0;
    u16 five_hundred = 500;
    u16 two_hundred = 200;
    u8 seven = 7;
    u8 two = 2;
    float scale = lbl_80650B80;
    Pair pair;
    pair.first = lbl_80650B78;
    pair.second = lbl_80650B7C;

    object->mode = ten;
    object->type = five;
    object->value04 = five;
    object->value06 = hundred;
    object->value08 = five;
    object->delta = delta;
    object->pair = pair;
    object->value22 = one_eighty;
    object->value23 = sixty;
    object->value20 = one;
    object->value21 = ten;
    object->value24 = zero;
    object->value1E = zero;
    object->value1C = five_hundred;
    object->value30 = two_hundred;
    object->value40 = scale;
    object->value29 = seven;
    object->value28 = one;
    object->value2C = zero;
    object->value2B = two;
}
