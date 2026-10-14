extern void *lbl_8064D950; /* SaveStart */
extern void *lbl_8064D954; /* SaveEnd */

/* Set the memory region to preserve across a reboot. */
void fn_8020DDAC(void *start, void *end)
{
    lbl_8064D950 = start;
    lbl_8064D954 = end;
}
