# stm32 rs

## 安装工具

```bash
# 安装 代码生成器 用来生成项目
cargo install cargo-generate

# 安装 烧录 调试 运行 工具
cargo install probe-rs-tools 
# 【旧】下面这个提示这个库不是工具，要用 cargo add 而不是 cargo Install，因为拆出来上面这个库了。
cargo install probe-rs --features cli

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

## 编译运行

```bash
# 
cargo build --release


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



### [openocd](https://github.com/openocd-org/openocd)

github 上可以下载 windows 版本.
