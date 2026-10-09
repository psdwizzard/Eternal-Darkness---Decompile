typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;

/* Slot table owned by the animation sampler. */
typedef struct Slot Slot;

typedef struct EntryPair {
    void* first;
    void* second;
} EntryPair;

/* Eight-word texture/material description filled in by fn_8015DB84. */
typedef struct Material {
    u32 words[8];
} Material;

/* Per-frame controller state kept by the input layer. */
typedef struct InputState {
    void* resources[22];
    u32 color;
    s16 values[11];
} InputState;

typedef struct ChannelCache {
    s16 values[12];
    int attributes;
    int pad;
} ChannelCache;

typedef struct ControllerRegion {
    char pad0[0x207C];
    Material material1;
    Material material2;
    char pad20BC[0x20DC - 0x20BC];
    Material material3;
    char pad20FC[0x215C - 0x20FC];
    Material material0;
    char pad217C[0x21CC - 0x217C];
    int group[3];
    ChannelCache cache;
    int checksums[16];
    int commands[16];
} ControllerRegion;

/* Widening and narrowing preserves every 32-bit pointer bit while keeping
 * GC/1.3 from folding the field base into the indexed address (see
 * fn_801EDE34). */
#define UNFOLDED(p) ((u32)(unsigned long long)(u32)(p))
#define COMMAND(r, i) (((int*)UNFOLDED((r)->commands))[i])
#define CHECKSUM(r, i) (((int*)UNFOLDED((r)->checksums))[i])
#define CACHE(r) ((ChannelCache*)UNFOLDED(&(r)->cache))
#define CACHED(r) ((s16*)UNFOLDED((r)->cache.values))

extern int lbl_80265D80[];
extern int lbl_8064C378;
extern u8 lbl_8064D5F8;
extern void* lbl_8064D5FC;
extern int lbl_8064D61C;
extern int lbl_8064D634;
extern int lbl_8064D638;
extern int lbl_8064D650;
extern u8 lbl_8064D674[4];
extern u32 lbl_8064D678;
extern int lbl_8064D680;
extern int lbl_8064D684;
extern int lbl_8064D6E8;
extern int lbl_8064D6F0;
extern void* lbl_8064D744;
extern void* lbl_8064D748;
extern ControllerRegion lbl_80639260;

extern void fn_801ECD74(u32*);
extern void fn_801ED118(void);
extern u16 fn_801F6034(int, Slot*);
extern int fn_8015AA20(void);
extern void fn_8015DB84(void*, void*, u32);
extern EntryPair* fn_8015DB74(void*, u32);
extern void fn_8015DC54(void*, void*, void*, u32, u32);
extern void fn_80228B98(void*, int);
extern void fn_80228AFC(void*, int);
extern u16 fn_8022893C(void*);
extern void fn_801EB8E8(void*);
extern void fn_801EDE34(int, int, int, int);
extern void fn_801EF278(int, int, int, int, int, int);
extern void fn_801ED494(int, int, int, int, int);
extern void fn_801ED510(int, int, int);
extern void fn_801EF220(int, int);
extern void fn_801EF1A4(int, int, int, int, int);
extern void fn_801EF110(int, int, int, int, int, int);
extern void fn_801EF07C(int, int, int, int, int, int);
extern void fn_801EF000(int, int, int, int, int);
extern int fn_801EB304(void);

/*
 * Central controller-state dispatcher.  Filters the incoming sample, refreshes
 * the per-channel material cache and then emits the command set for the
 * requested channel.
 */
