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

#include <cassert>

namespace RSM {

	Config::Config() 
		: m_fileDescriptor(ConfigFileDescriptor::getDefaultDescriptor()) {}

	void Config::setFileDescriptor(ConfigFileDescriptor::Ptr configFileDescriptor) {
		m_fileDescriptor = std::move(configFileDescriptor);
	}

	void Config::load(const std::string& configFile) {
		assert(m_fileDescriptor && "No file descriptor set");
		m_fileDescriptor->load(*this, configFile);
	}

	void Config::save(const std::string& configFile) {
		assert(m_fileDescriptor && "No file descriptor set");
		m_fileDescriptor->save(*this, configFile);
	}

	bool Config::hasConfig(const Key& key) const {
		return m_configs.find(key) != m_configs.end();
	}

	const unsigned int Config::size() const {
		return m_configs.size();
	}

	const std::string& Config::get(const Key& key, const std::string& defaultValue) {
		if(hasConfig(key)) {
			return m_configs[key];
		}

		return defaultValue;
	}

	const int Config::getInt(const Key& key, const int defaultValue) {
		if(hasConfig(key)) {
			return std::stoi(m_configs[key]);
		}

		return defaultValue;
	}

	const unsigned int Config::getUint(const Key& key, const unsigned int defaultValue) {
		if(hasConfig(key)) {
			return static_cast<unsigned int>(std::stoul(m_configs[key]));
		}

		return defaultValue;
	}

	const float Config::getFloat(const Key& key, const float defaultValue) {
		if(hasConfig(key)) {
			return std::stof(m_configs[key]);
		}

		return defaultValue;
	}

	const std::vector<Config::Key> Config::getKeys() const {
		std::vector<Config::Key> keys;
		for(const auto& it : m_configs) {
			keys.push_back(it.first);
		}
		return keys;
	}

	void Config::set(const Key& key, const std::string& value) {
		m_configs[key] = value;
	}

	void Config::set(const Key& key, const int value) {
		m_configs[key] = std::to_string(value);
	}

	void Config::set(const Key& key, const unsigned int value) {
		m_configs[key] = std::to_string(value);
	}

	void Config::set(const Key& key, const float value) {
		m_configs[key] = std::to_string(value);
	}
}
