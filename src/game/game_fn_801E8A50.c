typedef struct Object { unsigned int words[9]; } Object;
extern void* memset(void*, int, unsigned int);
void fn_801E8A50(Object* object)
{
    memset(object, 0, sizeof(Object));
    object->words[5] = 1;
}
