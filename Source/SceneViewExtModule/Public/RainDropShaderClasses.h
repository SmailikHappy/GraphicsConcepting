#include "GlobalShader.h"
#include "Runtime/Renderer/Public/ScreenPass.h"
#include "Runtime/Engine/Public/SceneView.h"


BEGIN_SHADER_PARAMETER_STRUCT(FClearShaderPSParams, )
	SHADER_PARAMETER(FVector4f, ClearColor)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FClearShaderPS : public FGlobalShader {
public:
	DECLARE_EXPORTED_SHADER_TYPE(FClearShaderPS, Global, );
	using FParameters = FClearShaderPSParams;
	SHADER_USE_PARAMETER_STRUCT(FClearShaderPS, FGlobalShader);
};



BEGIN_SHADER_PARAMETER_STRUCT(FTosterShaderVSParams, )
	SHADER_PARAMETER(FMatrix44f, ViewProjection)
	SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<FVector3f>, RainDropPositionBuffer)
	SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<FVector3f>, RainDropNormalBuffer)
	SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, RainDropScaleBuffer)
END_SHADER_PARAMETER_STRUCT()

class FTosterShaderVS : public FGlobalShader {
public:
	DECLARE_EXPORTED_SHADER_TYPE(FTosterShaderVS, Global, );
	using FParameters = FTosterShaderVSParams;
	SHADER_USE_PARAMETER_STRUCT(FTosterShaderVS, FGlobalShader);
};



BEGIN_SHADER_PARAMETER_STRUCT(FTosterShaderPSParams, )
	SHADER_PARAMETER(FVector3f, ViewLocation)
	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()

class FTosterShaderPS : public FGlobalShader
{
public:
	DECLARE_EXPORTED_SHADER_TYPE(FTosterShaderPS, Global, );
	using FParameters = FTosterShaderPSParams;
	SHADER_USE_PARAMETER_STRUCT(FTosterShaderPS, FGlobalShader);
};



BEGIN_SHADER_PARAMETER_STRUCT(FTosterShaderParameters, )
	SHADER_PARAMETER_STRUCT_INCLUDE(FTosterShaderVS::FParameters, VS)
	SHADER_PARAMETER_STRUCT_INCLUDE(FTosterShaderPS::FParameters, PS)
END_SHADER_PARAMETER_STRUCT()