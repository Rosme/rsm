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

#include <RSM/timer.hpp>

TEST_CASE("Testing Timer", "[timer]") {

	SECTION("Creating a timer with no callback") {
		RSM::Timer<void(), void()> timer;

		timer.start(std::chrono::milliseconds(1000));

		//Sleeping for 1200 instead of 1000 in case threading condition is not precise
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));

		REQUIRE(timer.isDone());
	}

	SECTION("Creating a timer with timeout callback") {
		bool isDone = false;

		RSM::Timer<void(), void()> timer;

		timer.setTimeoutFunction(std::bind([&]() {
			isDone = true;
		}));

		timer.start(std::chrono::milliseconds(1000));

		while(!timer.isDone());

		REQUIRE(isDone);
	}

	SECTION("Creating a timer with interrupt callback") {
		bool isDone = false;

		RSM::Timer<void(), void()> timer;

		timer.setInterruptFunction(std::bind([&]() {
			isDone = true;
		}));

		timer.start(std::chrono::milliseconds(1000));

		timer.interrupt();

		REQUIRE(isDone);
	}

	SECTION("Creating a timer with timeout and interrupt callback") {
		bool isDone = false;

		RSM::Timer<void(), void()> timer;

		timer.setTimeoutFunction(std::bind([&]() {
            timer.start(std::chrono::milliseconds(1000));
            timer.interrupt();
		}));

		timer.setInterruptFunction(std::bind([&]() {
			isDone = true;
		}));

		timer.start(std::chrono::milliseconds(1000));

		while(!isDone);

		REQUIRE(isDone);
	}

}