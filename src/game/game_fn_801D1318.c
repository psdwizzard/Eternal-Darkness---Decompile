extern int lbl_8064D538;
extern int lbl_8064D550;
extern void fn_8011E7E8(int, int);

void fn_801D1318(int value)
{
    int enabled = value != 0;

    lbl_8064D538 = value;
    if (value == 0) {
        lbl_8064D550 = 0;
    }
    fn_8011E7E8(enabled, 4);
    fn_8011E7E8(enabled, 1);
}
