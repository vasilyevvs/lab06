// Copyright 2022 Toschakov Pavel
#include <json_creator.hpp>

void json_creator::add_item(const json_data& val)  {
  std::lock_guard<std::mutex> lg(mut);
  json json_item;
  json_item["timestamp"] = val.timestamp;
  json_item["hash"] = val.hash;
  json_item["data"] = val.data;
  data.push_back(json_item);
}

void json_creator::save_json(const std::string& path) const {
  std::lock_guard<std::mutex> lg(mut);
  std::ofstream file(path);
  if (!file) {
    throw std::runtime_error{"unable to open json: " + path};
  }
  file << data;
  file.close();
  }

  bool json_creator::is_empty() const {
    return data.empty();
  }
