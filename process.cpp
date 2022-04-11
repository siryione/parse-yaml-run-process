#include "process.hpp"

#include <filesystem>
#include <iostream>
#include <functional>
#include <cstdio>


std::string Process::getExe() const{
    return std::filesystem::path(executable_path) / name;
}

std::vector<std::string> Process::getArgs() const{
    std::vector<std::string> launch_arguments;
    for(auto a: cmd_arguments){
        std::string k_argument{}, v_argument{};
        if(a.name != "*"){
            if(args_convention == ArgsConvention::unix_c | args_convention == ArgsConvention::linux_c){
                k_argument = "-" + a.name;
            }
            else if(args_convention == ArgsConvention::windows_c){
                k_argument = "|" + a.name;
            }
            launch_arguments.push_back(k_argument);
        }
        v_argument = a.option;
        launch_arguments.push_back(v_argument);
    }
    return launch_arguments;
}


void concatenateTempWithOutput(std::string temp_file, std::string outout_file){
    std::ifstream ifile(temp_file, std::ios::in);
    std::ofstream ofile(outout_file, std::ios::out | std::ios::app);

    if (!ofile.is_open()) {
        std::cout << "file not found";
    }
    else {
        ofile << ifile.rdbuf();
    }
    std::remove(temp_file.c_str());
}

int Process::run() const{
    int result{};
    if(stdout_config.mode == "append"){
        std::string temp_file = std::to_string(std::hash<std::string>{}(stdout_config.file));

        int result = boost::process::system(boost::process::exe=getExe(), boost::process::args=getArgs(), 
            boost::process::std_out > temp_file, boost::process::std_err > temp_file);

        concatenateTempWithOutput(temp_file, stdout_config.file);

    }
    else if(stdout_config.mode == "truncate"){
        int result = boost::process::system(boost::process::exe=getExe(), boost::process::args=getArgs(), 
            boost::process::std_out > stdout_config.file, boost::process::std_err > stdout_config.file);            
    }
    else{
        return 1;
    }
    
    return result;
}
