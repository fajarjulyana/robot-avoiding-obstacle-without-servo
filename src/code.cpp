/* 
  ===========================
    Robot Obstacle Avoiding
         (tanpa servo)
        by Fajar Julyana
  ===========================
*/
#include <AFmotor.h>        //library Adafruit motor driver . pasang manual
#include <NewPing.h>        //Library ping mili detik untuk Ultrasonic sensor. pasang manual

//pin sensor
#define trig_pin A0 //analog input 0
#define echo_pin A1 //analog input 1

#define jarak_maksimal 200
boolean kondisiMaju = false;
int jarak = 100;

NewPing sonar(trig_pin, echo_pin, jarak_maksimal); //sensor function

//deklarasi Motor DC pada modul Adafruit Motor Driver 
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

//deklarasi Kecepatan berdasarkan kendali mempermudah pengaturan
int kecepatanMaju = 150;
int kecepatanBelok = 200;
int kecepatanMundur = 200;

int bacaPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
void belokKanan(){
    Serial.println("Belok Kanan");
    motor1.run(FORWARD);
    motor1.setSpeed(kecepatanBelok);
    motor2.run(FORWARD);
    motor2.setSpeed(kecepatanBelok);
    motor3.run(BACKWARD);
    motor3.setSpeed(kecepatanBelok);
    motor4.run(BACKWARD);
    motor4.setSpeed(kecepatanBelok);

  delay(250);
  
    motor1.run(FORWARD);
    motor1.setSpeed(kecepatanBelok);
    motor2.run(FORWARD);
    motor2.setSpeed(kecepatanBelok);
    motor3.run(BACKWARD);
    motor3.setSpeed(kecepatanBelok);
    motor4.run(BACKWARD);
    motor4.setSpeed(kecepatanBelok);
  
}

void belokKiri(){
    Serial.println("Belok Kiri");
    motor1.run(BACKWARD);
    motor1.setSpeed(kecepatanBelok);
    motor2.run(BACKWARD);
    motor2.setSpeed(kecepatanBelok);
    motor3.run(FORWARD);
    motor3.setSpeed(kecepatanBelok);
    motor4.run(FORWARD);
    motor4.setSpeed(kecepatanBelok);

  delay(250);
  
    motor1.run(BACKWARD);
    motor1.setSpeed(kecepatanBelok);
    motor2.run(BACKWARD);
    motor2.setSpeed(kecepatanBelok);
    motor3.run(FORWARD);
    motor3.setSpeed(kecepatanBelok);
    motor4.run(FORWARD);
    motor4.setSpeed(kecepatanBelok);
}

int lihatKanan(){  
  Serial.println("Lihat Kanan");
  belokKanan();
  delay(500);
  int jarak = bacaPing();
  delay(100);
  belokKiri();
  return jarak;
}

int lihatKiri(){
  Serial.println("Lihat Kiri");
  belokKiri();
  delay(500);
  int jarak = bacaPing();
  delay(100);
  belokKanan();
  return jarak;
  delay(100);
}

void berhentiGerak(){
    Serial.println("Berhenti");
    motor1.run(RELEASE);
    motor1.setSpeed(0);
    motor2.run(RELEASE);
    motor2.setSpeed(0);
    motor3.run(RELEASE);
    motor3.setSpeed(0);
    motor4.run(RELEASE);
    motor4.setSpeed(0);
}

void gerakMaju(){

  if(!kondisiMaju){

    kondisiMaju=true;
    
    motor1.run(FORWARD);
    motor1.setSpeed(kecepatanMaju);
    motor2.run(FORWARD);
    motor2.setSpeed(kecepatanMaju);
    motor3.run(FORWARD);
    motor3.setSpeed(kecepatanMaju);
    motor4.run(FORWARD);
    motor4.setSpeed(kecepatanMaju);
    Serial.println("Maju");
  }
}

void gerakMundur(){

  kondisiMaju=false;
    Serial.println("Mundur");
    motor1.run(BACKWARD);
    motor1.setSpeed(kecepatanMundur);
    motor2.run(BACKWARD);
    motor2.setSpeed(kecepatanMundur);
    motor3.run(BACKWARD);
    motor3.setSpeed(kecepatanMundur);
    motor4.run(BACKWARD);
    motor4.setSpeed(kecepatanMundur);
    
    berhentiGerak();
  
}

void setup(){
  Serial.begin(9600); //informasi umpan balik menggunakan port komunikasi USB baut rate 9600
  delay(2000);
  jarak = bacaPing();
  delay(100);
  jarak = bacaPing();
  delay(100);
  jarak = bacaPing();
  delay(100);
  jarak = bacaPing();
  delay(100);
}

void loop(){

  int jarakKanan = 0;
  int jarakKiri = 0;
  delay(50);

  if (jarak <= 35){
    berhentiGerak();
    delay(300);
    gerakMundur();
    delay(1000);
    berhentiGerak();
    delay(300);
    jarakKanan = lihatKanan();
    delay(300);
    jarakKiri = lihatKiri();
    delay(300);

    if (jarak >= jarakKiri){
      belokKanan();
      berhentiGerak();
    }
    else{
      belokKiri();
      berhentiGerak();
    }
  }
  else{
    gerakMaju(); 
  }
    jarak = bacaPing();
}
