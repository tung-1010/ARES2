#ifndef _ADAFRUIT_PWMServoDriver_H  // Nếu chưa định nghĩa macro _ADAFRUIT_PWMServoDriver_H
#define _ADAFRUIT_PWMServoDriver_H  // Định nghĩa macro _ADAFRUIT_PWMServoDriver_H để tránh việc bao gồm nhiều lần

#include <Arduino.h>  // Bao gồm thư viện Arduino để sử dụng các hàm và kiểu dữ liệu của Arduino
#include <Wire.h>  // Bao gồm thư viện Wire để sử dụng giao thức I2C

// ĐĂNG KÝ ĐỊA CHỈ
#define PCA9685_MODE1 0x00 /**< Thanh ghi chế độ 1 */
#define PCA9685_MODE2 0x01 /**< Thanh ghi chế độ 2 */
#define PCA9685_SUBADR1 0x02 /**< Địa chỉ phụ bus I2C 1 */
#define PCA9685_SUBADR2 0x03 /**< Địa chỉ phụ bus I2C 2 */
#define PCA9685_SUBADR3 0x04 /**< Địa chỉ phụ bus I2C 3 */
#define PCA9685_ALLCALLADR 0x05 /**< LED All Call Địa chỉ bus I2C */
#define PCA9685_LED0_ON_L 0x06 /**< LED0 trên tích tắc, byte thấp*/
#define PCA9685_LED0_ON_H 0x07 /**< LED0 on tick, byte cao*/
#define PCA9685_LED0_OFF_L 0x08 /**< LED0 off tick, byte thấp */
#define PCA9685_LED0_OFF_H 0x09 /**< LED0 off tick, byte cao */
// v.v. tất cả 16: LED15_OFF_H 0x45
#define PCA9685_ALLLED_ON_L 0xFA /**< tải tất cả các thanh ghi LEDn_ON, thấp */
#define PCA9685_ALLLED_ON_H 0xFB /**< tải tất cả các thanh ghi LEDn_ON, cao */
#define PCA9685_ALLLED_OFF_L 0xFC /**< tải tất cả các thanh ghi LEDn_OFF, thấp */
#define PCA9685_ALLLED_OFF_H 0xFD /**< tải tất cả các thanh ghi LEDn_OFF, cao */
#define PCA9685_PRESCALE 0xFE /**< Bộ chia trước cho tần số đầu ra PWM */
#define PCA9685_TESTMODE 0xFF /**< định nghĩa chế độ kiểm tra sẽ được nhập */

// MODE1 bit
#define MODE1_ALLCAL 0x01 /**< phản hồi LED All Call địa chỉ bus I2C */
#define MODE1_SUB3 0x02 /**< phản hồi địa chỉ phụ bus I2C 3 */
#define MODE1_SUB2 0x04 /**< phản hồi địa chỉ phụ bus I2C 2 */
#define MODE1_SUB1 0x08 /**< phản hồi địa chỉ phụ bus I2C 1 */
#define MODE1_SLEEP 0x10 /**< Chế độ công suất thấp. Tắt bộ dao động */
#define MODE1_AI 0x20 /**< Tự động tăng được bật */
#define MODE1_EXTCLK 0x40 /**< Sử dụng xung nhịp chân EXTCLK */
#define MODE1_RESTART 0x80 /**< Khởi động lại được bật */
// MODE2 bit
#define MODE2_OUTNE_0 0x01 /**< Đầu vào cho phép đầu ra THẤP đang hoạt động */
#define MODE2_OUTNE_1 \
0x02 /**< Đầu vào cho phép đầu ra THẤP đang hoạt động - trở kháng cao */
#define MODE2_OUTDRV 0x04 /**< Cấu trúc cực totem so với cực thoát mở */
#define MODE2_OCH 0x08 /**< Đầu ra thay đổi khi ACK so với STOP */
#define MODE2_INVRT 0x10 /**< Trạng thái logic đầu ra bị đảo ngược */

#define PCA9685_I2C_ADDRESS 0x40 /**< Địa chỉ Slave I2C PCA9685 mặc định */
#define FREQUENCY_OSCILLATOR 25000000 /**< Tần số osc. Int. trong bảng dữ liệu */

#define PCA9685_PRESCALE_MIN 3 /**< giá trị prescale tối thiểu */
#define PCA9685_PRESCALE_MAX 255 /**< giá trị prescale tối đa */

class Adafruit_PWMServoDriver {
public:
  Adafruit_PWMServoDriver();  // Hàm khởi tạo không tham số
  Adafruit_PWMServoDriver(const uint8_t addr);  // Hàm khởi tạo với địa chỉ I2C
  Adafruit_PWMServoDriver(const uint8_t addr, TwoWire &i2c);  // Hàm khởi tạo với địa chỉ I2C và đối tượng TwoWire

  void begin(uint8_t prescale = 0);  // Khởi tạo thư viện với giá trị prescale tùy chọn (mặc định là 0)
  void reset();  // Đặt lại PCA9685 về trạng thái mặc định
  void sleep();  // Đặt PCA9685 vào chế độ ngủ
  void wakeup();  // Đánh thức PCA9685 từ chế độ ngủ
  void setExtClk(uint8_t prescale);  // Thiết lập đồng hồ ngoại vi cho PCA9685 với giá trị prescale
  void setPWMFreq(float freq);  // Đặt tần số PWM đầu ra
  void setOutputMode(bool totempole);  // Đặt chế độ đầu ra, totem pole hay open drain
  uint8_t getPWM(uint8_t num);  // Lấy giá trị PWM hiện tại của kênh
  void setPWM(uint8_t num, uint16_t on, uint16_t off);  // Đặt giá trị PWM cho kênh với giá trị bật và tắt
  void setPin(uint8_t num, uint16_t val, bool invert = false);  // Đặt giá trị PWM cho kênh với tùy chọn đảo ngược
  uint8_t readPrescale(void);  // Đọc giá trị prescale hiện tại
  void writeMicroseconds(uint8_t num, uint16_t Microseconds);  // Viết giá trị PWM theo đơn vị microsecond

  void setOscillatorFrequency(uint32_t freq);  // Đặt tần số dao động của PCA9685
  uint32_t getOscillatorFrequency(void);  // Lấy tần số dao động hiện tại của PCA9685

private:
  uint8_t _i2caddr;  // Địa chỉ I2C của PCA9685
  TwoWire *_i2c;  // Con trỏ đến đối tượng TwoWire để giao tiếp I2C

  uint32_t _oscillator_freq;  // Tần số dao động hiện tại
  uint8_t read8(uint8_t addr);  // Đọc một byte từ thanh ghi
  void write8(uint8_t addr, uint8_t d);  // Viết một byte vào thanh ghi
};

#endif  // Kết thúc điều kiện nếu định nghĩa _ADAFRUIT_PWMServoDriver_H
