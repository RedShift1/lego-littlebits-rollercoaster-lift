const int topSensor     = A0;
const int bottomSensor  = A1;
const int button        = 0;
const int motorOutput   = 5;
const int microBitOutput= 9;

const int lightLowThres      = 100;
const int lightHighThres     = 900;

const int MBIT_UP             = 5;  // Lift up display
const int MBIT_DOWN           = 35; // Lift down display
const int MBIT_NEUTRAL        = 20; // Neutral
const int MBIT_CTR            = 55; // Increment & show counter

const int LIFT_UNKNOWN        = 0; 
const int LIFT_GOINGUP        = 1;
const int LIFT_GOINGDOWN      = 2;
const int LIFT_DOWN           = 3;
const int LIFT_UP             = 4;
const int LIFT_STOPPED        = 5;

int liftState = LIFT_UNKNOWN;

int topReading    = 0;
int bottomReading = 0;
int buttonReading = 0;

void setup()
{
  pinMode(button,         INPUT);
  pinMode(topSensor,      INPUT);
  pinMode(bottomSensor,   INPUT);
  pinMode(motorOutput,    OUTPUT);
  pinMode(microBitOutput, OUTPUT);
  
  liftStop();
  Serial.begin(9600);
  Serial.println("Start");
}

void liftStop()
{
  Serial.println("Stopping motor");
  liftState = LIFT_STOPPED;
  analogWrite(motorOutput, 127);
  analogWrite(microBitOutput, MBIT_NEUTRAL);
}

void liftDown()
{
  Serial.println("Engage motor clockwise");
  liftState = LIFT_GOINGDOWN;
  analogWrite(motorOutput, 223);
  analogWrite(microBitOutput, MBIT_DOWN);
}

void liftUp()
{
  Serial.println("Engage motor counter-clockwise");
  liftState = LIFT_GOINGUP;
  analogWrite(motorOutput, 31);
  analogWrite(microBitOutput, MBIT_UP);
}

int whereIsLift()
{
  if(topReading < lightLowThres)
  {
    return LIFT_UP;
  }
  if(bottomReading < lightLowThres)
  {
    return LIFT_DOWN;
  }

  return LIFT_UNKNOWN;
}

void loop()
{
  delay(50);
  
  buttonReading   = digitalRead(button);
  topReading      = analogRead(topSensor);
  bottomReading   = analogRead(bottomSensor);
  
  /*Serial.print("bottom sensor: ");
  Serial.print(bottomReading);
  Serial.print(" top sensor: ");
  Serial.print(topReading);
  Serial.print(" button: ");
  Serial.println(buttonReading);*/

  // Lift at top
  if(liftState == LIFT_GOINGUP && whereIsLift() == LIFT_UP)
  {
    delay(15); // Make sure it's entirely at the top
    liftDown();
  }

  // Down after going down
  if(liftState == LIFT_GOINGDOWN && whereIsLift() == LIFT_DOWN)
  {
    liftStop();
    analogWrite(microBitOutput, MBIT_CTR);
  }

  // Activated through button when the lift is down
  if(buttonReading == 1 && whereIsLift() == LIFT_DOWN)
  {
    liftUp();
  }

  // Button press but we don't know where the lift is
  if(buttonReading == 1 && whereIsLift() == LIFT_UNKNOWN && liftState == LIFT_STOPPED)
  {
    liftUp();
  }
}


