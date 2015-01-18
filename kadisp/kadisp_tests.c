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

void KaDisp_test_run_all(void)
{
    Uint16 i;

    /* Initialize BSL */
    USBSTK5515_init();
    /* Initialize I2C */
    USBSTK5515_I2C_init();

#if specific_test_only
    while (1)
    {
        printf("KaDisp_test_06();\n");
        KaDisp_test_06();
    }

#else
    for (i = 0; i < 2; i++)
    {
        KaDisp_test_06();
        KaDisp_test_05();
        KaDisp_test_04();
        KaDisp_test_03();
        KaDisp_test_02();
        KaDisp_test_01();
    }
#endif
}

void KaDisp_test_01(void)
{
    printf("\n KaDisp_test_01() \n");

    KaDisp_init();

    KaDisp_printf(0, "This is");
    KaDisp_printf(1, "kamichal's");
    KaDisp_printf(2, "implementation");
    KaDisp_printf(3, "of the OSD%d", 9616);
    KaDisp_printf(4, "display");
    KaDisp_printf(5, "driver SSD1780");
    KaDisp_printf(6, "on C%d", 5515);
    KaDisp_printf(7, "eZdsp.");

    KaDisp_send_cache_all_pages();

    {
        Uint8 pos = 0;
        Int8 times = 3;

        do
        {
            //move display window around ("manual" scrolling)
            SSD1780_set_vertical_offset((Uint8) pos);
            USBSTK5515_waitusec(20000);

            if (pos % 0x3F == 0x3F - 12)
            {
                KaDisp_printf(7, "eZdsp.%10d", times--);
                KaDisp_send_page_cache(7);
            }
            pos++;
        } while (times >= 0);
    }
}

void KaDisp_test_02(void)
{
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
    } while (times < 0xF000);
}

void KaDisp_test_03(void)
{
    Int16 times = 0;
    const Int16 max_count = 1024;
    Uint16 idx;

    KaDisp_init();

    g_page_cache[0][0] = SSD1780_SEND_DATA;

    for (idx = 1; idx < fastLog2(max_count); idx += 2)
    {
        g_page_cache[0][idx] = 0x02;
        g_page_cache[0][idx + 1] = 0x02;

    }
    KaDisp_send_page_cache(0);

    KaDisp_printf(1, "binary counter");

    KaDisp_send_page_cache(1);

    while (times < max_count) // run as fast as you can
    {
        Int16 tmp = times;
        for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx += 6)
        {
            if (tmp & 0x1)
            {
                g_page_cache[0][idx] = 0x00;
                g_page_cache[0][idx + 1] = 0x7C + 1;
                g_page_cache[0][idx + 2] = 0x7C;
                g_page_cache[0][idx + 3] = 0x7C;
                g_page_cache[0][idx + 4] = 0x70;
                g_page_cache[0][idx + 5] = 0x00;
            }
            else
            {
                g_page_cache[0][idx] = 0x00;
                g_page_cache[0][idx + 1] = 0x08;
                g_page_cache[0][idx + 2] = 0x08;
                g_page_cache[0][idx + 3] = 0x08;
                g_page_cache[0][idx + 4] = 0x08;
                g_page_cache[0][idx + 5] = 0x00;
            }
            tmp >>= 1;
        }

        times++;
        KaDisp_send_page_cache_range(0, 0, 6 * fastLog2(times));
    }
}

void KaDisp_DrawHorizontalBar(Uint8 page, Uint8 bar_w)
{
    Uint16 idx;
    page = page % KADISP_MAX_NUMBER_OF_PAGES;

    for (idx = 1; idx < bar_w + 1; idx += 2)
    {
        g_page_cache[page][idx] = 0x7C;
        g_page_cache[page][idx + 1] = 0x7C + 1;
    }
    for (idx = bar_w + 1; idx < KADISP_CACHE_LINE_LGH; idx += 2)
    {
        g_page_cache[page][idx] = 0x00;
        g_page_cache[page][idx + 1] = 0x00;
    }
}

