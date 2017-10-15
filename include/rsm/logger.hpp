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

#include <vector>
#include <memory>

namespace rsm {
	
	class LogDevice {
	public:
		using Ptr = std::unique_ptr<LogDevice>;
	protected:
		LogDevice() = default;

	};

	class Logger {
	public:
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		static void addLogDevice(LogDevice::Ptr device) {
			logger().m_logDevices.emplace_back(std::move(device));
		}

	private:
		Logger() {}
		static Logger& logger() {
			static Logger logger;
			return logger;
		}

	private:
		std::vector<LogDevice::Ptr> m_logDevices;
	};

}

