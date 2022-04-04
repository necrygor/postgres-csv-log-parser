//
// Created by berkay on 4.04.2022.
//

#ifndef POSTGRES_CSV_PARSER_WORKER_H
#define POSTGRES_CSV_PARSER_WORKER_H

#include <string>
#include <vector>
#include <map>


class Worker {
/*
 * Check if storage is populated
 * Read data from shared storage
 * Generate HTTP request
 * send to graylog server
 */

public:
    explicit Worker(const std::string &host, const std::string& remote, const std::string &port);

    /*
     * Entry point for the worker
     */
    void run();

private:
    /*
     * Check if storage is populated
     * @param const std::vector<std::map<std::string, std::string>> &storage
     * @return bool
     */
    bool check_storage(const std::vector<std::map<std::string, std::string>> &storage) const;

    /*
     * Read data from shared storage
     * @param const std::vector<std::map<std::string, std::string>> &storage
     */
    void read_data(const std::vector<std::map<std::string, std::string>> &storage) const;

    /*
     * Generate HTTP request
     * @param const std::map<std::string, std::string> &data
     * @return std::string request string
     */
    std::string generate_request(std::map<std::string, std::string> &data) const;

    /*
     * send to graylog server
     * @param const std::string &request
     */
    void send_request(const std::string&);


    static int request_generated;
    static int request_sent;

    std::string request_url;
    std::string hostname;
};


#endif //POSTGRES_CSV_PARSER_WORKER_H
