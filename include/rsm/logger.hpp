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

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>

namespace rsm {

	////////////////////////////////////////////////////////////
	/// \brief Logging utilities that will log to console and file.
	///		   
	/// The logger is represented as singleton accessible from
	/// anywhere within an application. All function are actually static
	/// and can be called from anywhere. Some macro are defined to ease the use
	/// of the logger. 
	///
	/// To log your own object, you only need to define an overload for the operator<<.
	///
	////////////////////////////////////////////////////////////
	class Logger  {
	public:
		////////////////////////////////////////////////////////////
		/// \brief Logging levels of the logger
		///
		////////////////////////////////////////////////////////////
		enum class LoggingLevel {
			None,
			Debug,
			Info,
			Warn,
			Critical,
			Error
		};

		////////////////////////////////////////////////////////////
		/// \brief Possible output area of the loggers
		///
		////////////////////////////////////////////////////////////
		enum class Output{
			None	= 1 << 0,
			Console	= 1 << 1,
			File	= 1 << 2,
			All		= Console|File,
		};

		////////////////////////////////////////////////////////////
		/// \brief Set the minimum level that the logger should consider
		///
		/// By default, this is set to Debug(the lowest).
		///
		/// \param level The minimum logging level the logger should consider
		////////////////////////////////////////////////////////////
		static void setMinLoggingLevel(LoggingLevel level) {
			getLogger().mMinLevel = level;
		}

		////////////////////////////////////////////////////////////
		/// \brief A template function that logs the given data
		///
		/// This logs the passed data to the output defined by the logger flags.
		/// Those flags are by default All(Console and File).
		///
		/// \param data Template parameter representing all the data to ouput
		/// \param func Name of the function the log is called from
		/// \param level The logging level of the data that is passed
		///
		////////////////////////////////////////////////////////////
		template<class T>
		static void log(T data, const char * func, LoggingLevel level = LoggingLevel::Debug);

		////////////////////////////////////////////////////////////
		/// \brief Set the file to output the logs
		///
		/// This will close the current open logfile and open a new one.
		/// If the file doesn't exist, it will be created.
		///
		/// \param filename The name of the new log file to use
		///
		////////////////////////////////////////////////////////////
		static void setLogFile(const std::string& filename) {
			auto& logger = getLogger();
			logger.mLogFile = filename;
			if(logger.mFileStream.is_open()) {
				logger.mFileStream.close();
			}
			logger.mFileStream.open(filename, std::ios::out | std::ios::trunc);
			if(!logger.mFileStream.is_open()) {
				throw std::runtime_error("Impossible to create the new log file");
			}
		}

		////////////////////////////////////////////////////////////
		/// \brief Set the output flags for the logger to know where to output
		///		   the logs.
		///
		/// This defines the flags for the logger to use to know where it
		/// should output the logs. By default this is set to All, which
		/// output both on the console and the file.
		////////////////////////////////////////////////////////////
		static void setOutputFlags(Logger::Output flags) {
			getLogger().mOutputFlags = flags;
		}

	private:
		Logger()
			: mMinLevel(LoggingLevel::Debug), mLogFile("log"), mOutputFlags(Output::All) {
			mFileStream.open(mLogFile, std::ios::out | std::ios::trunc);
			if(!mFileStream.is_open()) {
				throw std::runtime_error("Impossible to create the new log file");
			}
		}

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		static Logger& getLogger() {
			static Logger logger;
			return logger;
		}

		const std::string getStringMinLevel() const {
			return getStringLevel(getLogger().mMinLevel);
		}

		const std::string getStringLevel(LoggingLevel level) const {
			switch(level) {
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

		const std::string getTime() const {
			using namespace std::chrono;
			typedef duration<int, std::ratio_multiply<hours::period, std::ratio<24>>::type> days;

			system_clock::time_point now = system_clock::now();
			system_clock::duration tp = now.time_since_epoch();
			days day = duration_cast<days>(tp);
			tp -= day;
			hours hour = duration_cast<hours>(tp);
			tp -= hour;
			minutes minute = duration_cast<minutes>(tp);
			tp -= minute;
			seconds second = duration_cast<seconds>(tp);
			tp -= second;
			milliseconds millisecond = duration_cast<milliseconds>(tp);

			time_t rawTimeT = system_clock::to_time_t(now);
			tm timeInfo;
		#ifdef WIN32
			localtime_s(&timeInfo, &rawTimeT);
		#else
			localtime_r(&rawTimeT, &timeInfo);
		#endif
			return std::to_string(timeInfo.tm_hour) + ":" + std::to_string(minute.count()) + ":"
				+ std::to_string(second.count()) + ":" + std::to_string(millisecond.count());
		}

	private:
		LoggingLevel mMinLevel;
		std::string mLogFile;
		std::ofstream mFileStream;
		Logger::Output mOutputFlags;
	};

	template<class T>
	void Logger::log(T data, const char* func, Logger::LoggingLevel level) {
		auto& logger = getLogger();
		if (logger.mMinLevel <= level && logger.mMinLevel != LoggingLevel::None) {
			// If it was determined that no output will be shown,
			// we'll return right away from the function
			if (logger.mOutputFlags == Output::None) {
				return;
			}

			//If the flag matches the file output
			if (static_cast<int>(logger.mOutputFlags) & static_cast<int>(Logger::Output::File)) {
				logger.mFileStream << "[" + logger.getStringLevel(level) + "] " << logger.getTime() << " " << func << " : " << data << '\n';
			}
			
			//If the flag matches the console output
			if (static_cast<int>(logger.mOutputFlags) & static_cast<int>(Logger::Output::Console)) {
				std::cout << "[" + logger.getStringLevel(level) + "] " << logger.getTime() << " " << func << " : " << data << '\n';
			}
		}
	}
}

#if defined(_MSC_VER)
	#if _MSC_VER <= 1800
		#define __func__ __FUNCTION__
	#endif
#endif

#define RSM_LOG_DEBUG(t) rsm::Logger::log(t, __func__, rsm::Logger::LoggingLevel::Debug)
#define RSM_LOG_INFO(t) rsm::Logger::log(t, __func__, rsm::Logger::LoggingLevel::Info)
#define RSM_LOG_WARN(t) rsm::Logger::log(t, __func__, rsm::Logger::LoggingLevel::Warn)
#define RSM_LOG_CRITICAL(t) rsm::Logger::log(t, __func__, rsm::Logger::LoggingLevel::Critical)
#define RSM_LOG_ERROR(t) rsm::Logger::log(t, __func__, rsm::Logger::LoggingLevel::Error)
