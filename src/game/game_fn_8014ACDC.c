typedef unsigned char u8; typedef unsigned int u32;
typedef struct Set { u8 count;u8 p1[7];u32 id;u8 pC[0x3C];u32 value48;u8 p4C[0x3C];void* objects[16]; } Set;
typedef struct Vec {float pad[2];float x,y,z;float trailing[4];} Vec;
typedef struct State { Set* entry; float* x; float* y; float* z; } State;
extern void *fn_80156938();extern void *fn_80201BC8();extern u8 fn_801938A0(void*);extern u8 fn_80193880(void*);
extern int fn_8011F6A4(void*,u32,u32,int,Vec*,int);extern short* fn_8017FDE4(void*);extern short* fn_801938A8(void*);
extern void fn_8014B604(float*,short*);extern unsigned short fn_8012DBE8(void*,int,u8*);extern u32 fn_80193860(void*);extern void fn_801938D8(void*,u32);
void fn_8014ACDC(void* left,void* right){
 State state;int i;int count;Set* right_set;Set* set;Vec value;u8 info[4];
 right_set=fn_80156938(right);set=fn_80156938(left);count=set->count;
 if(set){state.entry=set;state.x=&value.x;state.y=&value.y;state.z=&value.z;
  for(i=0;i<count;i++){
   void* object=state.entry->objects[0];void* context=fn_80201BC8(right_set);short* position;
   fn_8011F6A4(context,state.entry->id,state.entry->value48,fn_801938A0(object)-1,&value,1);
   position=fn_8017FDE4(object);fn_8014B604(state.x,position);fn_8014B604(state.y,position+1);fn_8014B604(state.z,position+2);
   fn_8011F6A4(context,state.entry->id,state.entry->value48,fn_80193880(object)-1,&value,1);
   position=fn_801938A8(object);fn_8014B604(state.x,position);fn_8014B604(state.y,position+1);fn_8014B604(state.z,position+2);
   fn_8012DBE8(context,15,info);if(info[3]<255&&object){u32 flags=fn_80193860(object);fn_801938D8(object,flags|0x40000);}
   state.entry=(Set*)((u8*)state.entry+4);
  }
 }
}
