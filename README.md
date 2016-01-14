# MyoMapper #
MyoMapper, is a tool to convert and rescale raw data from the Myo and to send them to musical applications (Eg. [Integra Live](http://www.integralive.org), [Pd](https://puredata.info), [Max/MSP](https://cycling74.com/products/max/)) through OSC and/or MIDI protocol.

It has been developed by [Balandino Di Donato](http://www.balandinodidonato.com) at [Integra Lab](http://www.integra.io/lab).

MyoMapper demos are available [here](https://vimeo.com/album/3313801).

## Requirements ##

- [Processing 3.0](https://processing.org/download/)
- Libraries for Processing:
  - [The midibus](http://www.smallbutdigital.com/themidibus.php)
  - [ControlP5](http://www.sojamo.de/libraries/controlP5/)
  - [oscP5](http://www.sojamo.de/libraries/oscP5/)
  - [Myo For Processing](https://github.com/nok/myo-processing)

##Build System##
Create a folder called MyoMapper.

Open a Terminal and change your directory to the MyoMapper Folder

`cd <path>/<to>/MyoMapper`

Clone the repository

`git clone https://github.com/balandinodidonato/MyoMapper`

Open the MyoMapper.pde file

`open MyoMapper/MyoMapper.pde`

Once the Processing Sketch came up

Navigate to the top bar and select `File -> Export Application`

- Select the Platform which you will be working on
- Click on `Export`

##How to use it##

- Launch [Myo Connect](https://developer.thalmic.com/downloads)
- Install `unlock.myo`  script (`path/to/MyoMapper/script/unlock.myo`) to do so:
`Myo Connect -> Application Manager -> +Add -> Select unlock.myo`
- Connect your Myo armband
- Verify that the connection is stable and Myo Connect is receiving data
- Launch MyoMapper

### How to change the OSC Port ###
Unfortunately there is no GUI command yet, (I promised to myself to insert this feature in) however it is still possible to do it. All you need to do is:

Open the osc.pde file
`open <path>/<to>/MyoMapper/MyoMapper/osc.pde`

Edit the IP and Port address with the one you need.
Save the osc.pde file
Build again MyoMapper. It is advisable to run it first from Processing using the top right corner button in order to check the OSC communication.

### How to Change MIDI  channel and cc value###
In order to change **MIDI channel** to which send MIDI data it is easily doable through the GUI.

To change **cc value** of the single Myo value, you need to open the relative pde file and edit the parameters of the functions which send MIDI data.

Eg.

To change cc values of Myo acceleration values you have to open the `myoAcceleration.pde` file

`open <path>/<to>/MyoMapper/MyoMapper/myoAcceleration.pde`

and then edit the function to send MIDI data at the line 19.


                            |MIDI ch| cc | value  |
                            |       |    |        |
    myBus.sendControllerChange(chMIDI, 4, rollMIDI);
    myBus.sendControllerChange(chMIDI, 5, pitchMIDI);
    myBus.sendControllerChange(chMIDI, 6, yawMIDI);



                              |MIDI ch| cc | value  |
                              |       |    |        |
     myBus.sendControllerChange(chMIDI, 4, rollMIDI);
     myBus.sendControllerChange(chMIDI, 5, pitchMIDI);
     myBus.sendControllerChange(chMIDI, 6, yawMIDI);

##MIDI and OSC default values ##

**N.B.:**

- EMG pad enumeration has been established by Thalmic Lab, please see image below, or visit the flowing page: [https://developer.thalmic.com/forums/topic/255/](https://developer.thalmic.com/forums/topic/255/).***

![EMG pad enumumeration](http://i59.tinypic.com/1zyez3r.jpg "EMG pad enumumeration")

- Some of the Velocity and OSC values might change after the range adjustment made through the UI.

###MIDI###

Midi port can be changed through the user interface once you have built the application.

In the table below you can find the correspondence between cc value and Myo parameters.

| cc value | Velocity | Myo parameter        |
| :---:    | :---:    | :---:                |
| 1        | 0-127    | Yaw                  |
| 2        | 0-127    | Pitch                |
| 3        | 0-127    | Roll                 |
| 4        | 0-127    | Acc X                |
| 5        | 0-127    | Acc Y                |
| 6        | 0-127    | Acc Z                |
| 7        | 0-127    | Gyro X               |
| 8        | 0-127    | Gyro Y               |
| 9        | 0-127    | Gyro Z               |
| 10       | 0-127    | EMG average          |
| 11       | 0-127    | EMG pad 1            |
| 12       | 0-127    | EMG pad 2            |
| 13       | 0-127    | EMG pad 3            |
| 14       | 0-127    | EMG pad 4            |
| 15       | 0-127    | EMG pad 5            |
| 16       | 0-127    | EMG pad 6            |
| 17       | 0-127    | EMG pad 7            |
| 18       | 0-127    | EMG pad 8            |
| 20       | 0        | Pose: Unknown        |
| 20       | 21       | Pose: Fist           |
| 20       | 42       | Pose: Fingers Spread |
| 20       | 64       | Pose: Wave In        |
| 20       | 85       | Pose: Wave Out       |
| 20       | 106      | Pose: Double Tap     |
| 20       | 127      | Pose: REST           |

###OSC###

OSC port can be changed through the sketch *osc.pde* and editing the following code line:

`myRemoteLocation = new NetAddress("127.0.0.1",5432); // IP address and Port`

Help:
`myRemoteLocation = new NetAddress("Address",Port); // IP address and Port`

| OSC tag      | Value                  | Myo parameter                |
| :---:        | :---:                  | :---:                        |
| /orientation | 0-1, 0-1, 0-1          | Yaw, Pitch, Roll             |
| /acc         | 0-1000, 0-1000, 0-1000 | Acc X, Acc Y, Acc Z          |
| /gyro        | 0-2PI, 0-2PI, 0-2PI    | Gyro X, Gyro Y, Gyro Z       |
| /emgAvg      | 0-1                    | EMG average                  |
| /emg         | 0-1, 0-1, 0-1, ... 0-1 | EMG 1, EMG 2, EMG 3 ... EMG 8|
| /pose        | `UNCKNOWN`, 0          | Pose: Unknown                |
| /pose        | `FIST`, 1              |  Pose: Fist                  |
| /pose        | `FINGERS_SPREAD`, 2    | Pose: Fingers Spread         |
| /pose        | `WAVE_IN`, 3           | Pose: Wave In                |
| /pose        | `WAVE_OUT`, 4          | Pose: Wave Out               |
| /pose        | `DOUBLE_TAP`, 5        | Pose: Double Tap             |
| /pose        | `REST`, 6              | Pose: Rest                   |

## License ##
Copyright (c)  2015 - Balandino Di Donato

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
