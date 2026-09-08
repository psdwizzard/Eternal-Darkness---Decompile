.include "macros.inc"
.text
.balign 4
.global fn_801EDA68
fn_801EDA68:
    psq_l f1, 0(r3), 1, qr5
    stfs f1, 0(r4)
    blr
