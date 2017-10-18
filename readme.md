# rsm

rsm is a utility library that contains different utilities for different purposes. It`s basically different tools I tend to reprogram with every project that I decided to centralise in a library. It is programmed in C++ and requires C++11.

### Build Status		

Master: [![Build Status](https://img.shields.io/travis/Rosme/rsm/master.svg?label=linux+and+macOS)](https://travis-ci.org/Rosme/rsm) [![Build Status](https://img.shields.io/appveyor/ci/Rosme/rsm/master.svg?label=windows)](https://ci.appveyor.com/project/Rosme/rsm)

Develop: [![Build Status](https://img.shields.io/travis/Rosme/rsm/develop.svg?label=linux+and+macOS)](https://travis-ci.org/Rosme/rsm) [![Build Status](https://img.shields.io/appveyor/ci/Rosme/rsm/develop.svg?label=windows)](https://ci.appveyor.com/project/Rosme/rsm)		

### Features

* Any
    * Type-erasure class for generic storage
    * Easy to use(copyable, movable)
* Config
    * Allow you to read from a configuration file
    * Default Configuration type is a Key=Value type
    * Allow declaration of custom configuration type
* Logger
    * Easy to use logger
    * Two provided log device:
        * To stdout
        * To file
* Matrix
    * Matrix class for easier usage of matrix
    * Safe and easy to use with operator()
* Message Dispatcher
    * Lightweight Message class to ship any kind of message
    * Virtual Message Handler to handle messages using a key=> message type association
    * Async Message Dispatcher to dispatch messages in a asynchronous way
    * Or monothread Message Dispatcher to dispatch the messages when you want
* Timer
    * Timer that can trigger a callback when timed out
    * Can also trigger a callback when interrupted

### License

The library is distributed under the zlib/png license. This basically means you can use rsm in any project(commercial or not, proprietary or open-source) for free. There is no restriction to the use. You don't even need to mention rsm or me, though it would be appreciated.

Written by Jean-Sébastien Fauteux
