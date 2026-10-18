typedef unsigned long u32;

u32 PPCMfwpar(void); /* PPCMfwpar */
void PPCMtwpar(u32 newWPAR);

/* Wait for the write-gather pipe to empty, then reset its address. */
void GXResetWriteGatherPipe(void)
{
    while (PPCMfwpar() & 1) {
    }
    PPCMtwpar(0x0C008000);
}
