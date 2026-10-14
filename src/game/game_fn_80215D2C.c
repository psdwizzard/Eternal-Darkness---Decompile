/* Dolphin SDK dvd.c: DVDSetAutoInvalidation */
typedef int BOOL;

extern BOOL autoInvalidation_8064C408;

BOOL fn_80215D2C(BOOL autoInval) {
    BOOL previous = autoInvalidation_8064C408;
    autoInvalidation_8064C408 = autoInval;
    return previous;
}
