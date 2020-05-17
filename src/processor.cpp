#include "processor.h"

#include <iostream>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  float cpu_util{0.0};
  std::vector<std::string> current_cpu_stat = LinuxParser::CpuUtilization();

  if (current_cpu_stat.size() == kValidDataSize_) {
    long prev_idle = std::stol(previous_cpu_stat_[kIdle_]) +
                     std::stol(previous_cpu_stat_[kIOwait_]);
    long curr_idle = std::stol(current_cpu_stat[kIdle_]) +
                     std::stol(current_cpu_stat[kIOwait_]);

    long prev_non_idle = std::stol(previous_cpu_stat_[kUser_]) +
                         std::stol(previous_cpu_stat_[kNice_]) +
                         std::stol(previous_cpu_stat_[kSystem_]) +
                         std::stol(previous_cpu_stat_[kIRQ_]) +
                         std::stol(previous_cpu_stat_[kSoftIRQ_]) +
                         std::stol(previous_cpu_stat_[kSteal_]);
    long curr_non_idle = std::stol(current_cpu_stat[kUser_]) +
                         std::stol(current_cpu_stat[kNice_]) +
                         std::stol(current_cpu_stat[kSystem_]) +
                         std::stol(current_cpu_stat[kIRQ_]) +
                         std::stol(current_cpu_stat[kSoftIRQ_]) +
                         std::stol(current_cpu_stat[kSteal_]);

    long prev_total = prev_idle + prev_non_idle;
    long curr_total = curr_idle + curr_non_idle;

    long total_diff = curr_total - prev_total;
    long idle_diff = curr_idle - prev_idle;

    previous_cpu_stat_ = current_cpu_stat;
    cpu_util = static_cast<float>(total_diff - idle_diff) / total_diff;
  }

  return cpu_util;
}