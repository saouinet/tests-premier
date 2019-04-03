
typedef unsigned char ubyte;
typedef unsigned long int ulong;

#define TRACK_A        2
#define TRACK_B        3
#define BUTTON         4
#define LED            13
#define CYCLE_DURATION 1000

ulong milestone;
int value ;
ubyte oldTrackA;
ubyte newTrackA;
ubyte newTrackB;
ubyte encoder_status;

void setup()
{
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(TRACK_A, INPUT_PULLUP);
    pinMode(TRACK_B, INPUT_PULLUP);
    pinMode(BUTTON, INPUT_PULLUP);
    milestone += millis();


    
}

void loop()
{
    newTrackA = digitalRead(TRACK_A);
    newTrackB = digitalRead(TRACK_B);

    encoder_status = (oldTrackA << 2) | (newTrackA << 1) | newTrackB;

    switch(encoder_status)
    {
      case 5:
      case 2:
          value++;
          break;
      case 3:
      case 4:
          value--;
          break;
      default:
        break;      
    }

    oldTrackA = newTrackA;

    if(millis() >= milestone)
    {
        Serial.println(value);
        milestone += CYCLE_DURATION;
    }

    if(!digitalRead(BUTTON))
      value = 0;

    if(millis() & 0x200)
        digitalWrite(LED, 1);
    else
        digitalWrite(LED, 0);
}
