/*
 * kadisp_tests.c
 *
 *  Created on: Dec 29, 2014
 *      Author: kamichal
 */

#include <stdio.h>

#include <ka_pp.h>
#include "kadisp.h"
#include "kadisp_tests.h"

Int16 fastLog2(Int32 val)
{
    Int16 ret = 0;
    val = k_abs(val);

    while (val > 0)
    {
        ret++;
        val >>= 1;
    }
    return ret;
}


void KaDisp_test_01(void)
{
    /* This test uses manual scrolling for the display.
     * Initially each of the 8 lines is filled with sample text.
     * Then the program goes into a long loop which is responsible
     * for vertical scrolling of the display window (16x96px)
     * over the whole display RAM (64x96px).
     * The display's RAM content can be updated, which is shown
     * within the loop.
     * Of course, in regular usage, the DSP shouldn't be trapped in such
     * a while loop. The "vertical" scroll event should be handled in
     * an interrupt, e.g. once per 30ms. Then the DSP can do any other stuff.
     * */
    Uint8 pos = 0;
    Int8 times = 3;

    printf("\n KaDisp_test_01() \n");

    KaDisp_init();

    KaDisp_printf(0, "This is");
    KaDisp_printf(1, "kamichal's");
    KaDisp_printf(2, "implementation");
    KaDisp_printf(3, "of the OSD%d", 9616);
    KaDisp_printf(4, "display");
    KaDisp_printf(5, "driver SSD1780");
    KaDisp_test_pattern(6);
    KaDisp_printf(7, "eZdsp.");

    KaDisp_send_cache_all_pages();

    while (times >= 0)
    {
        //move display window around ("manual" scrolling)
        SSD1780_set_vertical_offset(pos);
        USBSTK5515_waitusec(30000);

        if (pos % 0x3F == 0x3F - 12)
        {
            // happens once per one full sweep
            KaDisp_printf(7, "eZdsp.%10d", times--); //decrement count
            KaDisp_send_page_cache(7);
        }
        pos++;
    }

}

void KaDisp_test_02(void)
{
    /* This test checks how fast the display can be updated with a text.
     * It's a brute force method. The DSP is doing only one thing
     * It sends a new string and after that - sends the next one in a loop.
     * The measurement is affected by time of text processing.
     * Unwrapping printf function takes some time. Simple pixel drawing should be faster.
     *
     * I haven't implemented measurement of frames per second
     * because I haven't figured out any method for time measurement yet.
     *
     * For increasing the speed only small area of the display is being updated.
     *
     * Running the test you can notice that the "frames" word is kept on the display.
     * That's because it's area is not updated. A trick :) */

    Int16 times = 0;

    KaDisp_init();

    KaDisp_printf(0, "          frames");
    KaDisp_send_page_cache(0);

    KaDisp_printf(1, "run max fps");
    KaDisp_send_page_cache(1);

    do // run as fast as you can
    {
        KaDisp_printf(0, "%d", times);
        KaDisp_send_page_cache_range(0, 0, 40);
        // the word "frames" stays untouched,
        // just a 8x40px rectangle is being updated
        times++;
    } while (times < 2000);
}

void KaDisp_test_03(void)
{
    /* This test shows an example of a simple drawing.
     * It draws a binary counter with maximum available speed.
     * You draw directly to the g_kadisp_page_cache buffer.
     * Then it's content is being sent to the display.
     * */
    Int16 count = 0;
    const Int16 max_count = 1024;
    const Uint8 columns_at_once = 6;
    Uint16 idx;

    KaDisp_init();

    /* the first value in the cache should be allways SSD1780_SEND_DATA_TOKEN*/

    KaDisp_printf(1, "binary counter");
    KaDisp_send_page_cache(1);

    while (count < max_count)
    {
        Int16 tmp = count;
        Uint8 counter_width_px;
        for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx += columns_at_once)
        {
            if (tmp & 0x1) // LSB bit is set
            {   //fill 6 columns
                g_kadisp_page_cache[0][idx] = 0x00;
                g_kadisp_page_cache[0][idx + 1] = 0x7C;
                g_kadisp_page_cache[0][idx + 2] = 0x7C;
                g_kadisp_page_cache[0][idx + 3] = 0x7C;
                g_kadisp_page_cache[0][idx + 4] = 0x7C;
                g_kadisp_page_cache[0][idx + 5] = 0x00;
            }
            else //bit is clear
            {   //fill 6 columns
                g_kadisp_page_cache[0][idx] = 0x00;
                g_kadisp_page_cache[0][idx + 1] = 0x80;
                g_kadisp_page_cache[0][idx + 2] = 0x80;
                g_kadisp_page_cache[0][idx + 3] = 0x80;
                g_kadisp_page_cache[0][idx + 4] = 0x80;
                g_kadisp_page_cache[0][idx + 5] = 0x00;
            }
            tmp >>= 1; //take the next bit
        }

        count++;
        counter_width_px = columns_at_once * fastLog2(count - 1);
        KaDisp_send_page_cache_range(0, 0, counter_width_px);

        /* Only necessary area is updated, basing on the count value.
         * As the count value grows the update rate slows down.
         * That's because with higher count values, the larger
         * amount of data needs to be send. */
    }
}

