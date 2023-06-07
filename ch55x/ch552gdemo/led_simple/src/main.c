#include <8052.h>

#define LED_B P1_1
#define LED_R P3_3
#define LED_G P3_4
#define BUTTON P3_1
#define LED_TX P3_0

int color[][3] = {
	{ 1, 0, 0, },
	{ 0, 1, 0, },
	{ 0, 0, 0, },
	{ 0, 0, 0, },
};

int color_count = sizeof(color) / sizeof(int) / 3;

inline void set_led(int r, int g, int b) {
	LED_R = r;
	LED_G = g;
	LED_B = b;
}

inline void delay(int t) {
	while (t--);
}

int button_state = 0;

inline int is_press_down() {
	int v = BUTTON;
	if (button_state != v) {
		button_state = v;
		return v == 1;
	}
	return 0;
}

inline int is_press_up() {
	int v = BUTTON;
	if (button_state != v) {
		button_state = v;
		return v == 0;
	}
	return 0;
}

void main() {
	int i = 0;

	BUTTON = 0;
	LED_TX = 1;
	set_led(0, 0, 0);

	while (1) {
		if (is_press_up()) {
			set_led(color[i][0], color[i][1], color[i][2]);
			i = (i + 1) % color_count;
			LED_TX = 1;
			delay(10000);
			LED_TX = 0;
		}
		//delay(10000000);
	}
}