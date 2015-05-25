/*
* Copyright (C) - Jean-Sébastien Fauteux 2015
* This work is licensed under the Creative Commons Attribution 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
* or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <RSM/logger.hpp>

#include <stdexcept>

namespace RSM {

	void Logger::setMaxLoggingLevel(Logger::LoggingLevel level) {
		auto& logger = getLogger();
		logger.mMaxLevel = level;
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
		auto& logger = getLogger();
		logger.mOutputFlags = flags;
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

	const std::string Logger::getStringLevel() const {
		return getStringLevel(getLogger().mMaxLevel);
	}

	const std::string Logger::getStringLevel(Logger::LoggingLevel level) const {
		switch (level) {
		case Logger::LoggingLevel::None:
			return "None";
			break;
		case Logger::LoggingLevel::Debug:
			return "Debug";
			break;
		case Logger::LoggingLevel::Info:
			return "Info";
			break;
		case Logger::LoggingLevel::Warn:
			return "Warn";
			break;
		case Logger::LoggingLevel::Critical:
			return "Critical";
			break;
		case Logger::LoggingLevel::Error:
			return "Error";
			break;
		default:
			return "Unknown";
		}
	}

}
