/*
 * alt_main.h
 *
 *  Created on: Oct 17, 2023
 *      Author: iroen
 */

#ifndef INC_ALT_MAIN_H_
#define INC_ALT_MAIN_H_

#include"main.h"

#define NUM_of_ADC_12bit 3
#define BUTTONS_DATA_BUFFER_SIZE 8

#ifdef __cplusplus
extern "C"
{
#endif


int alt_main();
int _write(int file, char *ptr, int len);	//ちゃんとextern"C"で囲まないとリンカから認識されなかった。

#ifdef __cplusplus
}
#endif



#endif /* INC_ALT_MAIN_H_ */
