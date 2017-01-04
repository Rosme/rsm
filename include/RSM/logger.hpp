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

#include <RSM/build_config.hpp>
#include <RSM/non_copyable.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace RSM {

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
	class RSM_API Logger 
		: RSM::NonCopyable {
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
		static void setMinLoggingLevel(LoggingLevel level);

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
		static void setLogFile(const std::string& filename);

		////////////////////////////////////////////////////////////
		/// \brief Set the output flags for the logger to know where to output
		///		   the logs.
		///
		/// This defines the flags for the logger to use to know where it
		/// should output the logs. By default this is set to All, which
		/// output both on the console and the file.
		////////////////////////////////////////////////////////////
		static void setOutputFlags(Logger::Output flags);

	private:
		Logger();
		static Logger& getLogger();

		const std::string getStringMinLevel() const;
		const std::string getStringLevel(LoggingLevel level) const;
		const std::string getTime() const;

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

#define RSM_LOG_DEBUG(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Debug)
#define RSM_LOG_INFO(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Info)
#define RSM_LOG_WARN(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Warn)
#define RSM_LOG_CRITICAL(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Critical)
#define RSM_LOG_ERROR(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Error)
