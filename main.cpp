//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"
#include "Worker.h"

int main(int argc, char *argv[]) {

    Parser parser("/home/berkay/vagrant-vms/postgres-logs/postgresql-Sun.csv");

    while (true) {
        parser.parse();
        break;
    }

    Worker worker{"example.org", "127.0.0.1", "8000"};
    auto storage = parser.get_storage();
    for (auto &s: storage) {
        std::string request = worker.generate_request(s);
        std::cout << request << "\n";
        worker.send_request(request);
        std::cout << "----------------------------------------\n";
    }
    return 0;
}