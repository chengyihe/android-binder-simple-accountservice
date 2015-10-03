#define LOG_TAG "AccountService"

#include <sys/wait.h>
#include <unistd.h>

#include <cutils/log.h>
#include <binder/BinderService.h>

#include "AccountService.h"

namespace android {

AccountService::AccountService()
{
}

AccountService::~AccountService()
{
}

int AccountService::addAccount(const String16& name)
{
    for (size_t i = 0; i < mAccounts.size(); i++) {
        if (mAccounts[i] == name)
            return -1;
    }

    mAccounts.push(name);

    return 0;
}

int AccountService::removeAccount(const String16& name)
{
    int index = -1;

    for (size_t i = 0; i < mAccounts.size(); i++) {
        if (mAccounts.itemAt(i) == name) {
            index = i;
            break;
        }
    }

    if (index < 0)
        return -1;

    mAccounts.removeAt(index);

    return 0;
}

Vector<String16> AccountService::listAccounts()
{
    return mAccounts;
}

}; // namespace android
