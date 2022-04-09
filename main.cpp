#include "process.hpp"

#include "yaml-cpp/yaml.h"

#include <boost/process.hpp>

#include <iostream>
#include <string>
#include <vector>


int main(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    try{ 
        std::vector<Process> processes = config["processes"].as<std::vector<Process>>();

        for(Process p: processes){
            // std::cout << p.getExe() << std::endl;
            // p.run();
        }
        processes[0].run();
    }
    catch(const YAML::BadConversion& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}



// #include <boost/process.hpp>

// #include <string>
// #include <iostream>

// // process command: ffmpeg -i in.webm out.opus
// const std::string kInputFilePath = "/home/ivan_main/Downloads/sato.webm";

// using namespace boost::process;

// int main()
// {
//     int result = system(exe="/usr/bin/ffmpeg", args={"-i", kInputFilePath, "out.opus"});
//     return 0;
// }