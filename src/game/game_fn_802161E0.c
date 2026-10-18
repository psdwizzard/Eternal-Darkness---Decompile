/* Return the current disc ID stored in the low-memory boot area. */
typedef struct DVDDiskID DVDDiskID;

DVDDiskID *DVDGetCurrentDiskID(void) {
    return (DVDDiskID *)0x80000000;
}
