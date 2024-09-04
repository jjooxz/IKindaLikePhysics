#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <memory>

class Logger
{
public:
    static Logger &instance()
    {
        static Logger instance; // Singleton garantido pelo static local
        return instance;
    }

    void flush() {
        spdlog::default_logger()->flush();
    }

private:
    Logger()
    {
        auto sink1 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto sink2 = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.log", true);

        auto logger = std::make_shared<spdlog::logger>("logger", std::initializer_list<spdlog::sink_ptr>{sink1, sink2});
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::set_default_logger(logger);
        spdlog::set_pattern("[%l] [%s:%#] %v");

        SPDLOG_INFO("Logger inicializado com sucesso.");
    }

    // Deleta os métodos de cópia e atribuição para garantir que não haja múltiplas instâncias
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

#endif
