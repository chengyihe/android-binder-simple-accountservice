LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES += \
	IAccountService.cpp \
	AccountService.cpp

LOCAL_STATIC_LIBRARIES += \
	libbinder \
	libcutils \
	libutils \
	liblog

LOCAL_MODULE := libaccountservice
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := AccountServer.cpp
LOCAL_STATIC_LIBRARIES += \
	libaccountservice \
	libbinder \
	libcutils \
	libutils \
	liblog

LOCAL_MODULE:= accountserver
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := AccountClient.cpp
LOCAL_STATIC_LIBRARIES += \
	libaccountservice \
	libbinder \
	libcutils \
	libutils \
	liblog

LOCAL_MODULE := accountclient
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
