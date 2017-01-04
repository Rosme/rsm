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

#include <RSM/config.hpp>

TEST_CASE("Testing config management", "[config]") {
	
	RSM::Config config;

	SECTION("Creating a config file from scratch") {
		//Cleaning up in case
		std::remove("config.txt");

		config.set("StringKey", "StringValue");
		config.set("IntKey", -5);
		config.set("UintKey", 5);
		config.set("FloatKey", 5.5f);

		REQUIRE(config.hasConfig("StringKey") == true);
		REQUIRE(config.hasConfig("IntKey") == true);
		REQUIRE(config.hasConfig("UintKey") == true);
		REQUIRE(config.hasConfig("FloatKey") == true);

		REQUIRE_NOTHROW(config.save("config.txt"));
	}

	SECTION("Loading a config file") {
		REQUIRE_NOTHROW(config.load("config.txt"));

		REQUIRE(config.hasConfig("StringKey") == true);
		REQUIRE(config.hasConfig("IntKey") == true);
		REQUIRE(config.hasConfig("UintKey") == true);
		REQUIRE(config.hasConfig("FloatKey") == true);

		REQUIRE(config.get("StringKey") == "StringValue");
		REQUIRE(config.getInt("IntKey") == -5);
		REQUIRE(config.getUint("UintKey") == 5);
		REQUIRE(config.getFloat("FloatKey") == 5.5f);
	}

	SECTION("Loading a config file, change and save") {
		REQUIRE_NOTHROW(config.load("config.txt"));

		REQUIRE(config.hasConfig("StringKey") == true);
		REQUIRE(config.hasConfig("IntKey") == true);
		REQUIRE(config.hasConfig("UintKey") == true);
		REQUIRE(config.hasConfig("FloatKey") == true);

		REQUIRE(config.get("StringKey") == "StringValue");
		REQUIRE(config.getInt("IntKey") == -5);
		REQUIRE(config.getUint("UintKey") == 5);
		REQUIRE(config.getFloat("FloatKey") == 5.5f);

		config.set("StringKey", "NewStringValue");
		config.set("IntKey", 10);
		config.set("UintKey", -10);
		config.set("FloatKey", 10.1f);
		config.set("OtherKey", "OtherValue");

		REQUIRE_NOTHROW(config.save("config.txt"));
	}

	SECTION("Loading a config file with new value") {
		REQUIRE_NOTHROW(config.load("config.txt"));

		REQUIRE(config.hasConfig("StringKey") == true);
		REQUIRE(config.hasConfig("IntKey") == true);
		REQUIRE(config.hasConfig("UintKey") == true);
		REQUIRE(config.hasConfig("FloatKey") == true);
		REQUIRE(config.hasConfig("OtherKey") == true);

		REQUIRE(config.get("StringKey") == "NewStringValue");
		REQUIRE(config.getUint("IntKey") == 10);
		REQUIRE(config.getInt("UintKey") == -10);
		REQUIRE(config.getFloat("FloatKey") == 10.1f);
		REQUIRE(config.get("OtherKey") == "OtherValue");
		
		//Cleaning up
		std::remove("config.txt");
	}
}
