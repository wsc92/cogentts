#include "defines.hpp"
#include "handlers/data_handler.hpp"

int main() {
    Logger& logger = Logger::getInstance();

    // Set up logging
    logger.setLogFile("logs/application.log");
    logger.setLogLevel(Logger::LogLevel::DEBUG); // Enable all log levels
    CINFO("Logger Initialized.");

    // InfluxDB connection credentials
    std::string host = "localhost";
    std::string port = "8086";  // Default InfluxDB port
    std::string db_name = "trade_data";
    std::string db_user = "cogent";
    std::string db_password = "Hellohi21!";  // Replace with actual credentials

    // Create a DataHandler object for InfluxDB
    DataHandler dataHandler(host, port, db_name, db_user, db_password);

    // Example trade data
    std::string symbol = "SPY";
    double price = 7296.89;
    long long timestamp = 1575526691134;  // Timestamp in milliseconds
    double volume = 200;

    // Insert the trade data into InfluxDB
    dataHandler.insertTrade(symbol, price, timestamp, volume);

    // Example: Retrieve data
    dataHandler.retrieveData("SELECT * FROM trades");

    return 0;
}

