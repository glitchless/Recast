/**
 * @file
 * @brief Config description
 * @author LionZXY
 * @project Recast
 * @date 08.06.17
 *
 * Save INSTANCE config and get if you need this.
 * 
 **/

#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include "io/configs/Config.hpp"


using namespace boost::property_tree::json_parser;
using namespace std;
using namespace boost::property_tree;
const int CONFIG_VERSION = 1;
const string DEFAULT_FOLDER("./config/");
const string DEFAULT_CONFIG("general.json");
const int NOTHING = -1;
static Config *INSTANCE = NULL;

Config *Config::instance() {
    if (INSTANCE == NULL) {
        INSTANCE = new Config(DEFAULT_CONFIG);
    }
    return INSTANCE;
}

Config::Config(const string &filename) {
    this->filename = DEFAULT_FOLDER + filename;
    try {
        read_json(this->filename, pt);
    } catch (const json_parser_error &e) {
        save();
    }
    if (pt.get("config.version", NOTHING) == NOTHING) {
        pt.put("config.version", CONFIG_VERSION);
    }
}

ptree &Config::tree() {
    return this->pt;
}

void Config::save() {
    boost::filesystem::path dir(DEFAULT_FOLDER);
    if (!boost::filesystem::exists(dir)) {
        if (boost::filesystem::create_directory(dir)) {
            BOOST_LOG_TRIVIAL(info) << "Folder " << DEFAULT_FOLDER << " create successful";
            write_json(filename, pt);
        } else {
            BOOST_LOG_TRIVIAL(info) << "Error while create dir: " << DEFAULT_FOLDER;
        }
    } else { write_json(filename, pt); }
}

void Config::load() {
    read_json(filename, pt);
}

Config::~Config() {
    save();
    INSTANCE = NULL;
}