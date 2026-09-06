
extern const unsigned int lbl_8023A414[12];
int fn_80113E48(unsigned int value)
{
    unsigned int required = value & 0x00070000;
    const unsigned int *entry_ptr;
    unsigned int entry;
    unsigned int shape = value & 0x00003FF0;
    int i;
    if ((value & 0xF) == 0) {
        return -1;
    }
    if (required == 0) {
        return -1;
    }
    entry_ptr = lbl_8023A414;
    for (i = 0; i < 12; entry_ptr++, i++) {
        entry = *entry_ptr;
        if (((entry & required) == required) && (shape == (entry & 0x3FF0))) {
            return i;
        }
    }

    return -1;
}
