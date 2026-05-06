/**
 * 834 Bytes of Feluda
 * Satyajit Ray's signature score — theme tune of Feluda, as a doorbell.
 *
 * Designed and developed by Asif R. Porosh
 * https://github.com/asif-r-porosh/feluda-doorbell
 *
 * Built: 2023 | Published: 2026
 * Rev: 1.0
 *
 * License: MIT
 * See LICENSE-MIT in the root of this repository.
 *
 * Hardware:
 *   IC1  - ATtiny13A
 *   OPT1 - PC817 Optocoupler (mains isolation, doorbell trigger via RESET pin)
 *   MOD1 - PAM8403 Audio Amplifier board
 *   MOD2 - TP4056 LiPo Charge/Protection board
 *   SPK1 - 4 Ohm 3W speaker
 *   B1   - Nokia BL-5C or any 1S LiPo
 *
 * Notes:
 *   Melody notes sourced from a veteran YouTuber who transcribed them by ear
 *   and listed them in a video description. Note durations and rest periods
 *   were tuned by listening to the original score repeatedly until it
 *   sounded right. The math and the ear do not fully agree. The ear won.
 *
 *   Compiles to 834 bytes (81% of ATtiny13A flash). 190 bytes remaining.
 *
 *   Trigger mechanism: SW1 on 220V mains line → PC817 optocoupler →
 *   RESET pin pulled LOW → MCU resets → setup() runs melody → sleep.
 *   No interrupt handler. Hardware reset as the doorbell event.
 *
 * Board: ATtiny13 (MicroCore by MCUdude)
 * Clock: 4.8 MHz internal oscillator
 * Programmer: Arduino as ISP
 **/

#include <avr/sleep.h>

#define AMPLIFIER_EN_PIN 3
#define AUDIO_PIN 4
#define LED_R_PIN 0
#define LED_G_PIN 1
#define LED_B_PIN 2

#define LONG 600
#define SHORT 250

#define NOTE_C5_L note(523, LONG)
#define NOTE_B4_S note(494, SHORT)
#define NOTE_C5_S note(523, SHORT)
#define NOTE_D5_S note(587, SHORT)
#define NOTE_E5_L note(659, LONG)
#define NOTE_F5_S note(698, SHORT)
#define NOTE_E5_S note(659, SHORT)
#define NOTE_A4_S note(440, SHORT)
#define NOTE_G4_L note(392, LONG)

#define PAUSE delayMicroseconds(16383)

#define LED_R digitalWrite(LED_R_PIN, HIGH), digitalWrite(LED_G_PIN, LOW), digitalWrite(LED_B_PIN, LOW)
#define LED_G digitalWrite(LED_R_PIN, LOW), digitalWrite(LED_G_PIN, HIGH), digitalWrite(LED_B_PIN, LOW)
#define LED_B digitalWrite(LED_R_PIN, LOW), digitalWrite(LED_G_PIN, LOW), digitalWrite(LED_B_PIN, HIGH)
#define LED_O digitalWrite(LED_R_PIN, LOW), digitalWrite(LED_G_PIN, LOW), digitalWrite(LED_B_PIN, LOW)

void note(int frequency, int length) {
  int delayValue = 500000 / frequency;
  for (long i = 0; i < (long(frequency) * length / 2000); i++) {
    digitalWrite(AUDIO_PIN, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(AUDIO_PIN, LOW);
    delayMicroseconds(delayValue);
  }
  PAUSE;
  PAUSE;
  PAUSE;
}


void setup(void) {
  pinMode(AUDIO_PIN, OUTPUT);
  pinMode(AMPLIFIER_EN_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  digitalWrite(AMPLIFIER_EN_PIN, HIGH);
  delay(500);

  LED_R;
  NOTE_C5_L;
  LED_O;
  NOTE_C5_L;
  LED_R;
  NOTE_B4_S;
  LED_G;
  NOTE_C5_S;
  LED_B;
  NOTE_D5_S;
  LED_G;
  NOTE_E5_L;
  LED_O;
  NOTE_E5_L;
  LED_R;
  NOTE_F5_S;
  LED_G;
  NOTE_E5_S;
  LED_B;
  NOTE_D5_S;
  LED_B;
  NOTE_C5_L;
  LED_O;
  NOTE_C5_L;
  LED_R;
  NOTE_B4_S;
  LED_G;
  NOTE_C5_S;
  LED_B;
  NOTE_A4_S;
  LED_R;
  NOTE_G4_L;
  LED_O;
  PAUSE;
  LED_R;
  NOTE_C5_S;
  LED_G;
  NOTE_B4_S;
  LED_B;
  NOTE_C5_S;
  LED_O;

  digitalWrite(AMPLIFIER_EN_PIN, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}



void loop() {
}
