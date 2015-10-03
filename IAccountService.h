#ifndef IHELLOSERVICE_H
#define IHELLOSERVICE_H

#include <stdint.h>
#include <sys/types.h>

#include <utils/RefBase.h>
#include <utils/Errors.h>

#include <binder/IInterface.h>

namespace android {

class IAccountService: public IInterface {
public:
    DECLARE_META_INTERFACE(AccountService);

    virtual int addAccount(const String16&) = 0;
    virtual int removeAccount(const String16&) = 0;
    virtual Vector<String16> listAccounts() = 0;
};

class BnAccountService: public BnInterface<IAccountService> {
public:
    enum {
        TRANSACTION_ADD_ACCOUNT = IBinder::FIRST_CALL_TRANSACTION,
        TRANSACTION_REMOVE_ACCOUNT,
        TRANSACTION_LIST_ACCOUNTS,
    };

    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flag = 0);
};

}; // namespace android

#endif // IHELLOSERVICE_H
