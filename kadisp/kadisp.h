/*
 * osd9616_buf_prints.h
 *
 *  Created on: Dec 7, 2014
 *      Author: kamichal
 */

#ifndef OSD9616_BUF_PRINTS_H_
#define OSD9616_BUF_PRINTS_H_

#include "osd9616.h"

#if 5515
#include <usbstk5515.h>
#else
#include <usbstk5505.h>
#endif
#define KADISP_USED_PAGE_NUMBER SSD1780_PAGE_COUNT

#ifndef NDEBUG
#  define debug_print(msg) my_printf msg
#else
#  define debug_print(msg) (void)0
#endif

extern Uint8 g_page[KADISP_USED_PAGE_NUMBER][SSD1780_PAGE_WIDTH + 1];

void KaDisp_send_all_page_buffers();
void KaDisp_send_page_buffer(Uint8 page);
void KaDisp_test_pattern(Uint8 page);
void KaDisp_static_text(Uint8 page, char * text);
void KaDisp_init(void);
void KaDisp_text(Uint8 page, char * format, ...);
void KaDisp_scroll_to_page(Uint8 page);
void KaDisp_clear(void);
#endif /* OSD9616_BUF_PRINTS_H_ */
