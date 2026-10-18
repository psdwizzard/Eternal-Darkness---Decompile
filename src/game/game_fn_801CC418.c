typedef unsigned int u32;
extern u32 synthGetTicksPerSecond(u32 value);

void sndConvertTicks(u32* value, u32 divisor)
{
    divisor = synthGetTicksPerSecond(divisor);
    *value = (((*value << 16) / divisor) * 1000) >> 5;
}
