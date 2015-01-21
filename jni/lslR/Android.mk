# http://stackoverflow.com/questions/7651608/simplifying-an-android-mk-file-which-build-multiple-executables

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := lslR
LOCAL_SRC_FILES := lslR.c
include $(BUILD_EXECUTABLE)

