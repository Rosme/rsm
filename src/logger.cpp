/*
* Copyright (c) 2015 Jean-Sébastien Fauteux
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

#include <RSM/logger.hpp>

#include <stdexcept>

namespace RSM {

	void Logger::setMaxLoggingLevel(Logger::LoggingLevel level) {
		getLogger().mMaxLevel = level;
	}

	void Logger::setLogFile(const std::string& filename) {
		auto& logger = getLogger();
		logger.mLogFile = filename;
		if (logger.mFileStream.is_open()) {
			logger.mFileStream.close();
		}
		logger.mFileStream.open(filename, std::ios::out|std::ios::trunc);
		if (!logger.mFileStream.is_open()) {
			throw std::runtime_error("Impossible to create the new log file");
		}
	}

	void Logger::setOutputFlags(Logger::Output flags) {
		getLogger().mOutputFlags = flags;
	}

	Logger::Logger()
		: mMaxLevel(LoggingLevel::Error), mLogFile("log"), mOutputFlags(Output::All) {
		mFileStream.open(mLogFile, std::ios::out|std::ios::trunc);
		if (!mFileStream.is_open()) {
			throw std::runtime_error("Impossible to create the new log file");
		}
	}

	Logger& Logger::getLogger() {
		static Logger logger;
		return logger;
	}

	const std::string Logger::getStringMaxLevel() const {
		return getStringLevel(getLogger().mMaxLevel);
	}

	const std::string Logger::getStringLevel(Logger::LoggingLevel level) const {
		switch (level) {
		case Logger::LoggingLevel::None:
			return "None";
		case Logger::LoggingLevel::Debug:
			return "Debug";
		case Logger::LoggingLevel::Info:
			return "Info";
		case Logger::LoggingLevel::Warn:
			return "Warn";
		case Logger::LoggingLevel::Critical:
			return "Critical";
		case Logger::LoggingLevel::Error:
			return "Error";
		default:
			return "Unknown";
		}
	}

}
