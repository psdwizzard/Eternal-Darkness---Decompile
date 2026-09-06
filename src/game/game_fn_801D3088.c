typedef unsigned char u8;

typedef struct Position {
    u8 pad00[8];
    float y;
} Position;

extern float lbl_806510A4;
extern void fn_80156938(void);
extern void* fn_80201BC8(void);
extern Position* fn_8011F130(void*);
extern int fn_8011FCB0(void*);
extern void fn_8012A72C(void*);
extern void fn_8012D0D0(void*);
extern void fn_80124DBC(void*);

int fn_801D3088(void)
{
    void* object;

    fn_80156938();
    object = fn_80201BC8();
    if (object != 0) {
        Position* position = fn_8011F130(object);
        position->y += lbl_806510A4;
        if (fn_8011FCB0(object) != 0) {
            fn_8012A72C(object);
        }
        fn_8012D0D0(object);
        fn_80124DBC(object);
    }
    return 3;
}
