typedef unsigned char u8;

typedef struct Vec8012B8A8 {
    float x;
    float y;
    float z;
} Vec8012B8A8;

extern volatile Vec8012B8A8 lbl_8023A6D8;
extern const float lbl_806501D4;

extern void* fn_8011F130(void*);
extern void fn_8012B690(void*, const Vec8012B8A8*, Vec8012B8A8*);
extern void fn_80211A6C();
extern float fn_80211B44(const Vec8012B8A8*, const Vec8012B8A8*);

u8 fn_8012B8A8(void* owner, const Vec8012B8A8* position)
{
    Vec8012B8A8 normal;
    Vec8012B8A8 direction = lbl_8023A6D8;
    Vec8012B8A8 local_position;
    void* transform;
    float value;

    transform = fn_8011F130(owner);
    fn_80211A6C(position, transform, &normal);
    fn_8012B690(owner, &direction, &local_position);
    fn_80211A6C(&local_position, transform, &local_position);
    value = fn_80211B44(&local_position, &normal);
    return value > lbl_806501D4;
}
