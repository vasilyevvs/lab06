// Copyright 2022 Vasilyev Danila
#include <hash_calculation.hpp>

std::atomic<bool> in_process = true;

void stop(const int S){
  in_process = S != SIGINT;
}

void get_hash(json_creator& hashes_json){
  while (in_process){
    std::string rand_str = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(rand_str);
    std::time_t timestamp(std::time(nullptr));

    if (hash.substr(hash.size()-4) == "0000" &&
    hash.substr(hash.size()-5) != "00000"){
      BOOST_LOG_TRIVIAL(info) << "Got required hash type is found: " << hash
                              << " from string: " << rand_str;
      hashes_json.add_item({timestamp, hash, rand_str});
    }
    BOOST_LOG_TRIVIAL(trace) << "Got hash: " << hash
                             << " from string: " << rand_str;
  }
}

void hash_calc(const std::string& path, size_t num_of_threads, size_t rotation){
  std::srand(time(nullptr));
  set_logs(rotation);
  logs::add_common_attributes();

  std::vector<std::thread> threads;
  json_creator hashes_json;

  threads.reserve(num_of_threads);
  std::signal(SIGINT, stop);

  for (size_t i = 0; i < num_of_threads; ++i){
    threads.emplace_back(get_hash, std::ref(hashes_json));
  }
  for (auto& thread : threads){
    thread.join();
  }
  if (!hashes_json.is_empty()){
    hashes_json.save_json(path);
  }
}
