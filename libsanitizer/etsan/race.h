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

// Defines Race class for storing race metadata

#ifndef ETSAN_RACE_H_
#define ETSAN_RACE_H_

#include <tuple>

// This class saves information of race reported by the tool
class Race {

public:
  unsigned int          tid;
  int                   lineNo;
  bool                  isWrite;
  std::string           objName;
  std::string           fileName;
  std::vector<char *>   trace;

  Race(unsigned int _tid,
       int _lineNo,
       bool _isWrite,
       char *_objName,
       char *_fileName): tid{_tid}, lineNo{_lineNo}, isWrite{_isWrite}, objName{_objName}, fileName{_fileName} {}


// bool operator==(Race &rhs) {
//   if(lineNo != rhs.lineNo)
//     return false;
//   if(accessType != rhs.accessType)
//     return false;
//   if(fileName != rhs.fileName)
//     return false;
//   return true;
// }

  // Prints the call stack of a thread when a race is found
  void printStack(std::ostream& ss) const {
    int depth = 1;
    for (char * func : trace) {
      std::string msg(depth, ' ');
      depth += 4;
      ss << msg << " '--->" << func << "(...)\n";
    }
  }

  // Constructs a nicely reading message about the race
  // and stores the result in "msg" string
  std::string createRaceMessage() const {
    std::stringstream ss;

    ss << "=============================================\n"  ;
    ss << "\033[1;32mEMBEDSANITIZER Race report\033[m\n"     ;
    ss << "\033[1;31m A race detected at: " << fileName << "\033[m\n";
    ss << "  At line number: "     << lineNo        << "\n"  ;
    ss << "  Thread (tid=" << tid << ") "                    ;
    ss <<    (isWrite ? "write" : "read") << " \"" << objName  << "\"     \n"  ;
    ss << "                                             \n"  ;
    ss << "\033[1;33m Call stack:   \033[m              \n"  ;
    printStack(ss);
    ss << "=============================================\n"  ;

    return ss.str();
  }
};

// Comparison functor for comparing between two race reports
struct race_compare {
  bool operator() (const Race& lhs, const Race& rhs) const {
    return std::make_tuple(lhs.fileName, lhs.lineNo, lhs.isWrite) < std::make_tuple(rhs.fileName, rhs.lineNo, rhs.isWrite);
  }
};


#endif // ETSAN_RACE_H_
