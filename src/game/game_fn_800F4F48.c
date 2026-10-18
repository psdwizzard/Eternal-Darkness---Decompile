#pragma force_active on
void TRKPositionFile(void)
{
    __asm { twi 31, r0, 0 }
}
#pragma force_active reset
