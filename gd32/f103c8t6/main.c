#include "all.h"
#include <gd32f10x.h>
#include <gd32f10x_rcu.h>

int main(void) {
	RCU_APB2EN |= (1 << 3);
	
	return 0;
}
