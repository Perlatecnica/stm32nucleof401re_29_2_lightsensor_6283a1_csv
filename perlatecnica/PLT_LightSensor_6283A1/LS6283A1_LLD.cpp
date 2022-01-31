#include "LS6283A1_LLD.h"


LS6283A1_LLD* LS6283A1_LLD::instance = 0;

LS6283A1_LLD* LS6283A1_LLD::getInstance() {
    if (instance == 0)
    	instance = new LS6283A1_LLD;
    return instance;
}

LS6283A1_LLD::LS6283A1_LLD(){}


/**
  * @brief Initializes the light sensor.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::init(void){
	  status = VD6283A1_LIGHT_SENSOR_Init(LIGHT_SENSOR_INSTANCE_0);
	  return status;
}

/**
  * @brief Deinitializes the light sensor.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::deInit(){
	return VD6283A1_LIGHT_SENSOR_Init(LIGHT_SENSOR_INSTANCE_0);
}

/**
  * @brief Read the light sensor device ID.
  * @param pId    Pointer to the device ID.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::readID(uint32_t *pId){
	return VD6283A1_LIGHT_SENSOR_ReadID(LIGHT_SENSOR_INSTANCE_0, pId);
}


/**
  * @brief Set the exposure time.
  * @param ExposureTime    New exposure time to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::setExposureTime(uint32_t _exposure){
	return VD6283A1_LIGHT_SENSOR_SetExposureTime(LIGHT_SENSOR_INSTANCE_0, _exposure);
}

/**
  * @brief Get the exposure time.
  * @param pExposureTime    Pointer to the current exposure time value.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::getExposureTime(uint32_t *pExposureTime){
	return VD6283A1_LIGHT_SENSOR_GetExposureTime(LIGHT_SENSOR_INSTANCE_0, pExposureTime);
}

/**
  * @brief Set the gain of a channel.
  * @param Channel    Device channel.
  * @param Gain    New gain to be applied on the provided channel.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::setGain(uint8_t pChannel, uint32_t pGain){
	return VD6283A1_LIGHT_SENSOR_SetGain(LIGHT_SENSOR_INSTANCE_0, pChannel, pGain);
}

/**
  * @brief Get the current gain of a channel.
  * @param Channel    Device channel.
  * @param pGain    Pointer to the current gain value.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::getGain(uint8_t pChannel, uint32_t *pGain){
	return VD6283A1_LIGHT_SENSOR_GetGain(LIGHT_SENSOR_INSTANCE_0, pChannel, pGain);
}

/**
  * @brief Set the inter-measurement time.
  * @param InterMeasurementTime    Inter-measurement to be applied.
  * @note This should be configured only when using the device in continuous mode.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::setInterMeasurementTime(uint32_t pInterMeasurementTime){
	return VD6283A1_LIGHT_SENSOR_SetInterMeasurementTime(LIGHT_SENSOR_INSTANCE_0, pInterMeasurementTime);
}

/**
  * @brief Get the inter-measurement time.
  * @param pInterMeasurementTime    Pointer to the current inter-measurement time.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::getInterMeasurementTime(uint32_t *pInterMeasurementTime){
	return VD6283A1_LIGHT_SENSOR_GetInterMeasurementTime(LIGHT_SENSOR_INSTANCE_0, pInterMeasurementTime);
}

/**
  * @brief Start the light measurement on all channels.
  * @param Mode    Measurement mode (continuous or single-shot)
  * @retval BSP status
  */
int32_t LS6283A1_LLD::start(uint8_t pMode){
	return VD6283A1_LIGHT_SENSOR_Start(LIGHT_SENSOR_INSTANCE_0, pMode);
}

/**
  * @brief Stop the measurement on all channels.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::stop(){
	return VD6283A1_LIGHT_SENSOR_Stop(LIGHT_SENSOR_INSTANCE_0);
}

/**
  * @brief Start flicker capture.
  * @param Channel    The channel that will be used for flicker detection.
  * @param OutputMode    Analog or Digital depending on the hardware configuration.
  * @note The application must call VD6283A1_LIGHT_SENSOR_Start before calling this function.
  * @warning The flicker can be started only on one channel at a time.
  * @note Calling this function will enable ALS capture on all the other channels.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::startFlicker(uint8_t pChannel, uint8_t pOutputMode){
	return VD6283A1_LIGHT_SENSOR_StartFlicker(LIGHT_SENSOR_INSTANCE_0, pChannel, pOutputMode);
}

/**
  * @brief Stop flicker capture.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::stopFlicker(){
	return VD6283A1_LIGHT_SENSOR_StopFlicker(LIGHT_SENSOR_INSTANCE_0);
}

/**
  * @brief Returns the measurement values for all the channels.
  * @param pResult    Pointer to an array which will be filled with the values of each channel.
  * @note The array size must match the number of channels of the device.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::getValues(uint32_t *pResult){
	return VD6283A1_LIGHT_SENSOR_GetValues(LIGHT_SENSOR_INSTANCE_0, pResult);
}

/**
  * @brief Enable and disable control features.
  * @param ControlMode    Feature to be be enabled or disabled.
  * @param Value    Value to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::setControlMode(uint32_t pControlMode, uint32_t pValue){
	return VD6283A1_LIGHT_SENSOR_SetControlMode(LIGHT_SENSOR_INSTANCE_0, pControlMode, pValue);
}

/**
  * @brief Get saturation value from the device.
  * @param pValue    Pointer to the variable where the saturation value is stored.
  * @warning The saturation value is reset when the device is stopped.
  * @retval BSP status
  */
int32_t LS6283A1_LLD::getSaturation(uint32_t *pValue){
	return VD6283A1_LIGHT_SENSOR_GetSaturation(LIGHT_SENSOR_INSTANCE_0, pValue);
}
