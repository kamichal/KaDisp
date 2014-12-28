/*
 * main.c
 *
 *  Created on: Dec 21, 2014
 *      Author: kamichal
 */

/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 *  at 01-12-2014
 *  This piece of rubbish crap has been refactored
 *  by kamichal (michal.s.kaczmarczyk@gmail.com)
 *
 */


#include <stdio.h>

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>
//
//#include <csl_sar.h>
//#include <csl_intc.h>
//#include <csl_general.h>


#include "kadisp.h"

/* ------------------------------------------------------------------------ *
 *  main( )                                                                 *
 * ------------------------------------------------------------------------ */

void main(void)
{
    /* Initialize BSL */
    USBSTK5515_init();
    /* Initialize I2C */
    USBSTK5515_I2C_init();
    printf("SYS_EXBUSSEL = %02x\n", SYS_EXBUSSEL);

    KaDisp_init();

#if scroling_test

    Kaprintf(0, "This is");
    Kaprintf(1, "kamichal's");
    Kaprintf(2, "implementation");
    Kaprintf(3, "of the OSD%d", 9616);
    Kaprintf(4, "display");
    Kaprintf(5, "driver SSD1780");
    Kaprintf(6, "on C%d", 5515);
    Kaprintf(7, "eZdsp.");

    KaDisp_send_entire_cache();
   {
        Uint8 pos = 0;
        Uint8 times = 0;

        do
        {

            SSD1780_send_cmd_val(SSD1780_SET_VERTICAL_OFFSET, pos & 0x3F);  // 0xD3

            USBSTK5515_waitusec(50000);
            if (pos % 0x3F == 0)
            {
                Kaprintf(7, "eZdsp.%10d", ++times);
                KaDisp_send_page_cache(7);
                pos = 0;
            }
            pos++;
        } while (1);
    }
#else

#if! licznik
    {
        Uint8 times = 0;

        do // run as fast as you can
        {
            Kaprintf(0, "eZdsp.%10d", ++times);
            KaDisp_send_page_cache(0);
        } while (1);
    }

#endif
#endif

    SW_BREAKPOINT
    ;
}
