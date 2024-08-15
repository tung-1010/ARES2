#include <stdio.h>  // Bao gồm thư viện chuẩn để sử dụng các hàm nhập/xuất chuẩn như printf
#include "Wire.h"  // Bao gồm thư viện Wire để giao tiếp I2C
#include "Adafruit_PWMServoDriver.h"  // Bao gồm thư viện Adafruit_PWMServoDriver để điều khiển PWM
#include <SimpleKalmanFilter.h>
#define MIN_PWM 0  // Định nghĩa giá trị PWM tối thiểu
#define MAX_PWM 4095  // Định nghĩa giá trị PWM tối đa

// Định nghĩa các kênh PWM cho động cơ
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15


SimpleKalmanFilter bo_loc(2, 2, 0.001);
 
float u0 = 100.0; // giá trị thực (không đổi)
float e; // nhiễu
float u; // giá trị đo được (có thêm nhiễu)
float u_kalman; // giá được lọc nhiễu
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // Tạo đối tượng pwm từ lớp Adafruit_PWMServoDriver

// Hàm để thiết lập PWM cho các động cơ
void setPWMMotors(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8) {
    Serial.print(c1);  // In giá trị c1 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c2);  // In giá trị c2 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c3);  // In giá trị c3 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c4);  // In giá trị c4 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c5);  // In giá trị c5 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c6);  // In giá trị c6 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c7);  // In giá trị c7 lên Serial Monitor
    Serial.print("\t");  // In dấu tab
    Serial.print(c8);  // In giá trị c8 lên Serial Monitor
    Serial.println();  // Xuống dòng

    // Thiết lập PWM cho các kênh động cơ
    pwm.setPWM(PWM_CHANNEL1, c1, MAX_PWM - c1);
    pwm.setPWM(PWM_CHANNEL2, c2, MAX_PWM - c2);
    pwm.setPWM(PWM_CHANNEL3, c3, MAX_PWM - c3);
    pwm.setPWM(PWM_CHANNEL4, c4, MAX_PWM - c4);
    pwm.setPWM(PWM_CHANNEL5, c5, MAX_PWM - c5);
    pwm.setPWM(PWM_CHANNEL6, c6, MAX_PWM - c6);
    pwm.setPWM(PWM_CHANNEL7, c7, MAX_PWM - c7);
    pwm.setPWM(PWM_CHANNEL8, c8, MAX_PWM - c8);
}

// Hàm khởi tạo các động cơ
void initMotors() {
    Wire.begin();  // Khởi động giao tiếp I2C
    pwm.begin();  // Khởi động đối tượng pwm
    pwm.setOscillatorFrequency(27000000);  // Đặt tần số dao động cho PWM
    pwm.setPWMFreq(1600);  // Đặt tần số PWM
    Wire.setClock(400000);  // Đặt tốc độ đồng hồ I2C

    setPWMMotors(0, 0, 0, 0, 0, 0, 0, 0);  // Thiết lập giá trị PWM mặc định cho tất cả các động cơ là 0
}

// Hàm để cấu hình các chân cảm biến đường line
void intline() {
    pinMode(36, INPUT);  // Đặt chân 36 là đầu vào
    pinMode(39, INPUT);  // Đặt chân 39 là đầu vào
    pinMode(32, INPUT);  // Đặt chân 32 là đầu vào
}

// Hàm để theo dõi đường line và điều khiển động cơ
void linefollow() {
    Serial.println("Doline");  // In thông báo "Doline" lên Serial Monitor
    int L = digitalRead(36);  // Đọc giá trị từ chân 36 (cảm biến bên trái)
    int R = digitalRead(39);  // Đọc giá trị từ chân 39 (cảm biến bên phải)
    int M = digitalRead(32);  // Đọc giá trị từ chân 32 (cảm biến giữa)
    Serial.println(L);  // In giá trị cảm biến bên trái lên Serial Monitor

    // Điều khiển động cơ dựa trên giá trị cảm biến
    if (L == 1 && M == 0 && R == 1) {
        pwm.setPWM(8, 0, 1600);  // Thiết lập PWM cho kênh 8 để tiến
        pwm.setPWM(9, 0, 0);  // Thiết lập PWM cho kênh 9
        pwm.setPWM(10, 0, 1600);  // Thiết lập PWM cho kênh 10 để tiến
        pwm.setPWM(11, 0, 0);  // Thiết lập PWM cho kênh 11
        Serial.print("\ntien");  // In thông báo "tien" lên Serial Monitor
    } else if (L == 0 && R == 1) {
        pwm.setPWM(8, 0, 1600);  // Thiết lập PWM cho kênh 8 để quay trái
        pwm.setPWM(9, 0, 0);  // Thiết lập PWM cho kênh 9
        pwm.setPWM(10, 0, 0);  // Thiết lập PWM cho kênh 10
        pwm.setPWM(11, 0, 0);  // Thiết lập PWM cho kênh 11
        Serial.print("\ntrai");  // In thông báo "trai" lên Serial Monitor
    } else if (L == 1 && R == 0) {
        pwm.setPWM(8, 0, 0);  // Thiết lập PWM cho kênh 8
        pwm.setPWM(9, 0, 0);  // Thiết lập PWM cho kênh 9
        pwm.setPWM(10, 0, 1600);  // Thiết lập PWM cho kênh 10 để quay phải
        pwm.setPWM(11, 0, 0);  // Thiết lập PWM cho kênh 11
        Serial.print("\nphai");  // In thông báo "phai" lên Serial Monitor
    } else {
        pwm.setPWM(8, 4096, 0);  // Thiết lập PWM cho kênh 8 để lùi
        pwm.setPWM(9, 4096, 0);  // Thiết lập PWM cho kênh 9 để lùi
        pwm.setPWM(11, 4096, 0);  // Thiết lập PWM cho kênh 11 để lùi
        pwm.setPWM(10, 4096, 0);  // Thiết lập PWM cho kênh 10 để lùi
        Serial.print("\nlui");  // In thông báo "lui" lên Serial Monitor
    }
}
