/*
* Copyright (c) 2017 Jean-S�bastien Fauteux
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

TEST_CASE("Testing logging", "[log]") {

	SECTION("File Log Device") {
		std::string logFileName = "log";
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::log(rsm::LogLevel::Debug, "Test");

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
	}

}

TEST_CASE("Log Level", "[log]") {

	SECTION("Debug") {
		std::string logFileName = "log";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::debug("Test");
		
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
		std::string logFileName = "log";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::info("Test");
		
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
		std::string logFileName = "log";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::warning("Test");
		
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
		std::string logFileName = "log";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::critical("Test");
		
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
		std::string logFileName = "log";
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::error("Test");
		
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