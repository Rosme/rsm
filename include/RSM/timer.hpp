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

namespace RSM {

	template<class Timeout, class Interrupt>
	class Timer {
	public:
		Timer();
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		void start(std::chrono::milliseconds length);

		void setTimeoutFunction(const std::function<Timeout>& function);
		void setInterruptFunction(const std::function<Interrupt>& function);

		void interrupt();

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

#include <RSM/timer.inl>