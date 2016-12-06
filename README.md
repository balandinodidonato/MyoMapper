# MyoMapper
MyoMapper, is an application to convert and rescale raw data from the Myo and to send them to musical applications through OSC and/or MIDI protocol.

It has been developed by [Balandino Di Donato](http://www.balandinodidonato.com) and [Jamie Bullock](http://jamiebullock.com/) at [Integra Lab](http://www.integra.io/lab).

[**DOWNLOAD MyoMapper**](https://github.com/balandinodidonato/MyoMapper/releases)

[Myo Mapper receiver for Pd](https://github.com/balandinodidonato/MyoMapper/tree/master/examples/Pd)

## Get Started

- Launch [Myo Connect](https://developer.thalmic.com/downloads)
- Connect your Myo armband
- Verify that the connection is stable and Myo Connect is receiving data
- Launch MyoMapper
- Select the Myo

To map multiple Myos, launch a second Myo Mapper's instance and select a different Myo. To do so:
- Duplicate the Myo Mapper application you have already installed.
- Rename it with a different name, eg. "Myo Mapper 2"
- Launch it

## OSC Communication

MyoMapper initially sends OSC messages at the port 5432 and receive messages at the port 5431, but it can changed through the setting pannel.

### Outgoing OSC messages
     
| OSC tag                          | Myo parameter                                           | Value Type                     | Range                     |
| :---:                            | :---:                                                   | :---:                          |:---:                      |
| `/myo+id/orientation/scaled`     | Scaled Yaw, Scaled Pitch, Scaled Roll                   | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`    |
| `/myo+id/orientation/raw`        | Yaw, Pitch, Roll                                        | `float`, `float`, `float`      | `-PI, PI`, `-PI, PI`, `-PI, PI` |
| `/myo+id/orientation/wl`         | Scaled Yaw WfL, Scaled Pitch WfL, Scaled Roll WfL       | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`      |
| `/myo+id/acceleration/raw`       | Acc. x, Acc. y, Acc. z                                  | `float`, `float`, `float`      | `-16, 16`, `-16, 16`, `-16, 16` |
| `/myo+id/acceleration/rawWfL`    | Acc. x WfL, Acc. y WfL, Acc. z WfL                      | `float`, `float`, `float`      | `-16, 16`, `-16, 16`, `-16, 16` |
| `/myo+id/acceleration/scaled`    | Acc. x Scaled, Acc. y Scaled, Acc. z Scaled             | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`    |
| `/myo+id/acceleration/scaledWfL` | Acc. x Scaled WfL, Acc. y Scaled WfL, Acc. z Scaled WfL | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`    |
| `/myo+id/gyro/raw`               | Gyro X, Gyro Y, Gyro Z                                  | `float`, `float`, `float`      | `-2000, 2000`, `-2000, 2000`, `-2000, 2000` |
| `/myo+id/gyro/rawWfL`            | Gyro x WfL, Gyro y WfL, Gyro z WfL                      | `float`, `float`, `float`      | `-2000, 2000`, `-2000, 2000`, `-2000, 2000` |
| `/myo+id/gyro/scaled`            | Gyro x Scaled, Gyro y Scaled, Gyro z Scaled             | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`    |
| `/myo+id/gyro/scaledWfL`         | Gyro x Scaled WfL, Gyro y Scaled WfL, Gyro z Scaled WfL | `float`, `float`, `float`      | `0, 1`, `0, 1`, `0, 1`    |
| `/myo+id/EMG/mav`                | EMGs Mean Absolute Value                                | `float`                        | `0, 1`                          |
| `/myo+id/EMG/mavWfL`             | EMGs Mean Absolute Value WfL                            | `float`                        | `0, 1` |
| `/myo+id/EMG/scaled`             | EMG 1, EMG 2 ... EMG 8                                  | `float`, `float`, ... `float`  | `0, 1`, `0, 1` ... `0, 1`        |
| `/myo+id/EMG/raw`                | EMG 1, EMG 2 ... EMG 8                                  | `int`, `int`, ... `int`        | `-127, 128`, `-127, 128` ... `-127, 128`   |
| `/myo+id/pose`                   | Hand pose                                               | `int`, `string`                | `-1, 5` ; `"unknown", "rest",  "fist", "fingerSpread", "waveIn", "waveOut", "doubleTap"`        |
| `/myo+id/all`                | Scaled Yaw, Scaled Pitch, Scaled Roll, Scaled Yaw WL, Scaled Pitch WL, Scaled Roll WL, Acc. x, Acc. y, Acc. z, Acc. x WL, Acc. y WL, Acc. z WL, Gyro X, Gyro Y, Gyro Z, Gyro X WL, Gyro Y WL, Gyro Z WL, EMGs Mean Absolute Value, EMGs Mean Absolute Value WL | `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float` | `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `-PI, PI`, `-PI, PI`, `-PI, PI`, `0, PI`,`0, PI`,`0, PI`, `-1000, 1000`, `-1000, 1000`, `-1000, 1000`, `0, 1000`, `0, 1000`, `0, 1000`, `0, 1`, `0, 1` |
| `/myo+id/EMG`               | Scaled Yaw, Scaled Pitch, Scaled Roll, Scaled Yaw WL, Scaled Pitch WL, Scaled Roll WL, Acc. x, Acc. y, Acc. z, Acc. x WL, Acc. y WL, Acc. z WL, Gyro X, Gyro Y, Gyro Z, Gyro X WL, Gyro Y WL, Gyro Z WL, EMGs Mean Absolute Value, EMGs Mean Absolute Value WL, EMG 1 Scaled, EMG 2 Scaled, EMG 3 Scaled, EMG 4 Scaled, EMG 5 Scaled, EMG 6 Scaled, EMG 7 Scaled, EMG 8 Scaled | `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float`, `float` | `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `-PI, PI`, `-PI, PI`, `-PI, PI`, `0, PI`,`0, PI`,`0, PI`, `-1000, 1000`, `-1000, 1000`, `-1000, 1000`, `0, 1000`, `0, 1000`, `0, 1000`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1`, `0, 1` |


### Accepted OSC messages

**NB:**
id = the value which indicates the selected Myo. It has to be an `int`, which value can be `1`, `2`, `3`, `4`.
myoValue = the value which has to be processed. It has to be a `String` which value can be `yaw`, `pitch`, `roll`, `mav`.

| OSC tag                      | Value Type | Range                     | Functions                                              |
| :---:                        | :---:      | :---:                     |  :---:                                                 |
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
- [Myo Framework for Mac](https://developer.thalmic.com/downloads)
- [JUCE](https://www.juce.com/get-juce)

### Build process

- Move the Myo framework into `~/Library/Frameworks`.

  From terminal: `mv current-myo-framework-path ~/Library/Frameworks`

  If there is not any folder named Frameworks under `~/Library` then create one and move the Myo framework into it.

- Move the JUCE into `/Applications`.

  From terminal: `mv current-JUCE-path /Applications`

- Open `Myo Mapper.jucer`
- Verify that all modules are linked by clicking `config` -> `modules`
- Click `Save Project and Open in IDE`
- Build App

If any issue, please [report and issue](https://github.com/balandinodidonato/MyoMapper/issues) or [email the developer](info@balandinodidonato.com).

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
