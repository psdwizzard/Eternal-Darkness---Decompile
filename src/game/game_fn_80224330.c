/* GXGetFifoBase: return the base address stored in the FIFO object. */
typedef struct {
    unsigned char *base;
} GXFifoHeader;

void *fn_80224330(void *fifo)
{
    return ((GXFifoHeader *)fifo)->base;
}
