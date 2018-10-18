/*
* Copyright (c) 2018 Jean-Sébastien Fauteux
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim
*    that you wrote the original software. If you use this software in a product,
*    an acknowledgment in the product documentation would be appreciated but is
*    not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "catch.hpp"

#include <rsm/log/logger.hpp>
#include <rsm/log/stream_log_device.hpp>
#include <rsm/log/file_log_device.hpp>

#include <fstream>
#include <string>

class LoggingTestClass {
public:
    LoggingTestClass(const std::string& data)
      : m_data(data)
    {}
    
private:
    std::string m_data;
    
    friend std::ostream& operator<<(std::ostream& out, const LoggingTestClass& logging);
};

std::ostream& operator<<(std::ostream& out, const LoggingTestClass& logging) {
    return out << logging.m_data;
}

TEST_CASE("Testing logging", "[log]") {

	SECTION("File Log Device") {
        const std::string logFileName = "log-test";
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::log(rsm::LogLevel::Debug, "Test");

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
	}

}

TEST_CASE("Log Level", "[log]") {

	SECTION("Debug") {
		const std::string logFileName = "log-debug";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::debug() << "Test";
		
		rsm::Logger::resetLogDevices();

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
		std::string content;
		std::getline(stream, content);
		INFO(content)
		REQUIRE(content.find("Debug") != std::string::npos);
	}

	SECTION("Info") {
		const std::string logFileName = "log-info";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::info() << "Test";
		
		rsm::Logger::resetLogDevices();

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
		std::string content;
		std::getline(stream, content);
		INFO(content)
		REQUIRE(content.find("Info") != std::string::npos);
	}

	SECTION("Warning") {
		const std::string logFileName = "log-warning";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::warning() << "Test";
		
		rsm::Logger::resetLogDevices();

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
		std::string content;
		std::getline(stream, content);
		INFO(content)
		REQUIRE(content.find("Warning") != std::string::npos);
	}

	SECTION("Critical") {
		const std::string logFileName = "log-critical";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::critical() << "Test";
		
		rsm::Logger::resetLogDevices();

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
		std::string content;
		std::getline(stream, content);
		INFO(content)
		REQUIRE(content.find("Critical") != std::string::npos);
	}

	SECTION("Error") {
		const std::string logFileName = "log-error";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::error() << "Test";
		
		rsm::Logger::resetLogDevices();

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
		std::string content;
		std::getline(stream, content);
		INFO(content)
		REQUIRE(content.find("Error") != std::string::npos);
	}
    
}

TEST_CASE("Log Streaming", "[log]") {
    
    SECTION("Single item stream") {
        const std::string logFileName = "log-stream-single";
        
        rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));
        
        rsm::Logger::debug() << "Test Single";
        rsm::Logger::resetLogDevices();
        
        std::ifstream stream;
        stream.open(logFileName, std::ios::in);
        
        REQUIRE(stream.is_open());
        std::string content;
        std::getline(stream, content);
        INFO(content)
        REQUIRE(content.find("Test Single") != std::string::npos);
    }
    
    SECTION("Single item stream") {
        const std::string logFileName = "log-stream-multi";
        
        rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));
        
        rsm::Logger::debug() << "Test Multi 1" << "Test Multi 2" << 3;
        rsm::Logger::resetLogDevices();
        
        std::ifstream stream;
        stream.open(logFileName, std::ios::in);
        
        REQUIRE(stream.is_open());
        std::string content;
        std::getline(stream, content);
        INFO(content)
        REQUIRE(content.find("Test Multi 1") != std::string::npos);
        
        std::getline(stream, content);
        INFO(content)
        REQUIRE(content.find("Test Multi 2") != std::string::npos);
        
        std::getline(stream, content);
        INFO(content)
        REQUIRE(content.find("3") != std::string::npos);
    }
    
    SECTION("Custom class streaming") {
        const std::string logFileName = "log-stream-class";
        const std::string testClassData = "test-class";
        LoggingTestClass testClass(testClassData);
        
        rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));
        
        rsm::Logger::info() << testClass;
        rsm::Logger::resetLogDevices();
        
        std::ifstream stream;
        stream.open(logFileName, std::ios::in);
        
        REQUIRE(stream.is_open());
        std::string content;
        std::getline(stream, content);
        INFO(content)
        REQUIRE(content.find(testClassData) != std::string::npos);
    }
}
