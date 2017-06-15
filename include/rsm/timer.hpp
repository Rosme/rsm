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

#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>

namespace rsm {

    ////////////////////////////////////////////////////////////
    /// \brief Templated class that for a triggering timer
    ///
    /// This class represent a timer that can trigger two types of callback.
    /// Timeout Callback: Is called once the timer is done after X milliseconds.
    /// Interrupt Callback: Is called if the timer is interrupted before timing out.
    /// Template parameters represent std::function argument.
    ////////////////////////////////////////////////////////////
	template<class Timeout, class Interrupt>
	class Timer {
	public:
        ////////////////////////////////////////////////////////////
        /// \brief Constructor
        ////////////////////////////////////////////////////////////
		Timer();

        ////////////////////////////////////////////////////////////
        /// \brief Deleted Copy Constructor
        ////////////////////////////////////////////////////////////
		Timer(const Timer&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Deleted Copy Assignment
        ////////////////////////////////////////////////////////////
		Timer& operator=(const Timer&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Start the time with specified time length
        ///
        /// \param length The time in milliseconds until the timer will timeout.
        ////////////////////////////////////////////////////////////
		void start(std::chrono::milliseconds length);

        ////////////////////////////////////////////////////////////
        /// \brief Set the timeout callback function to be called on timeout.
        ///
        /// \param function A std::function/lambda that represents the callback function.
        ////////////////////////////////////////////////////////////
		void setTimeoutFunction(const std::function<Timeout>& function);

        ////////////////////////////////////////////////////////////
        /// \brief Set the timeout callback function to be called on interrupt.
        ///
        /// \param function A std::function/lambda that represents the callback function.
        ////////////////////////////////////////////////////////////
		void setInterruptFunction(const std::function<Interrupt>& function);

        ////////////////////////////////////////////////////////////
        /// \brief Interrupt the timer before it times out.
        ////////////////////////////////////////////////////////////
		void interrupt();

        ////////////////////////////////////////////////////////////
        /// \brief Tells if the timer is done(either interrupted or timeout).
        ///
        /// \return true if is done(interrupted or timeout), false otherwise
        ////////////////////////////////////////////////////////////
		const bool isDone() const;

	private:
		void priv_start(std::chrono::milliseconds length);

	private:
		std::function<Timeout> m_timeoutFunction;
		std::function<Interrupt> m_interruptFunction;
		std::thread m_thread;
		std::condition_variable m_cv;
		std::mutex m_cvMutex;
		bool m_done;
	};

}

#include <rsm/timer.inl>