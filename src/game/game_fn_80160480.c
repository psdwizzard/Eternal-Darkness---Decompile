typedef struct Entry {
    int type;
    char pad4[12];
} Entry;

extern unsigned char* volatile lbl_8023A878[];
extern char lbl_8024F554[];
extern char lbl_8024F578[];
extern void fn_80163BB4(void*, const char*, ...);

void fn_80160480(void* object, Entry* entry)
{
    int current_type = entry[-1].type;
    int previous_type = entry[-2].type;
    unsigned char* previous_descriptor = lbl_8023A878[previous_type];
    unsigned char* current_descriptor = lbl_8023A878[current_type];

    if ((signed char)current_descriptor[2] ==
        (signed char)previous_descriptor[2])
        fn_80163BB4(object, lbl_8024F554);
    else
        fn_80163BB4(object, lbl_8024F578);
}
