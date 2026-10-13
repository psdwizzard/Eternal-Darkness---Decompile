typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void fn_80211AAC(Vec3 *in, Vec3 *out);
extern float fn_80211B44(Vec3 *a, Vec3 *b);

/* Reflects the reversed incident direction about the normal and
 * normalizes the result: out = normalize(2 * dot(-in, n) * n + in).
 * The scale temp keeps each product a separate fmuls instead of fmsubs. */
void fn_80211C78(Vec3 *in, Vec3 *normal, Vec3 *out) {
    Vec3 dir;
    Vec3 n;
    float dot;
    float scale;

    dir.x = -in->x;
    dir.y = -in->y;
    dir.z = -in->z;
    fn_80211AAC(&dir, &dir);
    fn_80211AAC(normal, &n);
    dot = fn_80211B44(&dir, &n);
    scale = 2.0f * n.x * dot;
    out->x = scale - dir.x;
    scale = 2.0f * n.y * dot;
    out->y = scale - dir.y;
    scale = 2.0f * n.z * dot;
    out->z = scale - dir.z;
    fn_80211AAC(out, out);
}
