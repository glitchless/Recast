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
    Config(std::string filename);

    ~Config();

    Config(Config &other) = delete;

    boost::property_tree::ptree &tree();

    void save();

    void load();

    static std::shared_ptr<Config> instance();

private:

    std::string filename;
    boost::property_tree::ptree pt;
};


#endif //RECAST_CONFIG_H
