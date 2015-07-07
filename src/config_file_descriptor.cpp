#include <RSM/config_file_descriptor.hpp>
#include <RSM/logger.hpp>
#include <RSM/config.hpp>
#include <stdexcept>
#include <fstream>

namespace RSM {

	class DefaultFileDescriptor 
		: public ConfigFileDescriptor {

		void load(Config& config, const std::string& configFile) {
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
					config.set(line.substr(0, index), line.substr(index + 1));
				}
			}
		}

		void save(Config& config, const std::string& configFile) const {
			std::ofstream file;

			file.open(configFile, std::ios::out | std::ios::trunc);
			if(!file.is_open()) {
				RSM_LOG_ERROR("Could not open config file : " + configFile);
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

	ConfigFileDescriptor::~ConfigFileDescriptor() = default;
}
