#pragma once

#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <dirent.h>
#include <vector>
#include "ini.hpp"

void rebootToPayload(const char* Payload);

std::vector<std::string> getBins();

std::string getFavPayload();
std::string writeFavPayload(const char* payload);