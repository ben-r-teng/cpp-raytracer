
#include "pch.h"
#include "variables.h"  /* Declaration made available here */

int  g_imgdimsx;
int  g_imgdimsy;
vec3 g_lookFrom, g_lookAt, g_upVec;
float g_fovy;

Printer* g_printer = new Printer();

float g_tMin        = 0.01f;
float g_tMax        = 10000.0f;
int   g_maxRecDepth = 5;

float g_kConst = 1.0f;
float g_kLin = 0.0f;
float g_kQuad = 0.0f;

// Settings
string g_outName = "outputImg.png";
bool g_vertexNormalInterp = true;
bool g_multithreadCPU = false;
