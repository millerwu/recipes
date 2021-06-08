This is the testbed for ION buffer allocing and sharing which only support the kernel version higher than 4.19.

The base code is from [AOSP](https://android.googlesource.com/platform/system/memory/libion/+/refs/heads/master).  The base testbed only support the kernel version less than 4.14, since the [Ion ABI changes](https://source.android.google.cn/devices/architecture/kernel/ion_abi_changes).

