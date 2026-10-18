extern unsigned char GetUseSerialIO(void);
extern int GetTRKConnected(void);
extern unsigned char TRKAccessFile(int, int, unsigned int *, void *);

int __TRK_write_console(int unused, void *arg, unsigned int *value)
{
    unsigned int local;
    unsigned char result;
    if (GetUseSerialIO() == 0) {
        return 1;
    }
    if (GetTRKConnected() == 0) {
        return 1;
    }
    local = *value;
    result = TRKAccessFile(0xD0, 1, &local, arg);
    *value = local;
    switch (result) {
    case 0:
        return 0;
    case 2:
        return 2;
    default:
        return 1;
    }
}
