typedef unsigned int u32;

extern u32 salMessageCallback;

void hwSetMesgCallback(u32 value)
{
    salMessageCallback = value;
}
