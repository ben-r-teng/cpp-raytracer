#ifndef VARIABLE_INCLUDE
#define VARIABLE_INCLUDE


#include <glm.hpp>
using namespace glm;
#include "Printer.h"

extern float g_tMin;
extern float g_tMax;
extern int g_maxRecDepth; // For Recursive RayTracing (RayTracer)

extern int  g_imgdimsx;
extern int  g_imgdimsy;
extern vec3 g_lookFrom, g_lookAt, g_upVec;
extern float g_fovy;

extern Printer* g_printer;
extern string g_outName;

extern float g_kConst;
extern float g_kLin;
extern float g_kQuad;

extern bool g_vertexNormalInterp;
extern bool g_multithreadCPU;

#endif