#include "LightSensor.h"

static const char *AlsChannelStr[] = {
		  [LIGHT_SENSOR_RED_CHANNEL] = "RED",
		  [LIGHT_SENSOR_VISIBLE_CHANNEL] = "VISIBLE",
		  [LIGHT_SENSOR_BLUE_CHANNEL] = "BLUE",
		  [LIGHT_SENSOR_GREEN_CHANNEL] = "GREEN",
		  [LIGHT_SENSOR_IR_CHANNEL] = "IR",
		  [LIGHT_SENSOR_CLEAR_CHANNEL] = "CLEAR"
		};

LightSensor* LightSensor::instance = 0;

LightSensor* LightSensor::getInstance() {
    if (instance == 0)
    	instance = new LightSensor;
    return instance;
}

LightSensor::LightSensor(){
	init();
}

int32_t LightSensor::updateValues(){
	return status = lslld->getValues(AlsResults);
}

uint32_t* LightSensor::getBuffer(){
	return AlsResults;
}
/*
 * @brief print values for all channels
 */
void LightSensor::show()
{
	uint8_t channel;
	uint32_t current_gain;
	uint32_t current_exposure;
	uint32_t current_imt; /* inter-measurement time */

	/* start ALS capture on all channels in continuous mode */
	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);


	while (true)
	{
		status = lslld->getValues(AlsResults);

		if (status == BSP_ERROR_NONE)
		{
			/* display ALS values */
			for (channel = 0; channel < LIGHT_SENSOR_MAX_CHANNELS; channel++)
			{
				if (is_dark_enabled && (channel == LIGHT_SENSOR_VISIBLE_CHANNEL))
					printf("Channel %u - %8s", channel + 1, "DARK");
				else
					printf("Channel %u - %8s", channel + 1, AlsChannelStr[channel]);

				printf("\tValue: %lu\r\n", (unsigned long)AlsResults[channel]);
			}
			printf("\r\n\r\n");
		}
	}
}

/*
 * @brief divide exposure time by 2
 */
void LightSensor::decrease_exposure()
{
  uint32_t current_exposure;
  lslld->stop();
  lslld->getExposureTime(&current_exposure);
  lslld->setExposureTime(current_exposure >> 1);
  lslld->getExposureTime(&current_exposure);
  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
  printf("\r\nExposure set to %lu us\r\n", (unsigned long)current_exposure);
}

/*
 * @brief multiply exposure time by 2
 */
void LightSensor::increase_exposure()
{
  uint32_t current_exposure;

  lslld->stop();
  lslld->getExposureTime(&current_exposure);
  lslld->setExposureTime(current_exposure << 1);
  lslld->getExposureTime(&current_exposure);
  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
  printf("\r\nExposure set to %lu us\r\n", (unsigned long)current_exposure);
}

/*
 * @brief set exposure time in us
 */
void LightSensor::setExposure(int32_t pExposure_us){
	uint32_t current_exposure;
	lslld->stop();
	lslld->setExposureTime(pExposure_us);
	lslld->getExposureTime(&current_exposure);
	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
	printf("\r\nExposure set to %lu us\r\n", (unsigned long)current_exposure);
}

/*
 * @brief divide inter-measurement time by 2
 */
void LightSensor::decrease_inter_measurement()
{
  uint32_t current_imt;
  uint32_t next_imt;

  lslld->stop();
  lslld->getInterMeasurementTime(&current_imt);
  next_imt = (current_imt == 20500) ? 0 : (current_imt >> 1);
  lslld->setInterMeasurementTime(next_imt);
  lslld->getInterMeasurementTime(&current_imt);
  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
  printf("\nInter measurement set to %lu us\n", (unsigned long)current_imt);
}

/*
 * @brief multiply inter-measurement time by 2
 */
void LightSensor::increase_inter_measurement()
{
  uint32_t current_imt;
  uint32_t next_imt;

  lslld->stop();
  lslld->getInterMeasurementTime(&current_imt);
  next_imt = (current_imt) ? (current_imt << 1) : 20500; //20.5 * 1000 = 20500 us
  lslld->setInterMeasurementTime(next_imt);
  lslld->getInterMeasurementTime(&current_imt);
  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
  printf("\nInter measurement set to %lu us\n", (unsigned long)current_imt);
}

/*
 * @brief set inter-measurement time Inter measurement period 256 steps of 20.5 ms (from 0 ms to 5.22 s)
 */
