/*
 * gamepad_digital_input_driver.h
 *
 *  Created on: Oct 31, 2023
 *      Author: iroen
 */

#ifndef GAMEPAD_DIGITAL_INPUT_DRIVER_H
#define GAMEPAD_DIGITAL_INPUT_DRIVER_H

#include "main.h"
#include "alt_main.h"
#include <vector>

class gamepad_digital_input_driver
{
public:
    gamepad_digital_input_driver(/* args */);
    ~gamepad_digital_input_driver();

    uint8_t HID_button[BUTTONS_DATA_BUFFER_SIZE]; //USB_HIDに渡す実際のデータ配列// 超重要存在
    std::vector<std::vector<uint8_t>> matrix_to_HID_button; // 横列(行)はinput、縦列(列)はoutput。マトリクスの入力とHID_gamepadのボタンの対応付けを行う。

    uint8_t init_gamepad_digital_input_driver(); //初期化関数。マトリクスの数などの設定を行う。
    void readButton();
    void setButton(GPIO_TypeDef* port, uint16_t pin, uint8_t HID_button); //butoon = pin name or pin number
    void set_input_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t input_num);
    void set_output_key_matrix(GPIO_TypeDef* port, uint16_t pin, uint8_t output_num);
    void set_matrix_to_HID_button(uint8_t input_num, uint8_t output_num, uint8_t HID_button);

    //----struct getter----
    size_t get_button_size();
    size_t get_input_key_matrix_size();
    size_t get_output_key_matrix_size();
    std::pair<size_t, size_t> get_matrix_to_HID_button_size()const;


private:
//実際のボタンとHID_gamepadのボタンの対応付けの構造体
    typedef struct button
    {
        GPIO_TypeDef* port;
        uint16_t pin;
        uint8_t HID_button; //HID_gamepadのボタン番号.  1から始まる整数. 被ってはいけない。
    } button_t;
     std::vector<button_t> buttons; // ボタン情報を保持するための動的配列

//マトリクスの入力の構造体。初期設定にしか使わない。
    typedef struct matrix_input
    {
        GPIO_TypeDef* port;
        uint16_t pin;
        uint8_t input_num; //マトリクスの入力の番号。0から始まる整数。被ってはいけない。
    } input_key_matrix_t;
    std::vector<input_key_matrix_t> input_key_matrix; // ボタン情報を保持するための動的配列

//マトリクスの出力の構造体。初期設定にしか使わない。
    typedef struct matrix_output
    {
        GPIO_TypeDef* port;
        uint16_t pin;
        uint8_t output_num; //マトリクスの出力の番号。0から始まる整数。被ってはいけない。
    } output_key_matrix_t;
    std::vector<output_key_matrix_t> output_key_matrix; // ボタン情報を保持するための動的配列

    //実際のボタンとマトリクスの対応付けの構造体
    typedef struct keyMatrix
    {
        input_key_matrix_t input;
        output_key_matrix_t output;
        uint8_t HID_button; //HID_gamepadのボタン番号.  1から始まる整数. 被ってはいけない。
    } matrix_t;
    std::vector<std::vector<matrix_t>> key_matrix; // ボタン情報を保持するための動的配列

    //実際のボタンｔとHID_gamepadのボタンの対応付け
    uint8_t readButton(uint8_t button);
};





#endif /*GAMEPAD_DIGITAL_INPUT_DRIVER_H*/