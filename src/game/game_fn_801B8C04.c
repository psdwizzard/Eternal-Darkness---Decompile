extern void* synthVoice;
extern void salFree(void*);

void synthExit(void)
{
    salFree(synthVoice);
}
