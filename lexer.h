#pragma once
#include "tokens.h"
typedef struct{
    tokens* token;
    int total_tokens;
    int current_array_space;

}lexer;
lexer read_memory(char* c);
void search_token(lexer *lexer);
TOKEN_KEYWORDS find_token(char* word_detected, unsigned int longitud);
TOKEN_KEYWORDS find_operator_token(char operator_detected);
void add_token(lexer* data, TOKEN_KEYWORDS type);