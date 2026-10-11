typedef struct ObjectData {
    unsigned char pad00[0x9F];
    unsigned char kind;
} ObjectData;

extern void *fn_80201B8C(unsigned char *object);

int fn_800459E0(unsigned char *object)
{
    ObjectData *data = object != 0 ? fn_80201B8C(object) : 0;

    return data != 0 ? data->kind : -1;
}
