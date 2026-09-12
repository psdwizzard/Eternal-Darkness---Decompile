extern int fn_800459E0(void* object);

int fn_802022B4(void* object)
{
    int kind = object != 0 ? fn_800459E0(object) : 0;

    return kind == 0x1F || kind == 0x20 || kind == 0x21 ||
           kind == 0x23 || kind == 0x24;
}
