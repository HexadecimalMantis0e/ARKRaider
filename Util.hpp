#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>
#include "Ark.hpp"

void usage();
void extractArk(const Ark &ark, const std::string &arkName);

#endif
