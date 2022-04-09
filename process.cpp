// input: structure
// var exe = structure.getExe()
// var args = structure.getArgs()
// var io_options = structure.prepare_io_options()
// system(exe, args, io_options)

#include "process.hpp"

#include <filesystem>
#include <iostream>
#include <functional>
#include <cstdio>

std::string Process::getExe(){
    return std::filesystem::path(executable_path) / name;
}

std::vector<std::string> Process::getArgs(){
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

int Process::run(){
    std::string hash_name = std::to_string(std::hash<std::string>{}(stdout_config.file));
    int result = boost::process::system(boost::process::exe=getExe(), boost::process::args=getArgs(), 
    boost::process::std_out > hash_name, boost::process::std_err > hash_name);
    if(std::filesystem::exists(stdout_config.file)){
        std::ifstream ifile(hash_name, std::ios::in);
        std::ofstream ofile(stdout_config.file, std::ios::out | std::ios::app);

        if (!ofile.is_open()) {
            std::cout << "file not found";
        }
        else {
            ofile << ifile.rdbuf();
        }
    }
    std::remove(hash_name.c_str());
    return result;
}
