// logger.h
#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace logging {

class Logger {
public:
    Logger() {
        m_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");
        m_logger->set_level(spdlog::level::debug);
    }

    void debug(const std::string &msg) {
        m_logger->debug(msg);
    }
    void info(const std::string &msg) {
        m_logger->info(msg);
    }
    void warn(const std::string &msg) {
        m_logger->warn(msg);
    }
    void error(const std::string &msg) {
        m_logger->error(msg);
    }

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

Logger &getLogger() {
    static Logger logger;
    return logger;
}

void debug(const std::string &msg) {
    getLogger().debug(msg);
}
void info(const std::string &msg) {
    getLogger().info(msg);
}
void warn(const std::string &msg) {
    getLogger().warn(msg);
}
void error(const std::string &msg) {
    getLogger().error(msg);
}

}   // namespace logging
