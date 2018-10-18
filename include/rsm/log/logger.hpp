/*
* Copyright (c) 2018 Jean-Sébastien Fauteux
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

#include <rsm/log/log_device.hpp>
#include <vector>
#include <memory>
#include <sstream>

namespace rsm {
	
	class Logger {
	public:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		static void addLogDevice(LogDevice::Ptr device) {
			loggerImpl().m_logDevices.emplace_back(std::move(device));
		}

        template<int>
        static void log(int data) {
            log(loggerImpl().m_currentLevel, data);
        }
        
        template<class T>
        static void log(const T& data) {
            log(loggerImpl().m_currentLevel, data);
        }
        
        template<class T>
        static void log(LogLevel level, const T& data) {
            auto& stream = loggerImpl().m_stream;
            stream << data;
            for(auto& device : loggerImpl().m_logDevices) {
                device->log(level, stream.str());
            }
            stream.str("");
            stream.clear();
        }

		static Logger& debug() {
            setCurrentLogLevel(LogLevel::Debug);
            return loggerImpl();
		}

		static Logger& info() {
            setCurrentLogLevel(LogLevel::Info);
            return loggerImpl();
		}

		static Logger& warning() {
            setCurrentLogLevel(LogLevel::Warning);
            return loggerImpl();
		}

		static Logger& critical() {
            setCurrentLogLevel(LogLevel::Critical);
            return loggerImpl();
		}

		static Logger& error() {
            setCurrentLogLevel(LogLevel::Error);
            return loggerImpl();
		}

		static void resetLogDevices() {
			loggerImpl().m_logDevices.clear();
		}
        
        template<class T>
        Logger& operator<<(const T& data) const
        {
            auto& logger = loggerImpl();
            logger.log(data);
            return logger;
        }
        
        static void setCurrentLogLevel(LogLevel level) {
            loggerImpl().m_currentLevel = level;
        }
        
	private:
		Logger() = default;
		static Logger& loggerImpl() {
			static Logger logger;
			return logger;
		}

    private:
		std::vector<LogDevice::Ptr> m_logDevices;
        std::ostringstream m_stream;
        LogLevel m_currentLevel;
	};
}
