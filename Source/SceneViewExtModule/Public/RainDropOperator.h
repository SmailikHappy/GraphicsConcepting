#pragma once

#include "CoreMinimal.h"
#include "CoreUObjectClasses.h"
#include "RainDropOperator.generated.h"

UCLASS(BlueprintType)
class SCENEVIEWEXTMODULE_API URainDropOperator : public UObject
{
	GENERATED_BODY()

private:
	TSharedPtr<class FCustomViewExtension, ESPMode::ThreadSafe> CustomViewExtension;

public:
	
	UFUNCTION(BlueprintCallable, Category = "Rain drop")
	bool CreateRainDropExtension(UTextureRenderTarget2D* RainDropMask);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RainDrop)
	TArray<FVector3f> PositionArray;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RainDrop)
	TArray<FVector3f> NormalArray;
		
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RainDrop)
	TArray<float>     ScaleArray;
	
	//
	//UFUNCTION(BlueprintCallable, Category = "Rain drop")
	//void GetRainDropPositionArray(TSharedRef<TArray<FVector3f>>& RainPositions) { RainPositions = MakeShared<TArray<FVector3f>>(RainDropPositionArray); }
	//
	//
	//UFUNCTION(BlueprintCallable, Category = "Rain drop")
	//void GetRainDropNormalArray(TSharedRef<TArray<FVector3f>>& RainNormals) { RainNormals = MakeShared<TArray<FVector3f>>(RainDropNormalArray); }
	//
	//
	//UFUNCTION(BlueprintCallable, Category = "Rain drop")
	//void GetRainDropScaleArray(TSharedRef<TArray<float>>& RainScales) { RainScales = MakeShared<TArray<float>>(RainDropScaleArray); }
};