void KaDisp_DrawHorizontalBar(Uint8 page, Uint8 fill_percent)
{
    /* The function draws a horizontal bar. */
    Uint16 idx;
    Uint16 frame_width_px = 96;
    Uint16 frame_margin_width_px = 2;
    Uint16 bar_width_px;

    //avoid overflow
    page = page % KADISP_MAX_NUMBER_OF_PAGES;

    bar_width_px = (frame_width_px - 2 * frame_margin_width_px) * fill_percent;
    bar_width_px /= 100;

    // begin the frame
    g_kadisp_page_cache[page][1] = 0x1C;
    g_kadisp_page_cache[page][2] = 0x22;

    for (idx = 1 + frame_margin_width_px; idx < bar_width_px + 1; idx++)
    {
        //it's a frame plus fill
        g_kadisp_page_cache[page][idx] = 0x41 | 0x1C; // bitwise "or" (sum)
    }
    for (idx = 1 + bar_width_px; idx < frame_width_px - frame_margin_width_px + 1; idx++)
    {
        //it's a frame only
        g_kadisp_page_cache[page][idx] = 0x41;
    }

    // finish the frame
    g_kadisp_page_cache[page][frame_width_px - 1] = 0x22;
    g_kadisp_page_cache[page][frame_width_px] = 0x1C;

}

void KaDisp_test_04(void)
{
    Int16 width = 0;

    KaDisp_init();

    while (width <= 100)
    {
        KaDisp_DrawHorizontalBar(0, width);
        KaDisp_send_page_cache(0);

        KaDisp_printf(1, "bar width: %d%%", width);
        KaDisp_send_page_cache(1);

        USBSTK5515_waitusec(10000);
        width++;

    }
    USBSTK5515_waitusec(90000);
}

void KaDisp_test_05(void)
{
    /* This test should show a semi-gray-scale effect.
     *
     * The idea is to send to the display cache four different images
     * and then just move display around them very fast in order to obtain a
     * gray-scale effect.
     *
     * Each image has two pages in height (two text lines) and contains a line in the
     * first page and a frame period information (text) in the second text line (page).
     *
     * The thickness of the line is different in each of the four images.
     * When you change the images very quickly you should notice that it looks
     * like a rectangle with gradient fill.
     * */

    Uint16 page;
    Uint16 decade;
    Uint8 depth = 8;

    KaDisp_init();

    SSD1780_send_cmd_with_val(SSD1780_SET_MULTIPLEX_RATIO, 0x32); // 0xA8, default: 0x3F, gives 8 pages

    for (page = 0; page < depth; page++)
    {
        // print semi-grayscale pattern into even pages (lines)
        Uint16 col;
        Uint8 pageMark = (1 << ((8 * page) / depth + 2)) - 1;

        // in effect:
        // in the page 0 - there is a single line
        // in the page 2 - there is a double line
        // in the page 4 - there is a triple line
        // in the page 6 - there is a quadruple line

        g_kadisp_page_cache[page][0] = SSD1780_SEND_DATA_TOKEN;

        for (col = 1; col < KADISP_CACHE_LINE_LGH; col += 4)
        {
            g_kadisp_page_cache[page][col] = pageMark;
            g_kadisp_page_cache[page][col + 1] = pageMark;
            g_kadisp_page_cache[page][col + 2] = pageMark;
            g_kadisp_page_cache[page][col + 3] = pageMark;
        }
        KaDisp_send_page_cache(page);
    }

    // now perform test - how the refresh rate affects flickering
    // yes - it should sweep refresh rate lineary, but I did it
    // with geometric progress of the period and haven't found time to change it
    // to linear progress. However I believe you catch the idea.

    for (decade = 6; decade < 15; decade++)
    {
        Uint32 times;
        Int32 period;

        period = 1 << decade;
        // print period info in odd pages (text-lines)
        KaDisp_printf(1, "%d us", period);
        KaDisp_printf(3, "%d us", period);
        KaDisp_printf(5, "%d us", period);
        KaDisp_printf(7, "%d us", period);
        KaDisp_send_page_cache(1);
        KaDisp_send_page_cache(3);
        KaDisp_send_page_cache(5);
        KaDisp_send_page_cache(7);

        times = 0x1000 / decade;
        //as the period grows, there is less number of refreshes
        while (times-- > 0)
        {
            // now it's not drawing anything
            // it just changing the display window position.
            // it moves to consecutive page pairs: (0&1), (2&3), (4%5), (6%7)

            Uint8 page_to_be_shown = (Uint8) ((2 * times) % depth);
            KaDisp_move_window_to_page(page_to_be_shown);
            USBSTK5515_waitusec(period);
        }
    }

}

