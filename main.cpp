//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"
#include "Worker.h"

int main(int argc, char *argv[]) {

    Parser parser("/home/berkay/vagrant-vms/postgres-logs/postgresql-Sun.csv");
    Worker worker{"test-son", "10.87.127.247", "12201"};
    parser.parse();
    auto storage = parser.get_storage();
    int counter = 0;

    while (true) {

        if(storage.size() > 0) {
            std::string request = worker.generate_request(storage.front());
            worker.send_request(request);
            storage.erase(storage.begin());
        } else {
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Waiting for new data... " << counter << "th time.\n";
            parser.parse();
        }
    }

    return 0;
    for (auto &s: storage) {
        std::string request = worker.generate_request(s);
        std::cout << request << "\n";
        worker.send_request(request);
        std::cout << "----------------------------------------\n";
    }
}