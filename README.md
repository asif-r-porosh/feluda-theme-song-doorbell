# 834 Bytes of Feluda

Satyajit Ray's signature score — theme tune of Feluda, as a doorbell.

https://github.com/user-attachments/assets/c79a2e3b-6780-4704-9e8d-c0a3ea4733b7


---

## How It Works

Doorbell button on 220V AC mains → PC817 optocoupler → ATtiny13A RESET pin pulled LOW → MCU resets → `setup()` plays melody once with RGB LED accompaniment → `SLEEP_MODE_PWR_DOWN`.

No interrupt handler. No event loop. Hardware reset as the doorbell event.

Audio: square wave bit-banged on PB4 → PAM8403 audio amplifier → 4Ω 3W speaker.

Power: Nokia BL-5C LiPo (or any 1S cell) → TP4056 charge/protection module. PAM8403 SHDN pulled LOW when idle.

Compiles to **834 bytes** (81% of ATtiny13A flash). 190 bytes remaining.

---

## Bill of Materials

| Ref | Component |
|-----|-----------|
| IC1 | ATtiny13A |
| OPT1 | PC817 Optocoupler |
| MOD1 | PAM8403 Audio Amplifier board |
| MOD2 | TP4056 LiPo Charge/Protection board |
| D1 | IN4007 (reverse protection / AC half-cycle bypass for optocoupler LED) |
| LED1 | Red LED 3mm |
| LED2 | Green LED 3mm |
| LED3 | Blue LED 3mm |
| R1 | 10K 0.25W |
| R2 | 1K 0.25W |
| R3 | 100K 0.25W |
| VR1 | 50K trimmer (volume) |
| C1 | 0.1µF Ceramic |
| C2 | 1µF Polar |
| SW1 | Momentary push switch |
| SPK1 | 4 Ohm 3W speaker |
| B1 | Nokia BL-5C or any 1S LiPo |
| H1 | 7 Pin female header |
| H2, H3 | 2 Pin male header |
| — | 8 Pin IC socket |
| — | Strip or Perf board, 10×10 holes |

> **Note:** R3 (100K, 0.25W) on the 220V mains side dissipates ~0.484W — over its rated value. Safe for momentary use (SW1 is a doorbell push). For a revised build, use a 1W rated resistor or an X-rated capacitor dropper.

---

## Build

**Arduino IDE settings:**

Board package: [MicroCore](https://github.com/MCUdude/MicroCore) by MCUdude

| Setting | Value |
|---------|-------|
| Board | ATtiny13 |
| BOD | Disabled |
| EEPROM | Not retained |
| Clock | 4.8 MHz internal oscillator |
| Bootloader | None |
| Programmer | Arduino as ISP |

Flash via USBasp or Arduino as ISP. Wiring reference in `resources/attiny13-with-usbasp.png`.

**Schematic and layout:** `hardware/feluda_doorbell.png`
**Layout source:** [DIY Layout Creator 4.37.0](https://github.com/bancika/diy-layout-creator/releases/tag/v4.37.0)

---

## RTTTL

The melody notation is in `firmware/feluda_doorbell/feluda.rtttl.txt`. Not used at runtime — hardcoded as note frequencies and durations in firmware. Documented for portability.

**[▶ Play it in your browser](https://asif-r-porosh.github.io/feluda-theme-song-doorbell/)**

---

## Repository Structure

```
.
├── firmware
│   ├── feluda_doorbell
│   │   └── feluda_doorbell.ino
│   └── feluda.rtttl.txt
├── hardware
│   ├── feluda_doorbell.diy
│   └── feluda_doorbell.png
├── index.html
├── LICENSE-CERN-OHL-P
├── LICENSE-MIT
├── media
│   ├── satyajit-feluda.jpg
│   ├── satyajit-feluda.mp4
│   ├── theme-tune-of-feluda.mp3
│   └── theme-tune-of-feluda.wav
├── README.md
└── resources
    ├── arduino_ide_settings.png
    ├── attiny13-with-usbasp.png
    ├── attiny13a-pinouts.jpg
    ├── oshw-logo-400-px.png
    ├── PC817-IC-Pinout.png
    └── PC817-Internal-Pins.png
```

---

## License

- **Firmware** (`firmware/`) — [MIT](LICENSE-MIT)
- **Hardware** (`hardware/`) — [CERN OHL-P v2](LICENSE-CERN-OHL-P)

---

**Designed and developed by [Asif R. Porosh](https://uraal.online) · Rev 1.0 · 2023**
