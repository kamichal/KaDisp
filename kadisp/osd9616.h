/*
 * osd9616.h
 *
 *  Created on: Dec 2, 2014
 *      Author: kamichal
 */

#ifndef OSD9616_H_
#define OSD9616_H_

#include "usbstk5515.h"

#define OSD9616_I2C_ADDR 0x3C
#define SSD1780_DUMMY_ZERO 0x00
#define SSD1780_DUMMY_FF 0xFF
#define SSD1780_SEND_COMMAND 0x00
#define SSD1780_SEND_DATA 0x40

#define SSD1780_SET_MEM_ADDRESSING_MODE 0x20
#define SSD1780_SET_VHAM_COLUMN_ADDRESS 0x21
#define SSD1780_SET_VHAM_PAGE_ADDRESS 0x22
#define SSD1780_SCROLL_H_RIGHT 0x26
#define SSD1780_SCROLL_H_LEFT 0x27
#define SSD1780_SCROLL_VH_RIGHT 0x29
#define SSD1780_SCROLL_VH_LEFT 0x2A
#define SSD1780_SCROLL_VH_BITMASK 0x28
#define SSD1780_DISABLE_SCROLLING 0x2E
#define SSD1780_ENABLE_SCROLLING  0x2F

#define SSD1780_SET_DISPLAY_START_LINE 0x40

#define SSD1780_SET_SEGMENT_REMAP_COL0_TO_SEG0 0xA0
#define SSD1780_SET_SEGMENT_REMAP_COL127_TO_SEG0 0xA1
#define SSD1780_SET_V_SCROLL_AREA 0xA3
#define SSD1780_DISPLAY_NORMAL 0xA6
#define SSD1780_DISPLAY_INVERSE 0xA7
#define SSD1780_SET_MULTIPLEX_RATIO 0xA8
#define SSD1780_TURN_DISP_OFF 0xAE
#define SSD1780_TURN_DISP_ON 0xAF

#define SSD1780_SET_PAM_PAGE_START_ADDRESS 0xB0

#define SSD1780_SET_VERTICAL_OFFSET 0xD3
#define SSD1780_SET_CLOCK_DIV_RATIO 0xD5
#define SSD1780_SET_PRE_CHARGE_PERIOD 0xD9
#define SSD1780_SET_COM_PINS_HW_CONFIG 0xDA
#define SSD1780_SET_COMH_DESELECT_LEVEL 0xDB

#define SSD1780_SET_CONSTRAST  0x81
#define SSD1780_SET_CHARGE_PUMP 0x8D
#define SSD1780_CHARGE_PUMP_DISABLED 0x10
#define SSD1780_CHARGE_PUMP_ENABLED 0x14

#define SSD1780_PAGE_WIDTH 128
#define SSD1780_PAGE_COUNT 8
#define OSD9616_PAGE_COUNT 2

typedef enum SSD1780_scroll_interval_e
{
    interval_05_frames = 0x0,
    interval_64_frames = 0x1,
    interval_128_frames = 0x2,
    interval_256_frames = 0x3,
    interval_03_frames = 0x4,
    interval_04_frames = 0x5,
    interval_25_frames = 0x6,
    interval_02_frames = 0x7
} SSD1780_scroll_interval_e;

typedef enum SSD1780_H_scroll_direction_e
{
    scroll_riht = 0x26, scroll_left = 0x27
} SSD1780_H_scroll_direction_e;
typedef enum SSD1780_VH_scroll_direction_e
{
    scroll_vert_riht = 0x29, scroll_vert_left = 0x2A
} SSD1780_VH_scroll_direction_e;

typedef enum SSD1780_mem_mode_e
{
    mem_mode_horizontal = 0x00,
    mem_mode_vertical = 0x01,
    mem_mode_page_addressing = 0x2,
    mem_mode_defaul = mem_mode_page_addressing
} SSD1780_mem_mode_e;

void SSD1780_init(void);
Int16 SSD1780_send_cmd(Uint16 command);
Int16 SSD1780_send_cmd_val(Uint8 command, Uint8 val);
Int16 SSD1780_send_data(Uint8 data);
void SSD1780_set_contrast(Uint8 contrast_value);

Int16 SSD1780_set_memory_addressing(SSD1780_mem_mode_e mode);

Int16 SSD1780_set_VHAM_column_addres(Uint8 start_7b, Uint8 end_7b);
Int16 SSD1780_set_VHAM_page_addres(Uint8 start_addres_3b, Uint8 end_addres_3b);

Int16 SSD1780_set_PAM_column_start_addres(Uint8 addres_4b);
Int16 SSD1780_set_PAM_page_addres(Uint8 addres_3b);
Int16 SSD1780_set_display_start_line(Uint8 line_6b);
Int16 SSD1780_clear_graphic_ram(void);

void SSD1780_setup_default_scrolling(void);
void SSD1780_set_vertical_scroll_area(Uint8 fixed_height, Uint8 floating_height);
void SSD1780_setup_horizontal_scroll(
                                     Uint8 start_page,
                                     Uint8 end_page,
                                     SSD1780_scroll_interval_e interval,
                                     SSD1780_H_scroll_direction_e dir);

void SSD1780_setup_vertical_and_horizontal_scroll(
                                                  Uint8 start_page,
                                                  Uint8 end_page,
                                                  SSD1780_scroll_interval_e interval,
                                                  SSD1780_VH_scroll_direction_e dir,
                                                  Uint8 V_offset);
#endif /* OSD9616_H_ */
