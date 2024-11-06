#pragma once

#include "SceneViewExtension.h"
#include "RainDropShaderBuffers.h"
#include "RainDropOperator.h"

class SCENEVIEWEXTMODULE_API FCustomViewExtension : public FSceneViewExtensionBase {

	FTextureResource* CustomTextureMask;

	int ExecCounter = 0;


	TGlobalResource<FCustomSquareVertexBuffer> GSquareVertexBuffer;
	TGlobalResource<FCustomSquareIndexBuffer> GSquareIndexBuffer;
	TGlobalResource<FCustomSquareVertexDeclaration> GSquareVertexDeclaration;
	SVertexPassInfo VertexPassInfo;

	URainDropOperator* RainDropOperator;

public:
	FCustomViewExtension(const FAutoRegister& AutoRegister,
		FTextureResource* ResourceRTTexture, URainDropOperator* OperatorRef);

	//~ Begin FSceneViewExtensionBase Interface
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override {};
	virtual void PostRenderBasePass_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override {};

	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	//~ End FSceneViewExtensionBase Interface

private:
};
