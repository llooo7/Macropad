#include <Bounce.h>

#define REVERSED false                      //if your controller is reversed change it to true

int val = 0;
int previousval = 0;
int val2 = 0;
int longpress = 2000;
Bounce button0 = Bounce(0, 10);
Bounce button1 = Bounce(1, 10);
Bounce button2 = Bounce(2, 10);
Bounce button3 = Bounce(3, 10);
Bounce button4 = Bounce(4, 10);

struct multiPress
{
  bool counting = false;
  int count = 0;
};

multiPress multiButton4;
multiPress multiButton3;
multiPress multiButton1;

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
  
 /* 
if (button1.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
  Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
}*/

if (button2.fallingEdge()) {
  Keyboard.press(KEY_MEDIA_PREV_TRACK);
  Keyboard.release(KEY_MEDIA_PREV_TRACK);
}

//BUTTON 1 starts here

if (button1.fallingEdge()) {
  multiButton1.counting = true;
  }

if (button1.risingEdge()) {
  multiButton1.counting = false;
  if (multiButton1.count < longpress) {
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
  }
  multiButton1.count = 0;
}

if (multiButton1.counting==true)
{
  multiButton1.count++;
  if(multiButton1.count > longpress)
  {
    Keyboard.set_modifier(MODIFIERKEY_GUI | MODIFIERKEY_SHIFT);
    Keyboard.send_now();
    
    Keyboard.set_key1(KEY_BACKSLASH);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
}

//BUTTON 3 starts here

if (button3.fallingEdge()) {
  multiButton3.counting = true;
  }

if (button3.risingEdge()) {
  multiButton3.counting = false;
  if (multiButton3.count < longpress) {
    Keyboard.set_modifier(MODIFIERKEY_GUI);
    Keyboard.send_now();
    
    Keyboard.set_key1(KEY_4);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  multiButton3.count = 0;
}

if (multiButton3.counting==true)
{
  multiButton3.count++;
  if(multiButton3.count > longpress)
  {
    Keyboard.set_modifier(MODIFIERKEY_SHIFT | MODIFIERKEY_GUI);
    Keyboard.send_now();
    
    Keyboard.set_key1(KEY_L);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
}

//BUTTON 4 starts here

if (button4.fallingEdge()) {
 // Keyboard.press(KEY_MEDIA_MUTE);
 // Keyboard.release(KEY_MEDIA_MUTE);
  multiButton4.counting = true;
  }

if (button4.risingEdge()) {
  multiButton4.counting = false;
  if (multiButton4.count < longpress) {
    Keyboard.press(KEY_MEDIA_MUTE);
    Keyboard.release(KEY_MEDIA_MUTE);
  }
  multiButton4.count = 0;
}

if (multiButton4.counting==true)
{
  multiButton4.count++;
  if(multiButton4.count > longpress)
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
}
