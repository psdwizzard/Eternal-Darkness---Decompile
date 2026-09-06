typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union ConfigData {
    u8 raw[0x40];
    struct {
        u8 pad[0xA];
        u8 counters[0x36];
    } fields;
} ConfigData;

extern int fn_80180430(void*, u8);
extern int fn_80180454(void*);
extern u8 fn_8018E26C(void*, void*);
extern void fn_8018284C(void*, int);
extern void fn_80180518(void*, u8, int);
extern void fn_8017D2B4(void*, void*, void*);
extern void fn_8018E230(void*, void*, int, int, s8, u8);

int fn_80182984(u8* self)
{
    u8 count;
    int counter;
    ConfigData* config;
    u8* entry;
    int i;
    int result = 0;

    config = (ConfigData*)(self + 0x8C);
    counter = *(u16*)(self + 0xA);
    if ((counter & self[0xC1]) == 0) {
        entry = *(u8**)(self + 0x4C);
        i = 0;
        count = self[1];
        while (i < count) {
            if (fn_80180430(self + 0x24, (u8)i)) {
                int active = 1;
                u8 amount = config->raw[0x33];
                if (amount != 0) {
                    entry[0x21] += amount;
                    if (entry[0x21] > config->raw[0x32]) {
                        entry[0x21] = config->raw[0x32];
                    }
                }
                if (entry[0] != 0 && !fn_8018E26C(entry, entry + 0x2B) &&
                    entry[0x2B] == 0) {
                    if (*(int*)(config->raw + 0x2C) != 0) {
                        fn_8018284C(self, i);
                    } else {
                        fn_80180518(self + 0x24, (u8)i, 0);
                    }
                    active = 0;
                }
                if (active) {
                    int index;
                    fn_8017D2B4(entry + 0xA, entry + 0x16, entry + 0x10);
                    index = i;
                    if (config->fields.counters[index] == *(u16*)(entry + 8)) {
                        fn_8018E230(entry, entry + 0x2B, 1, self[2],
                                    *(s8*)(self + 4), 0);
                    }
                    config->fields.counters[index]++;
                }
            }
            entry += 0x38;
            i++;
        }

        if (config->raw[9] < count - 1 && (counter & config->raw[0x36]) == 0) {
            config->raw[9]++;
            fn_80180518(self + 0x24, config->raw[9], 1);
            entry = *(u8**)(self + 0x4C) + config->raw[9] * 0x38;
            if (config->raw[0x30] == config->raw[0x31]) {
                entry[0x2B] = config->raw[0x31];
            } else {
                fn_8018E230(entry, entry + 0x2B, 1, 0,
                            (s8)config->raw[0x30], config->raw[0x31]);
            }
        }
        if (counter >= *(u16*)(self + 0xC)) {
            *(u32*)(config->raw + 0x2C) = 0;
        }
        if (fn_80180454(self + 0x24)) {
            *(u16*)(self + 0x22) = 8;
        }
        result = 1;
    }
    (*(u16*)(self + 0xA))++;
    return result;
}
