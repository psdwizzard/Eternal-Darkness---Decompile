typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Record {
    unsigned char pad00[0x50];
    Vec3 position;
    unsigned char pad5C[0x18];
    int handle;
    unsigned char pad78[0x0E];
    unsigned short id;
    unsigned char initial_volume;
    unsigned char current_volume;
    unsigned char current_aux;
    unsigned char initial_aux;
    unsigned char target_aux;
    unsigned char target_volume;
    unsigned char pad8E;
    signed char state;
    signed char timer;
    unsigned char kind;
    signed char active;
    unsigned char pad93[5];
} Record;

typedef struct SecondaryRecord {
    unsigned char pad00[0x92];
    unsigned char active;
} SecondaryRecord;

extern int lbl_8064D2F0;
extern int lbl_8064D2EC;
extern int lbl_8064D2E0;
extern int lbl_8064D2E4;
extern int lbl_8064D2E8;
extern void* lbl_8064C4E4;
extern unsigned int lbl_8064D18C;
extern float lbl_80650E74;

extern void fn_801B05B0(int, int);
extern void fn_801AB048(Record*);
extern Record* fn_801AB2EC(void);
extern int fn_801B0B64(void*, int);
extern void* fn_8011F130(void*);
extern int fn_801AAE68(unsigned short, unsigned char, unsigned char, float,
                       Vec3*, signed char, unsigned char, unsigned char,
                       unsigned short, unsigned int);
extern int fn_80048688(void);
extern SecondaryRecord* fn_8015C28C(int);
extern unsigned short fn_800486E8(void);
extern int fn_801AF85C(int);
extern Record* fn_801AB3CC(void);
extern void fn_801B0BB4(int, Vec3*);
extern void fn_801AB0C4(Record*, signed char, signed char);
extern int fn_801B05E8(unsigned short, int, int, int, Vec3*, unsigned char,
                      int, int);
extern void fn_801B097C(int, int, int);
extern void fn_801B09F0(int, unsigned char);
extern int fn_801C9078(void*);

