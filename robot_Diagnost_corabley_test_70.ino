#include <NewPing.h>
//----------------------------------------------------------------------------------
#define STEP_PIN 15
#define DIR_PIN 14  //Направление вращения
#define ENABLE_PIN 16
//----------------------------------------------------------------------------------
#define EN_PIN_1_PER 50
#define EN_PIN_2_PER 51
#define EN_PIN_1_ZAD 52
#define EN_PIN_2_ZAD 53
#define EN_PIN_1_R 46
#define EN_PIN_2_R 47
#define EN_PIN_1_L 48
#define EN_PIN_2_L 49
//----------------------------------------------------------------------------------
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 200
//----------------------------------------------------------------------------------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//----------------------------------------------------------------------------------
int kol_opusk = 3;
int shagi_1 = 10000;
int shagi_2 = shagi_1 * (kol_opusk - 1);
int ping;
int start_r = 0;
int start_l = 0;
const byte D_encInt_PIN = 18;
const byte U_encInt_PIN = 19;
const byte L_encInt_PIN = 20;
const byte R_encInt_PIN = 21;
volatile long L_enc = 0;
volatile long R_enc = 0;
volatile long D_enc = 0;
volatile long U_enc = 0;
int con;
int v_r;
int v_l;
int error;
int old_error = 0;
double error_sum = 0;
double cur_time;
double old_time = 0;
double dt;
double u;
float kp = 0.06;
float ki = 0.03;
float kd = kp / 10;
float kp_2 = 0.14;
float ki_2 = 0.03;
float kd_2 = kp_2 / 10;
//----------------------------------------------------------------------------------
void schit_datchik() {
  ping = sonar.ping_cm();
  while (ping == 0) {
    ping = sonar.ping_cm();
  }
}
//----------------------------------------------------------------------------------
void schit_tact() {
  con = digitalRead(23);
}
//----------------------------------------------------------------------------------
void start_ezda(){
  U_enc = 0;
  D_enc = 0;
  L_enc = 0;
  R_enc = 0;
  old_error = 0;
  error_sum = 0;
  start_r = 100;
  start_l = 100;
  old_time = micros();
}
//----------------------------------------------------------------------------------
void go_stop() {
  analogWrite(7, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  analogWrite(6, 0);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  analogWrite(44, 0);
  analogWrite(45, 0);
}
//----------------------------------------------------------------------------------
void go_vpered_po_en(int schet_znach) {
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  for (int schet = 0; schet < schet_znach; schet++) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp_2 + (error - old_error) / dt * kd_2 + error_sum * ki_2;
    if (start_r < 130){
      start_r = start_r + 10;
    }
    if (start_l < 130){
      start_l = start_l + 10;
    }
    v_r = start_r - u;
    v_l = start_l + u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 50) {
      v_r = 50;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 50) {
      v_l = 50;
    }
    analogWrite(7, v_r);
    analogWrite(44, v_l);
    Serial.print(" | U_enc = ");
    Serial.print(U_enc);
    Serial.print(" | D_enc = ");
    Serial.print(D_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_vpered() {
  analogWrite(7, 100);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  analogWrite(44, 130);
}
//----------------------------------------------------------------------------------
void go_nazad_po_en(int schet_znach) {
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  for (int schet = 0; schet < schet_znach; schet++) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp_2 + (error - old_error) / dt * kd_2 + error_sum * ki_2;
    if (start_r < 130){
      start_r = start_r + 10;
    }
    if (start_l < 130){
      start_l = start_l + 10;
    }
    v_r = start_r - u;
    v_l = start_l + u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 50) {
      v_r = 50;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 50) {
      v_l = 50;
    }
    analogWrite(7, v_r);
    analogWrite(44, v_l);
    Serial.print(" | U_enc = ");
    Serial.print(U_enc);
    Serial.print(" | D_enc = ");
    Serial.print(D_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
void go_nazad_do_en(int schet_znach) {
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  while(U_enc < schet_znach and D_enc < schet_znach) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp_2 + (error - old_error) / dt * kd_2 + error_sum * ki_2;
    if (start_r < 130){
      start_r = start_r + 10;
    }
    if (start_l < 130){
      start_l = start_l + 10;
    }
    v_r = start_r - u;
    v_l = start_l + u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 50) {
      v_r = 50;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 50) {
      v_l = 50;
    }
    analogWrite(7, v_r);
    analogWrite(44, v_l);
    Serial.print(" | U_enc = ");
    Serial.print(U_enc);
    Serial.print(" | D_enc = ");
    Serial.print(D_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -140){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
void go_nazad() {
  analogWrite(7, 100);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  analogWrite(44, 130);
}
//----------------------------------------------------------------------------------
void go_vpravo_po_en(int schet_znach) {
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
    for (int schet = 0; schet < schet_znach; schet++) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp + (error - old_error) / dt * kd + error_sum * ki;
    v_r = 180 + u;
    v_l = 170 - u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 100) {
      v_r = 100;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 100) {
      v_l = 100;
    }
    analogWrite(6, v_l);
    analogWrite(45, v_r);
    Serial.print(" | R_enc = ");
    Serial.print(R_enc);
    Serial.print(" | L_enc = ");
    Serial.print(L_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_vpravo_do_en(int schet_znach) {
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  while (R_enc < schet_znach and L_enc < schet_znach) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp + (error - old_error) / dt * kd + error_sum * ki;
    v_r = 180 + u;
    v_l = 170 - u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 100) {
      v_r = 100;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 100) {
      v_l = 100;
    }
    analogWrite(6, v_l);
    analogWrite(45, v_r);
    Serial.print(" | R_enc = ");
    Serial.print(R_enc);
    Serial.print(" | L_enc = ");
    Serial.print(L_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_vpravo() {
  analogWrite(6, 115);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  analogWrite(45, 100);
}
//----------------------------------------------------------------------------------
void go_vlevo_po_en(int schet_znach) {
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  for (int schet = 0; schet < schet_znach; schet++) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp + (error - old_error) / dt * kd + error_sum * ki;
    v_r = 180 + u;
    v_l = 170 - u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 100) {
      v_r = 100;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 100) {
      v_l = 100;
    }
    analogWrite(6, v_l);
    analogWrite(45, v_r);
    Serial.print(" | R_enc = ");
    Serial.print(R_enc);
    Serial.print(" | L_enc = ");
    Serial.print(L_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
void go_vlevo_do_en(int schet_znach) {
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  while (R_enc < schet_znach and L_enc < schet_znach) {
    cur_time = micros();
    error = U_enc - D_enc;
    dt = (cur_time - old_time) / 1000000.00;
    error_sum = error_sum + error * dt;
    u = error * kp + (error - old_error) / dt * kd + error_sum * ki;
    v_r = 180 + u;
    v_l = 170 - u;
    if (v_r > 255) {
      v_r = 255;
    }
    if (v_r < 100) {
      v_r = 100;
    }
    if (v_l > 255) {
      v_l = 255;
    }
    if (v_l < 100) {
      v_l = 100;
    }
    analogWrite(6, v_l);
    analogWrite(45, v_r);
    Serial.print(" | R_enc = ");
    Serial.print(R_enc);
    Serial.print(" | L_enc = ");
    Serial.print(L_enc);
    Serial.print(" | v_l = ");
    Serial.print(v_l);
    Serial.print(" | v_r = ");
    Serial.print(v_r);
    Serial.print(" | error = ");
    Serial.println(error);
    if (error > 125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
    if (error < -125){
      U_enc = 0;
      D_enc = 0;
      L_enc = 0;
      R_enc = 0;
      error_sum = 0;
      old_error = 0;
    }
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_vlevo() {
  analogWrite(6, 115);
  digitalWrite(8, 1);
  digitalWrite(9, 0);
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  analogWrite(45, 100);
}
//----------------------------------------------------------------------------------
void go_do_stena(int rast_do_stena) {
  schit_datchik();
  start_ezda();
  while (ping > rast_do_stena) {
    schit_datchik();
    Serial.print("Датчик ");
    Serial.print(ping);
    Serial.print(" ");
    go_vpered_po_en(1);
    go_stop();
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_do_end_vlevo() {
  start_ezda();
  schit_datchik();
  while (ping < 20) {
    schit_datchik();
    Serial.print("Влево ");
    go_vlevo_po_en(1);
    go_stop();
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_ot_stena(int rast_ot_stena) {
  start_ezda();
  schit_datchik();
  while (ping < rast_ot_stena) {
    schit_datchik();
    go_nazad_po_en(1);
    go_stop();
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void go_do_start_vpravo() {
  start_ezda();
  schit_datchik();
  while (ping > 30) {
    schit_datchik();
    go_vpravo_po_en(1);
    go_stop();
  }
  go_stop();
}
//----------------------------------------------------------------------------------
void shagoyMotor_turn(int dir, int amount) {
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, dir);
  for (int x = 0; x < amount; x++) {
    digitalWrite(STEP_PIN, 1);
    delayMicroseconds(600);
    digitalWrite(STEP_PIN, 0);
  }
  digitalWrite(ENABLE_PIN, 1);
}
//----------------------------------------------------------------------------------
void L_enc_func() {
  L_enc++;
}

void R_enc_func() {
  R_enc++;
}
//----------------------------------------------------------------------------------
void D_enc_func() {
  D_enc++;
}

void U_enc_func() {
  U_enc++;
}
//----------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(STEP_PIN, OUTPUT);  // Настраиваем пины управления
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(23, INPUT);
  pinMode(22, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(L_encInt_PIN), L_enc_func, CHANGE);
  attachInterrupt(digitalPinToInterrupt(R_encInt_PIN), R_enc_func, CHANGE);
  attachInterrupt(digitalPinToInterrupt(D_encInt_PIN), D_enc_func, CHANGE);
  attachInterrupt(digitalPinToInterrupt(U_encInt_PIN), U_enc_func, CHANGE);
  digitalWrite(41, 1);
  digitalWrite(22, 1);
  go_do_stena(15);
  delay(270);
  go_do_end_vlevo();
  delay(100);
  go_do_start_vpravo();
  // go_vpravo_po_en(3);
  delay(500);
  while (ping < 40) {
    for (int schet = 0; schet < kol_opusk; schet++) {
      go_do_stena(8);
      // delay(200);
      schit_tact();  // колебровка по кнопке
      // start_ezda();
      while(con != 1){
        go_vpered_po_en(1);
        schit_tact();
      }
      start_ezda();
      go_nazad_do_en(60);  // конец колибровки
      // проведение неразрушающего контроля
      delay(400);
      Serial.println("1000000");
      delay(400);
      //
      go_ot_stena(8);
      //
      if (schet == (kol_opusk - 1)){
        delay(500);
        start_ezda();
        go_vpravo_do_en(60);
        go_stop();
        shagoyMotor_turn(1, shagi_2);
        delay(500);
        start_ezda();
        go_vpravo_do_en(60);
        schit_datchik();
        if (ping < 40){
          start_ezda();
          go_vlevo_do_en(60);
        }
        delay(500);
      }
      else{
        shagoyMotor_turn(0, shagi_1);
      }
    }
    schit_datchik();
  }
  Serial.println("2000000");
  Serial.println(kol_opusk);
}

void loop() {
  // put your main code here, to run repeatedly:
}
