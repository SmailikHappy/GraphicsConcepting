// SceneViewExtModule/Public/SceneViewExtModule.h

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSceneViewExtModule : public IModuleInterface {
public:
	virtual void StartupModule() override;
};
