#include "RainDropOperator.h"

#include "Engine/TextureRenderTarget2D.h"
#include "CustomViewExtension.h"



bool URainDropOperator::CreateRainDropExtension(UTextureRenderTarget2D* RainDropMask)
{
	if (!RainDropMask)
	{
		UE_LOG(LogTemp, Error, TEXT("Render target is not assigned"));
		return false;
	}

	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get a game instance"));
		return false;
	}

	UGameViewportClient* GameViewportClient = GameInstance->GetGameViewportClient();

	if (!GameViewportClient)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get a game viewport from client"));
		return false;
	}

	FViewport* Viewport = GameViewportClient->Viewport;

	if (!Viewport)
	{
		UE_LOG(LogTemp, Error, TEXT("Viewport is a nullptr??"));
		return false;
	}

	RainDropMask->UpdateResource();

	FTextureResource* TextureResource = RainDropMask->GetResource();

	if (!TextureResource)
	{
		UE_LOG(LogTemp, Error, TEXT("The texture resource is nullptr"));
		return false;
	}

	CustomViewExtension = FSceneViewExtensions::NewExtension<FCustomViewExtension>(
		TextureResource,
		this
	);


	UE_LOG(LogTemp, Display, TEXT("The scene view extension has been successfully created and render-terget's resources delivered."));
	return true;
}