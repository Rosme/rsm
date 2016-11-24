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

namespace RSM {
    
    template<class T>
    Matrix<T>::Matrix(const std::size_t width, const std::size_t height, const T& default_value)
        : m_width(width)
        , m_height(height) {
            
            m_data = new T[width*height];
            
            for(int i = 0; i < width; ++i) {
                for(int j = 0; j < height; ++j) {
                    m_data[width * i + j] = default_value;
                }
            }
        }
    
    template<class T>
    Matrix<T>::~Matrix() {
        delete[] m_data;
    }
        
    template<class T>
    const T* Matrix<T>::data() const {
        return m_data;
    }
    
    template<class T>
    T* Matrix<T>::data() {
        return m_data;
    }
    
    template<class T>
    T& Matrix<T>::operator()(std::size_t x, std::size_t y) {
        return m_data[m_height * y + x];
    }
    
    template<class T>
    const T& Matrix<T>::operator()(std::size_t x, std::size_t y) const {
        return m_data[m_height * y + x];
    }
}
