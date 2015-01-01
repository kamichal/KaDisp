/*
 * kadisp_tests.c
 *
 *  Created on: Dec 29, 2014
 *      Author: kamichal
 */

#include "ka_pp.h"
#include "kadisp.h"
#include "kadisp_tests.h"

//#include <math.h>



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


    for(i = 0; i < 2; i++)
    {
        KaDisp_test_05();
        KaDisp_test_04();
        KaDisp_test_03();
        KaDisp_test_02();
        KaDisp_test_01();
    }
}


void KaDisp_test_01(void)
{
    printf("\n KaDisp_test_01() \n");

    KaDisp_init();

    ka_printf(0, "This is");
    ka_printf(1, "kamichal's");
    ka_printf(2, "implementation");
    ka_printf(3, "of the OSD%d", 9616);
    ka_printf(4, "display");
    ka_printf(5, "driver SSD1780");
    ka_printf(6, "on C%d", 5515);
    ka_printf(7, "eZdsp.");

    KaDisp_send_cache_all_pages();

    {
        Uint8 pos = 0;
        Int8 times = 3;

        do
        {

            //move display window around
            SSD1780_set_vertical_offset((Uint8) pos);
            USBSTK5515_waitusec(20000);

            if (pos % 0x3F == 0x3F - 12)
            {
                ka_printf(7, "eZdsp.%10d", times--);
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

    ka_printf(0, "          frames");
    KaDisp_send_page_cache(0);

    ka_printf(1, "run max fps");
    KaDisp_send_page_cache(1);

    do // run as fast as you can
    {
        ka_printf(0, "%d", ++times);
        KaDisp_send_page_cache_range(0, 0, 40);

        //KaDisp_send_page_cache_range(0, 0, 40);
        //KaDisp_send_page_cache(0);
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

    ka_printf(1, "binary counter");
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

        //KaDisp_send_page_cache(0);
    }
}

void KaDisp_HorizontalBar(Uint8 page, Uint8 bar_w)
{
    Uint16 idx;
    page = page % KADISP_USED_PAGE_NUMBER;

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

    ka_printf(1, "bar");
    KaDisp_send_page_cache(1);

    g_page_cache[0][0] = SSD1780_SEND_DATA;

    while (width < 128)
    {
        KaDisp_HorizontalBar(0, width);
        KaDisp_send_page_cache(0);

        ka_printf(1, "bar width: %d", width);
        KaDisp_send_page_cache(1);

        USBSTK5515_waitusec(10000);
        width++;

    }
}
void KaDisp_test_05(void)
{
    Int16 times = 0;

    KaDisp_init();

    ka_printf(1, "grayscale ?");
    KaDisp_send_page_cache(1);

    g_page_cache[0][0] = SSD1780_SEND_DATA;

    while (times < 0x12)
    {
        Uint8 i;

        for (i = 0; i < times % 64; i++)
        {
            g_page_cache[0][i+1] = 0xFF;
        }
        for (i = times %64 ; i < KADISP_CACHE_LINE_LGH; i++)
        {
            g_page_cache[0][i+1] = 0x00;
        }
        KaDisp_send_page_cache(0);

        //USBSTK5515_waitusec(10000);
        times++;

    }
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

