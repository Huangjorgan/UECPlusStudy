#include "MyUtilsLibrary.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogMyUtils);

void MyUtilsLibrary::printHello() {
    UE_LOG(LogMyUtils, Warning, TEXT(" [MyUtils] Hello From Util via Interface! "));
}

//  模块实现
IMPLEMENT_MODULE(FMyUtilsModule, MyUtils)

void FMyUtilsModule::StartupModule()
{
    UE_LOG(LogMyUtils, Warning, TEXT("[MyUtils] MyUtils module starting..."));

    //在模块启动时创建具体实现（延迟构造避免静态初始化问题）
    Impl = MakeUnique<MyUtilsLibrary>();

    //额外的安全检查
    if (Impl) {
        UE_LOG(LogMyUtils, Warning, TEXT("[MyUtils] Implementation created."));
    }
}

void FMyUtilsModule::ShutdownModule()
{
    UE_LOG(LogMyUtils, Warning, TEXT("[MyUtils] MyUtils module shutdown... "));
    Impl.Reset();
}
