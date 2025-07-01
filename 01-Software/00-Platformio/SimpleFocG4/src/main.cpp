#include <Arduino.h>
#include <SimpleFOC.h>
#include <Wire.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
float target_position = 0;

BLDCMotor motor = BLDCMotor(7);

BLDCDriver3PWM driver = BLDCDriver3PWM(IN1, IN2, IN3);

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_position, cmd); }

void setup() {
  // deactivate the OUT4 output
  pinMode(IN4,OUTPUT);
  digitalWrite(IN4,LOW);

  Wire.setClock(400000);
  Wire.begin();
  sensor.init(&Wire);
  motor.linkSensor(&sensor);

  Serial.begin(115200);
  SimpleFOCDebug::enable(&Serial);
  _delay(1000);
  Serial.println("AS5600 encoder initialized.");

  driver.voltage_power_supply = 7.4;
  driver.pwm_frequency = 4000;
  driver.init();
  motor.linkDriver(&driver);

  // limiting motor movements
  motor.voltage_limit = 6;   // [V]
  motor.velocity_limit = 20; // [rad/s]
  motor.KV_rating = 1000;
  motor.controller = MotionControlType::angle_openloop;

  // PID settings for velocity control
  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 2.0;
  motor.PID_velocity.D = 0;
  motor.LPF_velocity.Tf = 0.01;


  // motor.useMonitoring(Serial);
  // motor.foc_modulation = FOCModulationType::SpaceVectorPWM;


  // Initialize motor and FOC
  motor.init();
  motor.initFOC();

  command.add('T', doTarget, "target angle");


  Serial.println("Motor ready!");
  _delay(1000);
}

void loop() {
  sensor.update();
  motor.move(target_position);
  
  command.run();
}