#include <dummy.h>  // Bao gồm thư viện dummy.h 

#include "motors.h"  // Bao gồm file tiêu đề motors.h, chứa định nghĩa và hàm liên quan đến điều khiển động cơ

#include <PS2X_lib.h>  // Bao gồm thư viện PS2X_lib.h để điều khiển tay cầm PS2

#include "servo.h"  // Bao gồm file tiêu đề servo.h, chứa định nghĩa và hàm liên quan đến điều khiển servo

PS2X ps2x; // Tạo một đối tượng ps2x của lớp PS2X để điều khiển tay cầm PS2

#define PS2_DAT 12 // Định nghĩa chân dữ liệu PS2 (MISO)
#define PS2_CMD 13 // Định nghĩa chân lệnh PS2 (MOSI)
#define PS2_SEL 15 // Định nghĩa chân chọn PS2 (SS)
#define PS2_CLK 14 // Định nghĩa chân đồng hồ PS2 (SCK)

#define tocdo 2000 // Định nghĩa tốc độ mặc định cho các hành động

void setupPS2controller() {
    ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);  // Cấu hình tay cầm PS2 với các chân kết nối và chế độ tự động
    ps2x.readType();  // Đọc loại tay cầm PS2 (xác định loại tay cầm được kết nối)
}

bool PS2control() { 
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0; // Khởi tạo các biến điều khiển cho các động cơ và servo

    if(ps2x.Button(PSB_PAD_UP)){
        Serial.print("\nTIEN\n");  // In thông báo "TIEN" lên cửa sổ Serial Monitor
        c3 = tocdo; // Tiến lên với tốc độ đã định
        c5 = tocdo; // Tiến lên với tốc độ đã định
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
        Serial.print("\nLUI\n");  // In thông báo "LUI" lên cửa sổ Serial Monitor
        c4 = 4000; // Lùi với tốc độ đã định
        c6 = 4000; // Lùi với tốc độ đã định
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
        Serial.print("\nPHAI\n");  // In thông báo "PHAI" lên cửa sổ Serial Monitor
        c4 = tocdo; // Di chuyển sang phải với tốc độ đã định
        c5 = tocdo; // Di chuyển sang phải với tốc độ đã định
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
        Serial.print("\nTRAI\n");  // In thông báo "TRAI" lên cửa sổ Serial Monitor
        c3 = tocdo; // Di chuyển sang trái với tốc độ đã định
        c6 = tocdo; // Di chuyển sang trái với tốc độ đã định
    }
    if(ps2x.Button(PSB_R1)){
        Serial.print("\nQUAY TUA BIN\n");  // In thông báo "QUAY TUA BIN" lên cửa sổ Serial Monitor
        c2 = 3000; // Quay tua bin lấy bóng với tốc độ đã định
    }
    if(ps2x.Button(PSB_L1)){
        Serial.print("\nNANG THUNG\n");  // In thông báo "NANG THUNG" lên cửa sổ Serial Monitor
        c7 = 1000; // Nâng thùng bóng lên với tốc độ đã định
    }
    if(ps2x.Button(PSB_L2)){
        Serial.print("\nHA THUNG\n");  // In thông báo "HA THUNG" lên cửa sổ Serial Monitor
        c8 = 1000; // Hạ thùng bóng xuống với tốc độ đã định
    }
    if(ps2x.Button(PSB_PINK)){
        Serial.print("\nMO THUNG\n");  // In thông báo "MO THUNG" lên cửa sổ Serial Monitor
        servo_angle(90, Servo1); // Mở thùng servo quay 90°
    }
    if(ps2x.Button(PSB_GREEN)){
        Serial.print("\nDONG THUNG\n");  // In thông báo "DONG THUNG" lên cửa sổ Serial Monitor
        servo_angle(0, Servo1); // Đóng thùng servo quay về 0°
    }
    if(ps2x.Button(PSB_RED)){
        Serial.print("\nBAN BONG\n");  // In thông báo "BAN BONG" lên cửa sổ Serial Monitor
        c1 = 2500; // Đưa bóng vào máy bắn với tốc độ đã định
    }
    if(ps2x.Button(PSB_BLUE)){
        Serial.print("\nDAO CHIEU THANH CHAN\n");  // In thông báo "DAO CHIEU THANH CHAN" lên cửa sổ Serial Monitor
        // Đảo chiều thanh chặn cho bóng đi vào máy bắn
        // Tùy chỉnh thêm hành động ở đây
    }

    setPWMMotors(c1, c2, c3, c4, c5, c6, c7, c8);  // Gọi hàm để thiết lập PWM cho các động cơ và servo với các giá trị đã tính toán
    return 1;  // Trả về giá trị true (1) để xác nhận rằng việc điều khiển đã thực hiện thành công
}
