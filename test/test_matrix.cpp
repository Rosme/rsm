/*
 * Copyright (c) 2015 Jean-SÈbastien Fauteux
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

TEST_CASE("Testing Matrix", "[matrix]") {
    RSM::Matrix<int> matrix(5, 10, 1);
    
    SECTION("Getting Data") {
        
        int l = 0;
        for(int i = 0; i < 5; ++i) {
            for(int j = 0; j < 10; ++j) {
                matrix(j, i) = l;
                l++;
            }
        }
        printf("\n");
        
        for(int i = 0; i < matrix.width(); ++i) {
            for(int j = 0; j < 10; ++j) {
                printf("%d ", matrix(j,i));
            }
        }
        
        REQUIRE(5 == 5);
    }
}
