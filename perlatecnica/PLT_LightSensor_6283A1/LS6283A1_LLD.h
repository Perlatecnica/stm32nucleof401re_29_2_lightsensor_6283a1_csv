

#ifndef PLT_LIGHTSENSOR_6283A1_LLD
#define PLT_LIGHTSENSOR_6283A1_LLD

#include "mbed.h"
#include "6283a1_light_sensor.h"

#define LIGHT_SENSOR_INSTANCE_0 (0U) // It must be singleton

class LS6283A1_LLD
{
	public:
		static LS6283A1_LLD* getInstance();

		void show();
		int32_t init(void);
		int32_t deInit();
		int32_t readID(uint32_t *pId);
		int32_t setExposureTime(uint32_t _exposure);
		int32_t getExposureTime(uint32_t *pExposureTime);
		int32_t setGain(uint8_t pChannel, uint32_t pGain);
		int32_t getGain(uint8_t pChannel, uint32_t *pGain);
		int32_t setInterMeasurementTime(uint32_t pInterMeasurementTime);
		int32_t getInterMeasurementTime(uint32_t *pInterMeasurementTime);
		int32_t start(uint8_t Mode);
		int32_t stop();
		int32_t startFlicker(uint8_t pChannel, uint8_t pOutputMode);
		int32_t stopFlicker();
		int32_t getValues(uint32_t *pResult);
		int32_t setControlMode(uint32_t pControlMode, uint32_t pValue);
		int32_t getSaturation(uint32_t *pValue);

	protected:
		LS6283A1_LLD();

	private:
		static LS6283A1_LLD* instance;
		int32_t status;
		uint32_t current_exposure = 100000; // Default value
};



#endif /* PLT_LIGHTSENSOR_6283A1_LLD */
