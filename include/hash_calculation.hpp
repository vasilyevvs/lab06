// Copyright 2022 Vasilyev Danila

#ifndef INCLUDE_HASH_CALCULATION_HPP_
#define INCLUDE_HASH_CALCULATION_HPP_
#include <atomic>
#include <csignal>
#include <ctime>
#include <future>
#include <string>
#include "../third-party/PicoSHA2/picosha2.h"
#include <json_creator.hpp>
#include <logging.hpp>

void hash_calc(const std::string& path, size_t num_of_threads, size_t rotation);

#endif // INCLUDE_HASH_CALCULATION_HPP_
