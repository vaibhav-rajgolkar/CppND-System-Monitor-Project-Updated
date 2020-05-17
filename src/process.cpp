#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

namespace {
constexpr int kMemoryInMBConvFactor = 1000;
}

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  float cpu_utilisation{0.0};

  // check if all required cpu statistics are available for utilization
  // calculation
  if (cpu_util_stat_.size() == kValidDataSize_) {
    long total_time = cpu_util_stat_[kuTime_] + cpu_util_stat_[ksTime_];
    total_time =
        total_time + cpu_util_stat_[kCutTime_] + cpu_util_stat_[kCsTime_];

    float total_elapsed_time =
        LinuxParser::UpTime() -
        (cpu_util_stat_[kStartTime_] / sysconf(_SC_CLK_TCK));
    cpu_utilisation =
        100 * ((total_time / sysconf(_SC_CLK_TCK)) / total_elapsed_time);
  }

  return cpu_utilisation;
}

// TODO: Return the command that generated this process
string Process::Command() const { return command_; }

// TODO: Return this process's memory utilization
long int Process::Ram() const { return ram_ / kMemoryInMBConvFactor; }

// TODO: Return the user (name) that generated this process
string Process::User() const { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { return uptime_; }

void Process::Pid(int pid) { pid_ = pid; }

void Process::User(std::string user) { user_ = user; }

void Process::Command(std::string command) { command_ = command; }

void Process::Ram(long int ram) { ram_ = ram; }

void Process::UpTime(long int uptime) { uptime_ = uptime; }

void Process::CpuUtilizationStat(std::vector<long> const& cpu_util_stat) {
  cpu_util_stat_ = cpu_util_stat;
};

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->Ram() > a.Ram();
}