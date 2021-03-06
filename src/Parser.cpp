//
// Created by berkay on 3.04.2022.
//

#include "Parser.h"

int Parser::file_position = 0;

Parser::Parser(const std::string &filename) {
    open_file(filename);
}

int Parser::add_to_storage(const std::map<std::string, std::string>& map) {
    int status = 0;
    try{
        storage.push_back(map);
    } catch (std::exception &e) {
        status = -1;
    }

    return status;
}

int Parser::get_storage_size() const {
    return storage.size();
}

bool Parser::is_file_eof() const {
    return log_file.eof();
}

std::string Parser::readline() {
    std::string line{};

    if(log_file.tellg() <= file_position) {
        log_file.seekg(file_position);
    }

    if (log_file.is_open()) {
        std::getline(log_file, line);
    } else {
        std::cerr << "File is not open\n";
    }

    if(log_file.tellg() != -1) {
        file_position = log_file.tellg();
    }

    return line;
}

void Parser::open_file(const std::string &filename) {
    log_file.open(filename);

    if(!log_file.is_open()) {
        throw ParserException("File could not be opened");
    }
}

void Parser::close_file() {
    log_file.close();

    if(log_file.is_open()) {
        throw ParserException("File could not be closed");
    }
}

Parser::~Parser() {
    close_file();
}

std::vector<std::string> Parser::generate_vector_from_line(std::string line) const {
    std::vector<std::string> tokens;

    size_t pos = 0;
    std::string token;
    char delimiter = ',';
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + 1);
    }
    return tokens;
}

std::map<std::string, std::string> Parser::generate_gelf_map(std::vector<std::string> line) const {
    std::map<std::string, std::string> gelf_map;
    int i = 0;
    for(auto const & token : line) {
        if(line[0] == token) {
            gelf_map.insert(std::make_pair(field_names[i], token));
        } else {
            gelf_map.insert(std::make_pair(field_names[i], token));
        }
        i++;
    }
    return gelf_map;
}

std::vector<std::map<std::string, std::string>>& Parser::get_storage() {
    return storage;
}

void Parser::parse() {
    while(is_file_eof() == false) {
            add_to_storage(
                    generate_gelf_map(
                            generate_vector_from_line(
                                    readline())));

    }
}