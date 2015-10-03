#define LOG_TAG "AccountClient"

#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include "IAccountService.h"

using namespace android;

void showAccounts(const Vector<String16>& accounts)
{
    LOGD("There are %d accounts", accounts.size());

    for (size_t i = 0; i < accounts.size(); i++)
        LOGD("account %d is %s", i + 1, String8(accounts[i]).string());
}

int main()
{
    sp<IAccountService> service = interface_cast<IAccountService>(defaultServiceManager()->getService(String16("simple.account")));

    service->addAccount(String16("john"));
    showAccounts(service->listAccounts());

    service->addAccount(String16("tom"));
    showAccounts(service->listAccounts());

    service->removeAccount(String16("john"));
    showAccounts(service->listAccounts());

    return 0;
}
