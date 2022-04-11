#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "yaml-cpp/yaml.h"

#include <boost/process.hpp>

#include <string>
#include <vector>
#include <map>


struct CmdArgument{
    std::string name;
    std::string option;
};

struct StdoutConfig{
    std::string file;
    std::string mode;
};

enum struct ArgsConvention{
    windows_c, linux_c, unix_c
};

const std::map<std::string, ArgsConvention> kArgsConvention{
    {"windows", ArgsConvention::windows_c}, {"linux", ArgsConvention::linux_c}, {"unix", ArgsConvention::unix_c}
};

struct Process{
    std::string name;
    std::string executable_path;
    StdoutConfig stdout_config;
    ArgsConvention args_convention;
    std::vector<CmdArgument> cmd_arguments;

    int run() const;
    std::string getExe() const;
    std::vector<std::string> getArgs() const;
};

template<>
struct YAML::convert<CmdArgument>{
    static YAML::Node encode(const CmdArgument &cmda){
        YAML::Node node;
        node[cmda.name] = cmda.option;
        return node;
    }

    static bool decode(const YAML::Node &node, CmdArgument &cmda){
        for (const auto& kv : node) {
            cmda.name =  kv.first.as<std::string>();
            cmda.option = kv.second.as<std::string>();
        }

        return true;
    }
};

template<>
struct YAML::convert<StdoutConfig>{
    static YAML::Node encode(const StdoutConfig &stdc){
        YAML::Node node;
        node["file"] = stdc.file;
        node["mode"] = stdc.mode;
        return node;
    }

    static bool decode(const YAML::Node &node, StdoutConfig &stdc){
        if(node.size() != 2){
            return false;
        }

        stdc.file = node["file"].as<std::string>();
        stdc.mode = node["mode"].as<std::string>();
        return true;
    }
};

template<>
struct YAML::convert<ArgsConvention>{
    static YAML::Node encode(ArgsConvention ac){
        //encode might be implemented sooner
        return YAML::Node();
    }

    static bool decode(const YAML::Node &node, ArgsConvention &ac){
        std::string convention = node.as<std::string>();
        
        auto search = kArgsConvention.find(convention);
        if(kArgsConvention.end() != search){
            ac = search->second;
        }
        else{
            // elaborate
            return false;
        }
        return true;
    }

};



template<>
struct YAML::convert<Process>{
    static YAML::Node encode(const Process &pr){
        YAML::Node node;
        node["name"] = pr.name;
        node["executable-path"] = pr.executable_path;
        node["stdout-config"] = pr.stdout_config;
        node["args-convention"] = pr.args_convention;
        node["cmd-arguments"] = pr.cmd_arguments;
        return node;
    }

    static bool decode(const YAML::Node &node, Process &pr){
        if(node.size() != 5){
            return false;
        }

        pr.name = node["name"].as<std::string>();
        pr.executable_path = node["executable-path"].as<std::string>();
        pr.stdout_config = node["stdout-config"].as<StdoutConfig>();
        pr.args_convention = node["args-convention"].as<ArgsConvention>();
        pr.cmd_arguments = node["cmd-arguments"].as<std::vector<CmdArgument>>();

        return true;
    }
};

#endif
