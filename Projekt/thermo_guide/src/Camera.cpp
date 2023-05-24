#include "Camera.h"

bool Camera::begin() {
    if (i2c_open(i2c_dev, "/dev/i2c-0") < 0) {
        perror("i2c_open() failed");
        return false;
    }

    // enter normal mode
    _pctl.PCTL = AMG88xx_NORMAL_MODE;
    uint8_t a = _pctl.get();
    write8(AMG88xx_PCTL, &a);

    // software reset
    _rst.RST = AMG88xx_INITIAL_RESET;
    a=_rst.get();
    write8(AMG88xx_RST, &a);

    // set to 10 FPS
    _fpsc.FPS = AMG88xx_FPS_10;
    a=_fpsc.get();
    write8(AMG88xx_FPSC, &a);

    usleep(100000);

    return true;
}

/**************************************************************************/
/*!
    @brief  Read Infrared sensor raw values
    @param  buf the array to place the pixels in
    @param  pixels Optional number of pixels to read (up to 64). Default is
   64 pixels. Each pixel value is 12 bits, so it is stored in 2 bytes of
   the buf array,
    @return up to 128 bytes of pixel data in buf
*/
/**************************************************************************/
void Camera::readPixelsRaw(uint8_t *buf, uint8_t pixels) {
    uint8_t bytesToRead =
            MIN((uint8_t)(pixels << 1), (uint8_t)(AMG88xx_PIXEL_ARRAY_SIZE << 1));
    this->read(AMG88xx_PIXEL_OFFSET, buf, bytesToRead);
}

/**************************************************************************/
/*!
    @brief  Read Infrared sensor values
    @param  buf the array to place the pixels in
    @param  pixels Optional number of pixels to read (up to 64). Default is
   64 pixels.
    @return up to 64 float values of pixel data in buf
*/
/**************************************************************************/
void Camera::readPixels(float *buf, uint8_t pixels) {
    uint16_t recast;
    float converted;
    uint8_t bytesToRead =
            MIN((uint8_t)(pixels << 1), (uint8_t)(AMG88xx_PIXEL_ARRAY_SIZE << 1));
    uint8_t rawArray[bytesToRead];
    this->read(AMG88xx_PIXEL_OFFSET, rawArray, bytesToRead);

    for (int i = 0; i < pixels; i++) {
        uint8_t pos = i << 1;
        recast = ((uint16_t)rawArray[pos + 1] << 8) | ((uint16_t)rawArray[pos]);

        converted = int12ToFloat(recast) * AMG88xx_PIXEL_TEMP_CONVERSION;
        buf[i] = converted;
    }
}

/**************************************************************************/
/*!
    @brief  read one byte of data from the specified register
    @param  reg the register to read
    @returns one byte of register data
*/
/**************************************************************************/
uint8_t Camera::read8(uint8_t reg) {
    uint8_t ret;
    this->read(reg, &ret, 1);

    return ret;
}

void Camera::read(uint8_t reg, uint8_t *buf, uint8_t num) {
    uint8_t msg_addr[] = { reg};
    struct i2c_msg msgs[2] =
            {
                    /* Write 16-bit address */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = msg_addr },
                    /* Read 8-bit data */
                    { .addr = AMG88xx_ADDRESS, .flags = I2C_M_RD, .len = num, .buf = buf},
            };

    /* Transfer a transaction with two I2C messages */
    if (i2c_transfer(i2c_dev, msgs, 2) < 0) {
        perror("Error reading from I2C device");
    }
}

void Camera::write8(uint8_t reg, uint8_t *buf) {
    uint8_t prefix[1] = {reg};
    struct i2c_msg msgs[2] =
            {
                    /* Write 16-bit address */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = prefix },
                    /* Read 8-bit data */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = buf},
            };

    /* Transfer a transaction with two I2C messages */
    if (i2c_transfer(i2c_dev, msgs, 2) < 0) {
        perror("Error reading from I2C device");
    }
}

/**************************************************************************/
/*!
    @brief  convert a 12-bit signed magnitude value to a floating point number
    @param  val the 12-bit signed magnitude value to be converted
    @returns the converted floating point value
*/
/**************************************************************************/
float Camera::signedMag12ToFloat(uint16_t val) {
    // take first 11 bits as absolute val
    uint16_t absVal = (val & 0x7FF);

    return (val & 0x800) ? 0 - (float)absVal : (float)absVal;
}

/**************************************************************************/
/*!
    @brief  convert a 12-bit integer two's complement value to a floating point
   number
    @param  val the 12-bit integer  two's complement value to be converted
    @returns the converted floating point value
*/
/**************************************************************************/
float Camera::int12ToFloat(uint16_t val) {
    int16_t sVal =
            (val << 4); // shift to left so that sign bit of 12 bit integer number is
    // placed on sign bit of 16 bit signed integer number
    return sVal >> 4; // shift back the signed number, return converts to float
}