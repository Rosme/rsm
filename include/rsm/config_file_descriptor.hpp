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
#include <memory>
#include <stdexcept>
#include <fstream>

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
