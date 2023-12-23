/*
 * alt_main.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: iroen
 */
/*このファイルはcppをCubeMXによるコード生成に対応させるためのコードである。
 * CubeMXはmain.cファイルの生成にしか対応していないため、main.cppを作って運用してしていても途中でペリフェラルの変更等が行いずらい。
 * main.cppに名前を変えたままコード生成を行うと、main.cppの他に新たなmain.cが生まれてしまう。
 * これを避けるため、cppで記述する部分を本ファイルで実装し、main.cでは本ファイルのコードを読み出す形とする。
 * 参照:https://kleinembedded.com/cpp-and-stm32cubemx-code-generation/
 */
/*main.c と同じIncludeを行う。*/
#include <LinearHallSensorAH59E.h>
#include "main.h"
#include "adc.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/*include*/
#include "alt_main.h"
#include <stdio.h>
#include <usbd_customhid.h>
#include <gamepad.h>


int alt_main(){
	/* declaration Instance */
	LinearHallSensor_AH59E hall_1(&hadc1);
	/*Variable*/
	setbuf(stdout, NULL);	//printf用


		//----gamepad setting----
	gamepad gamepad;
	gamepad.setButton(BUTTON_1_GPIO_Port, BUTTON_1_Pin, 1);		//ここでBUTTON_1はMXで設定したピン名
	gamepad.setButton(BUTTON_2_GPIO_Port, BUTTON_2_Pin, 2);

	gamepad.set_input_key_matrix(IN0_GPIO_Port, IN0_Pin, 0);
	gamepad.set_input_key_matrix(IN1_GPIO_Port, IN1_Pin, 1);
	gamepad.set_input_key_matrix(IN2_GPIO_Port, IN2_Pin, 2);
	gamepad.set_output_key_matrix(OUT0_GPIO_Port, OUT0_Pin, 0);
	gamepad.set_output_key_matrix(OUT1_GPIO_Port, OUT1_Pin, 1);
	gamepad.set_output_key_matrix(OUT2_GPIO_Port, OUT2_Pin, 2);

	gamepad.digital_input.matrix_to_HID_button = {	//input_pinとputput_pinとHIDボタンとの対応。//0は何もつながっていない無効なボタンに指定。
		{3, 4, 5},
		{6, 7, 8},
		{9, 10, 0}
	};

	/* initialize ここで初期化処理等を書く  */
	gamepad.init_gamepad();

	while(1){
		/*alt_main loop ここにメイン関数のループを書く。*/
		printf("Value: %lu\r\n", hall_1.getVal());
		HAL_Delay(5);

	}
}


/* func */
/*
 * //printf用 printfの内部でこの処理が要る。参考:https://yukblog.net/stm32cubeide-printf-uart/
 *
 */
int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart1,(uint8_t *)ptr,len,10);
  return len;
}
