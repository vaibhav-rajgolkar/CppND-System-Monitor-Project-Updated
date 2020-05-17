#include <unistd.h>
#include <vector>
#include <experimental/filesystem>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
namespace filesystem = std::experimental::filesystem;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line{};
  string key{};
  string value{};
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os{};
  string version{};
  string kernel{};
  string line{};
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
std::vector<int> LinuxParser::Pids() {
  std::vector<int> pids{};
  filesystem::path proc_dir_path{kProcDirectory};
  for(const auto& element : filesystem::directory_iterator(proc_dir_path))
  {
    if(filesystem::is_directory(element.symlink_status()))
    {
      std::string filename{element.path().filename().string()};
      if (std::all_of(filename.begin(), filename.end(), isdigit)) 
      {
        pids.emplace_back(std::stoi(filename.c_str()));
      }
    }
  }
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  float total_memory_used{0.0};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open())
  {
    float mem_total{0.0};
    float mem_free{0.0};
    std::string mem_total_str{};
    std::string mem_free_str{};
    std::string line{};

    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> mem_total_str >> mem_total;

    std::getline(filestream, line);
    linestream.str(line);
    linestream >> mem_free_str >> mem_free;

    total_memory_used = (mem_total - mem_free) / mem_total;
  }
  return total_memory_used;
}

// TODO: Read and return the system uptime
float LinuxParser::UpTime() 
{ 
  float uptime{0.0};
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if(filestream.is_open())
  {
    std::string line{};
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
  std::vector<string> cpu_data{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open())
  {
    string line{};
    string value{};
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value)
    {
      cpu_data.emplace_back(value);
    }
  }
  return cpu_data;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  return ProcessFileForValue<std::string, int>(kProcDirectory+kStatFilename, "processes");
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
  return ProcessFileForValue<std::string, int>(kProcDirectory+kStatFilename, "procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  std::string command{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if(filestream.is_open())
  {
    getline(filestream, command);
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::Ram(int pid) 
{
  return ProcessFileForValue<std::string, long int>(kProcDirectory+std::to_string(pid)+kStatusFilename, "VmSize:");
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) 
{ 
  return ProcessFileForValue<std::string, std::string>(kProcDirectory+std::to_string(pid)+kStatusFilename, "Uid:");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{
  std::string user{}; 
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open())
  {
    std::string line{};
    while(getline(filestream, line))
    {
      std::string token{};
      std::string userid{};
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> token >> userid;
      if(userid == Uid(pid))
      {
        return user;
      }
    }
  }
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{ 
  long uptime{0};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    std::string line{};
    std::string value{};
    int index{1};
    
    getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value)
    {
      if(index == 22)
      {
        uptime = std::stol(value) / sysconf(_SC_CLK_TCK);
        break;
      }
      index++;
    }
  }
  return uptime; 
}

std::vector<long> LinuxParser::CpuUtilization(int pid)
{
  std::vector<long> cpu_stat{};
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open())
  {
    std::string line{};
    std::string value{};
    int index{1};

    getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> value)
    {
      if(index == 14 || index == 15 || index == 16 || index == 17 || index == 22 )
      {
        cpu_stat.emplace_back(std::stol(value));
        if(index == 22)
          break;
      }
      index++;
    }
  }
  return cpu_stat;
}