extern void *memset(void *dest, int value, unsigned long size);

/* Clear the fixed-size configuration when one is supplied. */
void mapping0_free_info(void *buffer)
{
    if (buffer != 0) {
        memset(buffer, 0, 0xCD0);
    }
}
