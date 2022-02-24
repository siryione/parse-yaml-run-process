// input: structure
// var exe = structure.getExe()
// var args = structure.getArgs()
// var io_options = structure.prepare_io_options()
// system(exe, args, io_options)

#include "process.hpp"

#include <filesystem>

std::string Process::getExe(){
    return std::filesystem::path(executable_path) / name;
}
