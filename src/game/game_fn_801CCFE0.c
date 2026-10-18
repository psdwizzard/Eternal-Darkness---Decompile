typedef unsigned char u8;

extern void salDeactivateStudio(u8 index);

void hwDeactivateStudio(u8 index)
{
    salDeactivateStudio(index);
}
