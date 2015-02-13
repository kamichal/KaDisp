/*
 * main.c
 *
 *  Created on: Dec 21, 2014
 *      Author: kamichal
 */


#include <stdio.h>
#include <kadisp_tests.h>

/* ------------------------------------------------------------------------ *
 *  main( )                                                                 *
 * ------------------------------------------------------------------------ */

void main(void)
{
    Uint16 i;

    /* Initialize BSL */
    USBSTK5515_init();
    /* Initialize I2C */
    USBSTK5515_I2C_init();

#if 0 // set 1 to run specific test only
    while (1)
    {
        KaDisp_test_07();
    }
#else

    for (i = 0; i < 2; i++)
    {
        KaDisp_test_01();
        KaDisp_test_02();
        KaDisp_test_03();
        KaDisp_test_04();
        KaDisp_test_05();
        KaDisp_test_06();
        KaDisp_test_07();
    }

#endif

}