void fn_801AB50C(Record* record)
{
    if (record->active != 0) {
        switch (record->state) {
        case 0:
        case 2:
            break;
        case 3:
        case 4:
        case 6:
        case 7:
            if (record->timer != 0) {
                int value = record->target_volume - record->target_volume / record->timer;
                if (value < 0) value = 0;
                record->target_volume = (unsigned char)value;
                record->timer--;
                if (record->state == 6 || record->state == 7) {
                    record->initial_volume =
                        record->target_volume < record->initial_volume
                            ? record->target_volume
                            : record->initial_volume;
                    record->current_volume =
                        record->target_volume < record->current_volume
                            ? record->target_volume
                            : record->current_volume;
                }
            } else {
                if (record->handle != -1) {
                    fn_801B05B0(record->handle, 0);
                    record->handle = -1;
                }
                if (record->state == 4 || record->state == 6)
                    fn_801AB048(record);
                else
                    record->state = 1;
            }
            break;
        case 5:
            if (record->timer != 0) {
                record->target_volume = (unsigned char)(
                    record->initial_volume <
                            record->target_volume + record->initial_volume / record->timer
                        ? record->initial_volume
                        : record->target_volume + record->initial_volume / record->timer);
                record->timer--;
            } else {
                record->target_volume = record->initial_volume;
                record->state = 1;
            }
            break;
        case 1:
            if (lbl_8064D2F0 == 0 && fn_801AB2EC() == record) {
                if (record->handle != -1) {
                    switch (record->id) {
                    case 0x17:
                        if (fn_801B0B64(0, record->handle) > 0x1A0298) {
                            unsigned int volume;
                            if (lbl_8064D2EC == 0 && (volume = record->target_volume) != 0) {
                                Vec3* source = fn_8011F130(lbl_8064C4E4);
                                fn_801AAE68(0x266, volume > 0x7F ? 0x7F : volume,
                                           0, lbl_80650E74, source, 2, 1, 0,
                                           (unsigned short)lbl_8064D18C, 0);
                                lbl_8064D2EC = 1;
                            }
                        } else {
                            lbl_8064D2EC = 0;
                        }
                        break;
                    case 0x1E6:
                        if (fn_80048688() == 0)
                            break;
                        if (fn_801B0B64(0, record->handle) > 0x26FC78) {
                            if (lbl_8064D2E0 == 0) {
                                SecondaryRecord* other = fn_8015C28C(2);
                                unsigned int a = other->active;
                                unsigned int b = record->target_volume;
                                if (a != 0 || b != 0) {
                                    unsigned short sound = fn_800486E8();
                                    Vec3* source = fn_8011F130(lbl_8064C4E4);
                                    int av = a + 0x1E;
                                    if (av > 0x7F) av = 0x7F;
                                    av = (unsigned char)av;
                                    a = b > 0x7F ? 0x7F : b;
                                    fn_801AAE68(sound, (unsigned char)av, 0, lbl_80650E74,
                                               source, 2, 1, 0,
                                               (unsigned short)lbl_8064D18C, 0);
                                    fn_801AAE68(0x267, a, 0,
                                               lbl_80650E74, source, 2, 1, 0,
                                               (unsigned short)lbl_8064D18C, 0);
                                    lbl_8064D2E0 = 1;
                                }
                            }
                        } else {
                            lbl_8064D2E0 = 0;
                        }
                        break;
                    case 0x1EA:
                        if (fn_801B0B64(0, record->handle) > 0x2AD6DE) {
                            unsigned int volume;
                            if (lbl_8064D2E4 == 0 && (volume = record->target_volume) != 0) {
                                Vec3* source = fn_8011F130(lbl_8064C4E4);
                                fn_801AAE68(0x266, volume > 0x7F ? 0x7F : volume,
                                           0, lbl_80650E74, source, 2, 1, 0,
                                           (unsigned short)lbl_8064D18C, 0);
                                lbl_8064D2E4 = 1;
                            }
                        } else {
                            lbl_8064D2E4 = 0;
                        }
                        break;
                    case 0x1EB:
                        if (fn_801B0B64(0, record->handle) > 0x2AD6DE) {
                            unsigned int volume;
                            if (lbl_8064D2E8 == 0 && (volume = record->target_volume) != 0) {
                                Vec3* source = fn_8011F130(lbl_8064C4E4);
                                fn_801AAE68(0x266, volume > 0x7F ? 0x7F : volume,
                                           0, lbl_80650E74, source, 2, 1, 0,
                                           (unsigned short)lbl_8064D18C, 0);
                                lbl_8064D2E8 = 1;
                            }
                        } else {
                            lbl_8064D2E8 = 0;
                        }
                        break;
                    }
                }

                if (record->handle == -1 || fn_801AF85C(record->handle) == 0) {
                    Record* other = fn_801AB3CC();
                    if (other != 0) {
                        if (other->state == 1 || other->state == 5 || other->state == 6) {
                            if (other->id == record->id) {
                                Vec3 position;
                                position.x = record->position.x;
                                position.y = record->position.y;
                                position.z = record->position.z;
                                record->handle = other->handle;
                                other->handle = -1;
                                other->target_volume = 0;
                                record->target_volume = record->initial_volume;
                                fn_801B0BB4(record->handle, &position);
                            } else if (other->state == 6) {
                                int timer = record->timer;
                                if (timer > 3) timer = 3;
                                record->timer = (signed char)timer;
                            } else {
                                fn_801AB0C4(other, 3, 3);
                            }
                        }
                    } else {
                        record->handle = fn_801B05E8(record->id, 0, 1, 1,
                                                    &record->position, record->kind,
                                                    0, 0);
                        if (record->handle != -1) {
                            record->target_volume = 0;
                            fn_801AB0C4(record, 5, 5);
                            if (record->id == 0x1EA || record->id == 0x1EB ||
                                record->id == 0x1E6 || record->id == 0x1E5) {
                                fn_801B097C(record->handle, 2, 0);
                            }
                        }
                    }
                } else {
                    record->target_volume = record->initial_volume;
                }
            }
            break;
        }

        if (record->state != 0 && record->handle != -1)
            fn_801B09F0(record->handle, record->target_volume);
    } else {
        switch (record->state) {
        case 0:
        case 1:
            break;
        case 2:
            if ((unsigned int)fn_801C9078(record) == 0)
                fn_801AB048(record);
            break;
        case 3:
        case 4:
            if (record->timer != 0) {
                int value = record->current_volume - record->current_volume / record->timer;
                if (value < 0) value = 0;
                record->current_volume = (unsigned char)value;
                record->timer--;
            } else if (record->state == 4) {
                fn_801AB048(record);
            } else {
                record->state = 1;
            }
            break;
        case 5:
            if (record->timer != 0) {
                if (record->initial_aux != 0) {
                    int value = record->current_volume + record->initial_aux / record->timer;
                    value = record->initial_aux < value ? record->initial_aux : value;
                    record->current_volume = (unsigned char)value;
                }
                if (record->target_aux != 0) {
                    int value = record->current_aux + record->target_aux / record->timer;
                    value = record->target_aux < value ? record->target_aux : value;
                    record->current_aux = (unsigned char)value;
                }
                record->timer--;
            } else {
                record->current_volume = record->initial_aux;
                record->current_aux = record->target_aux;
                record->state = 1;
            }
            break;
        }
    }
}
