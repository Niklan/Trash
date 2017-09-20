 1. Find out the audio sources using command: `ffmpeg -i FILENAME`
 2. Export needed sound `ffmpeg -i FILENAME -c:a libmp3lame -q:a 4 output.mp3`
    2.1 To specify audio stream line you must use `-map 0:LINE_NUMBER`.

`-q:a` is quality. More info [here](https://trac.ffmpeg.org/wiki/Encode/MP3). 4 is great for all cases. It's equals bitrate 140-185 kbit/s.