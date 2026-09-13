typedef void (*Callback)(void);

extern char lbl_802FC9A8[];

extern void *fn_802016CC(void *name);
extern void fn_80201328(Callback callback, int index, void *name);
extern void fn_80201D44(void *object, int value);
extern void fn_80202E28(void);
extern void fn_80205914(void);

void *fn_80204758(int type)
{
    void *object;
    char *names = lbl_802FC9A8;

    switch (type) {
    case 12:
        object = fn_802016CC(names + 0xC);
        fn_80201328(fn_80202E28, 12, names + 0x20);
        fn_80201D44(object, 12);
        return object;
    case 3:
        object = fn_802016CC(names + 0x34);
        fn_80201328(fn_80205914, 3, names + 0x4C);
        fn_80201D44(object, 3);
        return object;
    default:
        return 0;
    }
}
