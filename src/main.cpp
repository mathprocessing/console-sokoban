#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <deque>
#include <string>
#include <cassert>
#include "board.hpp"
#include "utils.hpp"
#include "gameloop.hpp"
#include "verifier.hpp"
#include "load_levels.hpp"
#define FILE_NOT_FOUND_ERROR_CODE 1

int main(int argc, char* argv[]) {
  std::string fileName;
  unsigned levelId = 0;
  unsigned arguments = argc - 1;
  if (arguments == 0) {
    std::cout << "no arguments provided."  << std::endl;
    return 0;
  } else if (arguments == 1) {
    fileName = argv[1];
  } else {
    fileName = argv[1];
    levelId = std::atoi(argv[2]);
  }

  std::cout << "fileName = " << fileName << std::endl;
  std::cout << "levelId = " << levelId << std::endl;

  std::ifstream levels_file(fileName);
  if(not levels_file.is_open()) {
    std::cout << "File \"" << fileName << "\" not found. Program exited.";
    if (fileName != "levels.txt") {
      std::cout << " Probably you can try file \"levels.txt\".";
    }
    std::cout << std::endl;
    return FILE_NOT_FOUND_ERROR_CODE;
  }
  // Now `levels_file.is_open() == true`
  auto levels = loadLevels(&levels_file);
  levels_file.close();
  
  if(levelId < levels.size()) {
    gameLoop(levels[levelId]);
  } else {
    std::cout << "levelId too big, levels.size() = " << levels.size() << ". Program exited." << std::endl;
  }
  return 0;
}
