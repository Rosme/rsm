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
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <queue>

namespace rsm {

    class AsyncMessageDispatcher {
    public:
        AsyncMessageDispatcher() = default;

        AsyncMessageDispatcher(const AsyncMessageDispatcher&) = delete;
        AsyncMessageDispatcher& operator=(const AsyncMessageDispatcher&) = delete;

        void registerHandler(const std::string& key, rsm::MessageHandler& handler) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_handlers.emplace(std::make_pair(key, &handler));
        }

        void unregisterHandler(const std::string& key, rsm::MessageHandler& handler) {
            std::lock_guard<std::mutex> lock(m_mutex);
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
            std::lock_guard<std::mutex> lock(m_mutex);
            m_messages.emplace(std::make_pair(key, message));
        }

        void startDispatching() {
            m_running = true;
            m_thread = std::thread(&AsyncMessageDispatcher::dispatch, this);
            m_thread.detach();
        }

        void stopDispatching() {
            m_running = false;
        }

    private:
        void dispatch() {
            while(m_running) {
                while(m_messages.size() == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }

                MessageQueue messageQueue;
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    messageQueue.swap(m_messages);
                }
                while(!messageQueue.empty()) {
                    auto messagePair = messageQueue.front();
                    auto range = m_handlers.equal_range(messagePair.first);
                    for(auto it = range.first; it != range.second; ++it) {
                        it->second->onMessage(messagePair.first, messagePair.second);
                    }
                    messageQueue.pop();
                }
            }
        }

    private:
        typedef std::unordered_multimap<std::string, rsm::MessageHandler*> HandlerMap;
        HandlerMap m_handlers;
        typedef std::queue<std::pair<std::string, rsm::Message>> MessageQueue;
        MessageQueue m_messages;
        std::thread m_thread;
        std::mutex m_mutex;
        bool m_running = false;
    };

}