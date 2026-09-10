extern const unsigned int lbl_80239CD0[];

asm unsigned int fn_800F5C54(register double d)
{
    nofralloc
    stwu r1, -16(r1)
    lis r4, lbl_80239CD0@h
    ori r4, r4, lbl_80239CD0@l
    li r3, 0
    lfd fp0, 0(r4)
    lfd fp3, 8(r4)
    lfd fp4, 16(r4)
    fcmpu cr0, fp1, fp0
    fcmpu cr6, fp1, fp3
    blt cr0, exit
    addi r3, r3, -1
    bge cr6, exit
    fcmpu cr7, fp1, fp4
    fmr fp2, fp1
    blt cr7, skip
    fsub fp2, fp1, fp4
skip:
    fctiwz fp2, fp2
    stfd fp2, 8(r1)
    lwz r3, 12(r1)
    blt cr7, exit
    addis r3, r3, -0x8000
exit:
    addi r1, r1, 16
    blr
}
