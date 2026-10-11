typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Matrix34[3][4];
typedef struct SearchResult {
    int second, first;
    Vec3 position;
    u8 tail[0x14];
} SearchResult;
typedef struct GameState {
    float zAngle, xAngle;
    u8 pad08[0x184];
    Vec3 position;
    Vec3 target;
    Vec3 direction;
} GameState;
typedef struct MenuState { void *model; u8 pad04[0x630]; } MenuState;

extern Vec3 lbl_802393D8;
extern GameState lbl_8031CBA0;
extern MenuState lbl_8031CD84;
extern float lbl_8064EA14;
extern int fn_8011F6A4(void *, int, int, int, void *, int);
extern void fn_80211268(Matrix34, int, float);
extern void fn_80210FDC(Matrix34, Matrix34, Matrix34);
extern void fn_80211710(Matrix34, const Vec3 *, Vec3 *);
extern void fn_80211AAC(const Vec3 *, Vec3 *);
extern void fn_80211A48(const Vec3 *, const Vec3 *, Vec3 *);
extern void fn_80080A38(Vec3 *, const Vec3 *, Vec3 *, int, int);

void fn_80080B7C(void)
{
    Matrix34 transform, xRotation, yRotation, zRotation, intermediate;
    SearchResult result;
    Vec3 direction = lbl_802393D8;
    Vec3 adjusted, start, end;

    fn_8011F6A4(lbl_8031CD84.model, 2, 15, -1, &result, 1);
    fn_80211268(xRotation, 0x78, lbl_8031CBA0.xAngle);
    fn_80211268(yRotation, 0x79, lbl_8064EA14);
    fn_80211268(zRotation, 0x7A, lbl_8031CBA0.zAngle);
    fn_80210FDC(zRotation, yRotation, intermediate);
    fn_80210FDC(intermediate, xRotation, transform);
    fn_80211710(transform, &direction, &direction);
    lbl_8031CBA0.direction = direction;
    fn_80211AAC(&lbl_8031CBA0.direction, &lbl_8031CBA0.direction);
    fn_80211A48(&direction, &result.position, &lbl_8031CBA0.target);
    lbl_8031CBA0.position = result.position;
    end = lbl_8031CBA0.target;
    start = lbl_8031CBA0.position;
    fn_80080A38(&adjusted, &start, &end, 1, 0);
    lbl_8031CBA0.target = adjusted;
}
