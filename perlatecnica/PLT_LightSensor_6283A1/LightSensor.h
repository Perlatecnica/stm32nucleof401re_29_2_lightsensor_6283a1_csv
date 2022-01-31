

#ifndef PLT_6283A1_LIGHTSENSOR_H_
#define PLT_6283A1_LIGHTSENSOR_H_

#include "mbed.h"
#include "LS6283A1_LLD.h"

class LightSensor
{
	public:
		static LightSensor* getInstance();
		void decrease_exposure();
		void increase_exposure();
		void setExposure(int32_t pExposure);
		void decrease_inter_measurement();
		void increase_inter_measurement();
		void setIntermeasurement(uint32_t pExposure);
		void decrease_gain();
		void increase_gain();
		void setGain(uint32_t pGain);
		void setGainOnChannel(uint8_t c, uint32_t pGain);
		void toggle_dark_output();
		void display_gain(uint32_t gain);
		void show();
		int32_t updateValues();
		uint32_t* getBuffer();

	protected:
		LightSensor();

	private:
		LS6283A1_LLD* lslld;
		int32_t status;
		uint8_t is_dark_enabled;
		static LightSensor* instance;
		void init();
		uint32_t AlsResults[VD6283TX_MAX_CHANNELS] = {0};

};





#endif /* PLT_6283A1_LIGHTSENSOR_H_ */
