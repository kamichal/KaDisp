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

#define KADISP_PAGE_BUFFER_SIZE (KADISP_CACHE_LINE_LGH)

#ifndef KADISP_AUTO_SEND
#define KADISP_AUTO_SEND 1 // set 0 to disable
#endif

#ifndef KADISP_AUTO_SCROLL_TO_LAST_PAGE
#define KADISP_AUTO_SCROLL_TO_LAST_PAGE 0 // set 0 to disable
#endif


Uint8 g_page_cache[KADISP_USED_PAGE_NUMBER][KADISP_PAGE_BUFFER_SIZE];


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
            g_page_cache[p][x] = 0;
    }

    KaDisp_send_entire_cache();
}

void Kaprintf(Uint8 line_position, char * format, ...)
{
    char buffer[256];
    va_list args;
    line_position = line_position % KADISP_USED_PAGE_NUMBER;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

#ifdef _DEBUG
    printf("p%d: %s\n",line_position, buffer);
#endif

    KaDisp_string(line_position, buffer);
}

// displays static char buffer till first null
void KaDisp_string(Uint8 line_position, char * letter)
{
    Uint16 font_column;
    Uint16 buffer_column = 0;
    Uint16 max_length = 100;
    Uint16 p = line_position % KADISP_USED_PAGE_NUMBER;
    g_page_cache[p][buffer_column++] = SSD1780_SEND_DATA;

    // till buffer not terminated by null ('/0')or exceed max_length
    while ((*letter != 0) && max_length--)
    {
        for (font_column = 0; font_column < 6; font_column++) //used 6 px width font
        {
            g_page_cache[p][buffer_column++] = Font8x6[*letter][font_column];
            if (buffer_column > KADISP_CACHE_LINE_LGH)
                return;
        }
        letter++;
    }
    //clear rest of the buffer
    while (buffer_column < KADISP_CACHE_LINE_LGH)
    {
        g_page_cache[p][buffer_column++] = 0x00;
    }
#if KADISP_AUTO_SEND
    KaDisp_send_page_cache(p);
#endif

#if KADISP_AUTO_SCROLL_TO_LAST_PAGE
    KaDisp_scroll_to_page(p);
#endif
}

void KaDisp_test_pattern(Uint8 line_position)
{
    Uint16 idx = 0;
    Uint16 p = line_position % KADISP_USED_PAGE_NUMBER;
    g_page_cache[p][idx] = SSD1780_SEND_DATA;
    for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx++)
    {
        g_page_cache[p][idx] = (idx - 1) & 0xFF;
    }
#if KADISP_AUTO_SEND
    KaDisp_send_page_cache(p);
#endif
#if KADISP_AUTO_SCROLL_TO_LAST_PAGE
    KaDisp_scroll_to_page(p);
#endif

}


void KaDisp_scroll_to_page(Uint8 line_position)
{
    SSD1780_send_cmd_val(SSD1780_SET_VERTICAL_OFFSET, (line_position * 8) & 0x3F);  // 0xD3
}


void KaDisp_scroll_to_point(Uint8 display_offset)
{
    SSD1780_send_cmd_val(SSD1780_SET_VERTICAL_OFFSET, display_offset & 0x3F);  // 0xD3 // 0x3F = max 64 horizontal lines
}


void KaDisp_send_page_cache(Uint8 line_position)
{
    Uint16 p = line_position % KADISP_USED_PAGE_NUMBER;
    SSD1780_set_PAM_page_addres(p);
    SSD1780_set_PAM_column_start_addres(31); // Skip 32 columns
    // that's because the first 32 columns (left edge) are in ram, but not displayed.

    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, &g_page_cache[p][0], KADISP_CACHE_LINE_LGH);

//    SSD1780_set_PAM_column_start_addres(0);
}


void KaDisp_send_entire_cache(void)
{
    Uint16 p;
    for (p = 0; p < KADISP_USED_PAGE_NUMBER; p++)
    {
        KaDisp_send_page_cache(p);
    }
}
