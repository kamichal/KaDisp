/*
 * kadisp_tests.h
 *
 *  Created on: Dec 29, 2014
 *      Author: kamichal
 */

#ifndef KADISP_TESTS_H_
#define KADISP_TESTS_H_

#include <usbstk5515.h>
#include <usbstk5515_i2c.h>



/* SAMPLE USAGE:
 * #include

 * void main(void)
{
    KaDisp_test_run_all();
}
 * */


void KaDisp_test_run_all(void);

void KaDisp_test_01(void);
void KaDisp_test_02(void);
void KaDisp_test_03(void);
void KaDisp_test_04(void);
void KaDisp_test_05(void);
void KaDisp_test_06(void);

void KaDisp_test_pattern(Uint8 page_n);




#endif /* KADISP_TESTS_H_ */
