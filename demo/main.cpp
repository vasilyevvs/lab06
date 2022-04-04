#include <hash_calculation.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  po::options_description desc("Options");
  desc.add_options()("help", "Show help message")
      ("threads,t", po::value<size_t>(),//кол во потоков
       "Maximum number of concurrently executed threads")
          ("rotation,r", po::value<size_t>(),
           "Rotation for logfiles")
              ("json_file,j", po::value<std::string>(),
               "Path to output json-array");//путь к файлу
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc),vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << '\n';
    return 0;
  }

  size_t threads = std::thread::hardware_concurrency();
  if (vm.count("threads")) {
    if (vm.at("threads").as<size_t>() > threads) {
      threads = std::thread::hardware_concurrency();
      std::cerr << "Maximum allowed number of concurrently is " +
                       std::to_string(threads)
                << '\n';
    } else {
      threads = vm.at("threads").as<size_t>();
    }
  }

  std::string json_path;
  if (vm.count("json_file")) {
    if (vm.at("json_file").as<std::string>().empty()) {
      throw std::runtime_error{"empty json-file path"};
    }
    json_path = vm.at("json_file").as<std::string>();
  } else {
    return 0;
  }

  size_t rotation;
  if (vm.count("rotation")) {
    rotation = vm.at("rotation").as<size_t>();
  } else {
    throw std::runtime_error{"empty rotation value"};
  }

  hash_calc(json_path, threads, rotation);
}
