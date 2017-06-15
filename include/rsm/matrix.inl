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

namespace rsm {
    
    template<class T>
    Matrix<T>::Matrix(const std::size_t width, const std::size_t height, const T& default_value)
        : m_data(nullptr)
        , m_width(width)
        , m_height(height) {
            
        if(width > 0 && height > 0) {
            m_data = new T[width*height]();
        }
        
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {
                m_data[height * i + j] = default_value;
            }
        }
    }
        
    template<class T>
    Matrix<T>::Matrix(const Matrix<T>& other)
        : m_data(nullptr)
        , m_width(other.m_width)
        , m_height(other.m_height) {
        
        if(m_width > 0 && m_height > 0) {
            m_data = new T[m_width*m_height]();
            std::copy(other.m_data, other.m_data + m_width*m_height, m_data);
        }
    }
    
    template<class T>
    Matrix<T>::Matrix(Matrix&& other) {
        m_data = std::move(other.m_data);
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
        
        other.m_data = nullptr;
    }
    
    template<class T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T> other) {
        swap(*this, other);
        
        return *this;
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
        assert(m_data);
        assert(x >= 0 && "X index is below 0");
        assert(x <= m_height && "X index is out of bounds");
        assert(y >= 0 && "Y index is below 0");
        assert(y < m_width && "Y index is out of bounds");
        return m_data[m_height * y + x];
    }
    
    template<class T>
    const T& Matrix<T>::operator()(std::size_t x, std::size_t y) const {
        assert(m_data);
        assert(x >= 0 && "X index is below 0");
        assert(x < m_height && "X index is out of bounds");
        assert(y >= 0 && "Y index is below 0");
        assert(y < m_width && "Y index is out of bounds");
        return m_data[m_height * y + x];
    }
}
