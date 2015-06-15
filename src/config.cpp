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

#include <RSM/config.hpp>
#include <RSM/logger.hpp>

#include <stdexcept>
#include <fstream>

namespace RSM {

	void Config::load(const std::string& configFile) {
		std::ifstream file;

		file.open(configFile, std::ios::in);
		if(!file.is_open()) {
			RSM_LOG_ERROR("Could not open config file : " + configFile);
			throw std::runtime_error("Could not open config file : " + configFile);
		}

		std::string line;
		while(std::getline(file, line)) {
			//Empty line, we skip
			if(line.size() == 0) {
				continue;
			}

			//Let's see if the line is to be ignored
			if(line[0] == ';' || line[0] == '#') {
				RSM_LOG_INFO("Ignoring line : " + line);
				continue;
			}

			const auto& index = line.find('=');
			//Making sure we have a valid config line
			if(index != std::string::npos) {
				RSM_LOG_INFO("Loading config line : " + line);
				m_configs[line.substr(0, index)] = line.substr(index + 1);
			}
		}
	}

	void Config::save(const std::string& configFile) const {
		std::ofstream file;

		file.open(configFile, std::ios::out | std::ios::trunc);
		if(!file.is_open()) {
			RSM_LOG_ERROR("Could not open config file : " + configFile);
			throw std::runtime_error("Could not open config file : " + configFile);
		}

		for(const auto& config : m_configs) {
			file << config.first << "=" << config.second << "\n";
		}
	}

	bool Config::hasConfig(Key& key) const {
		return m_configs.find(key) != m_configs.end();
	}

	const unsigned int Config::size() const {
		return m_configs.size();
	}

	const std::string& Config::get(Key& key, const std::string& defaultValue) {
		if(hasConfig(key)) {
			return m_configs[key];
		}

		return defaultValue;
	}

	const int Config::getInt(Key& key, const int defaultValue) {
		if(hasConfig(key)) {
			return std::stoi(m_configs[key]);
		}

		return defaultValue;
	}

	const unsigned int Config::getUint(Key& key, const unsigned int defaultValue) {
		if(hasConfig(key)) {
			return static_cast<unsigned int>(std::stoul(m_configs[key]));
		}

		return defaultValue;
	}

	const float Config::getFloat(Key& key, const float defaultValue) {
		if(hasConfig(key)) {
			return std::stof(m_configs[key]);
		}

		return defaultValue;
	}

	void Config::set(Key& key, const std::string& value) {
		m_configs[key] = value;
	}

	void Config::set(Key& key, const int value) {
		m_configs[key] = std::to_string(value);
	}

	void Config::set(Key& key, const unsigned int value) {
		m_configs[key] = std::to_string(value);
	}

	void Config::set(Key& key, const float value) {
		m_configs[key] = std::to_string(value);
	}
}