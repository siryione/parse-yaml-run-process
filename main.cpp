#include "process.hpp"

#include "yaml-cpp/yaml.h"

#include <boost/process.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <thread>


int main(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    std::vector<std::thread> threads{};
    try{ 
        std::vector<Process> processes = config["processes"].as<std::vector<Process>>();
        for(int i = 0; i < processes.size(); i++){
            threads.emplace_back(&Process::run, &(processes[i]));
        }
        for(auto &t: threads){
            t.join();
        }
    }
    catch(const YAML::BadConversion& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
