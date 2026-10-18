/* Dolphin SDK dvd.c: DVDSetAutoInvalidation */
typedef int BOOL;

extern BOOL autoInvalidation_8064C408;

BOOL DVDSetAutoInvalidation(BOOL autoInval) {
    BOOL previous = autoInvalidation_8064C408;
    autoInvalidation_8064C408 = autoInval;
    return previous;
}
