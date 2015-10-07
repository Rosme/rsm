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

#pragma once

#include <RSM/build_config.hpp>
#include <RSM/non_copyable.hpp>
#include <RSM/config_file_descriptor.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <memory>

// Specialisation of std::hash
namespace std {
	template <>
	struct hash<const std::string> {
		std::size_t operator()(const std::string& k) const {
			return hash<std::string>()(k);
		}
	};
}

namespace RSM {

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
	class RSM_API Config 
		: RSM::NonCopyable {
	public:
		typedef std::string Key;

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		////////////////////////////////////////////////////////////
		explicit Config();

        ////////////////////////////////////////////////////////////
        /// \brief Set the config file descriptor used to load the config
        ///
        /// This function set the config file descriptor to be used to load
        /// a config file.
        ///
        ////////////////////////////////////////////////////////////
		void setFileDescriptor(ConfigFileDescriptor::Ptr configFileDescriptor);

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
		void load(const std::string& configFile = "config.txt");

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
		void save(const std::string& configFile = "config.txt");
		
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
		bool hasConfig(const Key& key) const;

		////////////////////////////////////////////////////////////
		/// \brief Give the amount of config stored in the config object
		///
		/// This returns the amount of configs that were loaded from the
		/// config file.
		///
		/// \return The amount of configs loaded
		///
		////////////////////////////////////////////////////////////
		const unsigned int size() const;

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
		const std::string& get(const Key& key, const std::string& defaultValue = "");

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
		const int getInt(const Key& key, const int defaultValue = 0);

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
		const unsigned int getUint(const Key& key, const unsigned int defaultValue = 0);

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
		const float getFloat(const Key& key, const float defaultValue = 0.f);

		////////////////////////////////////////////////////////////
		/// \brief Return an array containing all the keys
		///
		/// Return an std::vector containing all the keys currently
		/// stored in the config.
		///
		/// \return std::vector containing all the keys
		///
		////////////////////////////////////////////////////////////
		const std::vector<Config::Key> getKeys() const;

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
		void set(const Key& key, const std::string& value);

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
		void set(const Key& key, const int value);

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
		void set(const Key& key, const unsigned int value);

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
		void set(const Key& key, const float value);

	private:
		typedef std::unordered_map<const Key, std::string> ConfigMap;
		ConfigMap m_configs;
		ConfigFileDescriptor::Ptr m_fileDescriptor;
	};

}
