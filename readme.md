# rsm_utils

rsm_utils is a utility library that contains different utility for different purposes. It`s basically different tools I tend to reprogram with every project that I decided to centralise in a library. It is programmed in C++ and requires C++11.

### Build Status		

Master: [![Build Status](https://travis-ci.org/Rosme/rsm_utils.svg?branch=master)](https://travis-ci.org/Rosme/rsm_utils)		

Develop: [![Build Status](https://travis-ci.org/Rosme/rsm_utils.svg?branch=develop)](https://travis-ci.org/Rosme/rsm_utils)		

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
    * Macros to simplify usage
    * Log to file and stdout
* Matrix
    * Matrix class for easier usage of matrix
    * Safe and easy to use with operator()
* Timer
    * Timer that can trigger a callback when timed out
    * Can also trigger a callback when interrupted

### License

The library is distributed under the zlig/png license. This basically means you can use rsm_utils in any project(commercial or not, proprietary or open-source) for free. There is no restriction to the use. You don't even need to mention rsm_utils or me, though it would be appreciated.

Written by Jean-Sébastien Fauteux