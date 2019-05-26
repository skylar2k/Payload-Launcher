#pragma once

#include <switch.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <dirent.h>
#include <vector>

void rebootToPayload(const char* Payload);

std::vector<std::string> getBins();