/*
* Copyright (c) 2017 Jean-Sébastien Fauteux
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

TEST_CASE("Testing logging", "[log]") {
	
	/*SECTION("Stream Log Device") {
		
		rsm::Logger::addLogDevice(std::make_unique<rsm::StreamLogDevice>());
		
		rsm::Logger::log(rsm::LogLevel::Debug, "Test");		

		REQUIRE(true);
	}*/

	SECTION("File Log Device") {
		std::string logFileName = "log";
		rsm::Logger::addLogDevice(std::make_unique<rsm::FileLogDevice>(logFileName));

		rsm::Logger::log(rsm::LogLevel::Debug, "Test");

		std::ifstream stream;
		stream.open(logFileName, std::ios::in);

		REQUIRE(stream.is_open());
	}

}