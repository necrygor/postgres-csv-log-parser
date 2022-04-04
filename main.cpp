//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"

int main(int argc, char *argv[]) {

    Parser parser("/home/berkay/vagrant-vms/postgres-logs/postgresql-Sun.csv");

    while (true) {
        parser.parse();
        break;
    }
    auto storage = parser.get_storage();
    return 0;
}