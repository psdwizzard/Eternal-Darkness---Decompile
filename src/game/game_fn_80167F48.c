extern unsigned int ezgetc(void*, void*);
extern void ezread(void*, void*, void*, unsigned int);

#pragma use_lmw_stmw on
void LoadVector(void* object, unsigned char* destination, int count,
                 unsigned int size, void* input, int reverse)
{
    if (reverse != 0) {
        unsigned char* data = destination;

        while (count-- != 0) {
            unsigned char* output = data + size - 1;
            unsigned int remaining = size;

            while (remaining-- != 0) {
                *output-- = ezgetc(object, input);
            }
            data += size;
        }
    } else {
        ezread(object, input, destination, count * size);
    }
}
#pragma use_lmw_stmw reset
