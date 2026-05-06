# 834 Bytes of Feluda

Satyajit Ray's signature score — theme tune of Feluda, as a doorbell.

> *If you just felt something you can't quite name — welcome. You've heard the Feluda theme. You're now mildly infected, and there's no cure.*

**[▶ Listen: theme-tune-of-feluda.wav](media/theme-tune-of-feluda.wav)**
*Recorded directly from the ATtiny13A output. No processing. No cleanup.*

---

## The Idea

Standard doorbells are an insult to the ear. The Westminster chime is competent — it announces, it fulfills its contract, it has no opinion about Satyajit Ray.

I had an ATtiny13A in a parts drawer. 1 kilobyte of flash. 64 bytes of RAM. The question of whether fitting Feluda's theme into it was feasible occurred to me briefly, then I decided it was irrelevant. The fun was in finding out.

The melody compiles to **834 bytes** — 81% of available flash. 190 bytes remaining.

---

## How It Works

**Trigger mechanism:** The doorbell button sits on the 220V mains line, isolated from the low-voltage circuit by a PC817 optocoupler. Press the button → optocoupler pulls the ATtiny's RESET pin LOW → MCU resets → `setup()` runs the melody once with RGB LED accompaniment → deep sleep (`SLEEP_MODE_PWR_DOWN`).

No interrupt handler. No event loop. Hardware reset as the doorbell event.

**Audio:** Square wave bit-banged on PB4 → PAM8403 audio amplifier → 4Ω 3W speaker.

**Power:** Nokia BL-5C LiPo (or any 1S cell) → TP4056 charge/protection module. PAM8403 SHDN pulled LOW when idle to preserve battery.

**Note on the mains-side resistor (R3):** R3 is rated 0.25W; at 220V AC, dissipation is ~0.484W — technically over-rated for sustained operation. SW1 is momentary, so in practice this is fine. If you rev the board, use a 1W rated resistor or an X-rated capacitor dropper for a cleaner solution.

---

## The Melody

Notes were sourced from a veteran YouTuber who transcribed the theme by ear and listed them in a video description — that careful, unnamed person who wrote it down for no reason other than love of the tune.

Note durations and rest periods were tuned by listening to the original score repeatedly until the timing felt right. Not until the math was correct — until it sounded like Feluda. The RTTTL notation is preserved in `firmware/feluda_doorbell/feluda.rtttl.txt` for documentation and portability, even though the firmware doesn't use it at runtime.

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
| R3 | 100K 0.25W (see note above) |
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

Flash via USBasp or Arduino as ISP. See `resources/` for wiring diagrams.

**Schematic and layout:** `hardware/feluda_doorbell.png` (full schematic + perf board layout)
**Layout source:** [DIY Layout Creator 4.37.0](https://github.com/bancika/diy-layout-creator/releases/tag/v4.37.0)

---

## Repository Structure

```
├── firmware/
│   └── feluda_doorbell/
│       ├── feluda_doorbell.ino     ← ATtiny13A firmware
│       └── feluda.rtttl.txt        ← melody notation + documentation
├── hardware/
│   ├── feluda_doorbell.diy         ← DIY Layout Creator source
│   └── feluda_doorbell.png         ← schematic + perf board layout
├── media/
│   ├── theme-tune-of-feluda.wav    ← recorded from ATtiny output
│   ├── satyajit-feluda.jpg
│   └── satyajit-feluda.mp4
├── resources/
│   ├── arduino_ide_settings.png
│   ├── attiny13-with-usbasp.png
│   ├── attiny13a-pinouts.jpg
│   ├── oshw-logo-400-px.png
│   ├── PC817-IC-Pinout.png
│   └── PC817-Internal-Pins.png
├── LICENSE-MIT
├── LICENSE-CERN-OHL-P
└── README.md
```

---

## License

- **Firmware** (`firmware/`) — [MIT License](LICENSE-MIT)
- **Hardware** (`hardware/`) — [CERN Open Hardware Licence v2 - Permissive](LICENSE-CERN-OHL-P)

Open source hardware. Build one. Make it play something else. The architecture will hold.

---

## Author

**Asif R. Porosh**
Built: 2023 | Published: 2026 | Rev 1.0