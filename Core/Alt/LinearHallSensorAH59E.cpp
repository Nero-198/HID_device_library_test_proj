/*
 * LinearHallSensorAH59E.cpp
 *
 *  Created on: Aug 28, 2023
 *      Author: iroen
 */

#include <LinearHallSensorAH59E.h>


LinearHallSensor_AH59E::LinearHallSensor_AH59E(ADC_HandleTypeDef* hadc)
: m_hadc(hadc) // コンストラクタイニシャライザでメンバ変数を初期化
{
    // 必要に応じて、ここでADCの追加設定や初期化を行う
	  if (HAL_ADCEx_Calibration_Start(m_hadc) !=  HAL_OK)	//ADCを自動でキャリぶれーとしてくれる
	  {
	    Error_Handler();
	  }
}

LinearHallSensor_AH59E::~LinearHallSensor_AH59E() {
	// TODO Auto-generated destructor stub
}

uint32_t LinearHallSensor_AH59E::getVal(){
	if(HAL_ADC_Start(m_hadc) != HAL_OK){
		Error_Handler();
		return 0;
	}
	if(HAL_ADC_PollForConversion(m_hadc, 10) != HAL_OK){
		Error_Handler();
		return 0;
	}
	LinearHallSensor_AH59E::value = HAL_ADC_GetValue(m_hadc);
	return HAL_ADC_GetValue(m_hadc);
}
