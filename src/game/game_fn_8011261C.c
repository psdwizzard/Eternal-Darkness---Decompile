extern int lbl_8064CD44;
extern int lbl_8064CD58;
extern void* lbl_8064C504;
extern int lbl_8024DE38[];
extern int lbl_80331A08[];
extern const double lbl_8064FF60;

extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern int fn_801E6CA0(void*, int, int, int, int);
extern void fn_801E8B24(int, int, int);

int fn_8011261C(void* object)
{
    int item;

    if (lua_tonumber(object, 1) == lbl_8064FF60) {
        item = fn_801E6CA0(lbl_8064C504, 15,
                          fn_800F5C54(lua_tonumber(object, 1)), 0, 1);
        lbl_8024DE38[11] = item;
        fn_801E8B24(lbl_80331A08[6], 1, 0);
        lbl_8064CD44 = 23;
    } else {
        lbl_8064CD58 = fn_801E6CA0(lbl_8064C504, 15,
                                  fn_800F5C54(lua_tonumber(object, 1)), 0, 1);
    }
    return 0;
}
