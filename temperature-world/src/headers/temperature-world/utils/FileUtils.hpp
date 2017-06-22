//
// Created by Oleg Morozenkov on 02.06.17.
//

#ifndef RECAST_FILEUTILS_H
#define RECAST_FILEUTILS_H

#include <string>
#include <fstream>
#include <sstream>

/**
 * Collection of functions which work with files.
 */
namespace FileUtils {

    /**
     * Reads all file contents to a string.
     *
     * @param fileName Path of file
     * @return File contents
     */
    inline std::string readFile(const std::string& fileName) {
        std::ifstream file(fileName);
        std::ostringstream output;
        output << file.rdbuf();
        return output.str();
    }

}

#endif //RECAST_FILEUTILS_H
