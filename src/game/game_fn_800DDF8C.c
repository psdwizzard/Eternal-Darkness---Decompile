typedef struct Vec {
    float x;
    float y;
    float z;
} Vec;

typedef struct ActorState {
    unsigned char pad0[0x22];
    unsigned char unk22;
} ActorState;

typedef struct ActorData {
    unsigned char pad0[0x50];
    ActorState *state;
} ActorData;

extern int fn_80200C10(void *);
extern int fn_80200C38(void *);
extern void *fn_80201BC8(void *);
extern ActorData *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern int fn_80201B54(void *);
extern void fn_80201D14(void *, int);
extern void fn_80201D1C(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D34(void *, int);
extern void fn_80201DD8(void *, int);
extern void fn_8011F114(Vec *, void *);
extern void fn_8011FB4C(void *);
extern void fn_801E8328(int, void *);
extern int fn_8008D6E4(void *, void *, void *);
extern void fn_8008E078(void *, void *, void *);
extern void fn_8008E294(void *, ActorState *, void *, Vec *, void *);
extern void fn_8008E430(void *, int, ActorState *, void *, void *, int *, int);
extern void fn_8008E810(int, ActorState *);
extern void fn_800DD314(void *, int, int, int);
extern int fn_800DE3F8(void);

extern int lbl_8064B790;
extern int lbl_8064CAC8;
extern int lbl_8064D18C;

int fn_800DDF8C(void *context, int phase, void *message)
{
    ActorState *state;
    void *owner;
    void *object;
    int id;
    int kind;
    Vec pos;

    kind = fn_80200C10(message);
    object = fn_80201BC8(context);
    state = fn_80201B8C(context)->state;
    owner = fn_80201B94(context);
    id = fn_80201B54(context);
    fn_8011F114(&pos, object);
    fn_8011FB4C(object);

    if (phase == 0) {
        if (kind == 1) {
            fn_800DD314(context, 15, 255, 0);
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
        if (kind == 125) {
            if (lbl_8064D18C == 239) {
                fn_80201DD8(owner, fn_800DE3F8());
                fn_8008D6E4(context, object, message);
            } else {
                int value = fn_80200C38(message);
                fn_80201DD8(owner, value);
                fn_8008D6E4(context, object, message);
            }
            return 1;
        }
        if (kind == 57) {
            fn_80201D34(context, 0);
            fn_80201D1C(context, 1);
            fn_801E8328(2, context);
            return 1;
        }
    } else if (phase == 1) {
    } else if (phase == 59) {
        if (kind == 1) {
            fn_800DD314(context, 15, 5, 250);
            return 1;
        }
        if (kind == 6) {
            Vec p;
            p = pos;
            fn_8008E294(context, state, object, &p, message);
            return 1;
        }
    } else if (phase == 56) {
        if (kind == 1) {
            int value = 240;
            state->unk22 = 0;
            if (lbl_8064D18C == 239)
                value = 43;
            lbl_8064CAC8 = value;
            return 1;
        }
        if (kind == 3) {
            fn_8008E430(context, id, state, object, message, &lbl_8064CAC8, lbl_8064D18C == 239 ? 43 : 0);
            return 1;
        }
        if (kind == 6) {
            fn_8008E078(context, object, message);
            return 1;
        }
        if (kind == 2) {
            fn_8008E810(id, state);
            lbl_8064B790 = 300;
            return 1;
        }
    } else if (phase == 60) {
        if (kind == 1) {
            if (lbl_8064D18C == 239)
                fn_800DD314(context, 15, 2, 0);
            return 1;
        }
        if (kind == 6) {
            fn_80201D2C(context, 1);
            fn_80201D14(context, 1);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
