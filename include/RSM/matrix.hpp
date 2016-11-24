/*
* Copyright (c) 2015 Jean-Sébastien Fauteux
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

#pragma once

#include <cstdint>
#include <utility>
#include <cassert>
#include <algorithm>

namespace RSM {

    template<class T>
    class Matrix {
    public:
        Matrix(const std::size_t width, const std::size_t height, const T& default_value = T{});
        Matrix(const Matrix& other);
        ~Matrix();
        
        Matrix& operator=(Matrix other);
        
        const T* data() const;
        T* data();
        
        const std::size_t width() const { return m_width; }
        const std::size_t height() const { return m_height; }
        
        T& operator()(std::size_t x, std::size_t y);
        const T& operator()(std::size_t x, std::size_t y) const;
        
        friend void swap(Matrix& first, Matrix& second) {
            std::swap(first.m_data, second.m_data);
            std::swap(first.m_width, second.m_width);
            std::swap(first.m_height, second.m_height);
        }
        
    private:
        T* m_data;
        std::size_t m_width;
        std::size_t m_height;
    };
}

#include "matrix.inl"
