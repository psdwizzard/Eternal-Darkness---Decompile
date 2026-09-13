typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct Data8008E430 {
    u8 pad0[0x10];
    int primary;
    int fallback;
    u8 pad18[0xa];
    signed char attempts;
} Data8008E430;

extern int fn_800DE3F8(void);
extern unsigned long long fn_8020123C();
extern int fn_8008E078(void*, void*, void*);
extern int fn_80038308(void*, int, short*);
extern int fn_800389E0(void*, int, short, int);
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void* fn_8011F130(void*);
extern void fn_801A764C(void*, void*);
extern void fn_801A7228(void*);

void fn_8008E430(void* object, int object_id, Data8008E430* data,
                 void* resource, void* argument, int* timer, int delay)
{
    int selected;
    int is_current;
    short value;

    selected = data->primary != 0 ? data->primary : data->fallback;
    is_current = selected == fn_800DE3F8();
    if (is_current && (unsigned int)(fn_8020123C(125, object_id, selected, 1) & 0xFFFFFFFF) == 0) {
        fn_8020123C(126, object_id, object_id, 0);
        return;
    }
    if (--*timer > 1) return;
    value = 0;
    *timer = 240;
    if (data->fallback != 0) {
        fn_8020123C(128, object_id, selected, 0);
        fn_8008E078(object, resource, argument);
        fn_80038308(object, 0, &value);
        value += 5;
        fn_800389E0(object, 0, value, 0);
        return;
    }
    if (is_current) {
        fn_80038308(object, 0, &value);
        value += 5;
        fn_800389E0(object, 0, value, 0);
        *timer = delay != 0 ? delay : 100;
    } else {
        void* request = fn_801A717C();
        short other = 0;
        fn_801A74A0(request, object_id);
        fn_801A74A8(request, selected);
        fn_801A7538(request, 1);
        fn_801A7518(request, 5);
        fn_801A764C(request, fn_8011F130(resource));
        fn_8020123C(39, object_id, selected, (int)request);
        fn_801A7228(request);
        fn_80038308(object, 0, &other);
        other += 10;
        fn_800389E0(object, 0, other, 0);
    }
    ++data->attempts;
    if (data->attempts >= 5) fn_8008E078(object, resource, argument);
}
