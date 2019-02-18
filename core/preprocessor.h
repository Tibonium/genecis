#ifndef __PREPROCESSOR_H__
#define __PREPROCESSOR_H__

#define PP_CAT1(V1,V2) V1 ## V2

#define PP_CAT(V1,V2) PP_CAT1(V1,V2)

#endif /* __PREPROCESSOR_H__ */
