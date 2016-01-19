# Overview #
  * In a word, Android version of Firmata
  * Provides abstraction layer of Arduino to Android developers
  * Separation of the function of Arduino and Android
  * Web server supported (REST api)
  * Simple and easy to use on Android side
  * Reduce code size burden and amount of work in Arduino side

# Source code #
  * There are two version
  * Nov 8th (BT and ADK support) and Dec 4th (ADK only). Only modified files in Dec 4th version were uploaded (use Nov 8th version for other components)
  * Download zipped package from 'Downloads' tab
  * or, Download source code from Source tab (there are several repositories. download all repository)
  * Arduino side: sketch, ADK library
  * Android side: android side library
  * For Google ADK 1.0, download ADK library and USB shield library modified for USB host shield (tested only for Uno)
  * For SL4A, refer to SL4A download site http://code.google.com/p/android-scripting/
  * Remote control (receiver only) for Samsung appliances and Robosapien, donwload IR-remote source

# Example #
  * Robot
![https://lh4.googleusercontent.com/-6_C7SaWtNfM/UJ4gbDQ1qtI/AAAAAAAAHAs/P08VKV5C01E/s912/20121110_175536.jpg](https://lh4.googleusercontent.com/-6_C7SaWtNfM/UJ4gbDQ1qtI/AAAAAAAAHAs/P08VKV5C01E/s912/20121110_175536.jpg)
  * Ultrasonic sensor
![https://lh4.googleusercontent.com/-Xvar3loXdCg/UJ4gcnb33xI/AAAAAAAAHA0/98LKEdThuvw/s912/20121110_175615.jpg](https://lh4.googleusercontent.com/-Xvar3loXdCg/UJ4gcnb33xI/AAAAAAAAHA0/98LKEdThuvw/s912/20121110_175615.jpg)
  * DC motor control
  * Infrared (RoboSapien)
![https://lh3.googleusercontent.com/-YKvSJ3KbWJk/UJ4gRi-2ELI/AAAAAAAAHAk/oTohGqQkggA/s912/20121110_175435.jpg](https://lh3.googleusercontent.com/-YKvSJ3KbWJk/UJ4gRi-2ELI/AAAAAAAAHAk/oTohGqQkggA/s912/20121110_175435.jpg)
  * http REST interface
https://lh5.googleusercontent.com/-1XUtqry3ohI/UJ4kCAiaPSI/AAAAAAAAHBs/Kvv9mx1Y9zc/s48/logo.JPG
# Features #
  * Arduino API abstraction
  * Arduino shield abstraction
  * ADK procedure abstraction
  * Abstract byte stream handling
  * Event handler
  * Polling/Asynchronous messaging
  * Integration with SL4A