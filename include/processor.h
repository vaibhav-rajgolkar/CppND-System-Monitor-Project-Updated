#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

class Processor {
 public:
  Processor() : previous_cpu_stat_(11, "0") {}
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::vector<std::string> previous_cpu_stat_{};

  // CPU
    enum CPUStates {
        kCpu = 0,
        kUser_,
        kNice_,
        kSystem_,
        kIdle_,
        kIOwait_,
        kIRQ_,
        kSoftIRQ_,
        kSteal_,
        kGuest_,
        kGuestNice_,
        kValidDataSize_
    };
};

#endif