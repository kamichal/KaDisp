/*
 * osd9616_buf_prints.c
 *
 *  Created on: Dec 7, 2014
 *      Author: kamichal
 */

#include "kadisp.h"
#include <usbstk5515_i2c.h>
#include "font_8x6_philippe.h"
#include <stdio.h>
#include <stdarg.h>

#define KADISP_PAGE_BUFFER_SIZE (SSD1780_PAGE_WIDTH + 1)

#ifndef KADISP_AUTO_SEND
#define KADISP_AUTO_SEND 1 // set 0 to disable
#endif

#ifndef KADISP_AUTO_SCROLL_TO_LAST_PAGE
#define KADISP_AUTO_SCROLL_TO_LAST_PAGE 0 // set 0 to disable
#endif


Uint8 g_page[KADISP_USED_PAGE_NUMBER][KADISP_PAGE_BUFFER_SIZE];


void KaDisp_init(void)
{
    SSD1780_init();
    KaDisp_clear();

}

void KaDisp_clear(void)
{
    Uint16 p;
    Uint16 x;

    for (p = 0; p < KADISP_USED_PAGE_NUMBER; p++)
    {
        for (x = 0; x < KADISP_PAGE_BUFFER_SIZE; x++)
            g_page[p][x] = 0;
    }

    KaDisp_send_all_page_buffers();
}

void KaDisp_text(Uint8 page, char * format, ...)
{
    char buffer[256];
    va_list args;
    page = page % KADISP_USED_PAGE_NUMBER;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

#ifdef _DEBUG
    printf("p%d: %s\n",page, buffer);
#endif

    KaDisp_static_text(page, buffer);
}

void KaDisp_static_text(Uint8 page, char * text)
{
    Uint16 c;
    Uint16 col_idx = 0;
    Uint16 p = page % KADISP_USED_PAGE_NUMBER;
    g_page[p][col_idx++] = SSD1780_SEND_DATA;

    while (*text != 0)
    {
        for (c = 0; c < 6; c++)
        {
            if (col_idx >= SSD1780_PAGE_WIDTH + 1)
                return;
            g_page[p][col_idx++] = Font8x6[*text][c];
        }
        text++;
    }
    //clear rest
    while (col_idx < SSD1780_PAGE_WIDTH + 1)
    {
        g_page[p][col_idx++] = 0x00;
    }
#if KADISP_AUTO_SEND
    KaDisp_send_page_buffer(p);
#endif

#if KADISP_AUTO_SCROLL_TO_LAST_PAGE
    KaDisp_scroll_to_page(p);
#endif
}

void KaDisp_test_pattern(Uint8 page)
{
    Uint16 idx = 0;
    Uint16 p = page % KADISP_USED_PAGE_NUMBER;
    g_page[p][idx] = SSD1780_SEND_DATA;
    for (idx = 1; idx < SSD1780_PAGE_WIDTH + 1; idx++)
    {
        g_page[p][idx] = (idx - 1) & 0xFF;
    }
#if KADISP_AUTO_SEND
    KaDisp_send_page_buffer(p);
#endif
#if KADISP_AUTO_SCROLL_TO_LAST_PAGE
    KaDisp_scroll_to_page(p);
#endif

}

void KaDisp_scroll_to_page(Uint8 page)
{
    SSD1780_send_cmd_val(SSD1780_SET_VERTICAL_OFFSET, (page * 8) & 0x3F);  // 0xD3
}

void KaDisp_send_page_buffer(Uint8 page)
{
    Uint16 p = page % KADISP_USED_PAGE_NUMBER;
    SSD1780_set_PAM_page_addres(p);
    SSD1780_set_PAM_column_start_addres(31);

    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, &g_page[p][0], SSD1780_PAGE_WIDTH + 1);

//    SSD1780_set_PAM_column_start_addres(0);
}

void KaDisp_send_all_page_buffers(void)
{
    Uint16 p;
    for (p = 0; p < KADISP_USED_PAGE_NUMBER; p++)
    {
        KaDisp_send_page_buffer(p);
    }
}
