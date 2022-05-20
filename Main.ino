#include<LiquidCrystal.h>
#include<EEPROM.h>

//Variables

#define backlight 13
#define motor 10
#define moistSensor A0

//EEPROM Address
#define AmotorTimes 'E1'
#define AmaxMoist 'E2'
#define AminMoist 'E3'

//LED pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//EEPROM values
unsigned int motorTimes;
int maxMoist;
int minMoist;

int sensorReading;
int incommingBytes;
bool isTurning;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  pinMode(motor, OUTPUT);
  pinMode(backlight, OUTPUT);
  pinMode(sensorReading, INPUT); //--> Not necessary in UNO boards
  digitalWrite(backlight, HIGH);
  digitalWrite(motor, LOW);

  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.clear();

  for(int n = 0; n<=5; n++)
  {
    for(int i = 12; i<=15; i++)
    {
      lcd.setCursor(0,0);
      lcd.print("initializing");
      lcd.setCursor(i,1);
      lcd.print("-");
      delay(80);
      Serial.println(i);
    }
    delay(50);
    lcd.clear();
  }
}

void loop() 
{
  sensorReading = analogRead(moistSensor);
  //Serial.println(sensorReading);
  
  if(sensorReading > 950)
  {
    turnOnMotor(true);
    lcd.setCursor(0, 0);
    lcd.print("Moisture : Low");
    if(minMoist > sensorReading) minMoist = sensorReading;
    //Serial.print("Moisture : Low");
  }
  
  else 
  {
    turnOnMotor(false);
  }

  if(sensorReading < 300)
  {
    lcd.setCursor(0, 0);
    lcd.print("Moisture: High");
    if(maxMoist < sensorReading) maxMoist = sensorReading;
    //Serial.print("Moisture: High");
  }
  else if(sensorReading > 300 && sensorReading < 950)
  {
    lcd.setCursor(0, 0);
    lcd.print("Moisture: AVRG");
    //Serial.print("Mosture: Average");
  }

  //Serial Inputs
  if(Serial.available()>0)
  {
    incommingBytes = Serial.read();
    if(incommingBytes==97) //94 in the ASCII value of a
    { 
      showData();
    }
  }

}

void turnOnMotor(bool motorState)
{
  lcd.setCursor(1, 1);
  if (motorState==true)
  {
    if (isTurning==false) 
    {
      isTurning = true;
      motorTimes++;
    }
    lcd.print("Motor is ON ");
    //Serial.print("Turning On Motor ");
    digitalWrite(motor, HIGH);
    return;
  }
  lcd.print("Motor is OFF");
  if(isTurning==true) isTurning = false;
  //Serial.print("Turning Off Motor");
  digitalWrite(motor, LOW);
  return;
}

int showData()
{

  //updating values
  dataMgr(AmotorTimes, motorTimes);
  dataMgr(AminMoist, minMoist);
  dataMgr(AmaxMoist, maxMoist);

  //Print motorTimes to the Serial Monitor
  Serial.print("Total motor spins: ");
  Serial.print(motorTimes);
  Serial.print(" Times\n");

  //Minimum moisture  
  Serial.print("Minimum Recorded Moisture: ");
  Serial.print(minMoist);
  Serial.print("\n");

  //Maximum moisture
  Serial.print("Maximum Recorded Moisture: ");
  Serial.print(maxMoist);
  Serial.print("\n");
}


int dataMgr(int address, int value)
{
  int savedValue = EEPROM.read(address);
  if(value > savedValue)
  {
    EEPROM.write(address, value);
    return value;
  }
  return savedValue;
}
