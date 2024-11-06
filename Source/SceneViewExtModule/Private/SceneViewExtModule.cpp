// SceneViewExtModule/Private/SceneViewExtModule.cpp

#include "SceneViewExtModule.h"

void FSceneViewExtModule::StartupModule() {
	FString BaseDir = FPaths::Combine(FPaths::GameSourceDir(), TEXT("SceneViewExtModule"));
	FString ModuleShaderDir = FPaths::Combine(BaseDir, TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/SceneViewExtModule"), ModuleShaderDir);
	UE_LOG(LogInit, Log, TEXT("SceneViewExtModule has been loaded"));
}

IMPLEMENT_MODULE(FSceneViewExtModule, SceneViewExtModule)
