typedef unsigned long u32;

u32 fn_80209B48(void); /* PPCMfwpar */
void PPCMtwpar(u32 newWPAR);

/* Wait for the write-gather pipe to empty, then reset its address. */
void fn_802263D4(void)
{
    while (fn_80209B48() & 1) {
    }
    PPCMtwpar(0x0C008000);
}
