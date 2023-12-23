/*
 * gamepad.cpp
 *
 *  Created on: Oct 28, 2023
 *      Author: iroen
 */

#include <gamepad.h>
#include "usb_device.h"


gamepad::gamepad()
{
}

gamepad::~gamepad()
{
}

gamepad::status gamepad::init_gamepad(){
	//matrix_to_HID_buttonから行列の数を取得
	size_t input_num = 0;
	size_t output_num = 0;
	uint8_t HID_button = 0;

	if (!digital_input.matrix_to_HID_button.empty()) {
	// 行数を取得
		input_num = digital_input.matrix_to_HID_button.size();

    	// 最初の行が存在する場合のみ列数を取得
		if (!digital_input.matrix_to_HID_button[0].empty()) {
			output_num = digital_input.matrix_to_HID_button[0].size();
		}
	}
	std::pair<size_t, size_t> matrix_size = digital_input.get_matrix_to_HID_button_size();
	if (matrix_size.first != input_num)  // 行数が一致するかアサーション
	{
		return ERROR;
	}
	if (matrix_size.second != output_num)// 列数が一致するかアサーション
	{
		return ERROR;
	}

	for (uint8_t i = 0; i < input_num; i++)
	{
		for (uint8_t o = 0; o < output_num; i++)
		{
			HID_button = digital_input.matrix_to_HID_button[i][o];
			digital_input.set_matrix_to_HID_button(i, o, HID_button);
		}
	}
	return OK;
}

void gamepad::setButton(GPIO_TypeDef* port, uint16_t pin, uint8_t HID_button){
	digital_input.setButton(port, pin, HID_button);	//gamepad_digital_input_driver digital_input;
}

void gamepad::set_input_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t input_num){
	digital_input.set_input_key_matrix(port, pin, input_num);
}

void gamepad::set_output_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t output_num){
	digital_input.set_output_key_matrix(port, pin, output_num);
}

uint8_t gamepad::SendUSB(USBD_HandleTypeDef *pdev, gamepad::gamepadHID_t *gamepadHID, uint16_t len){
	uint8_t *report = (uint8_t *)gamepadHID;
	return (USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len));
}
