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

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <cassert>

// Specialisation of std::hash
namespace std {
	template <>
	struct hash<const std::string> {
		std::size_t operator()(const std::string& k) const {
			return hash<std::string>()(k);
		}
	};
}

namespace rsm {

	class Config;

	class ConfigFileDescriptor {
	public:
		typedef std::unique_ptr<ConfigFileDescriptor> Ptr;

	public:
		ConfigFileDescriptor() = default;
		ConfigFileDescriptor(const ConfigFileDescriptor&) = delete;
		ConfigFileDescriptor& operator=(const ConfigFileDescriptor&) = delete;
		virtual ~ConfigFileDescriptor() = default;

		static ConfigFileDescriptor::Ptr getDefaultDescriptor();

		virtual void load(Config& config, const std::string& configFile) = 0;
		virtual void save(Config& config, const std::string& configFile) const = 0;
	};

	////////////////////////////////////////////////////////////
	/// \brief Config class to handle configuration file with Key/Value pair
	///		   
	/// The class allows to load from a file all key value. A key must be a string.
	/// A value can be a string, an integer, an unsigned integer or a float.
	///
	/// A Key/Value pair is represented in the config file like this: Key=Value
	///
	/// A line is ignored if it starts with ; or #.
	///
	/// When saving the config file, the file is overwritten with all values stored in
	/// the configuration class.
	///
	////////////////////////////////////////////////////////////
	class Config{
	public:
		typedef std::string Key;

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		////////////////////////////////////////////////////////////
		explicit Config()
			: m_fileDescriptor(ConfigFileDescriptor::getDefaultDescriptor()) {}

        ////////////////////////////////////////////////////////////
        /// \brief Set the config file descriptor used to load the config
        ///
        /// This function set the config file descriptor to be used to load
        /// a config file.
        ///
        ////////////////////////////////////////////////////////////
		void setFileDescriptor(ConfigFileDescriptor::Ptr configFileDescriptor) {
			m_fileDescriptor = std::move(configFileDescriptor);
		}

		////////////////////////////////////////////////////////////
		/// \brief Loading function that loads the config file
		///
		/// This function loads the config file passed as a parameter.
		/// The file is expected to follow the config file rule defined.
		/// This function throw if the config file cannot be open.
		///
		/// \param configFile Name of the config file to load
		///
		////////////////////////////////////////////////////////////
		void load(const std::string& configFile = "config.txt") {
			assert(m_fileDescriptor && "No file descriptor set");
			m_fileDescriptor->load(*this, configFile);
		}

		////////////////////////////////////////////////////////////
		/// \brief Saving function that save the config file
		///
		/// This function save the configs stored in the object to a
		/// config file. It overwrites the config file from scratch.
		/// This function throw if the config file cannot be open.
		///
		/// \param configFile Name of the config file to save
		///
		////////////////////////////////////////////////////////////
		void save(const std::string& configFile = "config.txt") {
			assert(m_fileDescriptor && "No file descriptor set");
			m_fileDescriptor->save(*this, configFile);
		}
		
		////////////////////////////////////////////////////////////
		/// \brief Tell if the object contains a specific config
		///
		/// This function verify if a config is stored with the given key.
		///
		/// \param key Config key to verify the presence in the configs
		///
		/// \return True if the config is present, false otherwise
		///
		////////////////////////////////////////////////////////////
		bool hasConfig(const Key& key) const {
			return m_configs.find(key) != m_configs.end();
		}

		////////////////////////////////////////////////////////////
		/// \brief Give the amount of config stored in the config object
		///
		/// This returns the amount of configs that were loaded from the
		/// config file.
		///
		/// \return The amount of configs loaded
		///
		////////////////////////////////////////////////////////////
		const unsigned int size() const {
			return m_configs.size();
		}

		////////////////////////////////////////////////////////////
		/// \brief Return the value of a config
		///
		/// Return the value of a stored config with the key. A default
		/// value may be provided in case the config does not exist.
		///
		/// \param key Config key to get the value from
		/// \param defaultValue Default value in case the configuration
		///						does not exist
		///
		/// \return Either the value stored or the default value
		///			as a std::string
		///
		////////////////////////////////////////////////////////////
		const std::string& get(const Key& key, const std::string& defaultValue = "") {
			if(hasConfig(key)) {
				return m_configs[key];
			}

			return defaultValue;
		}

		////////////////////////////////////////////////////////////
		/// \brief Return the value of a config
		///
		/// Return the value of a stored config with the key. A default
		/// value may be provided in case the config does not exist.
		///
		/// \param key Config key to get the value from
		/// \param defaultValue Default value in case the configuration
		///						does not exist
		///
		/// \return Either the value stored or the default value
		///			as an integer
		///
		////////////////////////////////////////////////////////////
		const int getInt(const Key& key, const int defaultValue = 0) {
			if(hasConfig(key)) {
				return std::stoi(m_configs[key]);
			}

			return defaultValue;
		}

