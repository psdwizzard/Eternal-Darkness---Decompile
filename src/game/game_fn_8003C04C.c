typedef struct Entry80201814 Entry80201814;
typedef void (*ObjectCallback)(int);

extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int id);
extern int fn_80201B54(int *object);
extern int fn_80201B64(int *object);
extern int fn_802006D4(int first, int object_id, int subtype, int kind,
                     ObjectCallback callback);
extern void fn_80201138(int kind, void *context, int value, int id,
                       int arg4, float delay);
extern int lbl_803003C8[];
extern float lbl_8064E268;

int fn_8003C04C(int *context)
{
    Entry80201814 *object;
    int result = 1;
    int id;

    object = fn_80201814(fn_80201B44());
    id = fn_80201B54(context);

    if (lbl_803003C8[2] == 5 && object != 0 &&
        fn_80201B64((int *)object) == 30) {
        fn_802006D4(id, id, 8, 17, 0);
        fn_80201138(17, context, 8, -1, 0, lbl_8064E268);
        result = 0;
    }
    return result;
}
