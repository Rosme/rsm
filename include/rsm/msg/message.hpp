/*
* Copyright (c) 2018 Jean-SŽbastien Fauteux
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

#include <rsm/any.hpp>
#include <string>

namespace rsm {

    ////////////////////////////////////////////////////////////
    /// \brief Message class wrapping an object for easy moving
    ///
    /// Using type-erasure class rsm::Any, the Message class wraps any object,
    /// allowing to move the object anywhere easily.
    ///
    /// \see Any
    ////////////////////////////////////////////////////////////
    class Message final {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Message() {}

        ////////////////////////////////////////////////////////////
        /// \brief Templated constructor for constructing a Message with
        ///        any kind of object
        ///
        /// \param content Any object that needs to be wrapped in the message.
        ///
        ////////////////////////////////////////////////////////////
        template<class T>
        Message(T content)
            : m_content(content) {}

        ////////////////////////////////////////////////////////////
        /// \brief Specialised constructor for strings of const char*
        ///
        /// This constructor will actually transform the const char* in
        /// a std::string.
        ///
        /// \param content String to wrap
        ///
        ////////////////////////////////////////////////////////////
        Message(const char* content)
            : m_content(std::string(content)) {}

        ////////////////////////////////////////////////////////////
        /// \brief Return a reference to the content of wrapped within the message
        ///
        /// \return The rsm::Any object containing the object
        const rsm::Any& getContent() const {
            return m_content;
        }

    private:
        rsm::Any m_content;
    };

}
