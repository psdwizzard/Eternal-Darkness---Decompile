/* fn_800DA480 (0x800DA480, 1108 bytes): event handler dispatching on the
 * current state and the incoming event id. */

typedef struct Node Node;
typedef struct Object Object;
typedef struct Position Position;
typedef struct Owner Owner;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D1C Object80201D1C;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D34 Object80201D34;
typedef struct ListNode80204E0C ListNode80204E0C;

extern int fn_80200C10(int *event);
extern void *fn_80200C38(void **event);
extern Node *fn_80155DB4(unsigned int id);
extern void *fn_80201BC8(void *object);
extern int fn_80201B54(int *object);
extern void fn_80201D14(Object80201D14 *object, unsigned char value);
extern void fn_80201D1C(Object80201D1C *object, unsigned char value);
extern void fn_80201D2C(Object80201D2C *object, int state);
extern void fn_80201D34(Object80201D34 *object, int value);
extern void fn_800DBEC4(void *object);
extern void fn_800DBE34(void *object);
extern int fn_8011EB04(Object *actor);
extern int fn_801261F4(Owner *actor);
extern void fn_80120AD0(Object *actor, const Position *position,
                        unsigned short value, unsigned int state, float x, float y);
extern int fn_801E8328(unsigned int type, unsigned int object);
extern void fn_800DBC0C(void *object);
extern void fn_800DBB24(void *object, void *event);
extern void fn_800DB2BC(void *object);
extern void fn_800DBA84(void *object, void *event);
extern void *fn_80204A8C(void);
extern int fn_80204E0C(void *object, ListNode80204E0C *value);
extern unsigned int fn_8011FA8C(void *actor, unsigned int flags, unsigned int value);
extern void fn_801568E4(Object *data);
extern void fn_801568D8(Object *data);
extern void fn_801568F0(Object *data);
extern void fn_8011FB54(void *actor, void *value);
extern void fn_800DBA0C(void *object, void *event);
extern void fn_800DB838(void *data);
extern int fn_801E82B4(unsigned int object, unsigned int value,
                       unsigned int callback, unsigned short arg);
extern int fn_800DCFE0(void *object, void *mode);
extern void fn_800DB9B0(void *object);
extern void fn_800DB62C(void *object);
extern void fn_800DB430(void *object);
extern void fn_800DB95C(void *actor);
extern void fn_800DB37C(void *object, int value);
extern void fn_800DB348(void);
extern void fn_800DB204(void *object);

extern int lbl_8064D18C;
extern float lbl_8064F460;
extern float lbl_8064F464;

int fn_800DA480(void *object, int state, void *event, int *handled) {
    int id;
    void *actor;
    void *data;

    id = fn_80200C10(event);
    data = fn_80155DB4((unsigned int)object);
    actor = fn_80201BC8(object);
    fn_80201B54(object);

    if (state == 0) {
        if (id == 1) {
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            fn_800DBEC4(object);
            fn_800DBE34(object);
            if (fn_8011EB04(actor) == 0xCD) {
                fn_801261F4(actor);
                fn_80120AD0(actor, 0, 100, 0x20A, lbl_8064F460, lbl_8064F464);
            }
            return 1;
        } else if (id == 0x39) {
            fn_801E8328(2, (unsigned int)object);
            fn_80201D34(object, 0);
            fn_80201D1C(object, 1);
            return 1;
        } else if (id == 0x3E) {
            fn_800DBC0C(object);
            return 1;
        } else if (id == 0x4B) {
            fn_800DBB24(object, event);
            return 1;
        } else if (id == 0x49) {
            fn_80201D2C(object, 0x25);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0xF0) {
            int value = (int)fn_80200C38(event);
            fn_80201D34(object, value);
            fn_80201D1C(object, 1);
            if (handled != 0) {
                *handled = 1;
            }
            return 1;
        }
    } else if (state == 1) {
        if (id == 3) {
            fn_800DB2BC(object);
            return 1;
        } else if (id == 0x47) {
            fn_80201D2C(object, 0x23);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0x48) {
            fn_80201D2C(object, 0x24);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0x49) {
            fn_80201D2C(object, 0x25);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0xDF) {
            fn_800DBA84(object, event);
            return 1;
        } else if (id == 1) {
            return 1;
        }
    } else if (state == 0x25) {
        if (id == 1) {
            fn_80204E0C(object, fn_80204A8C());
            fn_8011FA8C(actor, 0x802, 0);
            fn_801568E4(data);
            fn_801568D8(data);
            fn_801568F0(data);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 3) {
            return 1;
        }
    } else if (state == 0x24) {
        if (id == 0x47) {
            fn_80201D2C(object, 0x23);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 1) {
            fn_8011FA8C(actor, 0x10100, 0);
            return 1;
        }
    } else if (state == 0x23) {
        if (id == 0x3D) {
            fn_8011FB54(actor, (void *)lbl_8064D18C);
            return 1;
        } else if (id == 0x4A) {
            fn_800DBA0C(object, event);
            return 1;
        } else if (id == 0x2F) {
            fn_800DB838(data);
            fn_801E82B4((unsigned int)object, (unsigned int)fn_80200C38(event),
                        (unsigned int)fn_800DCFE0, 0);
            return 1;
        } else if (id == 0xBE) {
            fn_800DB9B0(object);
            fn_800DB62C(object);
            fn_80201D2C(object, 1);
            fn_80201D14(object, 1);
            return 1;
        } else if (id == 0x2E) {
            fn_800DB430(object);
            fn_800DB95C(actor);
            return 1;
        } else if (id == 1) {
            fn_800DB37C(object, 0);
            fn_800DB348();
            fn_800DB204(object);
            return 1;
        } else if (id == 3) {
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
