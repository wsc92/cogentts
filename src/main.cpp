#include "defines.hpp"
#include "handlers/data_handler.hpp"
#include <chrono>

int main() {
    try {
        // Initialize logger
        Logger& logger = Logger::getInstance();
        logger.setLogFile("logs/application.log");
        logger.setLogLevel(Logger::LogLevel::DEBUG);
        CINFO("Logger Initialized.");

        // InfluxDB connection credentials
        std::string host = "localhost";
        std::string port = "8086";
        std::string db_name = "trade_data";
        std::string db_user = "cogent";
        std::string db_password = "Hellohi21!";

        CINFO("Attempting to connect to InfluxDB...");
        
        // First try without database to create it
        {
            // Try different URL format
            DataHandler setupHandler("localhost", "8086", "", "", "");
            CINFO("Testing basic connection...");
            setupHandler.executeQuery("SHOW DATABASES");
        }

        CINFO("Basic connection successful, creating database...");
        
        // Now try with full credentials
        DataHandler dataHandler(host, port, db_name, db_user, db_password);
        CINFO("Connected to database successfully");

        return 0;

    } catch (const std::exception& e) {
        CERROR("Error in main: " + std::string(e.what()));
        return 1;
    }
}
