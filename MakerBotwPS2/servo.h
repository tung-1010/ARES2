#include "Wire.h"  // Bao gồm thư viện Wire để giao tiếp I2C
#include "Adafruit_PWMServoDriver.h"  // Bao gồm thư viện Adafruit_PWMServoDriver để điều khiển PWM

#define SERVOMIN  150  // Giá trị tối thiểu cho xung servo (trong số 4096)
#define SERVOMAX  600  // Giá trị tối đa cho xung servo (trong số 4096)
#define USMIN  600  // Độ dài micro giây tối thiểu tương ứng với xung tối thiểu 150
#define USMAX  2400  // Độ dài micro giây tối đa tương ứng với xung tối đa 600
#define SERVO_FREQ 50  // Tần số cập nhật cho servo là 50 Hz

#define Servo1 2  // Định nghĩa chân điều khiển cho Servo 1
#define Servo2 3  // Định nghĩa chân điều khiển cho Servo 2
#define Servo3 4  // Định nghĩa chân điều khiển cho Servo 3
#define Servo4 5  // Định nghĩa chân điều khiển cho Servo 4
#define Servo5 6  // Định nghĩa chân điều khiển cho Servo 5
#define Servo6 7  // Định nghĩa chân điều khiển cho Servo 6

int My_servo[6] = {Servo1, Servo2, Servo3, Servo4, Servo5, Servo6};  // Mảng chứa các chân điều khiển servo
int pwm_val, T_on;  // Biến lưu giá trị PWM và thời gian xung
float T_ON_90 = 1.5, T_ON_0 = 1.0, T_ON_180 = 2.0, Ts = 20;  // Thời gian xung cho các góc servo và chu kỳ điều khiển PWM servo

#define Clock_PCA9685 27000000  // Tần số dao động của PCA9685

// Khai báo đối tượng pwm từ lớp Adafruit_PWMServoDriver
extern Adafruit_PWMServoDriver pwm;

// Hàm để điều khiển góc của servo
void servo_angle(int angle, int servo_num) {
  T_on = map(angle, 0, 180, 1, 2);  // Chuyển đổi góc từ 0-180 độ thành thời gian xung từ 1-2 ms
  pwm.writeMicroseconds(My_servo[servo_num - 1], T_on * 1000);  // Ghi giá trị thời gian xung vào servo
}

// Hàm để dừng servo (đặt PWM tối đa để servo không hoạt động)
void servo_stop(int servo_num) {
  pwm.setPWM(My_servo[servo_num - 1], 4096, 4096);  // Đặt giá trị PWM tối đa để dừng servo
}

// Hàm khởi tạo servo
void initservo() {
  Wire.begin();  // Khởi động giao tiếp I2C
  pwm.begin();  // Khởi động đối tượng pwm
  pwm.setOscillatorFrequency(Clock_PCA9685);  // Đặt tần số dao động của PCA9685
  pwm.setPWMFreq(SERVO_FREQ);  // Đặt tần số PWM cho servo là 50 Hz
}

// Hàm để điều khiển nhiều servo cùng lúc
void servo(int a, int b, int c, int d) {
  // Chuyển đổi giá trị góc từ 0-180 độ thành giá trị xung tương ứng với phạm vi 150-600
  a = map(a, 0, 180, 150, 600);
  b = map(b, 0, 180, 150, 600);
  c = map(c, 0, 180, 150, 600);
  d = map(d, 0, 180, 150, 600);

  // Thiết lập PWM cho các kênh điều khiển servo
  pwm.setPWM(16, 0, a);  // Kênh 16
  pwm.setPWM(17, 0, b);  // Kênh 17
  pwm.setPWM(18, 0, c);  // Kênh 18
  pwm.setPWM(19, 0, d);  // Kênh 19
}
