//
// Created by rudi on 08/03/23.
//

#ifndef REDIS_CLONE_UTILS_H
#define REDIS_CLONE_UTILS_H

#include <iostream>
#include <string>

namespace Util {

void die_error(std::string errorMessage) {
    std::cout << "Error on : " << errorMessage << std::endl;
    exit(1);
}

} // namespace Util

#endif //REDIS_CLONE_UTILS_H
