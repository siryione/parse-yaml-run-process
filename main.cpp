#include "process.hpp"

#include "yaml-cpp/yaml.h"

#include <iostream>
#include <string>
#include <vector>

int main(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    try{ 
        std::vector<Process> processes = config["processes"].as<std::vector<Process>>();
        for(Process p: processes){
            std::cout << p.getExe() << std::endl;
        }
    }
    catch(const YAML::BadConversion& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
