#include "data_handler.hpp"
#include "../defines.hpp"
#include <influxdb.hpp>
#include <chrono>
#include <memory>  // for std::shared_ptr

DataHandler::DataHandler(const std::string& db_host, const std::string& db_port, const std::string& db_name, const std::string& db_user, const std::string& db_password) {
    try {
        // Set up the InfluxDB client connection
        influxdb::client client("http://" + db_host + ":" + db_port);
        client.set_db(db_name);
        client.set_user(db_user);
        client.set_password(db_password);

        if (client.ping()) {
            CINFO("Connected to InfluxDB successfully!");
        } else {
            CERROR("Failed to connect to InfluxDB!");
        }
        this->client = std::make_shared<influxdb::client>(client);
    } catch (const std::exception& e) {
        CERROR("Error: " + std::string(e.what()));
    }
}

DataHandler::~DataHandler() {
    // No need to manually close or delete the connection, std::shared_ptr handles cleanup
}

void DataHandler::executeQuery(const std::string& query) {
    try {
        auto result = client->query(query);  // Execute the query against InfluxDB
        if (result) {
            CDEBUG("Query executed successfully!");
        } else {
            CERROR("Failed to execute query.");
        }
    } catch (const std::exception& e) {
        CERROR("Query execution error: " + std::string(e.what()));
    }
}

void DataHandler::insertTrade(const std::string& symbol, double price, long long timestamp, double volume) {
    try {
        influxdb::point point("trades");
        point.add_tag("symbol", symbol);
        point.add_tag("side", "buy");  // You can dynamically change "buy" based on data
        point.add_field("price", price);
        point.add_field("volume", volume);
        point.timestamp(std::chrono::system_clock::from_time_t(timestamp));

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
        if (result) {
            for (auto& row : result->get_rows()) {
                for (auto& field : row) {
                    std::cout << field.second << " ";
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

