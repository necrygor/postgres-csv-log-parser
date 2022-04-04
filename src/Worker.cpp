//
// Created by berkay on 4.04.2022.
//

#include "Worker.h"

Worker::Worker(const std::string &host, const std::string &remote, const std::string &port) : hostname(host), request_url(remote + ":" + port) {

}

void Worker::run() {

}

bool Worker::check_storage(const std::vector<std::map<std::string, std::string>> &storage) const {
    return !storage.empty();
}

void Worker::read_data(const std::vector<std::map<std::string, std::string>> &storage) const {

}

std::string Worker::generate_request(std::map<std::string, std::string> &data) const {
    std::string request{R"({"version": "1.1", "host": ")"};
    request += hostname;
    request += "\", ";
    for (auto &item : data) {
        std::string key = item.first;
        std::string value = item.second;
        request += key + "\": \"" + value + "\"";
    }

    return request;
}

void Worker::send_request(const std::string &) {

}
