/*
* Copyright (c) 2018 Jean-SŽbastien Fauteux
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

#include <memory>
#include <string>

namespace rsm {
	
    ////////////////////////////////////////////////////////////
    /// \brief Enum class of the log levels
    ///
    ////////////////////////////////////////////////////////////
	enum class LogLevel {
		None,
		Debug,
		Info,
		Warning,
		Critical,
		Error
	};

    ////////////////////////////////////////////////////////////
    /// \brief Utility function to return the string definition
    ///        of the log levels
    ///
    /// \param level Log level to get the string version
    ///
    /// \return A string representing the log level
    ////////////////////////////////////////////////////////////
	std::string logLevelToString(LogLevel level) {
		switch (level) {
		case LogLevel::Debug:
			return "Debug";
		case LogLevel::Info:
			return "Info";
		case LogLevel::Warning:
			return "Warning";
		case LogLevel::Critical:
			return "Critical";
		case LogLevel::Error:
			return "Error";
		default:
			return "None";
		}
	}

    ////////////////////////////////////////////////////////////
    /// \brief Log device class
    ///
    /// This class needs to be inherited and the function log to be overriden.
    /// It is the interface for the log device used by the logger.
    ///
    /// Inheriting class should define how the logging is done.
    ////////////////////////////////////////////////////////////
	class LogDevice {
	public:
		virtual ~LogDevice() = default;
		using Ptr = std::unique_ptr<LogDevice>;

        ////////////////////////////////////////////////////////////
        /// \brief Pure virtual function called by the logger when logging
        ///
        /// This function is called by the logger and should do the logging
        /// the way the log device want.
        ///
        /// \param level Log level of the log
        /// \param message Message to be logged
        ////////////////////////////////////////////////////////////
		virtual void log(LogLevel level, const std::string& message) = 0;

	protected:
		LogDevice() = default;
	};

}