void LightSensor::setIntermeasurement(uint32_t pImt_us){
	uint32_t current_imt;
	lslld->stop();
	lslld->setInterMeasurementTime(pImt_us);
	lslld->getInterMeasurementTime(&current_imt);
	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
	printf("\nInter measurement set to %lu us\n", (unsigned long)current_imt);
}

/*
 * @brief divide gain by 2 on all channels
 */
void LightSensor::decrease_gain()
{
  uint8_t c;
  uint32_t current_gain;

  lslld->stop();

  printf("\r\n");
  for (c = 0; c < LIGHT_SENSOR_MAX_CHANNELS; c++)
  {
	lslld->getGain(c, &current_gain);
	lslld->setGain(c, current_gain >> 1);
	lslld->getGain(c, &current_gain);
    printf("Channel %u gain set to", c);
    display_gain(current_gain);
  }

  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
}

/*
 * @brief multiply gain by 2 on all channels
 */
void LightSensor::increase_gain()
{
  uint8_t c;
  uint32_t current_gain;

  printf("\r\n");
  lslld->stop();

  for (c = 0; c < LIGHT_SENSOR_MAX_CHANNELS; c++)
  {
	lslld->getGain(c, &current_gain);
	lslld->setGain(c, current_gain << 1);
	lslld->getGain(c, &current_gain);
    printf("Channel %u gain set to", c);
    display_gain(current_gain);
    printf("\r\n");
  }

  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
}

/*
 * @brief set gain on all channels
 */
void LightSensor::setGain(uint32_t pGain){
	uint8_t c;
	uint32_t current_gain;

	printf("\r\n");
	lslld->stop();

	for (c = 0; c < LIGHT_SENSOR_MAX_CHANNELS; c++)
	{
		lslld->setGain(c, pGain);
		lslld->getGain(c, &current_gain);
		printf("Channel %u gain set to", c);
		display_gain(current_gain);
		printf("\r\n");
	}

	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
}

/*
 * @brief set gain on specific channel
 */
void LightSensor::setGainOnChannel(uint8_t pC, uint32_t pGain){
	uint8_t c;
	uint32_t current_gain;

	printf("\r\n");
	lslld->stop();
	lslld->setGain(pC, pGain);
	lslld->getGain(c, &current_gain);
	printf("Channel %u gain set to", c);
	display_gain(current_gain);
	printf("\r\n");

	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
}

/*
 * @brief enable/disable dark channel
 */
void LightSensor::toggle_dark_output()
{
  is_dark_enabled = !is_dark_enabled;
  lslld->stop();
  lslld->setControlMode(LIGHT_SENSOR_CTRL_DARK, is_dark_enabled);
  lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
  printf("\r\nOutput dark enable is now %u\r\n", is_dark_enabled);
}

/*
 * @brief normalize, convert and dislay gain
 */
void LightSensor::display_gain(uint32_t gain)
{
  uint32_t g = (gain * 100) / 256;

  printf(" %3lu.%02lu\r\n", g / 100, (g % 100));
}


/*********** PRIVATE METHODS ***********/
void LightSensor::init(){
	uint8_t channel;
	uint32_t current_gain;
	uint32_t current_exposure;
	uint32_t current_imt; /* inter-measurement time */

	lslld = LS6283A1_LLD::getInstance();

	printf("\r\nVD6283TX ALS Values Example\r\n");

	status = VD6283A1_LIGHT_SENSOR_Init(LIGHT_SENSOR_INSTANCE_0);

	if (status)
	{
		printf("\r\nVD6283A1_LIGHT_SENSOR_Init failed\r\n");
		while(1);
	}
	else{
		printf("\r\nVD6283A1_LIGHT_SENSOR_Init OK!\r\n");
	}


	/* initialize exposure time */
	lslld->setExposureTime(100000); /* microseconds */
	lslld->getExposureTime(&current_exposure);
	printf("Exposure set to %lu us\r\n", (unsigned long)current_exposure);

	/* initialize gains */
	for (channel = 0; channel < LIGHT_SENSOR_MAX_CHANNELS; channel++)
	{
		lslld->setGain(channel, 256);
		lslld->getGain(channel, &current_gain);
		printf("Channel %d gain set to", channel + 1);
		display_gain(current_gain);
	}

	/* initialize inter measurement time */
	lslld->setInterMeasurementTime(500000); /* 100 ms */
	lslld->getInterMeasurementTime(&current_imt);

	/* start ALS capture on all channels in continuous mode */
	lslld->start(LIGHT_SENSOR_MODE_CONTINUOUS);
}
