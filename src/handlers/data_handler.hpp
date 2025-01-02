#pragma once
#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <pqxx/pqxx>
#include <string>
#include <iostream>

class DataHandler {
public:
    DataHandler(const std::string& db_host, const std::string& db_port, const std::string& db_name, const std::string& db_user, const std::string& db_password);
    ~DataHandler();

    void executeQuery(const std::string& query);
    void insertTrade(const std::string& symbol, double price, long long timestamp, double volume);
    void retrieveData(const std::string& query);
    void checkTable();


private:
    std::shared_ptr<pqxx::connection> connection;
};

#endif // DATA_HANDLER_HPP

