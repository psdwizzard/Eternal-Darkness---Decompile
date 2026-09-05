extern void* volatile lbl_8064D304;

#pragma global_optimizer off
int fn_801AD898(void)
{
    if ((unsigned int)lbl_8064D304 > 0) {
        return 0;
    }
    return 1;
}
#pragma global_optimizer reset
