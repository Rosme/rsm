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
#include <rsm/msg/message_handler.hpp>
#include <string>
#include <unordered_map>
#include <queue>

namespace rsm {

    ////////////////////////////////////////////////////////////
    /// \brief Synchronous message dispatcher
    ///
    /// This message dispatcher use a synchronous model, dispatching
    /// the messages only when dispatch is being called. As a very light
    /// and easy system, it dispatches all message before returning.
    ///
    /// The dispatcher make use of rsm::MessageHandler objects to know
    /// to whom a message should be dispatched, based on a Key-Handler system.
    ///
    /// For example, you may want a rsm::MessageHandler that listen only to "quit" key
    /// and another one that listen to all "position" key. Allowing multiple handler to
    /// handle different thing in a more flexible way.
    ///
    /// It is important to unregister the handler before an handler lifetime is over.
    /// If this is not done, it is considered undefined behavior.
    ///
    /// Messages are held in a FIFO queue.
    ////////////////////////////////////////////////////////////
    class MessageDispatcher final {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        MessageDispatcher() = default;

        MessageDispatcher(const MessageDispatcher&) = delete;
        MessageDispatcher& operator=(const MessageDispatcher&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Register an handler for a specific key
        ///
        /// \param key Key corresponding to the handler for message dispatching
        /// \param handler A rsm::MessageHandler to handle the messages dispatched
        ///        with the key
        ///
        ////////////////////////////////////////////////////////////
        void registerHandler(const std::string& key, rsm::MessageHandler& handler) {
            m_handlers.emplace(std::make_pair(key, &handler));
        }

        ////////////////////////////////////////////////////////////
        /// \brief Unregister an handler for a specific key
        ///
        /// \param key Key to unregister an handler
        /// \param handler Handler to unregister
        ///
        ////////////////////////////////////////////////////////////
        void unregisterHandler(const std::string& key, rsm::MessageHandler& handler) {
            auto range = m_handlers.equal_range(key);
            for(auto it = range.first; it != range.second;) {
                if(it->second == &handler) {
                    it = m_handlers.erase(it);
                } else {
                    ++it;
                }
            }
        }

        ////////////////////////////////////////////////////////////
        /// \brief Push a message on the queue
        ///
        /// Note that once a message is pushed, it is impossible to unpush it.
        ///
        /// \param key Key of the message for dispatching
        /// \param message Message to push and dispatch
        ///
        ////////////////////////////////////////////////////////////
        void pushMessage(const std::string& key, const rsm::Message& message = Message()) {
            m_messages.emplace(std::make_pair(key, message));
        }

        ////////////////////////////////////////////////////////////
        /// \brief Dispatch the queued up messages and remove them from the queue
        ///
        ////////////////////////////////////////////////////////////
        void dispatch() {
            while(!m_messages.empty()) {
                auto messagePair = m_messages.front();
                auto range = m_handlers.equal_range(messagePair.first);
                for(auto it = range.first; it != range.second; ++it) {
                    it->second->onMessage(messagePair.first, messagePair.second);
                }
                m_messages.pop();
            }
        }

    private:
        using HandlerMap = std::unordered_multimap<std::string, rsm::MessageHandler*>;
        HandlerMap m_handlers;
        using MessageQueue = std::queue<std::pair<std::string, rsm::Message>>;
        MessageQueue m_messages;
    };

}
