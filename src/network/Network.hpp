#include "logger.h"
#include "crow.h"
#include "crow/app.h"

#include "../utils/Config.hpp"


class reLogger : public crow::ILogHandler {

public:

    reLogger() {}
    void log(const std::string& message, crow::LogLevel level) {

        switch (level)
        {
            case crow::LogLevel::Debug:
                logger(0, message.c_str());
                break;
            case crow::LogLevel::Info:
                logger(1, message.c_str());
                break;
            case crow::LogLevel::Warning:
                logger(2, message.c_str());
                break;
            case crow::LogLevel::Error:
                logger(3, message.c_str());
                break;
            case crow::LogLevel::Critical:
                logger(4, message.c_str());
                break;
        }

    }

};


class Network {

    private:

        crow::SimpleApp _app;
        int _port;
        std::string _url;
        std::future<void> _crow_thread;
        reLogger* _logger;

    public:

        Network( Config* conf );
        ~Network();
        bool init();
        bool run();
        bool stop();

};
