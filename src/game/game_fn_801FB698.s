.include "macros.inc"
.text
.balign 4

.fn fn_801FB698, global
lfs f1, 0(r3)
psq_st f1, 0(r4), 1, qr5
blr
.endfn fn_801FB698
