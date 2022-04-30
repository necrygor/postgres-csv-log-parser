//
// Created by berkay on 4.04.2022.
//

#ifndef POSTGRES_CSV_PARSER_WORKER_H
#define POSTGRES_CSV_PARSER_WORKER_H

#include <string>
#include <vector>
#include <map>
#include <cerrno>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include "HelperUtils.h"
#include <algorithm>
#include <thread>

#define BUFSIZE 8192


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
     * Check if storage is populated
     * @param const std::vector<std::map<std::string, std::string>> &storage
     * @return bool
     */
    bool check_storage(const std::vector<std::map<std::string, std::string>> &storage) const;

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

    std::string request_url;
    int port;
    std::string hostname;
    int fail_status = -1;
};

class WorkerException : public std::exception {
public:
    explicit WorkerException(const std::string &message) : message(message) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif //POSTGRES_CSV_PARSER_WORKER_H
