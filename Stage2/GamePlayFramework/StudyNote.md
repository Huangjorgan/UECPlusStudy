# 学习笔记 GamePlayFramework 2025/11/24


## 日计划工作区
12/2 完成存档系统的底层构建 确认第一个游戏demo的题材与内容架构


## 项目目标
一个完整的模板工程，包括：
*基础 Gameplay 框架*
GameInstance（全局）
GameMode（流程控制）
GameState（同步关键数据）
PlayerController（输入、交互核心）
PlayerState（属性模板）
Character 与 AIController（可扩展的 Pawn）

*UI 框架*
起始菜单
暂停菜单
通用 WidgetBase 类

*系统模块*
输入系统 InputMapping
Gameplay 事件系统
存档系统（SaveGame）
武器系统

## 核心Core
MyGameInstance
MyGameMode
MyStartGameMode
MyHUD
MyPlayerController
MyPlayerState

MyGameMode与MyStartGameMode共同使用MyPlayerController。
在MyPlayerController中会进行GameMode判断防止某些绑定操作被不合理实施。


## 武器系统
**C++类**
1.UWeaponComp 武器组件
    作为武器系统与character链接的桥梁，绑定在character中，在组件内调用开火停火函数等等。
    核心函数：SpawnAndEquipDefaultWeapon()。设置武器并装备到角色的武器插槽上。
2.AWeaponBase 武器基类
    用于武器类的默认属性与函数，包括：
        武器名称，武器伤害，武器射程，武器射速，武器弹夹容量，当前弹药数量，是否开火中。
        开火函数，停止开火函数，装弹函数，单次开火逻辑函数。
3.AWeapon 武器实现类
    用于实现一种具体武器
**设计原则**
依赖倒置原则（DIP）
上层模块（WeaponComp）依赖抽象（AWeaponBase），而不是具体实现（AWeapon）。

## 伤害系统与属性系统
**核心** AMyPlayerState
*设计原则* ：属性存放在 PlayerState（因为 PlayerState 在 Character 被销毁时会保留）
负责保存玩家的核心属性（Health, Stamina）并提供伤害入口 ApplyDamage。
通过事件委托广播受到伤害或死亡。 在Character中接收广播来进行受击处理和死亡处理。
*注意* ：使用一个FinishDeath来延迟销毁角色

## 存档系统
**结构体**
FPlayerSaveData 玩家存档
FSaveSlotInfo 存档槽信息

**C++类**
USaveGame_Player 玩家存档对象
USaveSlotManager 存档槽管理器

### 核心功能函数
CreateNewSaveSlot 创建新存档
SaveToSlot 保存游戏存档
LoadSaveSlot 读取存档
DeleteSaveSlot 删除存档
GetSaveSlotList 获取存档列表

