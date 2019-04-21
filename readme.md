# rsm

rsm is a utility library that contains different utilities for different purposes. It`s basically different tools I tend to reprogram with every project that I decided to centralise in a library. It is programmed in C++ and requires C++11.

### Build Status		

Master: [![Build Status](https://img.shields.io/travis/Rosme/rsm/master.svg?label=linux+and+macOS)](https://travis-ci.org/Rosme/rsm) [![Build Status](https://img.shields.io/appveyor/ci/Rosme/rsm/master.svg?label=windows)](https://ci.appveyor.com/project/Rosme/rsm)

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

### Code Samples
#### Any
```cpp
rsm::Any obj(std::vector<int>{0, 1, 2});

if(obj.isValid()) {
	auto val = obj.get<std::vector<int>>();
    
    for(const auto i : val) {
    	//...
    }
}
```
#### Config
```cpp
rsm::Config config;
config.load("myConfig.txt");

if(config.hasConfig("key")) {
	auto value = config.get("key");
}

config.set("newKey", 42);

config.save("newConfig.txt");
```
#### Logging
```cpp
rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(myLogFile.txt));
rsm::Logger::info() << "A Info Log";

MyStreambleObject myObject; 
rsm::Logger::debug() << myObject; // Assuming myStreableObject overloads operator<<
```
#### Matrix
```cpp
rsm::Matrix<int> matrix(5, 10, 3); // Creates a 5x10 matrix filled with 3

matrix(2, 4) = 5; //Set value 5 to entry at row 2 and column 4
auto value = matrix(1, 3); //Return the value at row 1 and column 3
```
#### Message Dispatcher (Async)
```cpp
class MyHandler : public rsm::MessageHandler {
	void onMessage(const std::string& key, const rsm::Message& message) override {
    	//...
    }
};

rsm::MessageDispatcher dispatcher;
MyHandler handler;

rsm::AsyncMessageDispatcher asyncDispatcher;
asyncDispatcher.registerHandler("asyncKey", handler);
asyncDispatcher.startDispatching(); //Start thread for automatic dispatching of pushed message
asyncDispatcher.pushMessage("asyncKey", "asyncMessage"); //Push message and dispatch
asyncDispatcher.stopDispatching(); //Stop dispatching and the dispatching thread
```
#### Message Dispatcher (Synchronous)
```cpp
class MyHandler : public rsm::MessageHandler {
	void onMessage(const std::string& key, const rsm::Message& message) override {
    	//...
    }
};

rsm::MessageDispatcher dispatcher;
MyHandler handler;

dispatcher.registerHandler("syncKey", handler); //Register handler to a specific key
dispatcher.pushMessage("syncKey", "syncMessage"); //Push a message in the dispatching queue
dispatcher.dispatch(); //Required to dispatch all message previsouly pushed
```
#### Timer
```cpp
rsm::Timer<void(), void()> timer;
timer.setTimeoutFunction([]() {
	rsm::Logger::info() << "The timer timed out";
});

timer.setInterruptFunction([]() {
	rsm::Logger::info() << "The timer has been interrupted";
});

timer.start(std::chrono::milliseconds(1000)); //Call the timeout function after 1seconds

timer.interrupt(); //Call the interrupt function and stop the timer
```

### License

The library is distributed under the zlib/png license. This basically means you can use rsm in any project(commercial or not, proprietary or open-source) for free. There is no restriction to the use. You don't even need to mention rsm or me, though it would be appreciated.

Written by Jean-Sébastien Fauteux