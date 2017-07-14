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

#include <rsm/msg/message.hpp>
#include <rsm/msg/message_handler.hpp>
#include <string>
#include <unordered_map>
#include <queue>

namespace rsm {

    class MessageDispatcher {
    public:
        MessageDispatcher() = default;

        MessageDispatcher(const MessageDispatcher&) = delete;
        MessageDispatcher& operator=(const MessageDispatcher&) = delete;

        void registerHandler(const std::string& key, rsm::MessageHandler& handler) {
            m_handlers.emplace(std::make_pair(key, &handler));
        }

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

        void pushMessage(const std::string& key, const rsm::Message& message = Message()) {
            m_messages.emplace(std::make_pair(key, message));
        }

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