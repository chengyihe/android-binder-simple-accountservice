#define LOG_TAG "AccountService"

#include <stdint.h>
#include <sys/types.h>

#include <utils/String16.h>
#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "IAccountService.h"

namespace android {

class BpAccountService: public BpInterface<IAccountService>
{
public:
    BpAccountService(const sp<IBinder>& impl)
        : BpInterface<IAccountService>(impl)
    {
    }

    virtual int addAccount(const String16& name)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAccountService::getInterfaceDescriptor());
        data.writeString16(name);
        remote()->transact(BnAccountService::TRANSACTION_ADD_ACCOUNT, data, &reply);

        return reply.readInt32();
    }

    virtual int removeAccount(const String16& name)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IAccountService::getInterfaceDescriptor());
        data.writeString16(name);
        remote()->transact(BnAccountService::TRANSACTION_REMOVE_ACCOUNT, data, &reply);

        return reply.readInt32();
    }

    virtual Vector<String16> listAccounts()
    {
        Parcel data, reply;
        uint32_t n;
        Vector<String16> accounts;

        data.writeInterfaceToken(IAccountService::getInterfaceDescriptor());
        remote()->transact(BnAccountService::TRANSACTION_LIST_ACCOUNTS, data, &reply);
        n = reply.readInt32();

        while (n--)
            accounts.push(reply.readString16());

        return accounts;
    }
};

IMPLEMENT_META_INTERFACE(AccountService, "chengyihe.test.IAccountService");

status_t BnAccountService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case TRANSACTION_ADD_ACCOUNT: {
            CHECK_INTERFACE(IAccountService, data, reply);
            String16 name = data.readString16();
            int n = addAccount(name);
            reply->writeInt32(n);
            return NO_ERROR;
        }
        case TRANSACTION_REMOVE_ACCOUNT: {
            CHECK_INTERFACE(IAccountService, data, reply);
            String16 name = data.readString16();
            int n = removeAccount(name);
            reply->writeInt32(n);
            return NO_ERROR;
        }
        case TRANSACTION_LIST_ACCOUNTS: {
            CHECK_INTERFACE(IAccountService, data, reply);
            Vector<String16> accounts = listAccounts();
            reply->writeInt32(accounts.size());
            for (int i = 0; i < accounts.size(); i++)
                reply->writeString16(accounts.itemAt(i));
            return NO_ERROR;
        }
        default: {
            return BBinder::onTransact(code, data, reply, flags);
        }
    }
    // should be unreachable
    return NO_ERROR;
}

}; // namespace android
