/*
 * Accelerometer.h
 *
 *  Created on: Jul 12, 2022
 *      Author: Almaz
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "I2CDevice.h"
#include "BaseDevice.h"

namespace IntroSatLib {


class Accelerometer : virtual public BaseDevice {

private:

	static const uint8_t BASE_ADDRESS = 0x68;
	static constexpr float _rawg = 16384.0;

	enum RegisterMap
	{
		ACCEL_CONFIG = 0x1C,
		ACCEL_CONFIG_2,
		ACCEL_XOUT_H = 0x3B,
		ACCEL_XOUT_L,
		ACCEL_YOUT_H,
		ACCEL_YOUT_L,
		ACCEL_ZOUT_H,
		ACCEL_ZOUT_L,
	};

	I2CDevice _i2c;
	uint8_t _sensitivity = 0;

	uint8_t GetRegister(RegisterMap reg);
	void SetRegister(RegisterMap reg, uint8_t value);

public:

	enum Scale
	{
		twoG = 0,
		fourG,
		eightG,
		sixteenG
	};
	enum FilterBandwidth
	{
		F1046 = 8,
		F0218 = 0,
		F0218b,
		F0099,
		F0045,
		F0021,
		F0010,
		F0005,
		F0420
	};

#ifndef ARDUINO
	Accelerometer(I2C_HandleTypeDef *hi2c, uint8_t address = BASE_ADDRESS);
#else
	Accelerometer(TwoWire &hi2c, uint8_t address = BASE_ADDRESS);
#endif
	Accelerometer(const Accelerometer& other);
	Accelerometer& operator=(const Accelerometer& other);
	Accelerometer(Accelerometer&& other);
	Accelerometer& operator=(Accelerometer&& other);

	void Init();
	void Init(Scale sensitivity);
	void Init(Scale sensitivity, FilterBandwidth filter);

	void SetScale(Scale sensitivity);
	void SetFilter(FilterBandwidth filter);

	int16_t RawX();
	int16_t RawY();
	int16_t RawZ();

	float X();
	float Y();
	float Z();

	~Accelerometer();
};

} /* namespace IntroSatLib */

#endif /* ACCELEROMETER_H_ */
