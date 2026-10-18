extern int InitializeUART(unsigned long baud_rate);
extern int WriteUARTN(const void* data, unsigned long length);
extern void __TRK_write_console(void* context, const void* data, unsigned long* length,
                       void* callback);

extern int lbl_8064CC58;

int __write_console(void* context, const void* data, unsigned long* length,
                void* callback)
{
    int result = 0;

    if (lbl_8064CC58 == 0) {
        result = InitializeUART(57600);
        if (result == 0) {
            lbl_8064CC58 = 1;
        }
    }

    if (result != 0) {
        return 1;
    }

    if (WriteUARTN(data, *length) != 0) {
        *length = 0;
        return 1;
    }

    __TRK_write_console(context, data, length, callback);
    return 0;
}
