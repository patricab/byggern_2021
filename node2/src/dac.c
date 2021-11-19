#include <stdio.h>
#include <stdarg.h>
#include "dac.h"
#include "sam.h"

void dac_init() {
    REG_PMC_PCER1 |= PMC_PCER1_PID38; // Enable clock
    REG_DACC_MR &= ~DACC_MR_TRGEN_DIS; // External trigger mode disabled. DACC in free running mode
    REG_DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
    REG_DACC_CHER |= DACC_CHER_CH1; // Enable DAC channel 1
}

void dac_conversion(uint16_t value) {
    REG_DACC_CDR = value; // Convert value to analoge signal
}

void dac_status() {
    int channel_status = REG_DACC_CHSR;
}