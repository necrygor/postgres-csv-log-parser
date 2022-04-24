//
// Created by berkay on 4.04.2022.
//

#include "Worker.h"

Worker::Worker(const std::string &host, const std::string &remote, const std::string &port) : hostname(host), request_url(remote), port{std::stoi(port)} {

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
        std::string second{item.second};
        second.erase(remove( second.begin(), second.end(), '\"' ),second.end());
        // TODO: convert datetime to unix timestamp, item.first is timestamp

        request += "\"";
        request += item.first;
        request += "\": \"";
        request += second;
/*        if(item.first == "timestamp") {
            request += HelperUtils::get_timestamp_from_datetime(second);
        } else {
            request += second;
        }*/
        request += "\", ";
    }
    request += "}";

    return request;
}

void Worker::send_request(const std::string &request) {
    /*
     * Motherfucking C to the help
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[8192];
    int result = 0;
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        exit(1);
    }
    //setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &result, sizeof(result));

    signal(SIGPIPE, SIG_IGN);

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(request_url.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, request_url.c_str(), &server.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        exit(1);
    }

    connect(sockfd, (struct sockaddr *) &server, sizeof(server));

    result = send(sockfd, request.c_str(), request.length(), 0);

    if (result < 0) {
        std::cerr << "Error sending request" << std::endl;
        std::cerr << std::strerror(errno) << "\n";
        exit(186);
    }
    close(sockfd);
}

