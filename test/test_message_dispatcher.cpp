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

#include "catch.hpp"

#include <rsm/msg/message.hpp>
#include <rsm/msg/message_handler.hpp>
#include <rsm/msg/message_dispatcher.hpp>
#include <rsm/msg/async_message_dispatcher.hpp>

class Handler
    : public rsm::MessageHandler {
public:

    virtual void onMessage(const std::string& key, const rsm::Message& message) override {
        if(key == "empty") {
            REQUIRE(message.getContent().isValid() == false);
        } else if(key == "string") {
            REQUIRE(message.getContent().isValid());
            REQUIRE(message.getContent().get<std::string>() == "testing string");
        }
    }

};

TEST_CASE("Testing Message Dispatcher", "[msg_dispatcher]") {

    SECTION("Dispatching an empty message") {
        rsm::MessageDispatcher dispatcher;

        Handler handler;
        dispatcher.registerHandler("empty", handler);
        dispatcher.registerHandler("string", handler);

        dispatcher.pushMessage("empty");

        dispatcher.dispatch();
    }

    SECTION("Dispatching a string message") {
        rsm::MessageDispatcher dispatcher;

        Handler handler;
        dispatcher.registerHandler("empty", handler);
        dispatcher.registerHandler("string", handler);

        dispatcher.pushMessage("string", "testing string");
        
        dispatcher.dispatch();
    }

}

TEST_CASE("Testing Async Message Dispatcher", "[async_msg_dispatcher]") {

    SECTION("Dispatching an empty message") {
        rsm::AsyncMessageDispatcher dispatcher;

        Handler handler;
        dispatcher.registerHandler("empty", handler);
        dispatcher.registerHandler("string", handler);

        dispatcher.startDispatching();

        dispatcher.pushMessage("empty");

        dispatcher.stopDispatching();
    }

    SECTION("Dispatching a string message") {
        rsm::AsyncMessageDispatcher dispatcher;

        Handler handler;
        dispatcher.registerHandler("empty", handler);
        dispatcher.registerHandler("string", handler);

        dispatcher.startDispatching();

        dispatcher.pushMessage("string", "testing string");

        dispatcher.stopDispatching();
    }

}
