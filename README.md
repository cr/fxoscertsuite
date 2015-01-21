# FxOSCertSuite

Prototyping code for FxOS Ceritification Suite experiments.

## Prerequisites

* Android SDK
 * ensure that adb works
* Android NDK
 * ensure that you can run ndk-build

## Example
```
$ ndk-build
$ adb push obj/local/armeabi/lslR /data/local/tmp/
$ adb shell /data/local/tmp/lslR
```
