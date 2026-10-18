/* Set the current heap and return the previous heap handle. */
extern int __OSCurrHeap;

int OSSetCurrentHeap(int heap) {
    int previousHeap = __OSCurrHeap;
    __OSCurrHeap = heap;
    return previousHeap;
}
