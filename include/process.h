#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

class Process {
 public:
  Process(int pid, std::string user, long int ram, long int uptime, std::string command, std::vector<long> cpu_stat)
  :pid_(pid),
   user_(user),
   ram_(ram),
   uptime_(uptime),
   command_(command),
   cpu_util_stat_(cpu_stat)
   {}

  int Pid() const;                               // TODO: See src/process.cpp
  std::string User() const;                      // TODO: See src/process.cpp
  std::string Command() const ;                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  long int Ram() const;                       // TODO: See src/process.cpp
  long int UpTime() const;                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  void Pid(int pid);
  void User(std::string user);
  void Command(std::string command);
  void Ram(long int ram);
  void UpTime(long int uptime);
  void CpuUtilizationStat(std::vector<long> const& cpu_util_stat);

  // TODO: Declare any necessary private members
 private:
  int pid_{0};
  std::string user_{};
  long int ram_{0};
  long int uptime_{0};
  std::string command_{};
  std::vector<long> cpu_util_stat_{};

  enum ProcessCpuStats{
  kuTime_ = 0,
  ksTime_,
  kCutTime_,
  kCsTime_,
  kStartTime_,
  kValidDataSize_
};
};

#endif