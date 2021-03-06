/*
* Copyright (c) 2018 Jean-S�bastien Fauteux
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

#include <rsm/any.hpp>
#include <rsm/matrix.hpp>
#include <string>

TEST_CASE("Testing Any", "[any]") {

    SECTION("Empty Any") {
        rsm::Any anyObject;

        REQUIRE(!anyObject.isValid());
    }

    SECTION("Integer Const Any") {
        const rsm::Any anyInteger(1);

        REQUIRE(anyInteger.isValid());
        REQUIRE(anyInteger.get<int>() == 1);
    }

    SECTION("String Const Any") {
        const rsm::Any anyString(std::string("test"));

        REQUIRE(anyString.isValid());
        REQUIRE(anyString.get<std::string>() == "test");
    }

    SECTION("Integer Any") {
        rsm::Any anyInteger(1);

        REQUIRE(anyInteger.isValid());
        REQUIRE(anyInteger.get<int>() == 1);
    }

    SECTION("String Any") {
        rsm::Any anyString(std::string("test"));

        REQUIRE(anyString.isValid());
        REQUIRE(anyString.get<std::string>() == "test");
    }

    SECTION("Copying Integer Any") {
        rsm::Any anyIntegerSource(1);
        rsm::Any anyIntegerCopy;

        REQUIRE(anyIntegerSource.isValid());
        REQUIRE(!anyIntegerCopy.isValid());

        REQUIRE(anyIntegerSource.get<int>() == 1);

        anyIntegerCopy = anyIntegerSource;

        anyIntegerSource = 2;
        REQUIRE(anyIntegerSource.get<int>() == 2);
        REQUIRE(anyIntegerCopy.get<int>() == 1);
    }

    SECTION("Copy Construct String Any") {
        rsm::Any anyStringSource(1);

        REQUIRE(anyStringSource.isValid());
        REQUIRE(anyStringSource.get<int>() == 1);

        rsm::Any anyStringCopy(anyStringSource);

        anyStringSource = 2;
        REQUIRE(anyStringSource.get<int>() == 2);
        REQUIRE(anyStringCopy.get<int>() == 1);
    }

    SECTION("Moving Construct Integer Any") {
        rsm::Any anyIntegerSource(1);

        REQUIRE(anyIntegerSource.isValid());
        REQUIRE(anyIntegerSource.get<int>() == 1);

        rsm::Any anyIntegerMoved(std::move(anyIntegerSource));

        REQUIRE(anyIntegerMoved.isValid());
        REQUIRE(anyIntegerMoved.get<int>() == 1);
        REQUIRE(!anyIntegerSource.isValid());
    }

    SECTION("Moving String Any") {
        rsm::Any anyStringSource(std::string("test"));

        REQUIRE(anyStringSource.isValid());
        REQUIRE(anyStringSource.get<std::string>() == "test");

        rsm::Any anyStringMoved = std::move(anyStringSource);

        REQUIRE(anyStringMoved.isValid());
        REQUIRE(anyStringMoved.get<std::string>() == "test");
        REQUIRE(!anyStringSource.isValid());
    }

#if defined(WIN32)
    SECTION("Integer Any TypeId") {
        rsm::Any anyInteger(1);

        std::string name(anyInteger.type().name());
        REQUIRE(name.find("int") != std::string::npos);
    }

    SECTION("Matrix Any TypeId") {
        rsm::Matrix<int> matrix;
        rsm::Any anyMatrix(matrix);

        std::string name(anyMatrix.type().name());
        REQUIRE(name.find("rsm::Matrix") != std::string::npos);
    }
#endif
}
