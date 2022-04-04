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
#include <array>
#include "HelperUtils.h"

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
     * Entry point for parsing the csv file
     * Populates the storage map with the data from the csv file
     */
    void parse();

    /*
    * get_storage()
    * This function is used to get the storage
     * @return: std::vector<std::map<std::string, std::string>> storage
     */
    std::vector<std::map<std::string, std::string>> get_storage() const;


    /*
     * Destructor
     */
    ~Parser();

private:
    /*
     * add_to_storage()
     * This function is used to add the data to the storage
     * @param line: line to be added
     * @return: -1 if failed, 0 if success
     */
    int add_to_storage(const std::map<std::string, std::string>&);

    /*
     * get_storage_size()
     * This function is used to get the size of the storage
     * @return: size of the storage
     */
    int get_storage_size() const;

    /*
     * generate_vector_from_line(
     * This function is used to generate gelf from the line
     * @param line: line to be converted
     * @return: exploded string by commas into vector
     */
    std::vector<std::string> generate_vector_from_line(std::string line) const;

    bool is_file_eof() const;
    /*
     * generate_gelf_line()
     * This function is used to generate gelf line from the storage
     * @param line_vector: vector of strings to be converted
     * @return: key-value map for gelf formatting
     */
    std::map<std::string, std::string> generate_gelf_map(std::vector<std::string>) const;

    /*
     * readline()
     * This function is used to read the line from the file
     * @return: std::string line read from the file
     */
    std::string readline();

    std::vector<std::map<std::string, std::string>> storage;
    std::ifstream log_file{};

    const std::array<std::string, 26> field_names = {
            "timestamp",
            "user_name",
            "database_name",
            "process_id",
            "connection_from",
            "session_id",
            "session_line_num",
            "command_tag",
            "session_start_time",
            "virtual_transaction_id",
            "transaction_id",
            "error_severity",
            "sql_state_code",
            "message",
            "detail",
            "hint",
            "internal_query",
            "internal_query_pos",
            "context",
            "query",
            "query_pos",
            "location",
            "application_name",
            "backend_type",
            "leader_pid",
            "query_id",
    };
};


#endif //POSTGRES_CSV_PARSER_PARSER_H
