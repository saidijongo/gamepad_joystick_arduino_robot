// Include necessary libraries
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "le3dp_rptparser.h" // Include the report parser for Logitech gamepad

// Define USB objects
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

// Define joystick events
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

// Define pin assignments
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
#define BUZZER 8

// Define musical notes frequencies
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523

// Define arrays for button melodies and durations
int buttonXMelody[] = {NOTE_C4};
int buttonXDurations[] = {8};
int buttonAMelody[] = {NOTE_E4};
int buttonADurations[] = {8};
int buttonBMelody[] = {NOTE_G4};
int buttonBDurations[] = {8};
int buttonYMelody[] = {NOTE_C5};
int buttonYDurations[] = {8};

// Define functions to play melodies
#define playButtonXMelody() playMelody(buttonXMelody, buttonXDurations, 1)
#define playButtonAMelody() playMelody(buttonAMelody, buttonADurations, 1)
#define playButtonBMelody() playMelody(buttonBMelody, buttonBDurations, 1)
#define playButtonYMelody() playMelody(buttonYMelody, buttonYDurations, 1)

// Define global variables
volatile int ledPin = 0;
volatile byte F710Slider = 0x08; // Default value
volatile boolean beepFlag = false;
byte F710SliderLeft = 0x00; // Direction
byte F710SliderRight = 0x00; // Buttons
boolean F710ButtonX = false;
boolean F710ButtonA = false;
boolean F710ButtonB = false;
boolean F710ButtonY = false;

// Setup function
void setup() {
  // Initialize pins for LEDs and buzzer
  for (ledPin = 2; ledPin < 9; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }

  // Initialize serial communication
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect
#endif
  Serial.println("Start");

  // Initialize USB communication
  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
  delay(200);
  
  // Set the report parser for the Logitech gamepad
  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1);
}

// Main loop function
void loop() {
  // Process USB tasks
  Usb.Task();
}

// Function to handle gamepad events
void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
  // Print gamepad event data
  Serial.print("X: ");
  PrintHex<uint16_t>(evt->x, 0x80);
  Serial.print(" Y: ");
  PrintHex<uint16_t>(evt->y, 0x80);
  Serial.print(" Hat Switch: ");
  PrintHex<uint8_t>(evt->hat, 0x80);
  Serial.print(" Twist: ");
  PrintHex<uint8_t>(evt->twist, 0x80);
  Serial.print(" Slider: ");
  F710Slider = evt->slider;
  PrintHex<uint8_t>(F710Slider, 0x80);
  Serial.print(" Buttons A: ");
  PrintHex<uint8_t>(evt->buttons_a, 0x80);
  Serial.print(" Buttons B: ");
  PrintHex<uint8_t>(evt->buttons_b, 0x80);
  Serial.println("");

  // Clear all LED for joystick buttons
  for (ledPin = 2; ledPin < 8; ledPin++) {
    digitalWrite(ledPin, LOW);
  }
  
  // Extract gamepad button states
  F710SliderLeft = F710Slider & 0x0F;
  F710SliderRight = F710Slider & 0xF0;
  F710ButtonX = F710SliderRight & 0x10;
  F710ButtonA = F710SliderRight & 0x20;
  F710ButtonB = F710SliderRight & 0x40;
  F710ButtonY = F710SliderRight & 0x80;

  // Handle button presses
  if (F710ButtonX) playButtonXMelody();
  if (F710ButtonA) playButtonAMelody();
  if (F710ButtonB) playButtonBMelody();
  if (F710ButtonY) playButtonYMelody();
}

// Function to play a melody
void playMelody(int *melody, int *noteDurations, int notesLength) {
  for (int thisNote = 0; thisNote < notesLength; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
}
