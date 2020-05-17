#include "system.h"
#include "linux_parser.h"

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
std::vector<Process>& System::Processes() 
{ 
    std::vector<int> pids = LinuxParser::Pids();
    for(const auto& pid : pids)
    {
        std::string user = LinuxParser::User(pid);
        long int ram = LinuxParser::Ram(pid);
        long int uptime = LinuxParser::UpTime(pid);
        std::string command = LinuxParser::Command(pid);
        std::vector<long> cpu_stat = LinuxParser::CpuUtilization(pid);

        auto proc_iterator = std::find_if(processes_.begin(), processes_.end(), [&pid](const auto& process)->bool{ return pid == process.Pid();});
        if(proc_iterator != processes_.end())
        {
            proc_iterator->User(user);
            proc_iterator->Ram(ram);
            proc_iterator->UpTime(uptime);
            proc_iterator->Command(command);
            proc_iterator->CpuUtilizationStat(cpu_stat);
        }
        else
            processes_.emplace_back(pid, user, ram, uptime, command, cpu_stat);
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_;/*LinuxParser::Kernel();*/ }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return os_;/*LinuxParser::OperatingSystem();*/ }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
float System::UpTime() { return LinuxParser::UpTime(); }