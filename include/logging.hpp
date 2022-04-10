// Copyright 2022 Vasilyev Danila

#ifndef INCLUDE_LOGGING_HPP_
#define INCLUDE_LOGGING_HPP_
#include <iostream>
#include <boost/log/exceptions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

namespace logs = boost::log;
namespace keywords = boost::log::keywords;

void set_logs(size_t val);

#endif  // INCLUDE_LOGGING_HPP_
