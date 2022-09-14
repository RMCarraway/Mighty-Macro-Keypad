#include <Bounce2.h>
#include <BleKeyboard.h>

//////////Application: Arduino Coding////////////

// Functions for Button Control

int charDelay = 25; // UPDATE THIS CODE -- Amount of time between keypresses to avoid key buffer overflows

// initButtons loops through the array of Bounce2 buttons and attaches them as inputs.
// It also sets an interval of 25ms for responsiveness
void initButtons() {

  for (int i = 0; i < 9; i++) {
    buttons[i].attach(buttonPins[i], INPUT);
    buttons[i].interval(25);
  }
}

// readButtons loops through the array of Bounce2 buttons and updates each of them.
// It then checks to see if any button has risen and calls sendKey() if it has.
void readButtons() {

  for (int i = 0; i < 9; i++) {
    buttons[i].update();
    if (buttons[i].rose()) {
      sendKey(i);
      sendCompound(i);
      
    }
  }

}

// sendKey takes one argument (int k) and uses a switch/case structure to either call the
// sendShortcut(), sendCompound(), or sendMacro() functions. You can also create your own custom functions if needed.
void sendKey(int k) {

  switch (k) {

    case 0: //Ve(r)ify----button1
      sendShortcut('r');
      break;

    case 1: //save sketch----button 2
      sendShortcut('s');
      break;

    case 2: //Upload---------button 3
      sendShortcut('u');
      break;

    case 3: //auto align------button 4
      sendShortcut('t');
      break;

    case 4: //Find ----------button 5
      sendShortcut('f');
      break;

    case 5: //Open Serial Monitor------button 6
      sendCompound('m');
      break;

    case 6: //Write For Loop Template--------button 7
      sendMacro("for (int i = 0; i <= x; i++){someInstruction}",15);
      break;

    case 7: //Write If/Else Statement Template-------button 8
      sendMacro("if ( x someCondition y){someInstruction} else {someInstruction}",15);
      break;

    case 8: //Make Array Template ----------button 9
      sendMacro("someType myArray[someInt] = {someValue,someValue,someValue}",15);
      break;

  }
}

// sendShortcut takes one argument (char c) and combines it with a modifier (CRTL, CMD, ALT, SHIFT, etc.)
// Remember to delay between each press, and release each key. Call releaseAll before ending this function.
void sendShortcut(char c) {
  //presses control+character
  bleKeyboard.press(KEY_LEFT_CTRL); delay(charDelay);
  bleKeyboard.press(c); delay(charDelay);
  bleKeyboard.release(c); delay(charDelay);
  bleKeyboard.release(KEY_LEFT_CTRL); delay(charDelay);
  bleKeyboard.releaseAll();
}

// sendCompound takes one argument (char c) and combines it with multiple modifiers (CRTL, CMD, ALT, SHIFT, etc.)
// Remember to delay between each press, and release each key. Call releaseAll before ending this function.
void sendCompound(char c) {
  //presses Control+Shift+character
  bleKeyboard.press(KEY_LEFT_CTRL); delay(charDelay);
  bleKeyboard.press(KEY_LEFT_SHIFT); delay(charDelay);
  bleKeyboard.press(c); delay(charDelay);
  bleKeyboard.release(c); delay(charDelay);
  bleKeyboard.release(KEY_LEFT_SHIFT); delay(charDelay);
  bleKeyboard.release(KEY_LEFT_CTRL); delay(charDelay);
  bleKeyboard.releaseAll();

}

// sendMacro takes one argument (String s) and sends the string one character at a time.
void sendMacro(String s, int d) {
  int l = s.length() + 1;           // Determine length of string
  char c[l];                        // Create array for characters
  s.toCharArray(c, l);              // Copy characters to array
  for (int i = 0; i < l - 1; i++) { // Loop through character array
    char p = c[i];                  // Get the current character
    bleKeyboard.press(p); delay(d); // Press/Release the key w/ delay
    bleKeyboard.release(p); delay(d);
  }
  bleKeyboard.releaseAll();
}
