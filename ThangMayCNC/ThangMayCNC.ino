#include <EEPROM.h>
#include <Arduino.h>
#include <TimerOne.h>
#include <Servo.h> 

#include "BasicStepperDriver.h"


#define TIME_WAIT    5000
#define MOTOR_STEPS 200
#define RPM 200

#define MICROSTEPS 1

#define DIR 2
#define STEP 3
#define ENABLE 4 // optional (just delete ENABLE from everywhere if not used)

#define ty_le 40000// tỷ số truyền
//#define ty_le 4000 // tỷ số truyền

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);
Servo myservo; 
int servoPin = 12; 

byte data[4];




boolean slot1 = 0 ,slot2 = 0 ,slot3 = 0;



int32_t vi_tri_hien_tai, vi_tri=0;
int32_t goc_phai_xoay=0;
int32_t tag_value;
int32_t num_tag;
uint8_t last_state;


int disp_pin[7];  /* array for a-g pins of 7-Segment display */

void define_segment_pins(int a, int b, int c, int d, int e, int f, int g) /* Assigns 7-segment display pins to board */
{  
  disp_pin[0] = a;
  disp_pin[1] = b;
  disp_pin[2] = c;
  disp_pin[3] = d;
  disp_pin[4] = e;
  disp_pin[5] = f;
  disp_pin[6] = g;
}

void display_number(int num)  /* Function for displaying number (0-9) */
{
  switch(num)
  {
    case 0:
    digitalWrite(disp_pin[0], LOW); /* Drive disp_pin[0] to LOW */
    digitalWrite(disp_pin[1], LOW); /* Driving LOW turns on LED segment for common anode display */
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], LOW);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], HIGH); 
    break;
    case 1:
    digitalWrite(disp_pin[0], HIGH);  /* Drive disp_pin[7] to HIGH */
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], HIGH);  /* Driving HIGH turns off LED segment for common anode display */
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], HIGH);
    digitalWrite(disp_pin[6], HIGH);
    break;
    case 2:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], HIGH);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], LOW);
    digitalWrite(disp_pin[5], HIGH);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 3:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], HIGH);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 4:
    digitalWrite(disp_pin[0], HIGH);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], HIGH);
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 5:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], HIGH);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 6:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], HIGH);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], LOW);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 7:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], HIGH);
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], HIGH);
    digitalWrite(disp_pin[6], HIGH);
    break;
    case 8:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], LOW);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], LOW);
    break;
    case 9:
    digitalWrite(disp_pin[0], LOW);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], HIGH);
    digitalWrite(disp_pin[5], LOW);
    digitalWrite(disp_pin[6], LOW);
    break;
    default:
    digitalWrite(disp_pin[0], HIGH);
    digitalWrite(disp_pin[1], LOW);
    digitalWrite(disp_pin[2], LOW);
    digitalWrite(disp_pin[3], LOW);
    digitalWrite(disp_pin[4], LOW);
    digitalWrite(disp_pin[5], HIGH);
    digitalWrite(disp_pin[6], LOW);
    break;
  }
}



void write_eeprom_pos() // lưu góc hiện tại
{
  EEPROM.write(3,vi_tri_hien_tai);
}
void read_eeprom_pos()
{

  vi_tri_hien_tai = EEPROM.read(3);

}





uint8_t one, two, three;

void ScanKey()
{

  if(analogRead(A7) <100) //2
  {
     while (analogRead(A7) <100){digitalWrite(13,1);};
     digitalWrite(13,0);
    one =1;
  }

  if(analogRead(A6) <100) //2
  {
     Serial.print("val_adc2");
     Serial.println(analogRead(A6));
     while (analogRead(A6) <100){digitalWrite(13,1);};
     digitalWrite(13,0);
    two =1;
  }
  if(analogRead(A5) <100) //3
  {
     Serial.print("val_adc3");
     Serial.println(analogRead(A5));
     while (analogRead(A5) <100){digitalWrite(13,1);};
     digitalWrite(13,0);
    three =1;
  }


  
  if((digitalRead(A4) == 0))
  {
    while ((digitalRead(A4) == 0)) {digitalWrite(13,1);};
    digitalWrite(13,0);
    one =1;
  }
  if((digitalRead(A3) == 0))
  {
    while ((digitalRead(A3) == 0)) {digitalWrite(13,1);};
    digitalWrite(13,0);
    two =1;
  }
  if((digitalRead(A2) == 0))
  {
    while ((digitalRead(A2) == 0)) {digitalWrite(13,1);};
    digitalWrite(13,0);
    two =1;
  }
  if((digitalRead(A1) == 0))
  {
    while ((digitalRead(A1) == 0)) {digitalWrite(13,1);};
    digitalWrite(13,0);
    three =1;
  }
  
}

