#include <stdio.h>
#include <stdarg.h>
#include "dac.h"
#include "sam.h"

void dac_init() {
    REG_DACC_CR |= DACC_CR_SWRST; // Resets the DACC simulating a hardware reset
    REG_DACC_WPMR = DACC_WPMR_WPKEY(0x444143); // WPKEY = "DAC"
    REG_DACC_WPMR &= ~DACC_WPMR_WPEN; // Disables the Write Protect
    REG_DACC_MR |= DACC_MR_TRGEN_DIS; // External trigger mode disabled. DACC in free running mode
    REG_DACC_MR |= DACC_MR_TAG_EN; // Tag selection mode enabled
    REG_DACC_CHER |= DACC_CHER_CH1; // Enable DAC channel 1
}

void dac_conversion(int value) {
    REG_DACC_CDR = DACC_CDR_DATA(value); // Convert value to analoge signal
}