#include <regex>
#include <cstdio>
#include <fstream>
#include <cinttypes>
#include "rawbuf.hpp"
#include "argf.hpp"

static int cmd_help()
{
    std::printf("--help:\n");
    std::printf("--create-bin\n");
    std::printf("--create-hex\n");
    return 0;
}

static int cmd_create_hex(const argf::parser &cmd)
{
    auto szInFileName = [&cmd]() -> std::string
    {
        if(!cmd(1)){
            throw std::invalid_argument("no file provided");
        }
        return cmd[1];
    }();

    auto szOutFileName = [&cmd]() -> std::string
    {
        if(cmd["create-hex"]){
            return "out.inc";
        }else{
            if(cmd("create-hex").str().empty()){
                return "out.inc";
            }else{
                return cmd("create-hex").str();
            }
        }
    }();

    Rawbuf::buildHexFile(szInFileName.c_str(), szOutFileName.c_str(), 8);
    return 0;
}

int main(int argc, char *argv[])
{
    try{
        argf::parser cmd(argc, argv);
        if(cmd.has_option("help")){
            return cmd_help();
        }

        if(cmd.has_option("create-hex")){
            return cmd_create_hex(cmd);
        }

    }catch(std::exception &e){
        std::printf("%s\n", e.what());
        return -1;
    }
    return 0;
}
