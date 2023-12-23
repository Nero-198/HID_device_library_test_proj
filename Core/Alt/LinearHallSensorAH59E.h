/*
 * LinearHallSensorAH59E.h
 *
 *  Created on: Aug 28, 2023
 *      Author: iroen
 */
/*
 * 本クラスはCubeMXで生成された"main.c", "main.h"に依存する。
 * これはError_Handler();を呼び出し事によるものである。
 * この依存性は今後他のエラー処理を実装することによって解消したいと考えている。
 * 解消されない可能性もあるので注意すること。
 * 本クラスの上記の依存性が解消された場合は、このコメントを削除する事。
 *
 * 追記；このクラス、おそらく要らない。何故なら、ホールセンサーの挙動は可変抵抗器と同じだから。
 */

#ifndef INC_LINEARHALLSENSORAH59E_H_
#define INC_LINEARHALLSENSORAH59E_H_
#include "main.h"

class LinearHallSensor_AH59E{
public:
    LinearHallSensor_AH59E(ADC_HandleTypeDef* hadc); // コンストラクタでADC構造体のポインタを受け取る
    virtual ~LinearHallSensor_AH59E();
    /*variables*/
    uint32_t value;

    /*functions*/
    uint32_t getVal(); // AE59Eの値を読み取る
    uint32_t setrange();

private:
    ADC_HandleTypeDef* m_hadc; // ADC設定と状態を保持する構造体のポインタ
};

#endif /* INC_LINEARHALLSENSORAH59E_H_ */
