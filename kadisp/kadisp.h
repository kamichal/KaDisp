/*
 * osd9616_buf_prints.h
 *
 *  Created on: Dec 7, 2014
 *      Author: kamichal
 */

#ifndef SSD1780_OLED_CONTROLLER_
#define SSD1780_OLED_CONTROLLER_

#ifdef __cplusplus
extern "C" {
#endif


#include "ssd1780_oled_cntrl.h"

#if 5515
#include <usbstk5515.h>
#else
#include <usbstk5505.h>
#endif

#define KADISP_USED_PAGE_NUMBER SSD1780_PAGE_COUNT // max 8 // 0,1...,7

#define KADISP_CACHE_LINE_LGH SSD1780_PAGE_WIDTH + 1 // extra one byte for "command" token (goes first in burst)

extern Uint8 g_page_cache[KADISP_USED_PAGE_NUMBER][KADISP_CACHE_LINE_LGH];


void Kaprintf(Uint8 page, char * format, ...);

void KaDisp_send_entire_cache();
void KaDisp_send_page_cache(Uint8 page);
void KaDisp_send_page_cache_range(Uint8 page_number, Uint8 start_col, Uint8 width);

void KaDisp_static_string(Uint8 page, char * text);
void KaDisp_init(void);
void KaDisp_scroll_to_page(Uint8 page);
void KaDisp_clear(void);
#endif /* SSD1780_OLED_CONTROLLER_ */


#ifdef __cplusplus
} // extern "C" {
#endif
