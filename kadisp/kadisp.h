/*
 * kadisp.h
 *
 *  Created on: Dec 7, 2014
 *      Author: kamichal
 */

#ifndef KADISP_H
#define KADISP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ssd1780_oled_cntrl.h"

#if 5515
#include <usbstk5515.h>
#else
#include <usbstk5505.h>
#endif

#define KADISP_MAX_NUMBER_OF_PAGES SSD1780_PAGE_COUNT // max 8 can be set to 1,2,..,8
// extra one byte for "command" token (goes first in burst)
#define KADISP_CACHE_LINE_LGH SSD1780_PAGE_WIDTH + 1

extern Uint8 g_kadisp_page_cache[KADISP_MAX_NUMBER_OF_PAGES][KADISP_CACHE_LINE_LGH];

void KaDisp_printf(Uint8 page, char * format, ...);

void KaDisp_send_cache_all_pages();
void KaDisp_send_page_cache(Uint8 page);
void KaDisp_send_page_cache_range(Uint8 page_number, Uint8 start_col, Uint8 width);

void KaDisp_init(void);
void KaDisp_render_text(Uint8 page, char * text);
void KaDisp_move_window_to_page(Uint8 page);
void KaDisp_clear(void);

void KaDisp_scroll_on_off(Uint8 enable);
void KaDisp_scroll_vert_and_hor_first_line(void);
void KaDisp_scroll_horizontal_simple(void);
void KaDisp_scroll_vertical(void);

#endif /* KADISP_H */

#ifdef __cplusplus
} // extern "C" {
#endif
