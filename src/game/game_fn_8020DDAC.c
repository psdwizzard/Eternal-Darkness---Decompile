extern void *SaveStart; /* SaveStart */
extern void *SaveEnd; /* SaveEnd */

/* Set the memory region to preserve across a reboot. */
void OSSetSaveRegion(void *start, void *end)
{
    SaveStart = start;
    SaveEnd = end;
}
