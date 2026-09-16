import runpy
m=runpy.run_path('reports/GEDE01/probe-ff31a8f4-27bc-4b2d-a516-c5b4bd2c49ad.py')
BASE=m['BASE']; trial=m['trial'];region=m['region']
s=BASE.replace('    void* found;','    void* attachment;\n    void* found;')
s=region(s,'        found = fn_80201C2C','        array = fn_80201C24','found','attachment')
for anchor in ['void* script_reg','void* view','Vec3s* position','s32 mode','void* handle','void* callback','s32 controller','void* attachment','void* found','ItemArray* array','s32 index','Request req']:
 a=s.replace('        void* object;\n','').replace('    '+anchor+';','    void* object;\n    '+anchor+';')
 r=trial('object_before_'+anchor.split()[-1],a,'With found roles separated, test ordering of the distinct late object interference web before '+anchor+'. Earlier attempts did not separate found roles.')
 if r.get('measurement',{}).get('match_percent')==100:break
