#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSlotManager.generated.h"

//玩家存档数据结构
USTRUCT(BlueprintType)
struct FPlayerSaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FVector PlayerLocation;

    UPROPERTY(BlueprintReadWrite)
    FRotator PlayerRotation;

    UPROPERTY(BlueprintReadWrite)
    int32 Health;

    // 如果你用二维数组存储背包，可以先序列化成一维数组
    //UPROPERTY(BlueprintReadWrite)
    //TArray<int32> Inventory;
};


// 存档槽信息，用于 UI 显示
USTRUCT(BlueprintType)
struct FSaveSlotInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 SlotIndex;

    UPROPERTY(BlueprintReadWrite)
    bool bExists;

    UPROPERTY(BlueprintReadWrite)
    FDateTime SaveTime;

    UPROPERTY(BlueprintReadWrite)
    FString DisplayName; // UI上显示用，如 "存档1 2025/11/30"
};

// 玩家存档对象
UCLASS()
class USaveGame_Player : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FPlayerSaveData PlayerData;

    UPROPERTY(BlueprintReadWrite)
    FDateTime SaveTime;
};

// 存档槽管理器
UCLASS()
class WORLDCORE_API USaveSlotManager : public UActorComponent
{
	GENERATED_BODY()

public:
    // 构造函数
    USaveSlotManager();

protected:
    virtual void BeginPlay() override;

public:
    // 存档槽总数，可在蓝图中修改
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxSlots = 5;

    // 存档槽信息数组
    UPROPERTY(BlueprintReadWrite)
    TArray<FSaveSlotInfo> SaveSlots;

    // ---------------- 核心功能函数 ----------------

    // 创建新存档
    UFUNCTION(BlueprintCallable)
    bool CreateNewSaveSlot(int32 SlotIndex);

    // 保存当前游戏状态到存档
    UFUNCTION(BlueprintCallable)
    bool SaveToSlot(int32 SlotIndex, FPlayerSaveData PlayerData);

    // 读取存档
    UFUNCTION(BlueprintCallable)
    USaveGame_Player* LoadSaveSlot(int32 SlotIndex);

    // 删除存档
    UFUNCTION(BlueprintCallable)
    bool DeleteSaveSlot(int32 SlotIndex);

    // 获取存档列表
    UFUNCTION(BlueprintCallable)
    TArray<FSaveSlotInfo> GetSaveSlotList();

private:
    // 获取存档槽的文件名
    FString GetSlotName(int32 SlotIndex) const;	
};
