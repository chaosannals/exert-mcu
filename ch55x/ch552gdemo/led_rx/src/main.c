#include <8052.h>

#define LED_G P3_4
#define LED_B P3_0
#define LED_R P3_1
#define LED_RX P1_1
#define BUTTON P3_6


inline void set_led(int r, int g, int b) {
	LED_R = r;
	LED_G = g;
	LED_B = b;
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

int rx_state = 0;

inline int is_rx() {
	int v = LED_RX;
	if (rx_state != v) {
		rx_state = v;
		return v == 1;
	}
	return 0;
}

int color[][3] = {
	{ 1, 0, 0, },
	{ 0, 1, 0, },
	{ 0, 0, 1, },
	{ 0, 0, 0, },
};

int color_count = sizeof(color) / sizeof(int) / 3;

inline void delay(short t) {
	while (t--);
}

int main() {
	int i = 0;

	BUTTON = 0;
	LED_RX = 0;
	set_led(0, 0, 0);

	while (1) {
		if (is_press_up()) {
			set_led(color[i][0], color[i][1], color[i][2]);
			i = (i + 1) % color_count;
		}
		if (is_rx()) {
			set_led(color[i][0], color[i][1], color[i][2]);
			i = (i + 1) % color_count;
		}
		//delay(10000000);
	}
	return 0;
}