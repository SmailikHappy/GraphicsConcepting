/*========================================================
	CustomShaderUtils.h: Utilities for custom shaders.

	These functions has been made using the same coding
	style as `PixelShaderUtils.h`.
========================================================*/

#pragma once

class FPointerTableBase;
class FRDGBuilder;


struct FCustomShaderUtils
{
	/** Dispatch a custom vertex and pixel shader to rhi command list with its parameters. */
	template<typename TVertexShaderClass, typename TPixelShaderClass, typename TPassParameters, typename TVertexPassInfo>
	static inline void DrawCustomVertexPixelShader(
		FRHICommandList& RHICmdList,
		const FGlobalShaderMap* GlobalShaderMap,
		const TShaderRef<TVertexShaderClass>& VertexShader,
		FBufferRHIRef VertexBufferRHI,
		FBufferRHIRef IndexBufferRHI,
		FVertexDeclarationRHIRef VertexDeclarationRHIRef,
		const TVertexPassInfo VertexPassInfo,
		const TShaderRef<TPixelShaderClass>& PixelShader,
		typename TPassParameters* Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState = nullptr,
		FRHIRasterizerState* RasterizerState = nullptr,
		FRHIDepthStencilState* DepthStencilState = nullptr,
		uint32 StencilRef = 0)
	{
		RHICmdList.SetViewport((float)Viewport.Min.X, (float)Viewport.Min.Y, 0.0f, (float)Viewport.Max.X, (float)Viewport.Max.Y, 1.0f);

		FGraphicsPipelineStateInitializer GraphicsPSOInit;

		RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
		GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
		GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
		GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();

		GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDeclarationRHIRef;
		GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
		GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
		GraphicsPSOInit.PrimitiveType = PT_TriangleList;

		GraphicsPSOInit.BlendState = BlendState ? BlendState : GraphicsPSOInit.BlendState;
		GraphicsPSOInit.RasterizerState = RasterizerState ? RasterizerState : GraphicsPSOInit.RasterizerState;
		GraphicsPSOInit.DepthStencilState = DepthStencilState ? DepthStencilState : GraphicsPSOInit.DepthStencilState;

		SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, StencilRef);

		SetShaderParameters(RHICmdList, VertexShader, VertexShader.GetVertexShader(), Parameters->VS);
		SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), Parameters->PS);

		RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);

		RHICmdList.DrawIndexedPrimitive(
			IndexBufferRHI,
			VertexPassInfo.BaseVertexIndex,
			VertexPassInfo.MinIndex,
			VertexPassInfo.NumVertices,
			VertexPassInfo.StartIndex,
			VertexPassInfo.NumPrimitives,
			VertexPassInfo.NumInstances);
	}

	/** Dispatch a vertex and pixel shader to render graph builder with its parameters. */
	template<typename TVertexShaderClass, typename TPixelShaderClass, typename TPassParameters, typename TVertexPassInfo>
	static inline void AddCustomPass(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* GlobalShaderMap,
		FRDGEventName&& PassName,
		const TShaderRef<TVertexShaderClass>& VertexShader,
		FBufferRHIRef VertexBufferRHI,
		FBufferRHIRef IndexBufferRHI,
		FVertexDeclarationRHIRef VertexDeclarationRHIRef,
		const TVertexPassInfo VertexPassInfo,
		const TShaderRef<TPixelShaderClass>& PixelShader,
		typename TPassParameters* Parameters,
		const FIntRect& Viewport,
		FRHIBlendState* BlendState = nullptr,
		FRHIRasterizerState* RasterizerState = nullptr,
		FRHIDepthStencilState* DepthStencilState = nullptr,
		uint32 StencilRef = 0)
	{
		check(PixelShader.IsValid());
		check(VertexShader.IsValid());
		ClearUnusedGraphResources(VertexShader, &Parameters->VS);
		ClearUnusedGraphResources(PixelShader, &Parameters->PS);

		GraphBuilder.AddPass(
			Forward<FRDGEventName>(PassName),
			Parameters,
			ERDGPassFlags::Raster,
			[Parameters, GlobalShaderMap, VertexShader, VertexBufferRHI, IndexBufferRHI, VertexDeclarationRHIRef, VertexPassInfo, PixelShader, Viewport, BlendState, RasterizerState, DepthStencilState, StencilRef](FRHICommandList& RHICmdList)
			{
				FCustomShaderUtils::DrawCustomVertexPixelShader<TVertexShaderClass, TPixelShaderClass, TPassParameters, TVertexPassInfo>(RHICmdList, GlobalShaderMap, VertexShader, VertexBufferRHI, IndexBufferRHI, VertexDeclarationRHIRef, VertexPassInfo, PixelShader, Parameters, Viewport,
					BlendState, RasterizerState, DepthStencilState, StencilRef);
			});
	}
};
