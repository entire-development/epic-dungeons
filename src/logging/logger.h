// logger.h
#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace logging {

class Logger {
public:
    Logger() {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true));
        m_logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
        spdlog::register_logger(m_logger);
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

    static Logger &getLogger() {
        static Logger logger;
        return logger;
    }

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

static void debug(const std::string &msg) {
    Logger::getLogger().debug(msg);
}

static void info(const std::string &msg) {
    Logger::getLogger().info(msg);
}

static void warn(const std::string &msg) {
    Logger::getLogger().warn(msg);
}

static void error(const std::string &msg) {
    Logger::getLogger().error(msg);
}

}   // namespace logging
