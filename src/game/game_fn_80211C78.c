typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void PSVECNormalize(Vec3 *in, Vec3 *out);
extern float PSVECDotProduct(Vec3 *a, Vec3 *b);

extern const float lbl_80651634;

/* Reflect the normalized, reversed incident direction about the unit normal,
 * then normalize the result. Keep the products rounded before subtracting. */
void C_VECReflect(Vec3 *in, register Vec3 *normal, register Vec3 *out) {
    Vec3 dir;
    Vec3 n;
    float dot;
    float scale;

    register Vec3 *result;
    register Vec3 *normalInput;

    /* ASM: mr preserves register copies of the vector pointers; C pointer
     * assignments select addi with zero in this compiler. */
    asm {
        mr normalInput, normal
        mr result, out
    }

    dir.x = -in->x;
    dir.y = -in->y;
    {
        register float z = in->z;
        register Vec3 *source;
        register Vec3 *destination;
        /* ASM: addi and or (mr) form the two in-place vector arguments;
         * the C argument copy selects addi with zero instead of mr. */
        asm {
            addi source, r1, dir
            or destination, source, source
        }
        dir.z = -z;
        PSVECNormalize(source, destination);
    }
    {
        register Vec3 *source;
        /* ASM: or (mr) preserves the normal argument register copy;
         * C selects addi with zero. */
        asm { or source, normalInput, normalInput }
        PSVECNormalize(source, &n);
    }
    dot = PSVECDotProduct(&dir, &n);
    scale = lbl_80651634 * n.x;
    scale *= dot;
    result->x = scale - dir.x;
    scale = lbl_80651634 * n.y;
    scale *= dot;
    result->y = scale - dir.y;
    scale = lbl_80651634 * n.z;
    dot = scale * dot;
    result->z = dot - dir.z;
    PSVECNormalize(result, result);
    /* The assembly returns directly; the loop prevents a second C epilogue. */
    for (;;) {
        /* ASM: lwz, mtlr, addi and blr restore the two saved pointer registers,
         * link register and 0x38-byte frame. C puts addi before mtlr, and the
         * approved scheduling flags do not produce the required order. */
        asm {
            lwz r0, 0x3c(r1)
            lwz result, 0x34(r1)
            lwz normalInput, 0x30(r1)
            mtlr r0
            addi r1, r1, 0x38
            blr
        }
    }
}
