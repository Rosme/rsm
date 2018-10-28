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
	
    ////////////////////////////////////////////////////////////
    /// \brief Logger class to log information with different level
    ///
    /// Make use of a rsm::LogDevice to know where to log. Multiple
    /// log devices can be registered.
    ///
    /// Uses different level of logging:
    ///     - Debug
    ///     - Info
    ///     - Warning
    ///     - Critical
    ///     - Error
    ///
    /// Using static function, it's an easy to use logger system.
    /// The logger works as a stream system, so it can be used easily
    /// like such:
    /// rsm::Logger::debug() << "Logging data" << myObject;
    ////////////////////////////////////////////////////////////
	class Logger final {
	public:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Add a logging device for logging
        ///
        /// \param device A LogDevice::Ptr that will be kept to use for logging
        ////////////////////////////////////////////////////////////
		static void addLogDevice(LogDevice::Ptr device) {
			loggerImpl().m_logDevices.emplace_back(std::move(device));
		}
        
        ////////////////////////////////////////////////////////////
        /// \brief Templated function to log data at the current log level
        ///
        /// While this function can be used, the level functions are more intuitive
        /// and easy to use.
        ///
        /// \param data Data to log
        ///
        /// \see debug
        /// \see info
        /// \see warning
        /// \see critical
        /// \see error
        ////////////////////////////////////////////////////////////
        template<class T>
        static void log(const T& data) {
            log(loggerImpl().m_currentLevel, data);
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Templated function to log data at the specified log level
        ///
        /// While this function can be used, the level functions are more intuitive
        /// and easy to use.
        ///
        /// \param level Level of logging
        /// \param data Data to log
        ///
        /// \see debug
        /// \see info
        /// \see warning
        /// \see critical
        /// \see error
        ////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////
        /// \brief Log at debug level
        ///
        /// Log the data given in the stream at debug level.
        ///
        /// \return A logger implementation to use with streaming
        ////////////////////////////////////////////////////////////
		static Logger& debug() {
            setCurrentLogLevel(LogLevel::Debug);
            return loggerImpl();
		}

        ////////////////////////////////////////////////////////////
        /// \brief Log at info level
        ///
        /// Log the data given in the stream at info level.
        ///
        /// \return A logger implementation to use with streaming
        ////////////////////////////////////////////////////////////
		static Logger& info() {
            setCurrentLogLevel(LogLevel::Info);
            return loggerImpl();
		}

        ////////////////////////////////////////////////////////////
        /// \brief Log at warning level
        ///
        /// Log the data given in the stream at warning level.
        ///
        /// \return A logger implementation to use with streaming
        ////////////////////////////////////////////////////////////
		static Logger& warning() {
            setCurrentLogLevel(LogLevel::Warning);
            return loggerImpl();
		}

        ////////////////////////////////////////////////////////////
        /// \brief Log at critical level
        ///
        /// Log the data given in the stream at critical level.
        ///
        /// \return A logger implementation to use with streaming
        ////////////////////////////////////////////////////////////
		static Logger& critical() {
            setCurrentLogLevel(LogLevel::Critical);
            return loggerImpl();
		}

        ////////////////////////////////////////////////////////////
        /// \brief Log at error level
        ///
        /// Log the data given in the stream at error level.
        ///
        /// \return A logger implementation to use with streaming
        ////////////////////////////////////////////////////////////
		static Logger& error() {
            setCurrentLogLevel(LogLevel::Error);
            return loggerImpl();
		}

        ////////////////////////////////////////////////////////////
        /// \brief Remove all log devices previously registered
        ///
        ////////////////////////////////////////////////////////////
		static void resetLogDevices() {
			loggerImpl().m_logDevices.clear();
		}
        
        ////////////////////////////////////////////////////////////
        /// \brief Templated stream overload for passing data to the logger
        ///
        /// \param data The data to log passed in the stream
        ////////////////////////////////////////////////////////////
        template<class T>
        Logger& operator<<(const T& data) const
        {
            auto& logger = loggerImpl();
            logger.log(data);
            return logger;
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Set the current log level of the logger
        ///
        /// While this function can be used with log, the level functions are more intuitive
        /// and easy to use.
        ///
        /// \param level Log level to set the logger
        /// \see debug
        /// \see info
        /// \see warning
        /// \see critical
        /// \see error
        ////////////////////////////////////////////////////////////
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
