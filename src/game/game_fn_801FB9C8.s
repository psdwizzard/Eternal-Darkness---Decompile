.include "macros.inc"
.text
.balign 4

.fn fn_801FB9C8, global
psq_l f1, 0(r3), 1, qr5
stfs f1, 0(r4)
blr
.endfn fn_801FB9C8
