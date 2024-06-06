#include<NewPing.h>
#include<Servo.h>
#include<AFMotor.h>

#define RIGHT A2              // Cảm biến hồng ngoại bên phải nối với chân analog A2 của Arduino Uno:
#define LEFT A3               // Cảm biến hồng ngoại bên trái nối với chân analog A3 của Arduino Uno:
#define TRIGGER_PIN A1        // Chân trigger nối với chân analog A1 của Arduino Uno:
#define ECHO_PIN A0           // Chân echo nối với chân analog A0 của Arduino Uno:
#define MAX_DISTANCE 200      // Khoảng cách ping tối đa:

unsigned int distance = 0;    // Biến lưu trữ khoảng cách của cảm biến siêu âm:
unsigned int Right_Value = 0; // Biến lưu trữ giá trị của cảm biến hồng ngoại bên phải:
unsigned int Left_Value = 0;  // Biến lưu trữ giá trị của cảm biến hồng ngoại bên trái:

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // Thiết lập NewPing với các chân và khoảng cách tối đa:

// Tạo đối tượng động cơ
AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

Servo myservo;  // Tạo đối tượng servo để điều khiển servo:
int pos = 0;    // Biến lưu trữ vị trí của servo:

void setup() {  // Hàm setup chạy một lần khi cấp nguồn hoặc reset bảng mạch:

   Serial.begin(9600);  // Khởi tạo giao tiếp serial ở tốc độ 9600 bps:
   myservo.attach(10);  // Servo gắn vào chân 10 của Arduino UNO
   {
      for(pos = 90; pos <= 180; pos += 1){  // Di chuyển từ 90 độ đến 180 độ:
         myservo.write(pos);  // Điều khiển servo theo giá trị của biến 'pos':
         delay(15);  // Chờ 15ms để servo di chuyển đến vị trí:
      } 
      for(pos = 180; pos >= 0; pos -= 1) {  // Di chuyển từ 180 độ về 0 độ:
         myservo.write(pos);  // Điều khiển servo theo giá trị của biến 'pos':
         delay(15);  // Chờ 15ms để servo di chuyển đến vị trí:
      }
      for(pos = 0; pos <= 90; pos += 1) {  // Di chuyển từ 0 độ đến 90 độ:
         myservo.write(pos);  // Điều khiển servo theo giá trị của biến 'pos':
         delay(15);  // Chờ 15ms để servo di chuyển đến vị trí:
      }
   }
   pinMode(RIGHT, INPUT);  // Đặt chân analog RIGHT là đầu vào:
   pinMode(LEFT, INPUT);   // Đặt chân analog LEFT là đầu vào:
}

// Hàm loop chạy liên tục
void loop() {                             
  
   delay(50);  // Chờ 50ms giữa các lần ping:
   distance = sonar.ping_cm();  // Gửi ping, nhận khoảng cách bằng cm và lưu vào biến 'distance':
   Serial.print("distance");                   
   Serial.println(distance);  // In khoảng cách ra màn hình serial:

   Right_Value = digitalRead(RIGHT);  // Đọc giá trị từ cảm biến hồng ngoại bên phải:
   Left_Value = digitalRead(LEFT);  // Đọc giá trị từ cảm biến hồng ngoại bên trái:
 
   Serial.print("RIGHT");                      
   Serial.println(Right_Value);  // In giá trị cảm biến hồng ngoại bên phải ra màn hình serial:
   Serial.print("LEFT");                       
   Serial.println(Left_Value);  // In giá trị cảm biến hồng ngoại bên trái ra màn hình serial:

   if((distance > 1) && (distance < 15)){  // Kiểm tra nếu giá trị cảm biến siêu âm nằm trong khoảng từ 1 đến 15.
      // Di chuyển về phía trước:
      Motor1.setSpeed(130);  // Đặt tốc độ cho động cơ 1:
      Motor1.run(FORWARD);   // Quay động cơ 1 theo chiều kim đồng hồ:
      Motor2.setSpeed(130);  // Đặt tốc độ cho động cơ 2:
      Motor2.run(FORWARD);   // Quay động cơ 2 theo chiều kim đồng hồ:
      Motor3.setSpeed(130);  // Đặt tốc độ cho động cơ 3:
      Motor3.run(FORWARD);   // Quay động cơ 3 theo chiều kim đồng hồ:
      Motor4.setSpeed(130);  // Đặt tốc độ cho động cơ 4:
      Motor4.run(FORWARD);   // Quay động cơ 4 theo chiều kim đồng hồ:
   } else if((Right_Value == 0) && (Left_Value == 1)) {  // Nếu điều kiện đúng thì thực hiện:
      // Rẽ trái                                                
      Motor1.setSpeed(150);  // Đặt tốc độ cho động cơ 1:
      Motor1.run(FORWARD);   // Quay động cơ 1 theo chiều kim đồng hồ:
      Motor2.setSpeed(150);  // Đặt tốc độ cho động cơ 2:
      Motor2.run(FORWARD);   // Quay động cơ 2 theo chiều kim đồng hồ:
      Motor3.setSpeed(150);  // Đặt tốc độ cho động cơ 3:
      Motor3.run(BACKWARD);  // Quay động cơ 3 ngược chiều kim đồng hồ:
      Motor4.setSpeed(150);  // Đặt tốc độ cho động cơ 4:
      Motor4.run(BACKWARD);  // Quay động cơ 4 ngược chiều kim đồng hồ:
      delay(150);
   } else if((Right_Value == 1) && (Left_Value == 0)) {  // Nếu điều kiện đúng thì thực hiện:
      // Rẽ phải
      Motor1.setSpeed(150);  // Đặt tốc độ cho động cơ 1:
      Motor1.run(BACKWARD);  // Quay động cơ 1 ngược chiều kim đồng hồ:
      Motor2.setSpeed(150);  // Đặt tốc độ cho động cơ 2:
      Motor2.run(BACKWARD);  // Quay động cơ 2 ngược chiều kim đồng hồ:
      Motor3.setSpeed(150);  // Đặt tốc độ cho động cơ 3:
      Motor3.run(FORWARD);   // Quay động cơ 3 theo chiều kim đồng hồ:
      Motor4.setSpeed(150);  // Đặt tốc độ cho động cơ 4:
      Motor4.run(FORWARD);   // Quay động cơ 4 theo chiều kim đồng hồ:
      delay(150);
   } else if(distance > 15) {  // Nếu điều kiện đúng thì thực hiện:
      // Dừng lại
      Motor1.setSpeed(0);  // Đặt tốc độ cho động cơ 1:
      Motor1.run(RELEASE);  // Dừng động cơ 1:
      Motor2.setSpeed(0);  // Đặt tốc độ cho động cơ 2:
      Motor2.run(RELEASE);  // Dừng động cơ 2:
      Motor3.setSpeed(0);  // Đặt tốc độ cho động cơ 3:
      Motor3.run(RELEASE);  // Dừng động cơ 3:
      Motor4.setSpeed(0);  // Đặt tốc độ cho động cơ 4:
      Motor4.run(RELEASE);  // Dừng động cơ 4:
   }
}
