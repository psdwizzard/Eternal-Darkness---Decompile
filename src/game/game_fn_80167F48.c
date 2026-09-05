extern unsigned int fn_80167DC8(void*, void*);
extern void fn_80167E58(void*, void*, void*, unsigned int);

#pragma use_lmw_stmw on
void fn_80167F48(void* object, unsigned char* destination, int count,
                 unsigned int size, void* input, int reverse)
{
    if (reverse != 0) {
        unsigned char* data = destination;

        while (count-- != 0) {
            unsigned char* output = data + size - 1;
            unsigned int remaining = size;

            while (remaining-- != 0) {
                *output-- = fn_80167DC8(object, input);
            }
            data += size;
        }
    } else {
        fn_80167E58(object, input, destination, count * size);
    }
}
#pragma use_lmw_stmw reset
