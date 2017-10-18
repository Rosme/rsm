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

#include <rsm/log/log_device.hpp>
#include <vector>
#include <memory>

namespace rsm {
	
	class Logger {
	public:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		static void addLogDevice(LogDevice::Ptr device) {
			logger().m_logDevices.emplace_back(std::move(device));
		}

		template<class T>
		static void log(LogLevel level, const T& data) {
			for(auto& device : logger().m_logDevices) {
				device->log(level, data);
			}
		}

		template<class T>
		static void debug(const T& data) {
			log(LogLevel::Debug, data);
		}

		template<class T>
		static void info(const T& data) {
			log(LogLevel::Info, data);
		}

		template<class T>
		static void warning(const T& data) {
			log(LogLevel::Warning, data);
		}

		template<class T>
		static void critical(const T& data) {
			log(LogLevel::Critical, data);
		}

		template<class T>
		static void error(const T& data) {
			log(LogLevel::Error, data);
		}

		static void resetLogDevices() {
			logger().m_logDevices.clear();
		}
	private:
		Logger() = default;
		static Logger& logger() {
			static Logger logger;
			return logger;
		}

	private:
		std::vector<LogDevice::Ptr> m_logDevices;
	};
}

