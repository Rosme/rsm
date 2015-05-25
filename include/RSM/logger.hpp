/*
* Copyright (C) - Jean-Sébastien Fauteux 2015
* This work is licensed under the Creative Commons Attribution 4.0 International License.
* To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/
* or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#pragma once

#include <RSM/config.hpp>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace RSM {

	////////////////////////////////////////////////////////////
	/// \brief Logger utilities that will log to console and file.
	///		   
	/// The logger is represented as singleton accessible from
	/// anywhere within an application. All function are actually static
	/// and can be called from anywhere. Some macro are defined to ease the use
	/// of the logger. 
	///
	/// To log your own object, you only need to define an overload for the operator<<.
	///
	////////////////////////////////////////////////////////////
	class RSM_API Logger {
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
		/// \brief Set the maximum level that the logger should consider
		///
		/// By default, this is set to Error(the highest).
		///
		/// \param level The maximum logging level the logger should consider
		////////////////////////////////////////////////////////////
		static void setMaxLoggingLevel(LoggingLevel level);

		////////////////////////////////////////////////////////////
		/// \brief A template function that logs the given data
		///
		/// This logs the passed data to the output defined by the logger flags.
		/// Those flags are by default All(Console and File).
		///
		/// \param data Template parameter representing all the data to ouput
		/// \param func Name of the function the log is called from. For
		///				easier use, the macro EVE_FUNC is provided.
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

		const std::string getStringLevel() const;
		const std::string getStringLevel(LoggingLevel level) const;

	private:
		LoggingLevel mMaxLevel;
		std::string mLogFile;
		std::ofstream mFileStream;
		Logger::Output mOutputFlags;
	};

	template<class T>
	void Logger::log(T data, const char* func, Logger::LoggingLevel level) {
		auto& logger = getLogger();
		if (level <= logger.mMaxLevel && level != LoggingLevel::None) {
			// If it was determined that no output will be shown,
			// we'll return right away from the function
			if (logger.mOutputFlags == Output::None) {
				return;
			}

			//If the flag matches the file output
			if (static_cast<int>(logger.mOutputFlags) & static_cast<int>(Logger::Output::File)) {
				logger.mFileStream << "[" + logger.getStringLevel(level) + "] " << func << " : " << data << '\n';
			}
			
			//If the flag matches the console output
			if (static_cast<int>(logger.mOutputFlags) & static_cast<int>(Logger::Output::Console)) {
				std::cout << "[" + logger.getStringLevel(level) + "] " << func << " : " << data << '\n';
			}
		}
	}
}

#define RSM_LOG_DEBUG(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Debug)
#define RSM_LOG_INFO(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Info)
#define RSM_LOG_WARN(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Warn)
#define RSM_LOG_CRITICAL(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Critical)
#define RSM_LOG_ERROR(t) RSM::Logger::log(t, __func__, RSM::Logger::LoggingLevel::Error)


