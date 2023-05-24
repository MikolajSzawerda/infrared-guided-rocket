#include "Camera.h"

i2c_t* begin() {
    i2c_t* i2c_dev=i2c_new();
printf("Opened main\n");
    if (i2c_open(i2c_dev, "/dev/i2c-1") < 0) {
        perror("i2c_open() failed");
        return 0;
    }
	printf("Opened a\n");
    // enter normal mode
    uint8_t a = AMG88xx_NORMAL_MODE;
    write8(i2c_dev, AMG88xx_PCTL, &a);
printf("Opened b\n");
    // software reset
    a= AMG88xx_INITIAL_RESET;
    write8(i2c_dev, AMG88xx_RST, &a);
printf("Opened c\n");
    // set to 10 FPS
    a=AMG88xx_FPS_10;
    write8(i2c_dev, AMG88xx_FPSC, &a);
printf("Opened d\n");
//    usleep(100000);

    return i2c_dev;
}

void readPixelsRaw(i2c_t* i2c_dev, uint8_t *buf, uint8_t pixels) {
    uint8_t bytesToRead =
            MIN((uint8_t)(pixels << 1), (uint8_t)(AMG88xx_PIXEL_ARRAY_SIZE << 1));
    plain_read(i2c_dev, AMG88xx_PIXEL_OFFSET, buf, bytesToRead);
}

void readPixels(i2c_t* i2c_dev, float *buf, uint8_t pixels) {
    uint16_t recast;
    float converted;
printf("read a\n");
    uint8_t bytesToRead =
            MIN((uint8_t)(pixels << 1), (uint8_t)(AMG88xx_PIXEL_ARRAY_SIZE << 1));
    uint8_t rawArray[bytesToRead];
    plain_read(i2c_dev, AMG88xx_PIXEL_OFFSET, rawArray, bytesToRead);
printf("read b\n");
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
uint8_t read8(i2c_t* i2c_dev, uint8_t reg) {
    uint8_t ret;
    plain_read(i2c_dev, reg, &ret, 1);

    return ret;
}

void plain_read(i2c_t* i2c_dev, uint8_t reg, uint8_t *buf, uint8_t num) {
    uint8_t msg_addr[] = { reg};
    struct i2c_msg msgs[2] =
            {
                    /* Write 16-bit address */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = msg_addr },
                    /* Read 8-bit data */
                    { .addr = AMG88xx_ADDRESS, .flags = I2C_M_RD, .len = num, .buf = buf},
            };

    /* Transfer a transaction with two I2C messages */
printf("pread a\n");
    if (i2c_transfer(i2c_dev, msgs, 2) < 0) {
        perror("Error reading from I2C device");
    }
printf("pread b\n");
}

void write8(i2c_t* i2c_dev,uint8_t reg, uint8_t *buf) {
    uint8_t prefix[1] = {reg};
    struct i2c_msg msgs[2] =
            {
                    /* Write 16-bit address */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = prefix },
                    /* Read 8-bit data */
                    { .addr = AMG88xx_ADDRESS, .flags = 0, .len = 1, .buf = buf},
            };
printf("write a\n");
    /* Transfer a transaction with two I2C messages */
    if (i2c_transfer(i2c_dev, msgs, 2) < 0) {
        perror("Error reading from I2C device");
    }
printf("write b\n");
}

/**************************************************************************/
/*!
    @brief  convert a 12-bit signed magnitude value to a floating point number
    @param  val the 12-bit signed magnitude value to be converted
    @returns the converted floating point value
*/
/**************************************************************************/
float signedMag12ToFloat(uint16_t val) {
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
float int12ToFloat(uint16_t val) {
    int16_t sVal =
            (val << 4); // shift to left so that sign bit of 12 bit integer number is
    // placed on sign bit of 16 bit signed integer number
    return sVal >> 4; // shift back the signed number, return converts to float
}
