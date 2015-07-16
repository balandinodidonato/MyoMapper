# MyoMusic #
MyoMusic, is a tool to convert and rescale raw data from the Myo and to send them to musical applications through OSC and MIDI protocoll.

It has been developed using Processing and the [myo-processing library](https://github.com/nok/myo-processing).

Please visit [www.balandinodidonato.com](http://balandinodidonato.com) and the Vimeo album: [https://vimeo.com/album/3313801](https://vimeo.com/album/3313801) to see  examples of MyoMusic's use.

## Requirements ##

Processing. You can download it from here: [https://processing.org/download/](https://processing.org/download/)

##Build System##
Create a folder called MyoMusic.

Open a Terminal and change your directory to the MyoMusic Folder

`cd <path>/<to>/MyoMusic`

Clone the repository

`git clone https://github.com/balandinodidonato/MyoMusic`

Open the MyoMusic.pde file

`open MyoMusic/MyoMusic.pde`

Once the Processing Skatch came up
Navigate to the top bar and select `File -> Export Application`
- Select the Platform which you will be working on
- Click on `Export`

Job Done!!!

##How to use it##

- Connect your Myo armband
- Once it the connection is stable launch MyoMusic and it is ready to go!

### How to Change the OSC Port ###
Unfortunately there is no GUI command yet, (I promised to myself to insert this feature in) however it is still possible to do it. All you need to do is:

`open <path>/<to>/MyoMusic/MyoMusic/osc.pde`

then edit the IP and Port address with the one you need.


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