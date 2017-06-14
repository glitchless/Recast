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

#include <boost/property_tree/ptree.hpp>

/**
 * @brief Config class
 *
 * Using Boost ptree struct.
 * Config file hashing and buffering in memory. (You can't get an instance of Config from constructor)
 * Please call Config::instance to get an instance of Config.
 *
 **/
class Config {
public:
    Config(const std::string &filename);

    ~Config();

    Config(const Config &other) = delete;

    boost::property_tree::ptree &tree();

    void save();

    void load();

    static Config *instance();

private:

    std::string filename;
    boost::property_tree::ptree pt;
};


#endif //RECAST_CONFIG_H
