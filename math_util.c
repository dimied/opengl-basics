
#include <math.h>

float dot(float *pVec, float *pVec2)
{
    return pVec[0] * pVec2[0] + pVec[1] * pVec2[1] + pVec[2] * pVec2[2];
}

void normalize(float *pVec)
{
    float len = sqrt(pVec[0] * pVec[0] + pVec[1] * pVec[1] + pVec[2] * pVec[2]);
    if (len > 0)
    {
        pVec[0] /= len;
        pVec[1] /= len;
        pVec[2] /= len;
    }
}
void cross(float *pA, float *pB, float *pRes)
{

    *pRes = pA[1] * pB[2] - pA[2] * pB[1];
    ++pRes;
    *pRes = pA[2] * pB[0] - pA[0] * pB[2];
    ++pRes;
    *pRes = pA[0] * pB[1] - pA[1] * pB[0];
}
/**
 * Column major
 */
void lookAtRightHandCM(float *pViewer, float *pLookAt, float *pUpDirection,
                       float *pResultMat4x4)
{
    {
        // vec<3, T, Q> const f(normalize(center - eye));
        // vec<3, T, Q> const s(normalize(cross(f, up)));
        // vec<3, T, Q> const u(cross(s, f));
        float viewDir[3] = {
            pLookAt[0] - pViewer[0],
            pLookAt[1] - pViewer[1],
            pLookAt[2] - pViewer[2],
        };
        normalize(viewDir);

        float leftDir[3];
        cross(viewDir, pUpDirection, leftDir);
        normalize(leftDir);

        float upDir[3];
        cross(leftDir, viewDir, upDir);

        for (int i = 0; i < 3; i++)
        {
            *pResultMat4x4 = leftDir[i]; // 0x0
            ++pResultMat4x4;
            *pResultMat4x4 = upDir[i]; // 1x0
            ++pResultMat4x4;
            *pResultMat4x4 = -viewDir[i]; // 2x0
            ++pResultMat4x4;
            *pResultMat4x4 = 0; // 3x0
            ++pResultMat4x4;
        }

        *pResultMat4x4 = -dot(leftDir, pViewer);
        ++pResultMat4x4;
        *pResultMat4x4 = dot(upDir, pViewer);
        ++pResultMat4x4;
        *pResultMat4x4 = dot(viewDir, pViewer);
        ++pResultMat4x4;
        *pResultMat4x4 = 1; // 3x0

        /*
              mat<4, 4, T, Q> Result(1);
              Result[0][0] = s.x;
              Result[1][0] = s.y;
              Result[2][0] = s.z;

              Result[0][1] = u.x;
              Result[1][1] = u.y;
              Result[2][1] = u.z;

              Result[0][2] = -f.x;
              Result[1][2] = -f.y;
              Result[2][2] = -f.z;
              Result[3][0] = -dot(s, eye);
              Result[3][1] = -dot(u, eye);
              Result[3][2] = dot(f, eye);
              return Result;
              */
    }
}