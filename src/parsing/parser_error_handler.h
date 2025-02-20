//
// Created by gregorgottschewski on 20.02.25.
//

#ifndef PARSER_ERROR_HANDLER_H
#define PARSER_ERROR_HANDLER_H

extern int line_number;

void print_error_syntax(char message[]);
void print_error_general(char message[]);
void reset_char_index();
void increment_char_index();

#endif //PARSER_ERROR_HANDLER_H
