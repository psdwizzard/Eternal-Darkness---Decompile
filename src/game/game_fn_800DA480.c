/* fn_800DA480 (0x800DA480, 1108 bytes): event handler dispatching on the
 * current state and the incoming event id. */

extern int fn_80200C10(void *event);
extern void *fn_80200C38(void *event);
extern void *fn_80155DB4(void *object);
extern void *fn_80201BC8(void *object);
extern void fn_80201B54(void *object);
extern void fn_80201D14(void *object, int value);
extern void fn_80201D1C(void *object, int value);
extern void fn_80201D2C(void *object, int state);
extern void fn_80201D34(void *object, int value);
extern void fn_800DBEC4(void *object);
extern void fn_800DBE34(void *object);
extern int fn_8011EB04(void *actor);
extern void fn_801261F4(void *actor);
extern void fn_80120AD0(void *actor, int a, int b, int c, float x, float y);
extern void fn_801E8328(int type, void *object);
extern void fn_800DBC0C(void *object);
extern void fn_800DBB24(void *object, void *event);
extern void fn_800DB2BC(void *object);
extern void fn_800DBA84(void *object, void *event);
extern void *fn_80204A8C(void);
extern void fn_80204E0C(void *object, void *value);
extern void fn_8011FA8C(void *actor, int flags, int value);
extern void fn_801568E4(void *data);
extern void fn_801568D8(void *data);
extern void fn_801568F0(void *data);
extern void fn_8011FB54(void *actor, int value);
extern void fn_800DBA0C(void *object, void *event);
extern void fn_800DB838(void *data);
extern void fn_801E82B4(void *object, void *value, void (*callback)(), int arg);
extern void fn_800DCFE0();
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
    data = fn_80155DB4(object);
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
            fn_801E8328(2, object);
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
            fn_8011FB54(actor, lbl_8064D18C);
            return 1;
        } else if (id == 0x4A) {
            fn_800DBA0C(object, event);
            return 1;
        } else if (id == 0x2F) {
            fn_800DB838(data);
            fn_801E82B4(object, fn_80200C38(event), fn_800DCFE0, 0);
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
