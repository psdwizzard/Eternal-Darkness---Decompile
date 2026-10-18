typedef unsigned char u8;

extern void* aramGetStreamBufferAddress(u8 index, void** info);

void* hwGetStreamPlayBuffer(u8 index)
{
    return aramGetStreamBufferAddress(index, 0);
}
