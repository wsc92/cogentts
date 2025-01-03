#include "data_handler.hpp"
#include "../defines.hpp"
#include <chrono>
#include <sstream>
#include <influxdb-cxx/InfluxDBFactory.h>

DataHandler::DataHandler(const std::string& db_host, const std::string& db_port, 
                       const std::string& db_name, const std::string& db_user, 
                       const std::string& db_password) {
    try {
        std::string url = "http://";
        if (!db_user.empty() && !db_password.empty()) {
            url += db_user + ":" + db_password + "@";
        }
        url += db_host + ":" + db_port + "?db=" + db_name;
        
        client = std::unique_ptr<influxdb::InfluxDB>(
            influxdb::InfluxDBFactory::Get(url));

        if (testConnection()) {
            CINFO("Connected to InfluxDB successfully!");
        } else {
            throw std::runtime_error("Failed to connect to InfluxDB");
        }
    } catch (const std::exception& e) {
        CERROR("Connection error: " + std::string(e.what()));
        throw;
    }
}

DataHandler::~DataHandler() = default;

bool DataHandler::testConnection() const {
    if (!client) return false;
    
    try {
        client->query("SHOW DATABASES LIMIT 1");
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

void DataHandler::executeQuery(const std::string& query) {
    if (!client) {
        CERROR("Database client not initialized");
        return;
    }

    try {
        client->query(query);
        CDEBUG("Query executed successfully!");
    } catch (const std::exception& e) {
        CERROR("Query execution error: " + std::string(e.what()));
    }
}

void DataHandler::insertTrade(const std::string& symbol, double price, 
                           long long timestamp, double volume,
                           const std::string& side) {
    if (!client) {
        CERROR("Database client not initialized");
        return;
    }

    try {
        // Construct the InfluxDB line protocol string manually
        std::stringstream ss;
        ss << "trades,symbol=" << symbol << ",side=" << side 
           << " price=" << price << ",volume=" << volume 
           << " " << timestamp;

        client->query("INSERT " + ss.str());
        CINFO("Trade inserted successfully");
    } catch (const std::exception& e) {
        CERROR("Trade insertion error: " + std::string(e.what()));
        throw;
    }
}

void DataHandler::retrieveData(const std::string& query) {
    if (!client) {
        CERROR("Database client not initialized");
        return;
    }

    try {
        client->query(query);
        CDEBUG("Data retrieved successfully");
    } catch (const std::exception& e) {
        CERROR("Data retrieval error: " + std::string(e.what()));
        throw;
    }
}
