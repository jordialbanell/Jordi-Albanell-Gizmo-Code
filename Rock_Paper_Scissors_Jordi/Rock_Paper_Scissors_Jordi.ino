#include <Servo.h>

/* Creator: Jordi Albanell Flores
 * Date: April 27th, 2019
 * Class:DE2-GIZMO Gizmo
 * Title: Rock Paper Scissors Code
 */

Servo myservo1;
Servo myservo2;

int pos = 0; //angle position of servos

int scissors = 0; //used for the code to know which gesture it deployed
int paper = 0; //used for the code to know which gesture it deployed

int randNumber = 0; //this integer will determine which gesture is deployed

int pushButtonG = 4; //GREEN button to play
int pushButtonR = 2; //RED button to restart

int ledred = 11;           // the PWM pin the red LED is attached to
int ledgreen = 12;       //the PWM pin the green LED is attached to
int ledyellow = 13;       //the PWM pin the yellow LED is attached to

int t = 300; //genral value for the delay in the code while playing rock paper scissors

void setup() {

  myservo1.attach(5);
  myservo2.attach(6);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(8, OUTPUT); //AIN1
  pinMode(7, OUTPUT); //BIN1
  pinMode(9, OUTPUT); //PWM2
  pinMode(3, OUTPUT); //PWM1

  pinMode(ledred, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledyellow, OUTPUT);

  pinMode(pushButtonG, INPUT);
  pinMode(pushButtonR, INPUT);

  int buttonStateG = digitalRead(pushButtonG);
  int buttonStateR = digitalRead(pushButtonR);

  for (pos = 0; pos < 90; pos += 1) { //resets the servo motors to 90 degrees, so not holding the pin back
    myservo1.write(pos);
    delay(2);                         //allow for the servo pin to move, without a delay, the pin would not have enough time to move
    myservo2.write(90 - pos);
    delay(2);
    }

}

void loop() {

  digitalWrite(ledred, LOW);                  // turn the LED off
  digitalWrite(ledyellow, LOW);              // turn the LED off
  digitalWrite(ledgreen, LOW);               // turn the LED off

  randNumber = random(1, 4);                 //1 is rock, 2 is scissors, 3 is paper

  if (buttonStateR == 1) {                   //reset button

    if (paper == 1) {                        //if paper was deployed, since both servos were deployed, they need to be put back to original position to hold pin back

      for (pos = 90; pos > 0; pos -= 1) {
        myservo1.write(90 - pos);
        delay(8);
        myservo2.write(pos);
        delay(8);
      }

      paper = 0;

    } else if (scissors == 1) {             //if only scissors was deployed, then servo2 has to be put back to original position to hold pin back

      for (pos = 90; pos > 0; pos--) {
        myservo2.write(pos);
        delay(8);
      }

      scissors = 0;

    }

  }

  if (buttonStateG == 1) {                   //start button is pressed

    delay(1000);                             //waits one second for player to get ready and pay attention
    Serial.println(randNumber);

    digitalWrite(ledred, HIGH);              // turn the red LED on
    delay(1000);
    digitalWrite(ledyellow, HIGH);           // turn the yellow LED on
    delay(1000);
    digitalWrite(ledgreen, HIGH);           // turn the green LED on
    digitalWrite(ledyellow, LOW);           // turn the yellow LED off
    digitalWrite(ledred, LOW);              //turn the red LED off
    delay(500);
    digitalWrite(8, HIGH);                  //run DC motor
    analogWrite(3, 255);                    //run at maximum speed

    delay(t);                               //this represents the amount of time the human is playing rock paper scissors
    Serial.println("rock");   

    delay(t);
    Serial.println("paper");

    delay(t);
    Serial.println("scissors");

    delay(t);

    if (randNumber == 1) {

      delay(1100);                          //the for loops below each take about one second to run, therefore the delay above had to be one second shorter, hence why one second is added here.
      Serial.println("rock");

    } else if (randNumber == 2) {

      Serial.println("scissors");
      delay(500);                          //this delay is added because since the last for loop takes the longest to run, everything had to be made quicker before to compensate
      scissors = 1;                        //this variable allows the code to know, once its played, that it deployed scissors so that it knows which servo motors to reset

      for (pos = 0; pos <= 90; pos += 1) {
        myservo2.write(pos);
        delay(2);
      }

      digitalWrite(8, HIGH);               //first the servos deploy before the motor stops so that when the motor stops, the hand is already showing a gesture
      analogWrite(3, 0);

    } else {

      Serial.println("paper");
      paper = 1;

      for (pos = 0; pos <= 90; pos += 1) {
        myservo1.write(90 - pos);
        delay(2);
        myservo2.write(pos);
        delay(2);
      }

      digitalWrite(8, HIGH);
      analogWrite(3, 0);

    }

    Serial.println("shoot");

    digitalWrite(8, HIGH);
    analogWrite(3, 0);

  }
}
