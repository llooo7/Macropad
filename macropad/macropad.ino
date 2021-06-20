#include <Bounce.h>

#define REVERSED false                      //if your controller is reversed change it to true

int val = 0;
int previousval = 0;
int val2 = 0;
bool counting = false;
int count = 0;
Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);
Bounce button2 = Bounce(2, 10);
Bounce button3 = Bounce(3, 10);
Bounce button4 = Bounce(4, 10);

void setup() {
pinMode(0, INPUT_PULLUP);
pinMode(1, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
}

void loop() {
  
button0.update();
button1.update();
button2.update();
button3.update();
button4.update();

// Buttons
if (button0.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_NEXT_TRACK);
  Keyboard.release(KEY_MEDIA_NEXT_TRACK);
  }
if (button1.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
  Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
}
if (button2.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_PREV_TRACK);
  Keyboard.release(KEY_MEDIA_PREV_TRACK);
}
if (button3.fallingEdge()) {
  Keyboard.set_modifier(MODIFIERKEY_GUI);
  Keyboard.send_now();
  
  Keyboard.set_key1(KEY_4);
  Keyboard.send_now();
  
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}
if (button4.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_MUTE);
  Keyboard.release(KEY_MEDIA_MUTE);
  counting = true;
  }

if (button4.risingEdge()) {
  counting = false;
  count = 0;
}

// Knob
val = analogRead(20);                      //read potentiometer value
  val = map(val, 0, 1023, 0, 101);          //map it to 102 steps
  if(REVERSED) {
    val = 101 - val;
  }
  if(abs(val - previousval) > 1) {          //check if potentiometer value has changed
    previousval = val;
    val /= 2;                               //divide it by 2 to get 51 steps
    while(val2 < val) {
      Keyboard.press(KEY_MEDIA_VOLUME_INC );
      Keyboard.release(KEY_MEDIA_VOLUME_INC );
      val2++;
      delay(2);
    }
    while(val2 > val) {
      Keyboard.press(KEY_MEDIA_VOLUME_DEC);
      Keyboard.release(KEY_MEDIA_VOLUME_DEC);    //turn volume down to appropiate level
      val2--;
      delay(2);
    }
  }

if (counting==true)
{
  count++;
  if(count > 2000)
  {
    Keyboard.set_modifier(MODIFIERKEY_GUI);
    Keyboard.send_now();
    
    Keyboard.set_key1(KEY_L);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
}

}
