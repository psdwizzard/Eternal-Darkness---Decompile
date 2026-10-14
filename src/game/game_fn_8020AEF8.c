/* Set the current heap and return the previous heap handle. */
extern int lbl_8064C3C8;

int fn_8020AEF8(int heap) {
    int previousHeap = lbl_8064C3C8;
    lbl_8064C3C8 = heap;
    return previousHeap;
}
