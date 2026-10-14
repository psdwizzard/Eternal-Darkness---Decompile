extern void *memset(void *dest, int value, unsigned long size);

/* Clear the fixed-size configuration when one is supplied. */
void fn_802335E4(void *buffer)
{
    if (buffer != 0) {
        memset(buffer, 0, 0xCD0);
    }
}