void KaDisp_test_04(void)
{
    Int16 width = 0;

    KaDisp_init();

    KaDisp_printf(1, "bar");
    KaDisp_send_page_cache(1);

    g_page_cache[0][0] = SSD1780_SEND_DATA;

    while (width < 128)
    {
        KaDisp_DrawHorizontalBar(0, width);
        KaDisp_send_page_cache(0);

        KaDisp_printf(1, "bar width: %d", width);
        KaDisp_send_page_cache(1);

        USBSTK5515_waitusec(10000);
        width++;

    }
}
void KaDisp_test_05(void)
{
    Int16 times = 0;

    KaDisp_init();

    KaDisp_printf(1, "grayscale ?");
    KaDisp_send_page_cache(1);

    g_page_cache[0][0] = SSD1780_SEND_DATA;

    while (times < 0x12)
    {
        Uint8 i;

        for (i = 0; i < times % 64; i++)
        {
            g_page_cache[0][i + 1] = 0xFF;
        }
        for (i = times % 64; i < KADISP_CACHE_LINE_LGH; i++)
        {
            g_page_cache[0][i + 1] = 0x00;
        }
        KaDisp_send_page_cache(0);

        //USBSTK5515_waitusec(10000);
        times++;

    }
}

void KaDisp_test_06(void)
{

    Uint16 idx;
    Uint16 page;
    Uint8 depth = 8;

    KaDisp_init();

    SSD1780_send_cmd_val(SSD1780_SET_MULTIPLEX_RATIO, 0x32);   // 0xA8, default: 0x3F, gives 8 pages

    for (page = 0; page < depth; page++)
    {

        g_page_cache[page][0] = SSD1780_SEND_DATA;
        for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx += 4)
        {
            Uint8 pageMark = (1 << ((8 * page) / depth + 2)) - 1;

            if ((idx % 64) > 55)
                pageMark &= 0xAA;

            g_page_cache[page][idx] = pageMark;
            g_page_cache[page][idx + 1] = pageMark;
            g_page_cache[page][idx + 2] = pageMark;
            g_page_cache[page][idx + 3] = pageMark;
        }
        KaDisp_send_page_cache(page);
    }

    {
        Int16 times;
        Uint16 decade;
        Uint32 period;
        for (decade = 6; decade < 18; decade++)
        {
            period = 1 << decade;
            KaDisp_printf(1, "%d us", (Int32)period);
            KaDisp_printf(3, "%d us", (Int32)period);
            KaDisp_printf(5, "%d us", (Int32)period);
            KaDisp_send_page_cache(1);
            KaDisp_send_page_cache(3);
            KaDisp_send_page_cache(5);

            times = 512;
            while (times-- > 0)
            {
                KaDisp_scroll_window_to_page((Uint8) ((2*times) % depth));
                USBSTK5515_waitusec((Int32)(period));
            }
        }
    }
}

void KaDisp_test_07(void)
{

    Uint16 idx;
    Uint16 page;
    Int16 times = 1024;

    KaDisp_init();

    while (times-- > 0)
    {

        Uint16 usedpage = 0;
        for (page = 0; page < KADISP_MAX_NUMBER_OF_PAGES; page++)
        {
            g_page_cache[usedpage][0] = SSD1780_SEND_DATA;

            for (idx = 1; idx < KADISP_CACHE_LINE_LGH; idx += 6)
            {
                Uint8 pageMark = (1 << (page + 1)) - 1;
                g_page_cache[usedpage][idx] = 0x0;
                g_page_cache[usedpage][idx + 1] = pageMark;
                g_page_cache[usedpage][idx + 2] = pageMark;
                g_page_cache[usedpage][idx + 3] = pageMark;
                g_page_cache[usedpage][idx + 3] = pageMark;
                g_page_cache[usedpage][idx + 4] = pageMark;
                g_page_cache[usedpage][idx + 5] = 0xFF;

            }
            KaDisp_send_page_cache(usedpage);
        }
    }
}

void KaDisp_test_pattern(Uint8 page_n)
{
    Uint16 idx = 0;
    Uint16 p = page_n % KADISP_MAX_NUMBER_OF_PAGES;
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

