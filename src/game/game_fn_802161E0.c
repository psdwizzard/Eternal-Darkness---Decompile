/* Return the current disc ID stored in the low-memory boot area. */
typedef struct DVDDiskID DVDDiskID;

DVDDiskID *fn_802161E0(void) {
    return (DVDDiskID *)0x80000000;
}
