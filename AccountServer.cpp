#define LOG_TAG "AccountServer"

#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include "AccountService.h"

using namespace android;

int main()
{
    LOGD("AccountServer is starting");

    sp<ProcessState> proc(ProcessState::self());
    ProcessState::self()->startThreadPool();

    defaultServiceManager()->addService(String16("simple.account"), new AccountService);

    LOGD("Successfully register service: simple.account");
    LOGD("Ready to joinThreadPool");

    IPCThreadState::self()->joinThreadPool();

    return 0;
}