void KaDisp_test_06(void)
{
    /* This is rather an experiment than a test. It shows how gray scale
     * images can be drawn. Similar as in KaDisp_test_05() it draws four
     * different images and switches the view between them around.
     * Image update rate affects flicker of the display. Observing the display
     * you can check at what update rate the display flickering is minimal. */
    Uint16 page;
    Uint32 refresh_period_us;

    KaDisp_init();

    for (page = 0; page < KADISP_MAX_NUMBER_OF_PAGES; page += 2)
    {
        Uint16 col;
        Uint8 pattern = (1 << (page + 2)) - 1;
        // fill even pages with gray scale pattern
        for (col = 1; col < KADISP_CACHE_LINE_LGH; col += 6)
        {
            g_kadisp_page_cache[page][col] = 0x0;
            g_kadisp_page_cache[page][col + 1] = pattern;
            g_kadisp_page_cache[page][col + 2] = pattern;
            g_kadisp_page_cache[page][col + 3] = pattern;
            g_kadisp_page_cache[page][col + 3] = pattern;
            g_kadisp_page_cache[page][col + 4] = pattern;
            g_kadisp_page_cache[page][col + 5] = 0xFF;
        }

    }

    KaDisp_send_cache_all_pages();

    for (refresh_period_us = 800; refresh_period_us <= 3000; refresh_period_us += 60)
    {
        Uint16 refresh_count;

        //fill odd pages with refresh time info text
        for (page = 1; page < KADISP_MAX_NUMBER_OF_PAGES; page += 2)
        {
            KaDisp_printf(page, "rate: %d us", (Int16)refresh_period_us);
            KaDisp_send_page_cache(page);
        }

        refresh_count = 1200 / fastLog2(refresh_period_us);
        while (--refresh_count > 0)
        {
            // now it's not drawing anything
            // it just changing the display window position.
            // it moves to consecutive page pairs: (0&1), (2&3), (4%5), (6%7)
            Uint8 page_to_be_shown = (refresh_count * 2) % SSD1780_PAGE_COUNT;
            KaDisp_move_window_to_page(page_to_be_shown);
            USBSTK5515_waitusec(refresh_period_us);
        }
    }
}

void KaDisp_test_07(void)
{
    /* This test shows scrolling setup options. */

    Int16 times = 1024;
    KaDisp_init();

//    SSD1780_setup_default_scrolling();
//    SSD1780_setup_vert_and_hor_first_line_scrolling();
//    SSD1780_setup_simple_horizontal_scrolling();
    KaDisp_scroll_vertical();

    KaDisp_printf(0, "This is");
    KaDisp_printf(1, "kamichal's");
    KaDisp_printf(2, "implementation");
    KaDisp_printf(3, "of the OSD%d", 9616);
    KaDisp_printf(4, "display");
    KaDisp_printf(5, "driver SSD1780");
    KaDisp_printf(6, "On C5515");
    KaDisp_printf(7, "eZ DSP USB STICK.");
    KaDisp_send_cache_all_pages();

    while(--times > 0)
    {
        // do anything
        USBSTK5515_waitusec(10000);
    }
}



void KaDisp_test_pattern(Uint8 page_n)
{
    Uint16 idx = 0;
    Uint16 p = page_n % KADISP_MAX_NUMBER_OF_PAGES;
    g_kadisp_page_cache[p][idx] = SSD1780_SEND_DATA_TOKEN;
    for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx++)
    {
        g_kadisp_page_cache[p][idx] = (idx - 1) & 0xFF;
    }
    KaDisp_send_page_cache(p);
}

