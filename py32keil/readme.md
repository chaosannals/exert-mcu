# 

定义这个宏选型号，官方库连这个都不给自动设置就很扯淡。这种东西选芯片的时候就应该自动设置，而不是选了芯片型号，还要自己设置宏，这样要是设置不匹配的宏，这选芯片型号还有什么意义？

PY32F002Ax5 

根据项目启用的功能外设，要配置宏，一些宏也是必须的。
注：通过报错来确定你要设置哪些宏。

USE_HAL_TIM_REGISTER_CALLBACKS

USE_HAL_UART_REGISTER_CALLBACKS

USE_HAL_I2C_REGISTER_CALLBACKS