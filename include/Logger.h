#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <vector>

class Logger
{
public:
    // Método estático para obter a instância do logger
    static std::shared_ptr<spdlog::logger> getInstance()
    {
        // Verifica se a instância já foi criada
        if (!instance)
        {
            // Criação dos "sinks"
            auto logger_text_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto logger_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/IKindaLikePhysics.txt", true);

            // Adiciona os "sinks" ao vetor
            sinks.push_back(logger_text_sink);
            sinks.push_back(logger_file_sink);

            // Cria o logger com múltiplos "sinks"
            instance = std::make_shared<spdlog::logger>("IKindaLikePhysics", sinks.begin(), sinks.end());

            // Configura o logger para ser assíncrono (opcional)
            spdlog::register_logger(instance);
            instance->set_level(spdlog::level::trace); // Ajuste o nível conforme necessário
            instance->flush_on(spdlog::level::trace);
        }
        return instance;
    }

private:
    // Construtor privado para evitar criação de instâncias
    Logger() {}

    // Ponteiro estático para a instância do logger
    static std::shared_ptr<spdlog::logger> instance;

    // Vetor estático de "sinks"
    static std::vector<spdlog::sink_ptr> sinks;
};

// Inicialização dos membros estáticos
std::shared_ptr<spdlog::logger> Logger::instance = nullptr;
std::vector<spdlog::sink_ptr> Logger::sinks;

#endif
