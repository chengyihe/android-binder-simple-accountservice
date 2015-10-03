#ifndef HELLOSERVICE_H
#define HELLOSERVICE_H

#include <stdint.h>
#include <sys/types.h>

#include <utils/RefBase.h>
#include <utils/Errors.h>

#include <binder/IInterface.h>

#include "IAccountService.h"

namespace android {

class AccountService: public BnAccountService
{
public:
    AccountService();
    ~AccountService();
    virtual int addAccount(const String16&);
    virtual int removeAccount(const String16&);
    virtual Vector<String16> listAccounts();
private:
    Vector<String16> mAccounts;
};

}; // namespace android

#endif // HELLOSERVICE_H
