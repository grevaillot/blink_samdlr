#include <libopencm3/sam/memorymap.h>
#include <libopencm3/sam/gpio.h>
#include <libopencm3/sam/nvmctrl.h>
#include <libopencm3/sam/sysctrl.h>
#include <libopencm3/sam/pm.h>
#include <libopencm3/sam/gclk.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

// led is on PA09 on R34 xplaind

// led is on PA27 and PB03 on samd21

int cnt = 0;
void sys_tick_handler(void)
{
	if (cnt++ == 1000) {
		gpio_toggle(PORTA, GPIO27 | GPIO17);
		gpio_toggle(PORTB, GPIO3);
		cnt = 0;
	}
}

int main(void)
{
	gpio_mode_setup(PORTA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO17 | GPIO27);
	gpio_mode_setup(PORTB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);
	gpio_set(PORTA, GPIO27 | GPIO17);

	sysctrl_osc_on(OSC_OSC8M);
	sysctrl_wait_for_osc_ready(OSC_OSC8M);
	sysctrl_set_osc8m_prescaler(SYSCTRL_OSC8M_PRESC_NODIV);

	pm_set_cpu_div(PM_CPUSEL_CPUDIV_NODIV);
	pm_set_apba_div(PM_CPUSEL_APBADIV_NODIV);
	pm_set_apbb_div(PM_CPUSEL_APBBDIV_NODIV);
	pm_set_apbc_div(PM_CPUSEL_APBCDIV_NODIV);

	pm_periph_enable_clock(PM_PORT);
	pm_periph_enable_clock(PM_GCLK);

	gclk_reset();

#if 0
	sysctrl_set_xosc_mode(SYSCTRL_XOSC_XTALEN, SYSCTRL_XOSC_AMPGC, SYSCTRL_XOSC_STARTUP_4096CYC);
	sysctrl_osc_on(OSC_XOSC);
	sysctrl_wait_for_osc_ready(OSC_XOSC);
#endif

#if 0
	sysctrl_set_xosc32k_mode(true, false, SYSCTRL_XOSC32K_STARTUP_2048CYC);
	sysctrl_osc_on(OSC_XOSC32K);
	sysctrl_wait_for_osc_ready(OSC_XOSC32K);
#endif

	systick_set_frequency(1000, 8000000);
	systick_interrupt_enable();
	systick_counter_enable();

	nvm_set_ws(2);
	// switch to dfll48
	// output glck on pa ?
	// enable clock for x periph ?

	/* test me 
	gpio_set_pmux(PORTA, GPIO_PMUX_FUNCTION_A, GPIO9);
	gpio_mode_setup(PORTA, GPIO_MODE_PMUX, GPIO_PUPD_NONE, GPIO9);
	*/

	while (1);

	return 0;
}
