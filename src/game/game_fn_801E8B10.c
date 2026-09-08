typedef struct Object { unsigned int words[9]; } Object;
void fn_801E8B10(Object* object, unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    object->words[5] = a;
    object->words[6] = b;
    object->words[7] = c;
    object->words[8] = d;
}
