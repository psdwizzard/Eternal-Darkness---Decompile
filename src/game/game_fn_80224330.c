/* GXGetFifoBase: return the base address stored in the FIFO object. */
typedef struct {
    unsigned char *base;
} GXFifoHeader;

void *GXGetFifoBase(void *fifo)
{
    return ((GXFifoHeader *)fifo)->base;
}
