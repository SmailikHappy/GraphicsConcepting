#include "RainDropShaderClasses.h"

IMPLEMENT_SHADER_TYPE(, FClearShaderPS, TEXT("/SceneViewExtModule/RainDropMaskShader.usf"), TEXT("ClearRT"), SF_Pixel);

IMPLEMENT_SHADER_TYPE(, FTosterShaderVS, TEXT("/SceneViewExtModule/RainDropMaskShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FTosterShaderPS, TEXT("/SceneViewExtModule/RainDropMaskShader.usf"), TEXT("MainPS"), SF_Pixel);