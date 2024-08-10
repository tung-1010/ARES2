#include "PS2_controller.h"  // Bao gồm thư viện điều khiển PS2 

void setup()
{
  Serial.begin(9600);  // Khởi động giao tiếp nối tiếp với tốc độ baud là 9600 bps, để gửi dữ liệu từ Arduino đến máy tính hoặc các thiết bị khác qua cổng nối tiếp
  initMotors();  // Gọi hàm để khởi tạo các động cơ của robot 
  initservo();  // Gọi hàm để khởi tạo các servo
  setupPS2controller();  // Gọi hàm để thiết lập điều khiển PS2 
  Serial.println("Done setup!");  // In thông báo "Done setup!" lên cửa sổ Serial Monitor để xác nhận rằng quá trình thiết lập đã hoàn tất
}

void loop()
{
  ps2x.read_gamepad(false, 0);  // Đọc dữ liệu từ điều khiển PS2 và cập nhật trạng thái của nó. Tham số false nghĩa là không cần phải bật chế độ rung và tham số 0 nghĩa là sử dụng chế độ điều khiển mặc định
  PS2control();  // Gọi hàm để xử lý các điều khiển từ PS2 
}
