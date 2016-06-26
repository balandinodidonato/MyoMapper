# MyoMapper
MyoMapper, is an application to convert and rescale raw data from the Myo and to send them to musical applications through OSC and/or MIDI protocol.

It has been developed by [Balandino Di Donato](http://www.balandinodidonato.com) and [Jamie Bullock](http://jamiebullock.com/) at [Integra Lab](http://www.integra.io/lab).

MyoMapper demos are available [here](https://vimeo.com/album/3313801).

[**DOWNLOAD MyoMapper**](http://www.balandinodidonato.com/myomapper/)

## Get Started

- Launch [Myo Connect](https://developer.thalmic.com/downloads)
- Connect your Myo armband
- Verify that the connection is stable and Myo Connect is receiving data
- Launch MyoMapper

## OSC Communication

MyoMapper initially sends OSC messages at the port 5432 and receive messages at the port 5431, but it can changed through the setting pannel.

### Outgoing OSC messages

| OSC tag             | Myo parameter            | Value Type               | Range       |
| :---:               | :---:                    | :---:                    |:---:        |
| `/myo+id/orientationScaled`  | Yaw, Pitch, Roll         | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`        |
| `/myo+id/orientationRaw`     | Yaw, Pitch, Roll         | `float`, float, `float`      | `-PI, PI`, `-PI, PI`, `-PI, PI`     |
| `/myo+id/acceleration`       | Acc. x, Acc. y, Acc. z   | `float`, `float`, `float`      | `-PI, PI`, `-PI, PI`, `-PI, PI`     |
| `/myo+id/gyro`               | Gyro X, Gyro Y, Gyro Z   | `float`, `float`, `float`      | `-1000, 1000`, `-1000, 1000`, `-1000, 1000` |
| `/myo+id/mav`                | EMGs Mean Absolute Value | `float`                    | `0, 1`, `0, 1`, `0, 1`        |
| `/myo+id/emgScaled`          | EMG 1, EMG 2 ... EMG 8   | `float`, `float`, ... `float`  | `0, 1`, `0, 1` ... `0, 1`        |
| `/myo+id/emgRaw`             | EMG 1, EMG 2 ... EMG 8   | `int`, `int`, ... `int`        | `-127, 128`, `-127, 128` ... `-127, 128`   |
| `/myo+id/pose`               | Hand pose                | `int`, `string`              | `-1, 5` ; `"unknown", "rest",  "fist", "fingerSpread", "waveIn", "waveOut", "doubleTap"` |

### Accepted OSC messages

**NB:**
id = the value which indicates the selected Myo. It has to be an `int`, which value can be `1`, `2`, `3`, `4`.
myoValue = the value which has to be processed. It has to be a `String` which value can be `yaw`, `pitch`, `roll`, `mav`.

| OSC tag                    | Value Type | Range                     | Functions                                              |
| :---:                      | :---:      | :---:                     |  :---:                                                 |
| `/myo+id/vibrate`            | `String`   | `short`, `medium`, `long` | Makes the Myo vibrate for a short, medium or long time |
| `/myo+id/myoValue/centre`    | `String`   | `centre`                  | Centre the current value within the set range          |
| `/myo+id/myoValue/setMin`    | `float`    |  `0`, `1`                 | Set the lowest outgoing value                          |
| `/myo+id/myoValue/setMax`    | `float`    |  `0`, `1`                 | Set the highest outgoing value                         |
| `/myo+id/myoValue/reverse`   | `int`      |  `0`, `1`                 | Reverse the current value                              |

---

**N.B.:**

- EMG pad enumeration has been established by Thalmic Lab, please see image below, or visit the flowing page: [https://developer.thalmic.com/forums/topic/255/](https://developer.thalmic.com/forums/topic/255/).***

![EMG pad enumumeration](http://i59.tinypic.com/1zyez3r.jpg "EMG pad enumumeration")

Source immage: Arief, Z., Sulistijono, I. A., & Ardiansyah, R. A. (2015, September). *Comparison of five time series EMG features extractions using Myo Armband.* In Electronics Symposium (IES), 2015 International (pp. 11-14). IEEE. Chicago.


## To build on OS X

### Requirements

- [X Code](https://developer.apple.com/xcode/)
- [Myo SDK for OS X](https://developer.thalmic.com/downloads)

### Build process

#### Updated soon

## License

Copyright (c)  2016 - Integra Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
