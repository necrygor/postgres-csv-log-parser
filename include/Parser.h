//
// Created by berkay on 3.04.2022.
//

#ifndef POSTGRES_CSV_PARSER_PARSER_H
#define POSTGRES_CSV_PARSER_PARSER_H
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <iostream>

/*
 * Parser class
 * This class is used to parse the csv file and store the data in a map
 * Parser also provides facility to convert lines to json and handle http requests to send json to remote server
 */

class Parser {
public:
    /*
     * Constructor
     * @param fileName: csv file name
     */
    Parser(const std::string&);

    /*
     * Destructor
     */
    ~Parser();

    /*
     * add_to_storage()
     * This function is used to add the data to the storage
     * @param line: line to be added
     * @return: processid from log if added successfully, zero otherwise
     */
    int add_to_storage(const std::string& line);

    /*
     * get_gelf_line()
     * This function is used to get the formatted gelf line from the storage
     * if no processid is provided, it will return last the formatted gelf line
     * @param processid: processid of the log
     * @return: gelf formatted string
     */
    std::pair<const int, std::vector<std::string>> get_gelf_line(int processid = 0) const;

    /*
     * get_storage_size()
     * This function is used to get the size of the storage
     * @return: size of the storage
     */
    int get_storage_size() const;

    /*
     * generate_gelf_from_line(
     * This function is used to generate gelf from the line
     * @param line: line to be converted
     * @return: gelf formatted string
     */
    std::vector<std::string> generate_vector_from_line(std::string line) const;

    bool is_file_eof() const;
    /*
     * generate_gelf_line()
     * This function is used to generate gelf line from the storage
     * @param line_vector: vector of strings to be converted
     * @return: gelf formatted string
     */
    std::string generate_gelf_line(std::vector<std::string>&) const;

    std::string readline();

private:
    std::map<int, std::vector<std::string>> storage;
    std::ifstream log_file{};
};


#endif //POSTGRES_CSV_PARSER_PARSER_H
