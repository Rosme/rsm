/*
 * Copyright (c) 2016 Jean-Sébastien Fauteux
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

#include <RSM/matrix.hpp>
#include <string>

TEST_CASE("Testing Matrix", "[matrix]") {
    
    SECTION("Creating a integer matrix without default intialization") {
        RSM::Matrix<int> matrix(5, 10);
        
        int l = 1;
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                matrix(i, j) = l;
                l++;
            }
        }
       
        l = 1;
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                REQUIRE(matrix(i, j) == l);
                l++;
            }
        }
    }
    
    SECTION("Creating a integer matrix with default intialization") {
        RSM::Matrix<int> matrix(5, 10, 7);
        
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                REQUIRE(matrix(i, j) == 7);
            }
        }
    }
    
    SECTION("Creating a string matrix without default intialization") {
        RSM::Matrix<std::string> matrix(5, 10);
        
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                matrix(i, j) = "Test";
            }
        }
        
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                REQUIRE(matrix(i, j) == "Test");
            }
        }
    }
    
    SECTION("Creating a string matrix with default intialization") {
        RSM::Matrix<std::string> matrix(5, 10, "Test");
        
        for(std::size_t i = 0; i < matrix.height(); ++i) {
            for(std::size_t j = 0; j < matrix.width(); ++j) {
                REQUIRE(matrix(i, j) == "Test");
            }
        }
    }
    
    SECTION("Copy construction integer matrix") {
        RSM::Matrix<int> matrix(5, 10, 7);
        RSM::Matrix<int> copy(matrix);
        
        REQUIRE(copy.width() == 5);
        REQUIRE(copy.height() == 10);
        REQUIRE(copy(0,0) == 7);
        REQUIRE(matrix.width() == 5);
        REQUIRE(matrix.height() == 10);
        REQUIRE(matrix(0,0) == 7);
    }
    
    SECTION("Copy assigment integer matrix") {
        RSM::Matrix<int> matrix(5, 10, 7);
        RSM::Matrix<int> copy(2, 8, 5);
        
        copy = matrix;
        
        REQUIRE(copy.width() == 5);
        REQUIRE(copy.height() == 10);
        REQUIRE(copy(0,0) == 7);
        REQUIRE(matrix.width() == 5);
        REQUIRE(matrix.height() == 10);
        REQUIRE(matrix(0,0) == 7);
    }
    
    SECTION("Copy construction string matrix") {
        RSM::Matrix<std::string> matrix(5, 10, "Test");
        RSM::Matrix<std::string> copy(matrix);
        
        REQUIRE(copy.width() == 5);
        REQUIRE(copy.height() == 10);
        REQUIRE(copy(0,0) == "Test");
        REQUIRE(matrix.width() == 5);
        REQUIRE(matrix.height() == 10);
        REQUIRE(matrix(0,0) == "Test");
    }
    
    SECTION("Copy assigment string matrix") {
        RSM::Matrix<std::string> matrix(5, 10, "Test");
        RSM::Matrix<std::string> copy(2, 8, "Test2");
        
        copy = matrix;
        
        REQUIRE(copy.width() == 5);
        REQUIRE(copy.height() == 10);
        REQUIRE(copy(0,0) == "Test");
        REQUIRE(matrix.width() == 5);
        REQUIRE(matrix.height() == 10);
        REQUIRE(matrix(0,0) == "Test");
    }
    
    SECTION("Move construction integer matrix") {
        RSM::Matrix<int> matrix(5, 10, 7);
        RSM::Matrix<int> moved(std::move(matrix));
        
        REQUIRE(moved.width() == 5);
        REQUIRE(moved.height() == 10);
        REQUIRE(moved(0,0) == 7);
    }
    
    SECTION("Move assignment integer matrix") {
        RSM::Matrix<int> matrix(5, 10, 7);
        RSM::Matrix<int> moved;
        
        moved = std::move(matrix);
        
        REQUIRE(moved.width() == 5);
        REQUIRE(moved.height() == 10);
        REQUIRE(moved(0,0) == 7);
    }
    
    SECTION("Move construction string matrix") {
        RSM::Matrix<std::string> matrix(5, 10, "Test");
        RSM::Matrix<std::string> moved(std::move(matrix));
        
        REQUIRE(moved.width() == 5);
        REQUIRE(moved.height() == 10);
        REQUIRE(moved(0,0) == "Test");
    }
    
    SECTION("Move assignment string matrix") {
        RSM::Matrix<std::string> matrix(5, 10, "Test");
        RSM::Matrix<std::string> moved;
        
        moved = std::move(matrix);
        
        REQUIRE(moved.width() == 5);
        REQUIRE(moved.height() == 10);
        REQUIRE(moved(0,0) == "Test");
    }
}
