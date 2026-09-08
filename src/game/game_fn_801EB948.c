typedef unsigned char u8;
typedef struct Object { u8 pad[8]; void* stream; u8 rest[8]; } Object;
typedef struct Scene { u8 pad[0x4C]; int count; Object* objects; } Scene;
extern int lbl_8064D618;
extern int lbl_8064D650;
extern int lbl_8064D654;
void fn_801EB948(Scene* scene)
{
    int i;
    int count;
    Object* object;
    lbl_8064D618 = -1;
    lbl_8064D654 = 0;
    lbl_8064D650 = 1;
    count = scene->count;
    object = scene->objects;
    if (count <= 0)
        return;
    for (i = 0; i < count; i++, object++)
        object->stream = 0;
}
