/*
 * gamepad_analog_input_driver.h
 *
 *  Created on: Oct 28, 2023
 *      Author: iroen
 */

/*このクラスでは、Analog inputのデータを処理し、Gamepad classへ伝える
* 能力
*   -gamepad axisへのアナログ値入力。
*   -アナログ値から、デジタル値へ変換し、gamepad buttonに入力。(joy to button)
*   -中央位置、最大最小位置のキャリブレーション。
*/

#ifndef GAMEPAD_ANALOG_INPUT_DRIVER_H
#define GAMEPAD_ANALOG_INPUT_DRIVER_H

#include"main.h"

class gamepad_analog_input_driver
{
public:
    enum class Axis{
        X,
        Y,
        Z,
        Rx,
        Ry,
        Rz
    };
    gamepad_analog_input_driver(ADC_HandleTypeDef* hadc);
    virtual ~gamepad_analog_input_driver();

    //functions
    //setter 関数
    void set_adc_channel();
    uint32_t get_ADC_Value();

    //values
    uint32_t ADC_val[4];

private:
    typedef struct ADCConfig {
        ADC_HandleTypeDef* hadc;
        uint32_t channel;
        uint32_t rank;
    }ADC_config_t;

    ADC_config_t adc_configs[4];
};

#endif  /*GAMEPAD_ANALOG_INPUT_DRIVER_H*/