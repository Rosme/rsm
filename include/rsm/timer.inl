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

    template<class Timeout, class Interrupt>
    Timer<Timeout, Interrupt>::Timer()
        : m_done(false) {}


    template<class Timeout, class Interrupt>
    void Timer<Timeout, Interrupt>::start(std::chrono::milliseconds length) {
        m_done = false;
        m_thread = std::thread(&Timer::priv_start, this, length);
        m_thread.detach();
    }

    template<class Timeout, class Interrupt>
    void Timer<Timeout, Interrupt>::setTimeoutFunction(const std::function<Timeout>& function) {
        m_timeoutFunction = function;
    }

    template<class Timeout, class Interrupt>
    void Timer<Timeout, Interrupt>::setInterruptFunction(const std::function<Interrupt>& function) {
        m_interruptFunction = function;
    }

    template<class Timeout, class Interrupt>
    void Timer<Timeout, Interrupt>::interrupt() {
        m_done = true;
        m_cv.notify_all();
    }

    template<class Timeout, class Interrupt>
    const bool Timer<Timeout, Interrupt>::isDone() const {
        return m_done;
    }

    template<class Timeout, class Interrupt>
    void Timer<Timeout, Interrupt>::priv_start(std::chrono::milliseconds length) {
        std::unique_lock<std::mutex> lock(m_cvMutex);
        if(m_cv.wait_for(lock, length, [this] {return m_done;})) {
            if(m_interruptFunction) {
                m_interruptFunction();
            }
        } else {
            m_done = true;
            if(m_timeoutFunction) {
                m_timeoutFunction();
            }
        }
    }

}