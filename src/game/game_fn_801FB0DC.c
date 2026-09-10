extern void* lbl_8064C3AC[1];

int fn_801FB0DC(void* value)
{
    int i;
    for (i = 0; i < 1; i++) {
        if (lbl_8064C3AC[i] == value) {
            return i;
        }
    }
    return -1;
}
