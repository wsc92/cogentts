#pragma once

#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <string>
#include <memory>
#include <influxdb-cxx/InfluxDB.h>

class DataHandler {
public:
    DataHandler(const std::string& db_host = "localhost", 
               const std::string& db_port = "8086",
               const std::string& db_name = "mydb",
               const std::string& db_user = "",
               const std::string& db_password = "");
    
    ~DataHandler();

    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;

    void executeQuery(const std::string& query);
    void insertTrade(const std::string& symbol, double price, 
                    long long timestamp, double volume, 
                    const std::string& side = "buy");
    void retrieveData(const std::string& query);

private:
    std::unique_ptr<influxdb::InfluxDB> client;
    bool testConnection() const;
};

#endif  // DATA_HANDLER_HPP