int fn_801EDF80(s16* values, int total, int count, int iteration_total,
                int parameter, int mode, int channel, Slot* context, int flags,
                InputState* state)
{
    ControllerRegion* region;
    int attributes;
    int tint;
    int kind;
    int speed;
    int command;
    int repeat;
    int selector;
    int accepted;
    int first;
    int next;
    int first_pass;
    int result;

    region = &lbl_80639260;
    result = 1;
    first_pass = 0;
    tint = 1;
    kind = 4;
    speed = 0x3C;

    attributes = values != 0 ? *(u32*)((char*)values + 0x18) : 0x80000000;
    if (flags & 0x8000) {
        attributes |= 0x80000000;
    }

    if (total == 0) {
        if (attributes & 0x80000000) {
            command = 2;
            repeat = 1;
            selector = 0xFF;
        } else {
            command = 10;
            repeat = 5;
            selector = 4;
        }
        first_pass = 1;
    } else {
        command = 0;
        repeat = 0;
        selector = 0;
    }
    if (lbl_8064D638 == 0) {
        selector = 0xFF;
    }

    if (channel == 10 && (flags & 0x800) == 0) {
        int* slots;
        int index;

        accepted = 1;
        if (values != 0) {
            u32 color = *(u32*)((char*)values + 0x1C);
            fn_801ECD74(&color);
        } else {
            u32 color = state->color;
            fn_801ECD74(&color);
        }

        slots = lbl_80265D80;
        for (index = 0; index < 4; index++, slots++) {
            int slot = *slots;
            int candidate;
            u32 bit;

            if (slot == 7) {
                continue;
            }
            if (values != 0) {
                candidate = values[slot];
                if (slot == 1) {
                    switch (lbl_8064D5F8) {
                    case 0:
                        candidate = values[1];
                        break;
                    case 1:
                        candidate = values[6];
                        break;
                    case 2:
                        candidate = values[8];
                        break;
                    }
                }
            } else {
                candidate = state->values[slot];
            }
            if (candidate == -1) {
                continue;
            }

            bit = 1U << slot;
            if (((u32)flags & bit) != 0 &&
                (((u32)lbl_8064C378 & bit) != 0 || lbl_8064D6E8 != 0)) {
                accepted = 0;
                break;
            }
        }

        if (!accepted) {
            if ((lbl_8064D674[0] == 0xFF && lbl_8064D674[1] == 0xFF &&
                 lbl_8064D674[2] == 0xFF && lbl_8064D674[3] == 0xFF) ||
                (attributes & 0x80000000) != 0) {
                return 0;
            }
            command = 10;
            repeat = 5;
            selector = 4;
        }
    }

    if (channel == 2 && lbl_8064D6F0 == 0) {
        return 0;
    }

    if (first_pass && lbl_8064D634 != channel) {
        fn_801ED118();
        lbl_8064D634 = channel;
    }

    if (channel != 10) {
        int candidate;
        int bit;
        int changed;

        if (values != 0) {
            candidate = values[channel];
            if (channel == 1) {
                switch (lbl_8064D5F8) {
                case 0:
                    candidate = values[1];
                    break;
                case 1:
                    candidate = values[6];
                    break;
                case 2:
                    candidate = values[8];
                    break;
                }
                if (region->group[0] != values[1] ||
                    region->group[1] != values[6] ||
                    region->group[2] != values[8]) {
                    region->group[0] = values[1];
                    region->group[1] = values[6];
                    region->group[2] = values[8];
                    CACHED(region)[channel] = -1;
                }
            }
        } else {
            candidate = state->values[channel];
        }

        bit = 1 << channel;
        changed = attributes & bit;
        if (changed != (CACHE(region)->attributes & bit) ||
            candidate != CACHE(region)->values[channel]) {
            if (changed != 0) {
                candidate = (s16)fn_801F6034(values[channel], context);
            }
            if ((s16)candidate != CACHED(region)[channel]) {
                Material material;

                CACHED(region)[channel] = candidate;
                if (values != 0) {
                    if (channel == 9) {
                        if (fn_8015AA20() != 0) {
                            fn_8015DB84(lbl_8064D744, &material,
                                        CACHED(region)[channel]);
                        } else {
                            fn_8015DB84(lbl_8064D748, &material,
                                        CACHED(region)[channel]);
                        }
                    } else if (channel == 3) {
                        switch (CACHED(region)[channel]) {
                        case 0:
                            material = region->material0;
                            break;
                        case 2:
                            material = region->material2;
                            break;
                        case 1:
                            material = region->material1;
                            break;
                        case 3:
                            material = region->material3;
                            break;
                        default:
                            material = region->material0;
                            break;
                        }
                    } else {
                        if (fn_8015DB74(lbl_8064D5FC,
                                        CACHED(region)[channel])->second != 0) {
                            u32 extra[3];

                            fn_8015DC54(lbl_8064D5FC, &material, extra, 1,
                                        CACHED(region)[channel]);
                            fn_80228B98(extra, 1);
                        } else {
                            fn_8015DB84(lbl_8064D5FC, &material,
                                        CACHED(region)[channel]);
                        }
                    }
                } else {
                    fn_8015DB84(state->resources[channel], &material, 0);
                }

                if (channel == 1 && lbl_8064D650 != 0) {
                    fn_801EB8E8(values);
                }
                fn_80228AFC(&material, mode);
                CHECKSUM(region, channel) = fn_8022893C(&material);
                lbl_8064D680++;
            } else {
                lbl_8064D684++;
            }
        } else {
            lbl_8064D684++;
        }
    }

    if (channel == 7 || channel == 9) {
        result = 2;
    }
    if ((flags & 0x7000) != lbl_8064D61C) {
        lbl_8064D61C = flags & 0x7000;
        COMMAND(region, total) = -1;
    }
    if (attributes & 0x40000000) {
        tint = 1;
        kind = 1;
        speed = 0x30;
    }

    switch (channel) {
    case 10:
        fn_801EDE34(total, 0xFF, 0xFF, selector);
        break;
    case 0:
        fn_801EF278(total, tint, kind, speed, mode, selector);
        break;
    case 1:
        if (lbl_8064D678 == 1 || lbl_8064D678 == 3 || lbl_8064D678 == 7) {
            fn_801EF278(total, tint, kind, speed, mode, selector);
        } else {
            fn_801EF278(total, 1, 5, 0x3C, mode, selector);
        }
        break;
    case 4:
        fn_801EF278(total, tint, kind, speed, mode, selector);
        break;
    case 5:
        fn_801EF278(total, tint, kind, speed, mode, selector);
        break;
    case 2:
        if (CHECKSUM(region, channel) == 1) {
            fn_801EF278(total, 1, 1, 0x2D, mode, 0);
        } else {
            fn_801EF278(total, 1, 4, 0x3C, mode, 1);
        }
        break;
    case 9:
        fn_801EF278(total, 1, 0, 0x36, mode, 0xFF);
        fn_801EF278(total + 1, 1, 0, 0x39, 7, 0xFF);
        break;
    case 7:
        if (lbl_8064D678 == 1 || lbl_8064D678 == 3 || lbl_8064D678 == 7) {
            fn_801EF278(total, 1, 4, 0x3C, mode, 0);
            fn_801EF278(total + 1, 2, 4, 0x3C, mode, 0);
        } else {
            fn_801EF278(total, 1, 4, 0x3C, mode, 0);
            fn_801EF278(total + 1, 9, 4, 0x3C, mode, 0);
        }
        break;
    case 3:
        fn_801EF278(total, 1, 0, 0x33, mode, 0);
        break;
    default:
        result = 0;
        break;
    }

    if (values != 0) {
        first = values[0];
    } else {
        first = state->values[0];
    }

    switch (channel) {
    case 10:
        COMMAND(region, total) = 10;
        fn_801ED510(total, 0, 0);
        if (repeat == 1) {
            repeat = 6;
        }
        if (command == 2) {
            command = 12;
        }
        fn_801EF220(total, 0xD);
        fn_801EF1A4(total, 7, repeat, 1, 7);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        if (first == -1) {
            fn_801EF000(total, 0xF, command, 2, 0xE);
        } else {
            fn_801EF000(total, 0xF, command, 2, 0xF);
        }
        break;
    case 0:
        COMMAND(region, total) = 0;
        if (flags & 0x1000) {
            switch (flags & 0x6000) {
            case 0:
                fn_801ED494(0, 0, 0, 0, 0);
                break;
            case 0x2000:
                fn_801ED494(0, 1, 1, 1, 1);
                break;
            case 0x4000:
                fn_801ED494(0, 2, 2, 2, 2);
                break;
            case 0x6000:
                fn_801ED494(0, 3, 3, 3, 3);
                break;
            }
        } else {
            fn_801ED494(0, 0, 1, 2, 3);
        }
        fn_801ED510(total, 0, 0);
        fn_801EF1A4(total, 7, repeat, 4, 7);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        fn_801EF220(total, 0x10);
        fn_801EF000(total, 0xF, 8, command, 0xE);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        break;
    case 1: {
        int alternate = fn_801EB304();
        int texture;

        COMMAND(region, total) = 1;
        texture = 0xC;
        fn_801ED510(total, 0, 0);
        fn_801EF1A4(total, 7, 7, 7, repeat);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        if (alternate != 0) {
            texture = 0xD;
        }
        if (first == -1 && total == 0) {
            fn_801EF220(total, 0x10);
            fn_801EF000(total, 0xF, texture, 8, 0xE);
        } else {
            fn_801EF000(total, 0xF, texture, 8, command);
        }
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        break;
    }
    case 4:
        COMMAND(region, total) = 4;
        fn_801ED510(total, 0, 0);
        fn_801EF1A4(total, 7, 7, 7, repeat);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        fn_801EF000(total, 0xF, 0xC, command, 8);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        break;
    case 5:
        COMMAND(region, total) = 5;
        fn_801ED494(1, 0, 0, 0, 0);
        fn_801ED510(total, 0, 1);
        fn_801EF1A4(total, 7, repeat, 4, 7);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        fn_801EF000(total, 0xF, 0xF, 0xF, command);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        break;
    case 2:
        COMMAND(region, total) = 2;
        fn_801ED510(total, 0, 0);
        fn_801EF1A4(total, 7, 7, 7, 0);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        fn_801EF000(total, 0xF, 0xA, 8, 0);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        break;
    case 9:
        COMMAND(region, total) = 9;
        fn_801ED510(total, 0, 0);
        fn_801EF220(total, 0xE);
        fn_801EF000(total, 0xF, 0xE, 8, 0xF);
        fn_801EF07C(total, 0, 0, 0, 1, 2);
        fn_801EF1A4(total, 7, 7, 7, repeat);
        fn_801EF110(total, 0, 0, 0, 1, 2);
        next = total + 1;
        COMMAND(region, next) = -1;
        fn_801EF000(next, 0xF, 8, 4, command);
        fn_801EF07C(next, 0, 0, 0, 1, 0);
        fn_801EF1A4(next, 7, 7, 7, repeat);
        fn_801EF110(next, 0, 0, 0, 1, 0);
        break;
    case 7:
        COMMAND(region, total) = 7;
        fn_801ED510(total, 0, 0);
        fn_801EF220(total, 0x14);
        fn_801EF000(total, 0xF, 8, 0xE, command);
        fn_801EF07C(total, 0, 0, 0, 0, 0);
        fn_801EF1A4(total, 7, 7, 7, repeat);
        fn_801EF110(total, 0, 0, 0, 1, 0);
        next = total + 1;
        COMMAND(region, next) = -1;
        fn_801ED510(next, 0, 0);
        fn_801EF220(next, 0x14);
        fn_801EF000(next, 0xF, 8, 0xE, 0);
        fn_801EF07C(next, 1, 0, 0, 1, 0);
        fn_801EF1A4(next, 7, 7, 7, 0);
        fn_801EF110(next, 0, 0, 0, 1, 0);
        break;
    case 3:
        COMMAND(region, total) = 3;
        fn_801ED510(total, 0, 0);
        fn_801EF000(total, 0xF, 6, 8, command);
        fn_801EF07C(total, 0, 0, 0, 1, 0);
        fn_801EF1A4(total, 7, 4, 3, repeat);
        fn_801EF110(total, 1, 0, 0, 1, 0);
        break;
    default:
        result = 0;
        break;
    }

    return result;
}
