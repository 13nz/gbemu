#pragma once

#incude <common.h>

// 8 bit data bus
// 16 bit address bus

u8 bus_read(u16 address); // pass in 16bit address > get 8bit value back
void bus_write(u16 address, u8 value); //