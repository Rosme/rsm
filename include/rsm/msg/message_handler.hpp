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

#include <rsm/msg/message.hpp>

namespace rsm {

    ////////////////////////////////////////////////////////////
    /// \brief Message handler class to handle the messages
    ///
    /// This class needs to be inherited from and the function onMessage
    /// needs to be overriden.
    ///
    ////////////////////////////////////////////////////////////
    class MessageHandler {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        MessageHandler() = default;
        
        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        virtual ~MessageHandler() = default;

        MessageHandler(const MessageHandler&) = delete;
        MessageHandler& operator=(const MessageHandler&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Pure virtual function to override to handle incoming message
        ///
        /// This function is called by the dispatcher with the key to the message
        /// and the corresponding message.
        ///
        /// \param key Key of the message when dispatched
        /// \param message Message dispatched
        ///
        /// \see MessageDispatcher
        /// \see AsyncMessageDispatcher
        ///
        ////////////////////////////////////////////////////////////
        virtual void onMessage(const std::string& key, const rsm::Message& message) = 0;
    };

}
