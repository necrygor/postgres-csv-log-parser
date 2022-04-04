//
// Created by berkay on 3.04.2022.
//

#include "Parser.h"

Parser::Parser(const std::string &filename) {
    log_file.open(filename);
}

int Parser::add_to_storage(const std::string& line) {
//    std::vector<std::string> tokens = generate_gelf_from_line(line);
return 1;
}

std::pair<const int, std::vector<std::string>> Parser::get_gelf_line(int processid) const {
    if(processid != 0) {
        return *storage.find(processid);
    }
    return *storage.end();
}

int Parser::get_storage_size() const {
    return 0;
}

bool Parser::is_file_eof() const {
    return log_file.eof();
}

std::string Parser::readline() {
    std::string line{};
    if (log_file.is_open()) {
        std::getline(log_file, line);
    } else {
        std::cerr << "File is not open\n";
    }
    return line;
}

Parser::~Parser() {
    log_file.close();
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

std::string Parser::generate_gelf_line(std::vector<std::string>& line) const {
    std::string gelf_line{};
    gelf_line = "{\"version\" : \"1.1\", \"host\": \"hostname\",\"timestamp\": \"";
    for(auto const & token : line) {
        gelf_line += token;
    }
    return gelf_line;
}

/*
 * postgresql csv log format is as follows
  log_time timestamp(3) with time zone,
  user_name text,
  database_name text,
  process_id integer,
  connection_from text,
  session_id text,
  session_line_num bigint,
  command_tag text,
  session_start_time timestamp with time zone,
  virtual_transaction_id text,
  transaction_id bigint,
  error_severity text,
  sql_state_code text,
  message text,
  detail text,
  hint text,
  internal_query text,
  internal_query_pos integer,
  context text,
  query text,
  query_pos integer,
  location text,
  application_name text,
  backend_type text,
  leader_pid integer,
  query_id bigint,
 */