		////////////////////////////////////////////////////////////
		/// \brief Return the value of a config
		///
		/// Return the value of a stored config with the key. A default
		/// value may be provided in case the config does not exist.
		///
		/// \param key Config key to get the value from
		/// \param defaultValue Default value in case the configuration
		///						does not exist
		///
		/// \return Either the value stored or the default value
		///			as an unsigned integer
		///
		////////////////////////////////////////////////////////////
		const unsigned int getUint(const Key& key, const unsigned int defaultValue = 0) {
			if(hasConfig(key)) {
				return static_cast<unsigned int>(std::stoul(m_configs[key]));
			}

			return defaultValue;
		}

		////////////////////////////////////////////////////////////
		/// \brief Return the value of a config
		///
		/// Return the value of a stored config with the key. A default
		/// value may be provided in case the config does not exist.
		///
		/// \param key Config key to get the value from
		/// \param defaultValue Default value in case the configuration
		///						does not exist
		///
		/// \return Either the value stored or the default value
		///			as a float
		///
		////////////////////////////////////////////////////////////
		const float getFloat(const Key& key, const float defaultValue = 0.f) {
			if(hasConfig(key)) {
				return std::stof(m_configs[key]);
			}

			return defaultValue;
		}

		////////////////////////////////////////////////////////////
		/// \brief Return an array containing all the keys
		///
		/// Return an std::vector containing all the keys currently
		/// stored in the config.
		///
		/// \return std::vector containing all the keys
		///
		////////////////////////////////////////////////////////////
		const std::vector<Config::Key> getKeys() const {
			std::vector<Config::Key> keys;
			for(const auto& it : m_configs) {
				keys.push_back(it.first);
			}
			return keys;
		}

		////////////////////////////////////////////////////////////
		/// \brief Store a std::string value in the config object
		///
		/// Store or replace a std::string value in the config object
		/// defined associated by the given key.
		///
		/// \param key Key to identify the value
		/// \param value The std::string value to store
		///
		////////////////////////////////////////////////////////////
		void set(const Key& key, const std::string& value) {
			m_configs[key] = value;
		}

		////////////////////////////////////////////////////////////
		/// \brief Store a integer value in the config object
		///
		/// Store or replace a std::string value in the config object
		/// defined associated by the given key.
		///
		/// \param key Key to identify the value
		/// \param value The integer value to store
		///
		////////////////////////////////////////////////////////////
		void set(const Key& key, const int value) {
			m_configs[key] = std::to_string(value);
		}

		////////////////////////////////////////////////////////////
		/// \brief Store a unsigned int value in the config object
		///
		/// Store or replace a std::string value in the config object
		/// defined associated by the given key.
		///
		/// \param key Key to identify the value
		/// \param value The unsigned integer value to store
		///
		////////////////////////////////////////////////////////////
		void set(const Key& key, const unsigned int value) {
			m_configs[key] = std::to_string(value);
		}

		////////////////////////////////////////////////////////////
		/// \brief Store a float value in the config object
		///
		/// Store or replace a std::string value in the config object
		/// defined associated by the given key.
		///
		/// \param key Key to identify the value
		/// \param value The float value to store
		///
		////////////////////////////////////////////////////////////
		void set(const Key& key, const float value) {
			m_configs[key] = std::to_string(value);
		}
		
	private:
		Config(const Config&) = delete;
		Config& operator=(const Config&) = delete;

	private:
		typedef std::unordered_map<const Key, std::string> ConfigMap;
		ConfigMap m_configs;
		ConfigFileDescriptor::Ptr m_fileDescriptor;
	};

	class DefaultFileDescriptor
		: public ConfigFileDescriptor {

		void load(Config& config, const std::string& configFile) {
			std::ifstream file;

			file.open(configFile, std::ios::in);
			if(!file.is_open()) {
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
					continue;
				}

				const auto& index = line.find('=');
				//Making sure we have a valid config line
				if(index != std::string::npos) {
					config.set(line.substr(0, index), line.substr(index + 1));
				}
			}
		}

		void save(Config& config, const std::string& configFile) const {
			std::ofstream file;

			file.open(configFile, std::ios::out | std::ios::trunc);
			if(!file.is_open()) {
				throw std::runtime_error("Could not open config file : " + configFile);
			}

			auto& keys = config.getKeys();
			for(const auto& key : keys) {
				file << key << "=" << config.get(key) << "\n";
			}
		}
	};


	ConfigFileDescriptor::Ptr ConfigFileDescriptor::getDefaultDescriptor() {
		return std::unique_ptr<DefaultFileDescriptor>(new DefaultFileDescriptor());
	}

}
