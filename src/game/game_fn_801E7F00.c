extern int lbl_8064C350;
extern int lbl_8064C354;
extern int lbl_8064C358;

void fn_801E7F00(void)
{
    int current = lbl_8064C350;
    int target = lbl_8064C358;

    if (current != target) {
        if (--lbl_8064C354 < 0) {
            lbl_8064C354 = 7;
        }
        if (lbl_8064C354 == target) {
            lbl_8064C358 = current;
        }
    }
}
