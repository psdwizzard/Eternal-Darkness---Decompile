typedef signed char s8;
typedef unsigned char u8;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct ColorStep {
    s8 r, g, b, a;
} ColorStep;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_8012C62C(void*, int, void*, void*, void*, int);
extern const char lbl_8024FF00[];

int fn_801755FC(void* state)
{
    Color first;
    Color second;
    ColorStep directions;
    Color call_first;
    ColorStep call_directions;
    Color call_second;
    s8 delta;
    int index;
    void* runtime;
    void* object;

    if (fn_8016A598(state) != 10) {
        fn_80163BB4(state, lbl_8024FF00, 10, fn_8016A598(state));
        return 0;
    }

    runtime = fn_80201814((int)fn_8016A694(state, 1));
    if (runtime != 0) {
        object = fn_80201BC8();
        if (object != 0) {
            index = fn_8016A694(state, 2);
            first.r = fn_8016A694(state, 3);
            first.g = fn_8016A694(state, 4);
            first.b = fn_8016A694(state, 5);
            first.a = fn_8016A694(state, 6);
            second.r = fn_8016A694(state, 7);
            second.g = fn_8016A694(state, 8);
            second.b = fn_8016A694(state, 9);
            second.a = fn_8016A694(state, 10);

            delta = -5;
            if (second.r >= first.r) delta = 5;
            directions.r = delta;
            delta = -5;
            if (second.g >= first.g) delta = 5;
            directions.g = delta;
            delta = -5;
            if (second.b >= first.b) delta = 5;
            directions.b = delta;
            delta = -5;
            if (second.a >= first.a) delta = 5;
            directions.a = delta;

            call_second = second;
            call_directions = directions;
            call_first = first;
            fn_8012C62C(object, index, &call_first, &call_directions,
                         &call_second, 4);
        }
    }
    return 0;
}
