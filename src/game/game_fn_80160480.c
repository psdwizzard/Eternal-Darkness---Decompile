typedef struct Entry {
    int type;
    char pad4[12];
} Entry;

extern char* const lbl_8023A878[6];
extern char lbl_8024F554[];
extern char lbl_8024F578[];
extern void fn_80163BB4(void*, const char*, ...);

void fn_80160480(void* object, Entry* entry)
{
    int current_type = entry[-1].type;
    int previous_type = entry[-2].type;
    char* previous_descriptor = lbl_8023A878[previous_type];
    char* current_descriptor = lbl_8023A878[current_type];

    if ((signed char)previous_descriptor[2] == (signed char)current_descriptor[2])
        fn_80163BB4(object, lbl_8024F554, previous_descriptor, current_descriptor);
    else
        fn_80163BB4(object, lbl_8024F578, previous_descriptor, current_descriptor);
}
