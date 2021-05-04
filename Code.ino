const int go = 3;   /* DC motor forward direction , Pulse Width Modulation, or PWM, is a technique for 
getting analog results with digital means.Arduino pwm pins = 3,5,6,9,10,11  (There are lightning-like signs next to them.)
*/
const int back = 5; // pwm pin of the reverse rotation
const int button = 2;
volatile boolean currentButtonValue = false; // current value on button
volatile boolean lastButtonValue = false;    // last value value on button
boolean flag = true;                         //The flag I will use to check the direction of the motor

#define Pot A0 // analog pin I will read the value of the potentiometer

/*
The logic I have established in the creation of 3 seconds and the instant response of the button
I wait for very short periods of time and I keep the durations of these waits in my variable named delayTimeSum.
When the button is pressed, there is an instant response because these delay times are very short.
If the total delay time is 3000 milliseconds I change the direction of the motor and reset the delayTimeSum.
*/
int delayTimeSum = 0; 

void setup()
{
    Serial.begin(9600);  // I start the communication to suppress the potentiometer and the delay time to the screen.
    pinMode(go, OUTPUT); //Setting pwm outputs
    pinMode(back, OUTPUT);
}

void loop()
{

    int potentiometerValue = analogRead(Pot);                      // reading the value from the potentiometer
    potentiometerValue = map(potentiometerValue, 0, 1023, 0, 255); //Analog output values must be between 0 and 256 in Arduino, but the analog input value is 10 bits.
    // We have to rate the 10-bit data we read in analog form to be 8 bits. I use the map function for this.
    // Serial.println(potentiometerValue);

    if (flag)
    {
        analogWrite(go, potentiometerValue); // I make it rotate clockwise so that the value I read from the potentiometer is my motor speed.
        analogWrite(back, 0);                //The backward movement should be off
    }
    else
    {
        analogWrite(go, 0);                    // The forward movement should be off
        analogWrite(back, potentiometerValue); // I make it rotate counter clockwise so that the value I read from the potentiometer is my motor speed.
    }

    //// Reading button value 
    currentButtonValue = digitalRead(2);
    if (lastButtonValue != currentButtonValue)  // my control to make sure that the button changes just one time with a continuous press
    {
        if (digitalRead(2) == HIGH) // If the button pushed 
        {
            flag = !flag;     // changing direction flag
            delayTimeSum = 0; // reset time for 3 seconds
        }
    }
    lastButtonValue = currentButtonValue;
    ///////////////////

    //// Time Control
    delayTimeSum += 50; // adding time for Total running time
    ///Serial.println(delayTimeSum);
    if (delayTimeSum == 3000) // if the total delay equals 3 second we have to change direction
    {
        flag = !flag;     // changing direction
        delayTimeSum = 0; // reset total time delay
    }
    else // else waiting 50 miliseconds
    {
        delay(50);
    }
}
