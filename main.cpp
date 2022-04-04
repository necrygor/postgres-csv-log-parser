//
// Created by berkay on 1.04.2022.
//

#include "Parser.h"
#include "HelperUtils.h"

int main(int argc, char *argv[]) {

    Parser parser("/home/berkay/vagrant-vms/postgres-logs/postgresql-Sun.csv");

    std::cout << "timestamp: " << HelperUtils::get_timestamp_from_datetime("2020-04-01 00:00:00") << "\n";
    return 0;

    while (true) {
        while(parser.is_file_eof() == false) {

        }
        break;
    }
    /*
     * pseudo code
     * 1. create a storage object
     * 2. create a file object to read log file
     * 3. read the file line by line
     * 4. parse the line
     * 5. store the parsed data in the storage object
     * 6. remove the line from storage as soon as it is parsed
     * 7. repeat steps 3-6 until the file is empty
     * 8. await for input
     */
}