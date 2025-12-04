#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuTestActor.generated.h"

UCLASS()
class MENUSYSTEM_API AMenuTestActor : public AActor
{
    GENERATED_BODY()

public:
    AMenuTestActor();

protected:
    virtual void BeginPlay() override;

public:
    // 是否在 BeginPlay 时自动打开测试菜单
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MenuTest")
    bool bAutoOpenMenu = true;
};