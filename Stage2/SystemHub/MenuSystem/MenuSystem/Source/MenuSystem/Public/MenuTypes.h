#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "MenuTypes.generated.h"

/**
 * MenuTypes.h
 *
 * 插件的通用类型定义（枚举、结构体）。
 * 所有与菜单描述相关的数据都放在这里，便于序列化与蓝图编辑。
 */

// 菜单类型枚举示例，可以按需扩展
UENUM(BlueprintType)
enum class EMenuType : uint8
{
    Main     UMETA(DisplayName="Main Menu"),
    Pause    UMETA(DisplayName="Pause Menu"),
    Options  UMETA(DisplayName="Options Menu"),
    Custom   UMETA(DisplayName="Custom Menu")
};

// 菜单描述：用于在子系统中注册菜单 ID 与对应的 Widget Class
USTRUCT(BlueprintType)
struct FMenuDescriptor
{
    GENERATED_BODY()

    // 菜单 ID（可用 Name/枚举或字符串表示）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
    FName MenuId = NAME_None;

    // 菜单类型（供逻辑分组/过滤用，可选）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
    EMenuType MenuType = EMenuType::Custom;

    // 对应的 Widget Class（必须继承自 UMenuBaseWidget）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menu")
    TSubclassOf<UUserWidget> WidgetClass = nullptr;
};
