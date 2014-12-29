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

//#include <csl_sar.h>
//#include <csl_intc.h>
//#include <csl_general.h>


#include <kadisp_tests.h>
#include <kairq.h>

/* ------------------------------------------------------------------------ *
 *  main( )                                                                 *
 * ------------------------------------------------------------------------ */

void main(void)
{
    sar_interupt_test();

    //KaDisp_test_01();

    KaDisp_test_05();

    KaDisp_test_04();

    KaDisp_test_03();

    KaDisp_test_02();
}
