#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_L3GD20_U.h>

Adafruit_9DOF                 dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

void initSensors()
{
  if(!accel.begin())
  {
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void setup(void)
{
  Serial.begin(9600);
  //Serial.println(F("Adafruit 9 DOF Pitch/Roll/Heading Example")); 
  //Serial.println("");
  pinMode(6, OUTPUT);
  initSensors();  // iniciar sensor
}

void loop(void)
{
  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;

  // leer el estado de los sensores
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  // usar el algoritmo de fusion de la libreria para combinar las mediciones
  if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
  {
    /* 'orientation' should have valid .roll and .pitch fields */
  Serial.print(F("Orientation: "));
  Serial.print(orientation.roll);
  Serial.print(F(" "));
  Serial.print(orientation.pitch);
  Serial.print(F(" "));
  Serial.print(orientation.heading);
  Serial.println(F(""));
  }

  if (orientation.roll < -10 || orientation.roll > 10 || orientation.pitch < -10 || orientation.pitch > 10) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
  
  //delay(100);
}