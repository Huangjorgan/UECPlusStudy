#include "SaveSlotManager.h"

// ---------------- 构造函数 ----------------
USaveSlotManager::USaveSlotManager()
{
    PrimaryComponentTick.bCanEverTick = false;

    // 初始化存档槽信息
    SaveSlots.SetNum(MaxSlots);
    for (int32 i = 0; i < MaxSlots; ++i)
    {
        SaveSlots[i].SlotIndex = i;
        SaveSlots[i].bExists = false;
        SaveSlots[i].SaveTime = FDateTime();
        SaveSlots[i].DisplayName = FString::Printf(TEXT("存档%d (空)"), i + 1);
    }
}

// ---------------- BeginPlay ----------------
void USaveSlotManager::BeginPlay()
{
    Super::BeginPlay();

    // 检查现有存档文件并更新状态
    for (int32 i = 0; i < MaxSlots; ++i)
    {
        FString SlotName = GetSlotName(i);
        if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
        {
            USaveGame_Player* Loaded = Cast<USaveGame_Player>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
            if (Loaded)
            {
                SaveSlots[i].bExists = true;
                SaveSlots[i].SaveTime = Loaded->SaveTime;
                SaveSlots[i].DisplayName = FString::Printf(TEXT("存档%d %s"), i + 1, *Loaded->SaveTime.ToString());
            }
        }
    }
}

// ---------------- 获取存档槽文件名 ----------------
FString USaveSlotManager::GetSlotName(int32 SlotIndex) const
{
    return FString::Printf(TEXT("SaveSlot_%d"), SlotIndex);
}

// ---------------- 创建新存档 ----------------
bool USaveSlotManager::CreateNewSaveSlot(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= MaxSlots) return false;

    USaveGame_Player* NewSave = Cast<USaveGame_Player>(UGameplayStatics::CreateSaveGameObject(USaveGame_Player::StaticClass()));
    NewSave->SaveTime = FDateTime::Now();

    FString SlotName = GetSlotName(SlotIndex);
    bool bSuccess = UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);

    if (bSuccess)
    {
        SaveSlots[SlotIndex].bExists = true;
        SaveSlots[SlotIndex].SaveTime = NewSave->SaveTime;
        SaveSlots[SlotIndex].DisplayName = FString::Printf(TEXT("存档%d %s"), SlotIndex + 1, *NewSave->SaveTime.ToString());
    }

    return bSuccess;
}

// ---------------- 保存到存档 ----------------
bool USaveSlotManager::SaveToSlot(int32 SlotIndex, FPlayerSaveData PlayerData)
{
    if (!SaveSlots.IsValidIndex(SlotIndex) || !SaveSlots[SlotIndex].bExists) return false;

    USaveGame_Player* SaveObj = Cast<USaveGame_Player>(UGameplayStatics::CreateSaveGameObject(USaveGame_Player::StaticClass()));
    SaveObj->PlayerData = PlayerData;
    SaveObj->SaveTime = FDateTime::Now();

    FString SlotName = GetSlotName(SlotIndex);
    bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveObj, SlotName, 0);

    if (bSuccess)
        SaveSlots[SlotIndex].SaveTime = SaveObj->SaveTime;

    return bSuccess;
}

// ---------------- 读取存档 ----------------
USaveGame_Player* USaveSlotManager::LoadSaveSlot(int32 SlotIndex)
{
    if (!SaveSlots.IsValidIndex(SlotIndex) || !SaveSlots[SlotIndex].bExists) return nullptr;

    FString SlotName = GetSlotName(SlotIndex);
    return Cast<USaveGame_Player>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

// ---------------- 删除存档 ----------------
bool USaveSlotManager::DeleteSaveSlot(int32 SlotIndex)
{
    if (!SaveSlots.IsValidIndex(SlotIndex) || !SaveSlots[SlotIndex].bExists) return false;

    FString SlotName = GetSlotName(SlotIndex);
    bool bSuccess = UGameplayStatics::DeleteGameInSlot(SlotName, 0);

    if (bSuccess)
    {
        SaveSlots[SlotIndex].bExists = false;
        SaveSlots[SlotIndex].SaveTime = FDateTime();
        SaveSlots[SlotIndex].DisplayName = FString::Printf(TEXT("存档%d (空)"), SlotIndex + 1);
    }

    return bSuccess;
}

// ---------------- 获取存档列表 ----------------
TArray<FSaveSlotInfo> USaveSlotManager::GetSaveSlotList()
{
    return SaveSlots;
}
