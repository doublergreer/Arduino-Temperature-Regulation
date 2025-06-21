## Temperature-to-Binary LED Display (Arduino Uno)

Reads temperature from an analog sensor (TMP36) connected to `A0`, converts it to Celsius, and displays the value modulo 32 in binary using a 5 bit LED readout.

### Hardware & Pinout

#### Temperature Sensor (e.g., TMP36):
| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC        | 5V          |
| GND        | GND         |
| OUT        | A0          |

#### Binary Output LEDs:
Each LED displays a bit of `(int)temperature_C % 32`, from least to most significant.

| Binary Weight | LED Index | Arduino Pin | LED Color (Optional) |
|----------------|-----------|-------------|-----------------------|
| 1 (2⁰)         | 0         | D7          | Red                   |
| 2 (2¹)         | 1         | D8          | Yellow                |
| 4 (2²)         | 2         | D9          | Red                   |
| 8 (2³)         | 3         | D10         | Yellow                |
| 16 (2⁴)        | 4         | D11         | Red                   |

- Anode of each LED connects to the Arduino digital pin.
- Cathode connects to GND via a 330Ω resistor.
