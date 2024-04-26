Arduino 要使用 VScode 需要安装  [Arduino Cli](https://arduino.github.io/arduino-cli/) 这个工具。

如果安装过 ArduinoIDE 的话，可能这个工具已经被安装了。不用手动去下载。一般在 C 盘。但是需要把这个工具的安装目录添加到 Path 里面才能使用。
这里不使用 ArduinoIDE 而使用 VsCode 装 Arduino 插件的原因可能是 接手的项目使用这种方式，也可能是 Vscode 使用更多的插件。

通过下面的命令可以看到 arduino 对 vscode 的支持

```bash
# code 就是指的 vscode 吧。
arduino-cli help code

# 查看库列表
arduino-cli lib list
```

然后在 VsCode 里面安装 Arduino 插件，再打开插件配置，把 ArduinoCli 的路径配置上。


一切安装完成后，重启启动 VsCode.

Vscode 底部会有很多选项。可以选择 板子类型，串口号之类的。

选板子的选项会让你装不同板子的管理器。如果开发 ESP32 就安装 ESP32, 如果是其他的就装其他的。但是都是必须是 Arduino 兼容的芯片，这也就是为什么 Arduino 只适合发烧友，而不适合工业。因为工业上用的很多便宜国产芯片，根本没有 arduino 支持。


下载好慢。

安装 板子管理器后（例如 ESP）插上板子，可以自动识别型号。

[Arduino 官方示例](https://github.com/arduino/arduino-examples)


默认配置使得   xxxx.ino  的名字必须是项目目录名，比如 ino 的目录叫 xxxx ，名字就要叫 xxxx.ino

.vscode 文件下面的 c_cpp_properties.json 和 arduino.json 是配置文件，有硬件和编译器配置信息。由插件 UI 界面设配后生成。

## 包管理 Library Manager
通过 VsCode 的命令面板（Ctrl+Shift+P），搜索 Arduino 可以看到有一个 LibraryManager 的命令，执行它可以打开包管理面板。
居然不做个 UI 按钮来打开这个面板。。。。

这些库管理是全局的。只要安装一次，所有项目都可用。

[社区库仓库](https://github.com/arduino-libraries)


## ESP

### Wifi 智能连接

通过安装 乐鑫的APP 广播 SSDI 和 密码给设备。
[GitHub仓库](https://github.com/EspressifApp/EsptouchForAndroid)

安装 APP 后，启动配网。单片机使用智能配网模式去配网。
