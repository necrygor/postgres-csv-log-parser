//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"
#include "Worker.h"

int main(int argc, char *argv[]) {

    /*
     * Control inside Parser::parse() could be done against the return value of seekg() and tellg()
     * We control tellg() against eof() for every iteration and get the current position of the stream with seekg()
     * I'm gonna implement this by tomorrow I hope.
     */

    Parser parser("/home/berkay/vagrant-vms/postgres-logs/postgresql-Sun.csv");
    Worker worker{"test-artık-son", "10.87.127.247", "12201"};
    parser.parse();
    auto& storage = parser.get_storage();
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
}