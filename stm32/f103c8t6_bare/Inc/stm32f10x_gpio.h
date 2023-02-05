#ifndef STM32F10X_GPIO_H_
#define STM32F10X_GPIO_H_

#include "stm32f10x_periph.h"

typedef struct {
	volatile uint64_t cr;
	volatile uint32_t idr;
	volatile uint32_t odr;
	volatile uint32_t bsrr;
	volatile uint32_t brr;
	volatile uint32_t lckr;
} gpio_t;

gpio_t *const GPIOA = (gpio_t *)(APB2_BASE + 0x0800);
gpio_t *const GPIOB = (gpio_t *)(APB2_BASE + 0x0C00);
gpio_t *const GPIOC = (gpio_t *)(APB2_BASE + 0x1000);

// CNFx [1:0]
typedef enum {
	GPIO_MODE_IN_AC = 0b0000, // 模拟输入
	GPIO_MODE_IN_FLOATING = 0b0100, // 浮空输入
	GPIO_MODE_IN_PULL = 0b1000, // 下拉输入/上拉输入
	GPIO_MODE_OUT_PUSH_PULL = 0b0000, // 推挽输出
	GPIO_MODE_OUT_OPEN_DRAIN = 0b0100, // 开漏输出
	GPIO_MODE_OUT_PUSH_PULL_AF = 0b1000, // 复用推挽输出
	GPIO_MODE_OUT_OPEN_DRAIN_AF = 0xb1100, // 复用开漏输出
} gpio_mode_t;

// MODEx [1:0]
typedef enum {
	GPIO_SPEED_IN = 0b0000, // 输入模式
	GPIO_SPEED_OUT_10MHZ = 0b0001, // 输出 10MHz
	GPIO_SPEED_OUT_2MHZ = 0b0010, // 输出 2MHz
	GPIO_SPEED_OUT_50MHZ = 0b0011, // 输出 50MHz
}gpio_speed_t;

const uint64_t GPIO_CONF_MASK = 0xF;

void gpio_init(
		gpio_t *gpio,
		uint8_t pin,
		gpio_mode_t mode,
		gpio_speed_t speed) {
	uint8_t step = pin << 2;
	uint64_t cnf = mode | speed;
	uint64_t save = gpio->cr & ~(GPIO_CONF_MASK << step);
	gpio->cr = save | (cnf << step);
}

void gpio_pin_reset(
		gpio_t *gpio,
		uint8_t pin) {
	//gpio->odr &= ~(1 << pin);
	gpio->brr = 1 << pin;
}
void gpio_pin_set(gpio_t *gpio, uint8_t pin) {
	//gpio->odr |= (1 << pin);
	gpio->bsrr = 1 << pin;
}

#endif /* STM32F10X_GPIO_H_ */
