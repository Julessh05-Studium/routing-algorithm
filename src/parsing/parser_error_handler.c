//
// Created by gregorgottschewski on 20.02.25.
//

#include "parser_error_handler.h"

#include <stdio.h>

int line_number = 1;
int char_index = 1;

void print_error_syntax(char message[]) {
    fprintf(stderr, "SYNTAX ERROR IN LINE l:%i c:%i %s\n", line_number, char_index, message);
}

void print_error_general(char message[]) {
    fprintf(stderr, "ERROR: l:%i c:%i %s\n", line_number, char_index, message);
}

void reset_char_index() {
    char_index = 1;
}

void increment_char_index() {
    char_index++;
}