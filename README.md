# Xe dò line

Firmware điều khiển robot dò line bằng 8 cảm biến hồng ngoại và PID. Dự án có encoder để đo chuyển động, màn hình OLED và Bluetooth để theo dõi trạng thái; cảm biến VL53L0X được dùng để phát hiện vật cản.

## Phần cứng

- Board STM32 tương thích Arduino, có các chân PA/PB được dùng trong mã.
- Driver động cơ TB6612FNG và 2 động cơ giảm tốc GA25 có encoder.
- Mảng 8 cảm biến line analog, OLED SSD1306 I2C, cảm biến VL53L0X.
- HC-05/HC-06 và 2 nút nhấn (OK, MODE).

**Nối dây theo mã nguồn:**

| Chức năng                    | Chân STM32                            |
| ------------------------------ | -------------------------------------- |
| TB6612: PWMA, AIN1, AIN2, STBY | PA10, PA8, PB15, PB14                  |
| TB6612: BIN1, BIN2, PWMB       | PB12, PB13, PA9                        |
| Cảm biến line S1–S8         | PA6, PB1, PA5, PB0, PA4, PA7, PA3, PA2 |
| Encoder trái A/B; phải A/B   | PA0/PA1; PB6/PB7                       |
| OLED và VL53L0X (I2C)         | PB9 (SDA), PB8 (SCL)                   |
| Bluetooth HC-05/HC-06          | PB11 (RX), PB10 (TX), 115200 baud      |
| Nút OK, MODE                  | PA12, PA15                             |

Kiểm tra sơ đồ chân của board và module trước khi cấp nguồn; pin map có thể cần chỉnh trong `khaibao.h`.

## Cài đặt và chạy

1. Cài Arduino IDE, thêm STM32 core và chọn đúng board cùng phương thức nạp.
2. Cài thư viện **Adafruit GFX Library**, **Adafruit SSD1306** và **VL53L0X** tương thích với API Pololu (`init`, `setAddress`, `startContinuous`).
3. Đặt các file `.h` cạnh file `.ino`. Arduino IDE yêu cầu tên thư mục sketch trùng tên file `.ino`; đổi tên một trong hai nếu cần.
4. Chọn cổng nạp, build và upload firmware. Khi lần đầu sử dụng, chọn **CALIBRATE** và nhấn **OK** để hiệu chuẩn cảm biến; kết quả được lưu trong EEPROM.
5. Nhấn **MODE** để chuyển chế độ, **OK** để bắt đầu/dừng. Thử lần đầu khi bánh xe được kê khỏi mặt đất.

## Chế độ hiện có

| Mode | Chức năng                                    |
| ---- | ---------------------------------------------- |
| 0    | Chạy theo lộ trình với PID                 |
| 1    | Kiểm tra chuyển động: quay trái một lần |
| 2    | Hiệu chuẩn cảm biến line và lưu EEPROM   |
| 3    | Hiển thị trạng thái cảm biến line        |
| 4    | Hiển thị số đếm encoder                   |

Thông số PID, tốc độ và trình tự chạy hiện được cấu hình trực tiếp trong mã nguồn. Hãy kiểm tra robot trong môi trường an toàn trước khi vận hành thực tế.
