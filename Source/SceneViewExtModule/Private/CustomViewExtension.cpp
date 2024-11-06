#include "CustomViewExtension.h"
#include "RainDropShaderClasses.h"

#include "PixelShaderUtils.h"
#include "CustomShaderUtils.h"
#include "PostProcess/PostProcessing.h"

#include "Engine/TextureRenderTarget2D.h"

DECLARE_GPU_STAT_NAMED(RainMaskPass, TEXT("Rain mask pass"));

FCustomViewExtension::FCustomViewExtension(const FAutoRegister& AutoRegister,
	FTextureResource* ResourceRTTexture, URainDropOperator* OperatorRef) : FSceneViewExtensionBase(AutoRegister)
{
	CustomTextureMask = ResourceRTTexture;

	RainDropOperator = OperatorRef;

	VertexPassInfo.BaseVertexIndex = 0;
	VertexPassInfo.MinIndex = 0;
	VertexPassInfo.NumVertices = 4;
	VertexPassInfo.StartIndex = 0;
	VertexPassInfo.NumPrimitives = 2;
	VertexPassInfo.NumInstances = 1;
}

void FCustomViewExtension::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	RDG_GPU_STAT_SCOPE(GraphBuilder, RainMaskPass);
	RDG_EVENT_SCOPE(GraphBuilder, "Rain mask pass");


	const FIntRect ViewInfo = static_cast<const FViewInfo&>(InView).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = static_cast<const FViewInfo&>(InView).ShaderMap;
	FRDGTextureRef TargetTextureReference = GraphBuilder.RegisterExternalTexture(CreateRenderTarget(CustomTextureMask->GetTexture2DRHI(), TEXT("Yes")));


	TShaderMapRef<FClearShaderPS> ClearShader(GlobalShaderMap);

	FClearShaderPSParams* ClearShaderParams = GraphBuilder.AllocParameters<FClearShaderPSParams>();

	ClearShaderParams->ClearColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearShaderParams->RenderTargets[0] = FRenderTargetBinding(TargetTextureReference, ERenderTargetLoadAction::ENoAction);

	FPixelShaderUtils::AddFullscreenPass<FClearShaderPS>(
		GraphBuilder,
		GlobalShaderMap,
		RDG_EVENT_NAME("Clearing rain RT pass"),
		ClearShader,
		ClearShaderParams,
		FIntRect(CustomTextureMask->GetSizeX(), CustomTextureMask->GetSizeY())
	);

	FTosterShaderParameters* PassParams = GraphBuilder.AllocParameters<FTosterShaderParameters>();

	if (!RainDropOperator) {
		UE_LOG(LogTemp, Display, TEXT("No Rain Drop storage detected"));
		return;
	}

	if (RainDropOperator->PositionArray.Num() != RainDropOperator->NormalArray.Num()
		|| RainDropOperator->PositionArray.Num() != RainDropOperator->ScaleArray.Num()) {
		UE_LOG(LogTemp, Display, TEXT("Arrays are not the same size. No rendering called"));
		return;
	}

	int dropCount = RainDropOperator->PositionArray.Num();

	if (dropCount == 0) {
		UE_LOG(LogTemp, Display, TEXT("There is no rain drops dropped in the array. No rendering called"));
		return;
	}


	FRDGBufferRef RainDropPositionBuffer =	CreateUploadBuffer(
		GraphBuilder,
		TEXT("Rain Drop position Buffer"),
		sizeof(FVector3f),
		dropCount,
		(void*)RainDropOperator->PositionArray.GetData(),
		sizeof(FVector3f) * dropCount
	);

	FRDGBufferRef RainDropNormalBuffer = CreateUploadBuffer(
		GraphBuilder,
		TEXT("Rain Drop normal Buffer"),
		sizeof(FVector3f),
		dropCount,
		(void*)RainDropOperator->NormalArray.GetData(),
		sizeof(FVector3f) * dropCount
	);

	FRDGBufferRef RainDropScaleBuffer = CreateUploadBuffer(
		GraphBuilder,
		TEXT("Rain Drop scale Buffer"),
		sizeof(float),
		dropCount,
		(void*)RainDropOperator->ScaleArray.GetData(),
		sizeof(float) * dropCount
	);

	FRDGTextureDesc DepthStencilDesc = FRDGTextureDesc::Create2D(
		FIntPoint(CustomTextureMask->GetSizeX(), CustomTextureMask->GetSizeY()),
		PF_DepthStencil,
		FClearValueBinding(0.0f),
		TexCreate_DepthStencilTargetable
	);

	FRDGTextureRef depthStencilTexture = GraphBuilder.CreateTexture(DepthStencilDesc, TEXT("Depth texture for Rain Drop mask"));
	PassParams->VS.ViewProjection = (FMatrix44f) InView.ViewMatrices.GetViewProjectionMatrix();
	PassParams->VS.RainDropPositionBuffer = GraphBuilder.CreateSRV(RainDropPositionBuffer, EPixelFormat::PF_R32G32B32F);
	PassParams->VS.RainDropNormalBuffer = GraphBuilder.CreateSRV(RainDropNormalBuffer, EPixelFormat::PF_R32G32B32F);
	PassParams->VS.RainDropScaleBuffer = GraphBuilder.CreateSRV(RainDropScaleBuffer, EPixelFormat::PF_R32_FLOAT);
	PassParams->PS.ViewLocation = (FVector3f) InView.ViewLocation;
	PassParams->PS.RenderTargets[0] = FRenderTargetBinding(TargetTextureReference, ERenderTargetLoadAction::ENoAction);
	PassParams->PS.RenderTargets.DepthStencil = FDepthStencilBinding(
		depthStencilTexture,
		ERenderTargetLoadAction::EClear,
		ERenderTargetLoadAction::ENoAction,
		FExclusiveDepthStencil::DepthWrite_StencilNop);

	VertexPassInfo.NumInstances = dropCount;

	// Create FTrianglePS Pixel Shader
	TShaderMapRef<FTosterShaderPS> PixelShader(GlobalShaderMap);
	TShaderMapRef<FTosterShaderVS> VertexShader(GlobalShaderMap);


	FCustomShaderUtils::AddCustomPass<FTosterShaderVS, FTosterShaderPS, FTosterShaderParameters, SVertexPassInfo>(
		GraphBuilder,
		GlobalShaderMap,
		RDG_EVENT_NAME("Drawing the Rain Drop mask"),
		VertexShader,
		GSquareVertexBuffer.VertexBufferRHI,
		GSquareIndexBuffer.IndexBufferRHI,
		GSquareVertexDeclaration.VertexDeclarationRHI,
		VertexPassInfo,
		PixelShader,
		PassParams,
		ViewInfo,
		nullptr,
		nullptr,
		TStaticDepthStencilState<true, CF_GreaterEqual>::GetRHI()
	);
}