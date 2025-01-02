#include "defines.hpp"
#include "handlers/data_handler.hpp"

int main() {
    Logger& logger = Logger::getInstance();

    // Set up logging
    logger.setLogFile("logs/application.log");
    logger.setLogLevel(Logger::LogLevel::DEBUG); // Enable all log levels
    CINFO("Logger Initialized.");

    // Database credentials
    std::string host = "localhost";
    std::string port = "8812";  // QuestDB uses PostgreSQL protocol on port 8812
    std::string db_name = "qdb";
    std::string db_user = "admin";
    std::string db_password = "quest";

    // Create a data handler object
    DataHandler dataHandler(host, port, db_name, db_user, db_password);

    // Example data
    std::string symbol = "SPY";
    double price = 7296.89;
    long long timestamp = 1575526691134;
    double volume = 200;

    // Insert the trade data into the table
    dataHandler.insertTrade(symbol, price, timestamp, volume);

    // Example: Retrieve data
    dataHandler.retrieveData("SELECT * FROM trades");


    return 0;
}

