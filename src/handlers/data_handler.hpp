#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <influxdb-cxx/InfluxDB.h>/ Ensure the full client is included
#include <influxdb-cxx/Point.h>/ Ensure Point is included
#include <memory>
#include <string>

class DataHandler {
public:
    DataHandler(const std::string& db_host, const std::string& db_port,
                const std::string& db_name, const std::string& db_user,
                const std::string& db_password);
    ~DataHandler();

    void executeQuery(const std::string& query);
    void insertTrade(const std::string& symbol, double price, long long timestamp, double volume);
    void retrieveData(const std::string& query);

private:
    std::shared_ptr<influxdb::client> client;
};

#endif // DATA_HANDLER_HPP

