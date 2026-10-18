extern unsigned int ezgetc(void*, void*);
extern void ezread(void*, void*, void*, unsigned int);

void LoadBlock(void* object, unsigned char* destination, unsigned int size,
                 void* input, int reverse)
{
    if (reverse != 0) {
        unsigned char* output = destination + size - 1;
        unsigned int count = size;

        while (count-- != 0) {
            *output-- = ezgetc(object, input);
        }
    } else {
        ezread(object, input, destination, size);
    }
}
