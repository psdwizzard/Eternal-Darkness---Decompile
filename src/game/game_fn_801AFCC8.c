typedef unsigned char u8;

typedef struct Entry {
    u8 pad000[0x15c];
    int owner;
    u8 pad160[0x19];
    u8 rank;
    u8 state;
    u8 pad17b[3];
    u8 count;
    u8 pad17f[5];
} Entry;

extern Entry lbl_8060B5E0[];
extern void fn_801B0E68(int);

int fn_801AFCC8(int owner, int mode, u8 wanted, int limit,
                Entry** choices, Entry** special)
{
    int i;
    int ranks[2];
    int result;
    Entry* entry;
    int remaining;
    int total;
    int found;

    result = 0;
    entry = lbl_8060B5E0;
    found = 0;
    remaining = 3;
    total = 0;
    ranks[0] = 7;
    ranks[1] = 7;

    choices[0] = 0;
    choices[1] = 0;
    *special = 0;
    if (limit != 0) {
        wanted++;
    }

    for (i = 0; i < 4; i++, entry++) {
        switch (entry->state) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if (entry->owner != owner) {
                remaining -= entry->count;
                if (entry->rank < wanted) {
                    total += entry->count;
                    if (entry->count == 2) {
                        if (found == 1) {
                            fn_801B0E68(12);
                        }
                        found = 1;
                        *special = entry;
                    }
                    if (ranks[0] > entry->rank && ranks[0] >= ranks[1]) {
                        ranks[0] = entry->rank;
                        choices[0] = entry;
                    } else if (ranks[1] > entry->rank) {
                        ranks[1] = entry->rank;
                        choices[1] = entry;
                    }
                }
            }
            break;
        }
    }

    if (remaining >= mode) {
        *special = 0;
        choices[1] = 0;
        choices[0] = 0;
        result = 1;
    } else if (mode == 1) {
        if (ranks[0] == 1) {
            *special = 0;
            choices[1] = 0;
            result = 1;
        } else if (ranks[1] == 1) {
            *special = 0;
            choices[0] = 0;
            result = 1;
        } else if (found != 0) {
            choices[1] = 0;
            choices[0] = 0;
            result = 1;
        } else if (ranks[0] < ranks[1]) {
            choices[1] = 0;
            result = 1;
        } else if (ranks[1] < 7) {
            choices[0] = 0;
            result = 1;
        } else {
            *special = 0;
            choices[1] = 0;
            choices[0] = 0;
        }
    } else if (remaining == 1 && ranks[0] == 1) {
        *special = 0;
        choices[1] = 0;
        result = 1;
    } else if (remaining == 1 && ranks[1] == 1) {
        *special = 0;
        choices[0] = 0;
        result = 1;
    } else if (ranks[0] == 1 && ranks[1] == 1) {
        *special = 0;
        result = 1;
    } else if (remaining == 1 && found != 0) {
        choices[1] = 0;
        choices[0] = 0;
        result = 1;
    } else if (total >= 2) {
        if (found != 0) {
            if (choices[0] == *special) {
                if (choices[1] != 0) {
                    choices[0] = 0;
                    result = 1;
                } else {
                    *special = 0;
                    result = 1;
                }
            } else if (choices[1] == *special) {
                if (choices[0] != 0) {
                    choices[1] = 0;
                    result = 1;
                } else {
                    *special = 0;
                    result = 1;
                }
            } else if (ranks[0] < ranks[1]) {
                choices[1] = 0;
            } else if (ranks[1] < 7) {
                choices[0] = 0;
            } else {
                result = 0;
            }
        } else if (choices[0] != 0 && choices[1] != 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        *special = 0;
        choices[1] = 0;
        choices[0] = 0;
        result = 0;
    }
    return result;
}
