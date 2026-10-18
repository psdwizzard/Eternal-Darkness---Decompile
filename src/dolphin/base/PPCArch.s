.include "macros.inc"
.text
.balign 4

.fn PPCMfmsr, global
mfmsr r3
blr
.endfn PPCMfmsr
.fn PPCMtmsr, global
mtmsr r3
blr
.endfn PPCMtmsr
.fn PPCMfhid0, global
mfspr r3, HID0
blr
.endfn PPCMfhid0
.fn PPCMthid0, global
mtspr HID0, r3
blr
.endfn PPCMthid0
.fn PPCMfl2cr, global
mfspr r3, L2CR
blr
.endfn PPCMfl2cr
.fn PPCMtl2cr, global
mtspr L2CR, r3
blr
.endfn PPCMtl2cr
.fn PPCMtdec, weak
mtdec r3
blr
.endfn PPCMtdec
.fn PPCSync, global
sc
blr
.endfn PPCSync
.fn PPCHalt, weak
sync
1:
nop
li r3, 0
nop
b 1b
.endfn PPCHalt
.fn PPCMtmmcr0, global
mtspr MMCR0, r3
blr
.endfn PPCMtmmcr0
.fn PPCMtmmcr1, global
mtspr MMCR1, r3
blr
.endfn PPCMtmmcr1
.fn PPCMfpmc1, global
mfspr r3, PMC1
blr
.endfn PPCMfpmc1
.fn PPCMtpmc1, global
mtspr PMC1, r3
blr
.endfn PPCMtpmc1
.fn PPCMtpmc2, global
mtspr PMC2, r3
blr
.endfn PPCMtpmc2
.fn PPCMfpmc3, global
mfspr r3, PMC3
blr
.endfn PPCMfpmc3
.fn PPCMtpmc3, global
mtspr PMC3, r3
blr
.endfn PPCMtpmc3
.fn PPCMfpmc4, global
mfspr r3, PMC4
blr
.endfn PPCMfpmc4
.fn PPCMtpmc4, global
mtspr PMC4, r3
blr
.endfn PPCMtpmc4
.fn PPCMfhid2, global
mfspr r3, HID2
blr
.endfn PPCMfhid2
.fn PPCMthid2, global
mtspr HID2, r3
blr
.endfn PPCMthid2
.fn PPCMfwpar, global
sync
mfspr r3, WPAR
blr
.endfn PPCMfwpar
.fn PPCMtwpar, global
mtspr WPAR, r3
blr
.endfn PPCMtwpar
.fn PPCDisableSpeculation, global
mflr r0
stw r0, 4(r1)
stwu r1, -8(r1)
bl PPCMfhid0
ori r3, r3, 0x200
bl PPCMthid0
lwz r0, 0xc(r1)
addi r1, r1, 8
mtlr r0
blr
.endfn PPCDisableSpeculation
.fn PPCSetFpNonIEEEMode, global
mtfsb1 cr7gt
blr
.endfn PPCSetFpNonIEEEMode
