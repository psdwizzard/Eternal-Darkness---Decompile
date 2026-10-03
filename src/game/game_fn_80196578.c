typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Object {
    u8 type;
    u8 mode;
    u8 pad02;
    signed char delta;
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[10];
    Color color0;
    Color color1;
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

void fn_80196578(Object* object)
{
    Color color0 = {255, 0, 0, 180};
    Color color1 = {255, 0, 0, 40};

    object->type = 5;
    object->mode = 10;
    object->value04 = 5;
    object->value06 = 100;
    object->value08 = 5;
    object->delta = -30;
    object->color0 = color0;
    object->color1 = color1;
    object->value22 = 180;
    object->value23 = 60;
    object->value20 = 1;
    object->value21 = 10;
    object->value24 = 0;
    object->value1E = 0;
    object->value1C = 500;
    object->value30 = 200;
    object->value40 = 16.0f;
    object->value29 = 7;
    object->value28 = 1;
    object->value2C = 0;
    object->value2B = 2;
}
