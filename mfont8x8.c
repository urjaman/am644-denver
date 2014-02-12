#include <stdint.h>
#include <avr/pgmspace.h>

const uint8_t PROGMEM st7565_font[224][8] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00 },
	{ 0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00 },
	{ 0x00, 0x00, 0x3A, 0x2A, 0x7F, 0x2A, 0x2E, 0x00 },
	{ 0x00, 0x62, 0x64, 0x08, 0x10, 0x26, 0x46, 0x00 },
	{ 0x00, 0x04, 0x2A, 0x52, 0x2A, 0x04, 0x0A, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x00, 0x00 },
	{ 0x00, 0x00, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 },
	{ 0x00, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
	{ 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 },
	{ 0x00, 0x3C, 0x46, 0x4A, 0x52, 0x62, 0x3C, 0x00 },
	{ 0x00, 0x00, 0x22, 0x42, 0x7E, 0x02, 0x02, 0x00 },
	{ 0x00, 0x26, 0x4A, 0x4A, 0x4A, 0x4A, 0x32, 0x00 },
	{ 0x00, 0x24, 0x42, 0x42, 0x52, 0x52, 0x2C, 0x00 },
	{ 0x00, 0x0C, 0x14, 0x24, 0x7E, 0x04, 0x04, 0x00 },
	{ 0x00, 0x74, 0x52, 0x52, 0x52, 0x52, 0x4C, 0x00 },
	{ 0x00, 0x3C, 0x52, 0x52, 0x52, 0x52, 0x0C, 0x00 },
	{ 0x00, 0x40, 0x40, 0x46, 0x48, 0x50, 0x60, 0x00 },
	{ 0x00, 0x2C, 0x52, 0x52, 0x52, 0x52, 0x2C, 0x00 },
	{ 0x00, 0x30, 0x4A, 0x4A, 0x4A, 0x4A, 0x3C, 0x00 },
	{ 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x01, 0x26, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x00, 0x00 },
	{ 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 },
	{ 0x00, 0x00, 0x00, 0x22, 0x14, 0x08, 0x00, 0x00 },
	{ 0x00, 0x20, 0x40, 0x40, 0x4A, 0x50, 0x20, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x5A, 0x6A, 0x5A, 0x38, 0x00 },
	{ 0x00, 0x3E, 0x48, 0x48, 0x48, 0x48, 0x3E, 0x00 },
	{ 0x00, 0x7E, 0x52, 0x52, 0x52, 0x52, 0x2C, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00 },
	{ 0x00, 0x7E, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00 },
	{ 0x00, 0x7E, 0x52, 0x52, 0x52, 0x52, 0x42, 0x00 },
	{ 0x00, 0x7E, 0x50, 0x50, 0x50, 0x50, 0x40, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x42, 0x4A, 0x4A, 0x2C, 0x00 },
	{ 0x00, 0x7E, 0x10, 0x10, 0x10, 0x10, 0x7E, 0x00 },
	{ 0x00, 0x00, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00 },
	{ 0x00, 0x0C, 0x02, 0x02, 0x02, 0x02, 0x7C, 0x00 },
	{ 0x00, 0x7E, 0x10, 0x10, 0x28, 0x44, 0x02, 0x00 },
	{ 0x00, 0x7E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00 },
	{ 0x00, 0x7E, 0x20, 0x10, 0x10, 0x20, 0x7E, 0x00 },
	{ 0x00, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x7E, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00 },
	{ 0x00, 0x7E, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x4A, 0x46, 0x42, 0x3C, 0x00 },
	{ 0x00, 0x7E, 0x48, 0x48, 0x48, 0x4C, 0x32, 0x00 },
	{ 0x00, 0x24, 0x52, 0x52, 0x52, 0x52, 0x0C, 0x00 },
	{ 0x40, 0x40, 0x40, 0x7E, 0x40, 0x40, 0x40, 0x00 },
	{ 0x00, 0x7C, 0x02, 0x02, 0x02, 0x02, 0x7C, 0x00 },
	{ 0x00, 0x78, 0x04, 0x02, 0x02, 0x04, 0x78, 0x00 },
	{ 0x00, 0x7C, 0x02, 0x04, 0x04, 0x02, 0x7C, 0x00 },
	{ 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00 },
	{ 0x40, 0x20, 0x10, 0x0E, 0x10, 0x20, 0x40, 0x00 },
	{ 0x00, 0x42, 0x46, 0x4A, 0x52, 0x62, 0x42, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7E, 0x42, 0x42, 0x00 },
	{ 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00 },
	{ 0x00, 0x42, 0x42, 0x7E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, 0x00 },
	{ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
	{ 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x00, 0x00 },
	{ 0x00, 0x04, 0x2A, 0x2A, 0x2A, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7E, 0x12, 0x12, 0x12, 0x0C, 0x00 },
	{ 0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x00, 0x00 },
	{ 0x00, 0x0C, 0x12, 0x12, 0x12, 0x7E, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x2A, 0x2A, 0x2A, 0x12, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3E, 0x50, 0x40, 0x00, 0x00 },
	{ 0x00, 0x18, 0x25, 0x25, 0x25, 0x3E, 0x00, 0x00 },
	{ 0x00, 0x7E, 0x10, 0x10, 0x10, 0x0E, 0x00, 0x00 },
	{ 0x00, 0x00, 0x12, 0x5E, 0x02, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x02, 0x01, 0x01, 0x5E, 0x00, 0x00 },
	{ 0x00, 0x00, 0x7E, 0x18, 0x24, 0x02, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7C, 0x02, 0x02, 0x00, 0x00 },
	{ 0x00, 0x3E, 0x20, 0x1E, 0x20, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x3E, 0x20, 0x20, 0x20, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x3F, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00 },
	{ 0x00, 0x18, 0x24, 0x24, 0x24, 0x3F, 0x01, 0x00 },
	{ 0x00, 0x00, 0x1E, 0x20, 0x20, 0x20, 0x00, 0x00 },
	{ 0x00, 0x12, 0x2A, 0x2A, 0x2A, 0x04, 0x00, 0x00 },
	{ 0x00, 0x00, 0x20, 0x7C, 0x22, 0x02, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x02, 0x02, 0x02, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x30, 0x0C, 0x02, 0x0C, 0x30, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x02, 0x1C, 0x02, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00, 0x00 },
	{ 0x00, 0x38, 0x05, 0x05, 0x05, 0x3E, 0x00, 0x00 },
	{ 0x00, 0x22, 0x26, 0x2A, 0x32, 0x22, 0x00, 0x00 },
	{ 0x00, 0x00, 0x10, 0x10, 0x6E, 0x42, 0x42, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00 },
	{ 0x00, 0x42, 0x42, 0x6E, 0x10, 0x10, 0x00, 0x00 },
	{ 0x00, 0x00, 0x20, 0x40, 0x20, 0x40, 0x00, 0x00 },
	{ 0x00, 0x00, 0x20, 0x40, 0xFE, 0x40, 0x20, 0x00 },
	{ 0x00, 0x28, 0x7C, 0xAA, 0xAA, 0x82, 0x44, 0x00 },
	{ 0xF0, 0xC0, 0xA0, 0x90, 0x08, 0x04, 0x02, 0x00 },
	{ 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00 },
	{ 0x00, 0x01, 0x01, 0x3E, 0x50, 0x40, 0x00, 0x00 },
	{ 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00 },
	{ 0x00, 0x00, 0x20, 0x20, 0x7E, 0x20, 0x20, 0x00 },
	{ 0x00, 0x00, 0x24, 0x24, 0x7E, 0x24, 0x24, 0x00 },
	{ 0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, 0x00 },
	{ 0x00, 0x66, 0x08, 0x10, 0x66, 0x00, 0x06, 0x00 },
	{ 0x00, 0x12, 0x2A, 0xAA, 0x6A, 0xAA, 0x04, 0x00 },
	{ 0x00, 0x00, 0x00, 0x08, 0x14, 0x00, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x42, 0x7E, 0x52, 0x42, 0x00 },
	{ 0x00, 0x02, 0x04, 0x08, 0x90, 0xA0, 0xC0, 0xF0 },
	{ 0x00, 0x22, 0xA6, 0x6A, 0xAA, 0x32, 0x22, 0x00 },
	{ 0x0F, 0x03, 0x05, 0x09, 0x10, 0x20, 0x40, 0x00 },
	{ 0x00, 0x40, 0x20, 0x10, 0x09, 0x05, 0x03, 0x0F },
	{ 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00 },
	{ 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
	{ 0x00, 0x00, 0x20, 0x40, 0x20, 0x40, 0x00, 0x00 },
	{ 0x40, 0x78, 0x40, 0x78, 0x20, 0x10, 0x20, 0x78 },
	{ 0x00, 0x12, 0xAA, 0x6A, 0xAA, 0x04, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x14, 0x08, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x1C, 0x2A, 0x10, 0x00, 0x00 },
	{ 0x00, 0x00, 0x04, 0x02, 0x7F, 0x02, 0x04, 0x00 },
	{ 0x00, 0x22, 0xA6, 0x6A, 0xB2, 0x22, 0x00, 0x00 },
	{ 0x20, 0x90, 0x08, 0x06, 0x08, 0x90, 0x20, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00 },
	{ 0x00, 0x12, 0x3E, 0x52, 0x52, 0x42, 0x22, 0x00 },
	{ 0x00, 0x44, 0x38, 0x28, 0x38, 0x44, 0x00, 0x00 },
	{ 0x40, 0x24, 0x14, 0x0E, 0x14, 0x24, 0x40, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x58, 0xA5, 0xA5, 0x1A, 0x00, 0x00 },
	{ 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00 },
	{ 0x3C, 0x42, 0x99, 0xA5, 0xA5, 0x81, 0x42, 0x3C },
	{ 0x00, 0x00, 0x30, 0x78, 0x78, 0x78, 0x00, 0x00 },
	{ 0x00, 0x08, 0x14, 0x22, 0x08, 0x14, 0x22, 0x00 },
	{ 0x00, 0x00, 0x10, 0x10, 0x10, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },
	{ 0x3C, 0x42, 0xBD, 0xA9, 0xA9, 0x95, 0x42, 0x3C },
	{ 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00 },
	{ 0x00, 0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 0x00 },
	{ 0x00, 0x00, 0x11, 0x11, 0x7D, 0x11, 0x11, 0x00 },
	{ 0x00, 0x00, 0x98, 0xA8, 0x48, 0x00, 0x00, 0x00 },
	{ 0x00, 0x50, 0x88, 0xA8, 0xA8, 0x50, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x3F, 0x04, 0x04, 0x38, 0x04, 0x00 },
	{ 0x00, 0x30, 0x48, 0x7E, 0x40, 0x7E, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00 },
	{ 0x00, 0x00, 0x48, 0xF8, 0x08, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 0x00 },
	{ 0x00, 0x22, 0x14, 0x08, 0x22, 0x14, 0x08, 0x00 },
	{ 0x48, 0xF8, 0x08, 0x00, 0x0C, 0x14, 0x3E, 0x00 },
	{ 0x48, 0xF8, 0x08, 0x00, 0x26, 0x2A, 0x12, 0x00 },
	{ 0x88, 0xA8, 0x50, 0x00, 0x0C, 0x14, 0x3E, 0x00 },
	{ 0x00, 0x04, 0x0A, 0x52, 0x02, 0x02, 0x04, 0x00 },
	{ 0x00, 0x1E, 0x24, 0xA4, 0x64, 0x24, 0x1E, 0x00 },
	{ 0x00, 0x1E, 0x24, 0x64, 0xA4, 0x24, 0x1E, 0x00 },
	{ 0x00, 0x1E, 0x64, 0xA4, 0x64, 0x24, 0x1E, 0x00 },
	{ 0x00, 0x1E, 0x64, 0xA4, 0x64, 0xA4, 0x1E, 0x00 },
	{ 0x00, 0x1E, 0xA4, 0x24, 0x24, 0xA4, 0x1E, 0x00 },
	{ 0x00, 0x1E, 0x24, 0xA4, 0xA4, 0x24, 0x1E, 0x00 },
	{ 0x00, 0x3E, 0x48, 0x48, 0x7E, 0x52, 0x42, 0x00 },
	{ 0x00, 0x3C, 0x42, 0x42, 0x43, 0x42, 0x24, 0x00 },
	{ 0x00, 0x3E, 0x2A, 0xAA, 0x6A, 0x2A, 0x22, 0x00 },
	{ 0x00, 0x3E, 0x2A, 0x6A, 0xAA, 0x2A, 0x22, 0x00 },
	{ 0x00, 0x3E, 0x6A, 0xAA, 0x6A, 0x2A, 0x22, 0x00 },
	{ 0x00, 0x3E, 0xAA, 0x2A, 0x2A, 0xAA, 0x22, 0x00 },
	{ 0x00, 0x00, 0x22, 0xA2, 0x7E, 0x22, 0x22, 0x00 },
	{ 0x00, 0x00, 0x22, 0x22, 0x7E, 0xA2, 0x22, 0x00 },
	{ 0x00, 0x00, 0x22, 0x62, 0xBE, 0x62, 0x22, 0x00 },
	{ 0x00, 0x00, 0xA2, 0x22, 0x3E, 0xA2, 0x22, 0x00 },
	{ 0x00, 0x7E, 0x52, 0x42, 0x42, 0x24, 0x18, 0x00 },
	{ 0x00, 0x3E, 0x60, 0x90, 0x48, 0x84, 0x3E, 0x00 },
	{ 0x00, 0x1C, 0x22, 0xA2, 0x62, 0x22, 0x1C, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x62, 0xA2, 0x22, 0x1C, 0x00 },
	{ 0x00, 0x1C, 0x62, 0xA2, 0x62, 0x22, 0x1C, 0x00 },
	{ 0x00, 0x1C, 0x62, 0xA2, 0x62, 0xA2, 0x1C, 0x00 },
	{ 0x00, 0x1C, 0xA2, 0x22, 0x22, 0xA2, 0x1C, 0x00 },
	{ 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00 },
	{ 0x00, 0x3C, 0x46, 0x4A, 0x52, 0x62, 0x3C, 0x00 },
	{ 0x00, 0x3C, 0x02, 0x82, 0x42, 0x02, 0x3C, 0x00 },
	{ 0x00, 0x3C, 0x02, 0x42, 0x82, 0x02, 0x3C, 0x00 },
	{ 0x00, 0x1C, 0x42, 0x82, 0x42, 0x02, 0x1C, 0x00 },
	{ 0x00, 0x3C, 0x82, 0x02, 0x02, 0x82, 0x3C, 0x00 },
	{ 0x20, 0x10, 0x08, 0x46, 0x88, 0x10, 0x20, 0x00 },
	{ 0x00, 0xFE, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00 },
	{ 0x00, 0x3F, 0x40, 0x54, 0x52, 0x2C, 0x00, 0x00 },
	{ 0x00, 0x04, 0x2A, 0xAA, 0x6A, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x04, 0x2A, 0x6A, 0xAA, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x04, 0x6A, 0xAA, 0x6A, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x04, 0x6A, 0xAA, 0x6A, 0x9E, 0x00, 0x00 },
	{ 0x00, 0x04, 0xAA, 0x2A, 0x2A, 0x9E, 0x00, 0x00 },
	{ 0x00, 0x04, 0x2A, 0x2A, 0x2A, 0x1E, 0x00, 0x00 },
	{ 0x00, 0x04, 0x2A, 0x1C, 0x3A, 0x12, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x23, 0x22, 0x00, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x2A, 0xAA, 0x6A, 0x12, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x2A, 0x6A, 0xAA, 0x12, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x6A, 0xAA, 0x6A, 0x12, 0x00, 0x00 },
	{ 0x00, 0x1C, 0xAA, 0x2A, 0x2A, 0x92, 0x00, 0x00 },
	{ 0x00, 0x00, 0x92, 0x5E, 0x02, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x12, 0x5E, 0x82, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x52, 0x9E, 0x42, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x52, 0x1E, 0x42, 0x00, 0x00, 0x00 },
	{ 0x00, 0x0C, 0x12, 0xB2, 0x52, 0xBE, 0x00, 0x00 },
	{ 0x00, 0x1E, 0x50, 0x90, 0x50, 0x8E, 0x00, 0x00 },
	{ 0x00, 0x1C, 0xA2, 0x62, 0x22, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x62, 0xA2, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x62, 0xA2, 0x62, 0x9C, 0x00, 0x00 },
	{ 0x00, 0x1C, 0xA2, 0x22, 0xA2, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x2A, 0x08, 0x08, 0x00 },
	{ 0x00, 0x1C, 0x26, 0x2A, 0x32, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x82, 0x42, 0x02, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x02, 0x42, 0x82, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x1C, 0x42, 0x82, 0x42, 0x1C, 0x00, 0x00 },
	{ 0x00, 0x3C, 0x82, 0x02, 0x82, 0x3C, 0x00, 0x00 },
	{ 0x00, 0x38, 0x05, 0x45, 0x85, 0x3E, 0x00, 0x00 },
	{ 0x00, 0x7E, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00 },
	{ 0x00, 0x38, 0x85, 0x05, 0x85, 0x3E, 0x00, 0x00 },
};

