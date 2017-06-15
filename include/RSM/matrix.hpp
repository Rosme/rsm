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

#pragma once

#include <cstdint>
#include <utility>
#include <cassert>
#include <algorithm>

namespace rsm {

    ////////////////////////////////////////////////////////////
    /// \brief Templated class that represents a Matrix
    ///
    /// This class can be used for a Matrix. It exposes very basic functionnality.
    /// The access to the index is done using the operator().
    ////////////////////////////////////////////////////////////
    template<class T>
    class Matrix {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Construct the Matrix with the width, height and default value indicated.
        ///
        /// \param width Width of the matrix
        /// \param height Height of the matrix
        /// \param default_value Default value of the cells in the matrix
        ////////////////////////////////////////////////////////////
        Matrix(const std::size_t width = 0, const std::size_t height = 0, const T& default_value = T{});
        ////////////////////////////////////////////////////////////
        /// \brief Copy Constructor
        ///
        /// Construct the Matrix with the width, height and current values of the passed Matrix
        ///
        /// \param other Matrix to copy construct from
        ////////////////////////////////////////////////////////////
        Matrix(const Matrix& other);
        ////////////////////////////////////////////////////////////
        /// \brief Move Constructor
        ///
        /// Construct the Matrix with the width, height and value of the passed Matrix
        /// The passed Matrix will be invalidated after construction
        ///
        /// \param other Matrix to move construct from
        ////////////////////////////////////////////////////////////
        Matrix(Matrix&& other);
        ///////////////////////////////////////////////////////////
        /// \brief Destructor
        ////////////////////////////////////////////////////////////
        ~Matrix();
        
        ///////////////////////////////////////////////////////////
        /// \brief Copy assignment
        ///
        /// Copy assign the width, height and data from another matrix.
        ///
        /// \param other Matrix to copy the value from
        ///
        /// \return Reference to Matrix
        ////////////////////////////////////////////////////////////
        Matrix& operator=(Matrix other);
        
        ///////////////////////////////////////////////////////////
        /// \brief Const pointer to raw data
        ///
        /// Obtain a const pointer to the raw data under the matrix.
        ///
        /// \return Const pointer to raw data
        ////////////////////////////////////////////////////////////
        const T* data() const;
        ///////////////////////////////////////////////////////////
        /// \brief Pointer to raw data
        ///
        /// Obtain a pointer to the raw data under the matrix.
        ///
        /// \return Pointer to raw data
        ////////////////////////////////////////////////////////////
        T* data();
        
        ///////////////////////////////////////////////////////////
        /// \brief Width of matrix
        ///
        /// Return the width of the matrix has defined at initilisation
        ///
        /// \return The width of the matrix
        ////////////////////////////////////////////////////////////
        const std::size_t width() const { return m_width; }
        ///////////////////////////////////////////////////////////
        /// \brief Height of matrix
        ///
        /// Return the height of the matrix has defined at initilisation
        ///
        /// \return The height of the matrix
        ////////////////////////////////////////////////////////////
        const std::size_t height() const { return m_height; }
        
        ///////////////////////////////////////////////////////////
        /// \brief Cell at index x and y
        ///
        /// Return a reference to the cell indicated by x and y.
        /// Can be used to modify the value of a cell in the matrix.
        ///
        /// \param x X index of the matrix
        /// \param y Y index of the matrix
        ///
        /// \return A reference to the cell indicated by x and y
        ////////////////////////////////////////////////////////////
        T& operator()(std::size_t x, std::size_t y);
        ///////////////////////////////////////////////////////////
        /// \brief Cell at index x and y
        ///
        /// Return a const reference to the cell indicated by x and y.
        ///
        /// \param x X index of the matrix
        /// \param y Y index of the matrix
        ///
        /// \return A const reference to the cell indicated by x and y
        ////////////////////////////////////////////////////////////
        const T& operator()(std::size_t x, std::size_t y) const;
        
        ///////////////////////////////////////////////////////////
        /// \brief Swap the value between two matrix
        ///
        /// This is used to implement the assignment operator.
        /// It swaps the value of width, height and the array between two matrixes.
        ///
        /// \param first The first matrix
        /// \param second The second matrix
        ////////////////////////////////////////////////////////////
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

#include <rsm/matrix.inl>
