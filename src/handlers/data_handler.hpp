#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <string>
#include <memory>  // for std::shared_ptr
#include <influxdb-cxx/InfluxDB.h>

class DataHandler {
public:
    // Constructor to initialize the DataHandler with InfluxDB connection details
    DataHandler(const std::string& db_host, const std::string& db_port, 
                const std::string& db_name, const std::string& db_user, 
                const std::string& db_password);
    
    // Destructor to clean up resources
    ~DataHandler();

    // Method to execute a query on the InfluxDB
    void executeQuery(const std::string& query);

    // Method to insert a trade entry into the InfluxDB
    void insertTrade(const std::string& symbol, double price, 
                     long long timestamp, double volume);

    // Method to retrieve data based on a query
    void retrieveData(const std::string& query);

private:
    // A shared pointer to the InfluxDB client
    std::shared_ptr<influxdb::InfluxDB> client;
};

#endif  // DATA_HANDLER_HPP

