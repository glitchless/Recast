/**
 * @file
 * @brief Config file
 * @author LionZXY
 * @project Recast
 * @date 08.06.17
 *
 * Config file.
 * 
 **/
#ifndef RECAST_CONFIG_H
#define RECAST_CONFIG_H

#include <cstdio>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using std::shared_ptr;

/**
 * @brief Config class
 *
 * Using Boost ptree struct.
 * Config file hashing and buffering in memmory. (You can't get Config from constructor)
 * Please calling Config::instance for get Config.
 *
 **/
class Config {
public:
    ~Config();

    Config(Config &other) = delete;

    ptree &tree();

    void save();

    void load();

    static shared_ptr<Config> instance();

private:
    Config(std::string filename);

    std::string filename;
    ptree pt;
};


#endif //RECAST_CONFIG_H
