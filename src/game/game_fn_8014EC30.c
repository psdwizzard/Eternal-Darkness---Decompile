typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3Words {
    unsigned int x, y, z;
} Vec3Words;

typedef struct Instance {
    u8 pad0[8];
    u8 second;
    u8 pad9[3];
    unsigned int zero_c;
    unsigned int zero_10;
    u8 pad14[0x1C];
    u16 first;
    u16 third;
    u16 fourth;
    u16 fifth;
    u16 sixth;
    u8 pad3a[2];
    Vec3Words position;
    u8 pad48[0x12E0];
    u8 seventh;
} Instance;

extern void fn_8014EE88(void*);
extern Instance* fn_80149D98(void*);
extern void fn_80149D64(void*);

/* NonMatching: behavior- and size-exact constructor at 97.14286% (168/168
 * bytes). The only remaining divergence is MWCC scheduling the independent
 * result-pointer add after, rather than before, the zero constant load. */
u8* fn_8014EC30(Vec3Words* position, u16 first, u8 second, u16 third,
                 u16 fourth, u16 fifth, u16 sixth, u8 seventh)
{
    register u8* result;
    Instance* object;

    result = 0;
    object = fn_80149D98(fn_8014EE88);
    if (object != 0) {
        fn_80149D64(object);
        result = &object->second;
        object->seventh = seventh;
        object->position = *position;
        object->first = first;
        object->second = second;
        object->third = third;
        object->fourth = fourth;
        object->fifth = fifth;
        object->sixth = sixth;
        object->zero_c = 0;
        object->zero_10 = 0;
    }
    return result;
}
