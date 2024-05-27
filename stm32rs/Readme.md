# stm32 rs

```bash
# 安装 烧录 调试 运行 工具
cargo install probe-rs-tools

# 安装 编译器目标 cortex m0 m0+ m1 系列
rustup target add thumbv6m-none-eabi

# 安装 编译器目标 cortex m3 系列
rustup target add thumbv7m-none-eabi

# 安装 编译器目标 cortex m4 m7 系列 无硬件浮点
rustup target add thumbv7em-none-eabi

# 安装 编译器目标 cortex m4 m7 系列 有硬件浮点
rustup target add thumbv7em-none-eabihf

# 安装 编译器目标 cortex m23 系列
rustup target add thumbv8m.base-none-eabi

# 安装 编译器目标 cortex m33 m35p 系列 无硬件浮点
rustup target add thumbv8m.main-none-eabi

# 安装 编译器目标 cortex m33f m35pf 系列 有硬件浮点
rustup target add thumbv8m.main-none-eabihf
```

```bash
# 编译
cargo +nightly build -Zbuild-std --target thumbv7em-none-eabihf -p f401rct6
cargo +nightly build -Zbuild-std --target thumbv7em-none-eabihf -p f401rct6 --release

# 编译
cargo +nightly build -Zbuild-std --target thumbv7em-none-eabihf -p f401rct6_rtic_usb_cdc_echo
cargo +nightly build -Zbuild-std --target thumbv7em-none-eabihf -p f401rct6_rtic_usb_cdc_echo --release
```

## probe-rs

```bash
# 列举芯片
probe-rs chip list

# 烧录
cargo flash --release

# 运行
cargo run --release

# 
cargo embed --release
```


## [openocd](https://github.com/openocd-org/openocd)

github 上可以下载 windows 版本.
