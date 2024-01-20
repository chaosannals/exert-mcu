# esp-idf demo

## 配置 sdkconfig

一些示例的配置修改了但是 build 时被直接清掉。这些值多半是宏定义。没办法的时候只能自己添加头文件手动定义了。


## 术语

- Wi-Fi Easy ConnectTM (DPP) 设备配网协议 (DPP) 或 Easy Connect，是一种安全和标准化的 Wi-Fi 设备配网协议。
- Wi-Fi Protected Setup (WPS)
- NVS （Non-Volatile Storage） 非易失性存储库

参考官方 git 仓库的 examples

vscode 没有创建项目的 UI 。建项目通过复制旧的或者官方示例然后修改。复制的时候要删掉 build 目录，缓存文件和具体目录相关，会影响编译。
