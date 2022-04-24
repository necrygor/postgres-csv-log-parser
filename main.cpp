//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"
#include "Worker.h"
#include "INIReader.h"

int main(int argc, char *argv[]) {

    INIReader reader("/etc/config.ini");

    auto filename = reader.Get("File", "filename", "");
    auto hostname = reader.Get("Host", "hostname", "");
    auto remote_address = reader.Get("LogServer", "address", "");
    auto remote_port = reader.Get("LogServer", "port", "");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'config.ini'\n";
        return 1;
    }

    Parser parser(filename);
    Worker worker{hostname, remote_address, remote_port};
    parser.parse();
    auto& storage = parser.get_storage();
    int counter = 0;
    parser.close_file();

    while (true) {
        if(storage.size() > 0) {
            std::string request = worker.generate_request(storage.front());
            worker.send_request(request);
            storage.erase(storage.begin());
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            parser.open_file(filename);
            parser.parse();
            parser.close_file();
        }
    }
    return 0;
}