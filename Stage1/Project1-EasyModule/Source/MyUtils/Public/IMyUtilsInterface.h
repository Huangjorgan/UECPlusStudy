
#pragma once
#include "CoreMinimal.h"

/**
 * MyUtils 功能接口（纯虚类，放在 Public 下）
 */
class  IMyUtilsInterface
{
public:
	//虚析构函数，用于防止多态删除时内存泄漏。
	virtual ~IMyUtilsInterface() = default;

	//定义一个虚函数，供其他模块调用
	virtual void printHello() = 0;
};
