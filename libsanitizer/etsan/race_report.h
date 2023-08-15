//===-- Runtime race detection module of EmbedSanitizer - for Embeded ARM--===//
//
//
// This file is distributed under the BSD 3-clause "New" or "Revised" License
// License. See LICENSE.md for details.
//
//===----------------------------------------------------------------------===//
//
// (c) 2017 - 2021  Hassan Salehe Matar, Koc University
//            Email: hmatar@ku.edu.tr
//===----------------------------------------------------------------------===//

// Code for formatting race warning messages

#ifndef __RACE_REPORT__H_
#define __RACE_REPORT__H_

#include <mutex>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include <set>
#include "race.h"
#include "file_dictionary.h"

// Namespace which contains utility functions for manipulating data
// race reporting metadata.
namespace etsan {
  
// Temporary location for Race reporting metadata:
static thread_local std::vector<char*> callStack;

// Keeps list of races
static std::set<Race, race_compare> races;
static std::mutex racesLock;

// Pushes a function name to a call stack of a thread
void pushFunction(char *funcName) {
  callStack.push_back(funcName);
}

void popFunction(char *funcName) {  
  if (!callStack.empty() && callStack.back() == funcName) {
    callStack.pop_back();
  }
  else {
    std::cout << "Something wrong with Function Stack: " << funcName << "\n";
  }
}

// Prints the call stack of a thread when a race is found
std::string printStack() {
  std::stringstream ss;

  int depth = 1;
  for (char *func : callStack) {
    std::string msg(depth, ' ');
    depth += 4;
    ss << msg << " '--->" << func << "(...)" << std::endl;
  }

  return ss.str();
}

void reportRaceOnRead(int lineNo, void *objName, void *fileName) {

  unsigned int tid = (unsigned int)pthread_self();
  Race race(tid, lineNo, /*isWrite*/ false, (char *)objName, (char *)fileName);
  race.trace = callStack;

  {
    std::lock_guard<std::mutex> lock{racesLock};
    if (races.find(race) == races.end()) {
      std::cerr << race.createRaceMessage();
      races.insert(race);
    }
  }
}

void reportRaceOnWrite(int lineNo, void *objName, void *fileName) {

  unsigned int tid = (unsigned int)pthread_self();
  Race race(tid, lineNo, /*isWrite*/ true, (char *)objName, (char *)fileName);
  race.trace = callStack;

  {
    std::lock_guard<std::mutex> lock{racesLock};
    if (races.find(race) == races.end()) {
      std::cerr << race.createRaceMessage();
      races.insert(race);
    }
  }
}

}  // etsan
#endif