void Buzz()
{
  digitalWrite(13,1);
  delay(200);
  digitalWrite(13,0);
  delay(200);
  digitalWrite(13,1);
  delay(200);
  digitalWrite(13,0);
  delay(200);
  digitalWrite(13,1);
  delay(200);
  digitalWrite(13,0);
  delay(200);
}

void ControlStep()
{
  int vitri;
  
  if(one)
  {
    if(last_state==3)
    {
      vi_tri = 1 - vi_tri_hien_tai;
    stepper.rotate((vi_tri*ty_le)/2);
    display_number(2);
    stepper.rotate((vi_tri*ty_le)/2);
    vi_tri_hien_tai = 1;
    write_eeprom_pos();
    one=0;
     Serial.println(vi_tri_hien_tai);
     display_number(1);
     
     Buzz();
    Timer1.detachInterrupt();
    myservo.attach(servoPin);
    myservo.write(0);
    delay(TIME_WAIT);
    myservo.write(180);
    delay(1000);
    myservo.detach();
    }
    else
    {
    vi_tri = 1 - vi_tri_hien_tai;
    stepper.rotate(vi_tri*ty_le);
    vi_tri_hien_tai = 1;
    write_eeprom_pos();
    one=0;
     Serial.println(vi_tri_hien_tai);
     display_number(1);
     
     Buzz();
     Timer1.detachInterrupt();
    myservo.attach(servoPin);
    myservo.write(0);
    delay(TIME_WAIT);
    myservo.write(180);
    delay(1000);
    myservo.detach();
    }
    last_state=1;
  }
  if(two)
  {
    vi_tri = 2-vi_tri_hien_tai;
    stepper.rotate(vi_tri*ty_le);
    vi_tri_hien_tai = 2;
    write_eeprom_pos();
    two=0;
     Serial.println(vi_tri_hien_tai);
     display_number(2);
     Buzz();
    Timer1.detachInterrupt();
    myservo.attach(servoPin);
    myservo.write(0);
    delay(TIME_WAIT);
    myservo.write(180);
    delay(1000);
    myservo.detach();
    last_state=2;
  }
  if(three)
  {
    if(last_state==1)
    {
    vi_tri = 3-vi_tri_hien_tai;
    stepper.rotate((vi_tri*ty_le)/2);
    display_number(2);
    stepper.rotate((vi_tri*ty_le)/2);
    vi_tri_hien_tai = 3;
    write_eeprom_pos();
    three=0;
    Serial.println(vi_tri_hien_tai);
    display_number(3);
    Buzz();
    Timer1.detachInterrupt();
    myservo.attach(servoPin);
    myservo.write(0);
    delay(TIME_WAIT);
    myservo.write(180);
    delay(1000);
    myservo.detach();
    }
    else
    {
    vi_tri = 3-vi_tri_hien_tai;
    stepper.rotate(vi_tri*ty_le);
    vi_tri_hien_tai = 3;
    write_eeprom_pos();
    three=0;
    Serial.println(vi_tri_hien_tai);
    display_number(3);
    Buzz();
    Timer1.detachInterrupt();
    myservo.attach(servoPin);
    myservo.write(0);
    delay(TIME_WAIT);
    myservo.write(180);
    delay(1000);
    myservo.detach();
    }
    last_state=3;
  }
  Timer1.initialize(150000);
  Timer1.attachInterrupt(ScanKey);
  
  interrupts();

    
  
}

void setup() {
  
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  display_number(0);
  Timer1.initialize(150000);
  Timer1.attachInterrupt(ScanKey);
  
  interrupts();
  define_segment_pins(11,10,9,8,7,6,5);  /* a-g segment pins to Arduino */
  read_eeprom_pos();
  last_state=vi_tri_hien_tai;
  display_number(vi_tri_hien_tai);
  stepper.begin(RPM, MICROSTEPS);
  
  
  Serial.begin(9600);   
  Serial.println(vi_tri_hien_tai);
}

void loop() {

  ControlStep();

 

}
