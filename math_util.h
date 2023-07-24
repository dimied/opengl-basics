#ifndef __MATH_UTIL__
#define __MATH_UTIL__

float dot(float *pVec, float *pVec2);
void normalize(float *pVec);
void cross(float *pA, float *pB, float *pRes);
void lookAtRightHandCM(float *pViewer, float *pLookAt, float *pUpDirection,
                       float *pResultMat4x4);

#endif