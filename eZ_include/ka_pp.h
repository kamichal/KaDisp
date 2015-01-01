/*
 * ka_pp.h
 *
 *  Created on: Dec 28, 2014
 *      Author: kamichal
 */

#ifndef KA_PP_H_
#define KA_PP_H_

//#define fail_ocurence "in"#__LINE__"\n"#__FUNCTION__

#define expect_match_ret_msg(fcn_call, exp_val, err_msg, ret_val) \
    if (fcn_call != exp_val) \
    { printf("\n [T:] "err_msg"\n unexpected: "#fcn_call" !=  "#exp_val"\n f: %s\n l: %s\n f: %s\n",\
             __FILE__, \
             __LINE__, \
             __FUNCTION__); \
    return ret_val; }

#define expect_match(fcn_call, exp_val, ret_val) expect_match_ret_msg(fcn_call, exp_val, "", ret_val)

#define k_abs(a)                (a >= 0) ? a : -a
#define k_min(a,b)              (a < b) ? a : b
#define k_max(a,b)              (a > b) ? a : b
#define k_min_max(a,min,max)    ((a < min) ? min : (a>max ? max : a))



#endif /* KA_PP_H_ */
