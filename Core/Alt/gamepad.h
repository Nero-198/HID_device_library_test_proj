/*
 * gamepad.h
 *
 *  Created on: Oct 28, 2023
 *      Author: iroen
 */

#ifndef GAMEPAD_H
#define GAMEPAD_H
#include "main.h"
#include "gamepad_analog_input_driver.h"
#include "gamepad_digital_input_driver.h"
#include <usbd_customhid.h>
#include <vector>

#ifdef  CUSTOM_HID_EPIN_SIZE
#undef  CUSTOM_HID_EPIN_SIZE
#define CUSTOM_HID_EPIN_SIZE                         0x08U
#endif

class gamepad
{
public:
    gamepad();
    ~gamepad();
//------------------Instance------------------
    gamepad_digital_input_driver digital_input;
    gamepad_analog_input_driver analog_input(ADC_HandleTypeDef* hadc);

//------------------enum------------------
    typedef enum
    {
        OK = 0,
        ERROR = 1,
    }status;

    typedef struct HID_gamepad_struct{
        uint8_t buttons[BUTTONS_DATA_BUFFER_SIZE];
        int8_t axis[NUM_of_ADC_12bit * 2];
    }gamepadHID_t;
    //------------------USBD Data List------------------
    uint8_t USBD_data_tx_buffer[8]; // この配列にmemcpyして送信する。


    //---------------func----------------
    gamepad::status init_gamepad(); //初期化関数。マトリクスの数などの設定を行う。
    //--------setter-------
    //実際のボタンとHID_gamepadのボタンの対応付け
    void setButton(GPIO_TypeDef* port, uint16_t pin, uint8_t HID_button); //butoon = pin name or pin number
    void set_input_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t input_num);
    void set_output_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t output_num);

    //実際のアナログ入力とHID_gamepadのアナログ入力の対応付け
    void setAxis(uint8_t axis, uint8_t HID_axis); //axis = adc pin name or adc pin number
    void getbutton();
    void getaxis();

    uint8_t SendUSB(USBD_HandleTypeDef *pdev, uint8_t *USBD_data_tx_buffer, uint16_t len);


private:
};

#endif /*GAMEPAD_H*/
