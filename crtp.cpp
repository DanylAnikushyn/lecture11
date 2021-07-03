#include <ctime>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cstring>

template <class T>
class Logger
{
public:
    template <typename... Args>
    void log(Args&&... args)
    {
        auto current = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        char *buffer = new char[26];
        ctime_r(&current_time, buffer);
        if (buffer[strlen(buffer)-1] == '\n') buffer[strlen(buffer)-1] = '\0';
        static_cast<T*>(this)->header(buffer);
        static_cast<T*>(this)->write(std::forward<Args>(args)...);
        static_cast<T*>(this)->footer();
        delete[] buffer;
    }
};

class ConsoleLogger : public Logger<ConsoleLogger> 
{
public:
    ConsoleLogger() : level(0) {}
    void header(const std::string& time) 
    {
        std::cout << level << ", " << time << ": [";
        ++level;
    }
    template <typename... Args>
    void write(Args... args)
    {
        ((std::cout << args << " "), ...);
    }
    void footer() 
    {
        std::cout << "]\n";
    }
private: 
    unsigned level;
};

class FileLogger : public Logger<FileLogger>
{
public:
    FileLogger()
    {
        level = 0;
        out.open("logs.txt", std::ofstream::out | std::ofstream::app);
    }
    void header(const std::string& time) 
    {
        out << level << ", " << time << ": [";
        ++level;
    }
    template <typename... Args>
    void write(Args... args)
    {
        ((out << args << " "), ...);
    }
    void footer() 
    {
        out << "]\n";
    }
private:
    unsigned level;
    std::ofstream out;
};

int main() 
{   
    auto console_logger = ConsoleLogger();
    console_logger.log("hello", "heello", 10, 30);
    auto file_logger = FileLogger();
    file_logger.log("file", "logger", 1);
    file_logger.log("file", "logger", 2);
    return 0;
}