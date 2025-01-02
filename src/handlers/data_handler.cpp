#include "data_handler.hpp"
#include "../defines.hpp"
#include <chrono>
#include <memory>  // for std::shared_ptr
#include <influxdb-cxx/InfluxDBFactory.h> // Ensure this is included for InfluxDB client
#include <influxdb-cxx/Point.h>

DataHandler::DataHandler(const std::string& db_host, const std::string& db_port, 
                         const std::string& db_name, const std::string& db_user, 
                         const std::string& db_password) {
    try {
        // Use InfluxDBFactory to get the client instance
        std::string url = "http://" + db_host + ":" + db_port + "?db=" + db_name;
        client = influxdb::InfluxDBFactory::Get(url);  // Correct usage of the InfluxDB client class

        // Optionally, set authentication if needed
        client->setAuth(db_user, db_password);

        if (client->ping()) {
            CINFO("Connected to InfluxDB successfully!");
        } else {
            CERROR("Failed to connect to InfluxDB!");
        }
    } catch (const std::exception& e) {
        CERROR("Error: " + std::string(e.what()));
    }
}

DataHandler::~DataHandler() {
}

void DataHandler::executeQuery(const std::string& query) {
    try {
        // Execute the query and retrieve the result
        auto result = client->query(query);  // Execute the query against InfluxDB
        if (!result.empty()) {
            CDEBUG("Query executed successfully!");
            for (const auto& point : result) {
                std::cout << point.getName() << ": ";
                for (const auto& tag : point.getTags()) {
                    std::cout << tag.first << "=" << tag.second << " ";
                }
                for (const auto& field : point.getFields()) {
                    std::cout << field.first << "=" << field.second << " ";
                }
                std::cout << std::endl;
            }
        } else {
            CERROR("Failed to execute query or no results.");
        }
    } catch (const std::exception& e) {
        CERROR("Query execution error: " + std::string(e.what()));
    }
}

void DataHandler::insertTrade(const std::string& symbol, double price, 
                              long long timestamp, double volume) {
    try {
        influxdb::Point point("trades");  // Correct usage of the Point class
        point.addTag("symbol", symbol);
        point.addTag("side", "buy");  // You can dynamically change "buy" based on data
        point.addField("price", price);
        point.addField("volume", volume);
        point.setTimestamp(std::chrono::system_clock::from_time_t(timestamp));

        // Write the point to InfluxDB
        bool success = client->write(point);
        if (success) {
            CINFO("Trade Inserted into InfluxDB.");
        } else {
            CERROR("Error inserting trade data into InfluxDB.");
        }
    } catch (const std::exception& e) {
        CERROR("Error inserting trade data: " + std::string(e.what()));
    }
}

void DataHandler::retrieveData(const std::string& query) {
    try {
        auto result = client->query(query);  // Execute the query
        if (!result.empty()) {
            for (const auto& point : result) {
                std::cout << point.getName() << ": ";
                for (const auto& tag : point.getTags()) {
                    std::cout << tag.first << "=" << tag.second << " ";
                }
                for (const auto& field : point.getFields()) {
                    std::cout << field.first << "=" << field.second << " ";
                }
                std::cout << std::endl;
            }
        } else {
            CERROR("Retrieve data error: No result returned.");
        }
    } catch (const std::exception& e) {
        CERROR("Retrieve data error: " + std::string(e.what()));
    }
}

