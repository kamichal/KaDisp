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
#include <string.h>
#include <stdarg.h>

#define KADISP_PAGE_BUFFER_SIZE (KADISP_CACHE_LINE_LGH)

#ifdef __cplusplus
extern "C"
{
#endif

// g_kadisp_page_cache is a display memory buffer within the DSP (internal memory),
// stores e.g 8 lines per 128 pixels width
// when it's needed it can be send to display memory (update external mem)
// it's easier to do "painting" on DSP side and then send e.g. whole line
// to the display, than overriding display's internal memory.
Uint8 g_kadisp_page_cache[KADISP_MAX_NUMBER_OF_PAGES][KADISP_PAGE_BUFFER_SIZE];

void KaDisp_init(void)
{
    SSD1780_init_HW();
    KaDisp_scroll_on_off(0);
    KaDisp_clear();

}

void KaDisp_clear(void)
{
    Uint16 p;
    Uint16 x;

    for (p = 0; p < KADISP_MAX_NUMBER_OF_PAGES; p++)
    {
        //the first one should be a "data token"
        g_kadisp_page_cache[p][0] = SSD1780_SEND_DATA_TOKEN;

        for (x = 1; x < KADISP_PAGE_BUFFER_SIZE; x++)
            g_kadisp_page_cache[p][x] = 0;
    }

    KaDisp_send_cache_all_pages();
}

void KaDisp_printf(Uint8 page, char * format, ...)
{
    char buffer[256];
    va_list args;
    page = page % KADISP_MAX_NUMBER_OF_PAGES;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

#if defined(_DEBUG)
    printf("p%d: %s\n",page, buffer);
#endif

    KaDisp_render_text(page, buffer);
}

// displays static char buffer till first null
void KaDisp_render_text(Uint8 page, char * letter)
{
    Uint16 font_column;
    Uint16 buffer_column = 0;
    Uint16 max_length = 50;
    Uint16 p = page % KADISP_MAX_NUMBER_OF_PAGES;
    g_kadisp_page_cache[p][buffer_column++] = SSD1780_SEND_DATA_TOKEN;

    // till buffer terminated by null ('/0')or exceed max_length
    while ((*letter != 0) && max_length--)
    {
        for (font_column = 0; font_column < 6; font_column++) //used 6 px width font
        {
            g_kadisp_page_cache[p][buffer_column++] = Font8x6[*letter][font_column];
            if (buffer_column > KADISP_CACHE_LINE_LGH)
                return;
        }
        letter++;
    }
    //clear rest of the buffer
    while (buffer_column < KADISP_CACHE_LINE_LGH)
    {
        g_kadisp_page_cache[p][buffer_column++] = 0x00;
    }

    //if you_want_to_auto_scroll_to_last_page - uncomment the below call
    //KaDisp_scroll_window_to_page(p);
}

void KaDisp_move_window_to_page(Uint8 page_n)
{
    SSD1780_send_cmd_with_val(SSD1780_SET_VERTICAL_OFFSET, (page_n * 8) & 0x3F);  // 0xD3
}

void KaDisp_scroll_vert_to_point(Uint8 display_offset_px)
{
    SSD1780_send_cmd_with_val(SSD1780_SET_VERTICAL_OFFSET, display_offset_px & 0x3F); // 0xD3 // 0x3F = max 64 horizontal lines
}

void KaDisp_send_page_cache(Uint8 page_n)
{
    Uint16 p = page_n % KADISP_MAX_NUMBER_OF_PAGES;

    SSD1780_set_PAM_page_addres(p);
    SSD1780_set_PAM_column_start_addres(32); // Skip 32 columns
    // that's because the first 32 columns (left edge)
    // are present in display RAM (128px width), but are not displayed (96px width).

    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, &g_kadisp_page_cache[p][0], KADISP_CACHE_LINE_LGH);
}

// can be used to update just a small area in display (goes faster)
void KaDisp_send_page_cache_range(Uint8 page_number, Uint8 start_col, Uint8 width)
{
    Uint16 page;
    Uint8 packet[KADISP_CACHE_LINE_LGH];

    //start_col += 1; // first character is a "data token"

    // avoid overflows
    start_col %= KADISP_CACHE_LINE_LGH;
    width %= KADISP_CACHE_LINE_LGH;
    if (width + start_col > KADISP_CACHE_LINE_LGH)
        width = KADISP_CACHE_LINE_LGH - start_col;

    page = (Uint16) (page_number % KADISP_MAX_NUMBER_OF_PAGES);

    packet[0] = SSD1780_SEND_DATA_TOKEN;

    memcpy(&packet[1], &g_kadisp_page_cache[page][start_col + 1], width);

    SSD1780_set_PAM_page_addres(page);
    SSD1780_set_PAM_column_start_addres(31 + start_col); // Skip 32 columns

    USBSTK5515_I2C_write(OSD9616_I2C_ADDR, packet, width + 1);

}

void KaDisp_send_cache_all_pages(void)
{
    Uint16 p;
    for (p = 0; p < KADISP_MAX_NUMBER_OF_PAGES; p++)
    {
        KaDisp_send_page_cache(p);
    }
}

void KaDisp_scroll_on_off(Uint8 enable)
{
    if (enable == 0)
        SSD1780_send_cmd(SSD1780_DISABLE_SCROLLING);
    else
        SSD1780_send_cmd(SSD1780_ENABLE_SCROLLING);
}

void KaDisp_scroll_vertical(void)
{
    /* FIXME: For some reason I cannot set the first line scrolling disabled... */
    SSD1780_set_horizontal_scroll(0, 0, interval_64_frames, scroll_left);
    SSD1780_set_vertical_and_horizontal_scroll(0, 0, interval_128_frames, scroll_vert_left, 1);

    /* Set what area (lines) has to be scrolled vertically */
    SSD1780_set_vertical_scroll_area(0, 64);

    SSD1780_send_cmd(SSD1780_ENABLE_SCROLLING);
}

void KaDisp_scroll_horizontal_simple(void)
{
    SSD1780_set_horizontal_scroll(0, 1, interval_25_frames, scroll_left);
    SSD1780_send_cmd(SSD1780_ENABLE_SCROLLING);
}

void KaDisp_scroll_vert_and_hor_first_line(void)
{
    SSD1780_set_horizontal_scroll(0, 1, interval_64_frames, scroll_left);
    SSD1780_set_vertical_and_horizontal_scroll(0, // start page
                                                 SSD1780_PAGE_COUNT, // end page
                                                 interval_64_frames, //speed
                                                 scroll_vert_left, //direction
                                                 1); //v_offset

    /* The function call bellow sets that first 8 pixels are
     * scrolled only horizontally, and the next 8 pixels show
     * the image stored in display RAM with vertical scroll.  */
    SSD1780_set_vertical_scroll_area(8, SSD1780_PAGE_COUNT * 8);
    SSD1780_send_cmd(SSD1780_ENABLE_SCROLLING);

}

#ifdef __cplusplus
} // extern "C" {
#endif
