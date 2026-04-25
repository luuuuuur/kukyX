#include<stdlib.h>
#include<stdio.h>
#include "tokens.h"
#include "lexer.h"
#include<string.h>
tokens keywords_table[] = {
    {"IF", TOKEN_IF},
    {"ALL", TOKEN_ALL},
    {"IN", TOKEN_IN},
    {"FOR", TOKEN_FOR},
    {"FROM", TOKEN_FROM},
    {"PREPARE", TOKEN_PREPARE},
    {"REQUEST", TOKEN_REQUEST},
    {"ANALYZE", TOKEN_ANALYZE},
    {"SEND", TOKEN_SEND},
    {"CONTENT", TOKEN_CONTENT},
    {"TYPE", TOKEN_TYPE},
    {"LENGTH", TOKEN_LENGTH},
    {"TO", TOKEN_TO},
    {"SCHEME", TOKEN_SCHEME},
    {"STATUS", TOKEN_STATUS},
    {"CODE", TOKEN_CODE},
    {"HEADERS", TOKEN_HEADERS},
    {"METHOD", TOKEN_METHOD},
    {"AVAILABLE", TOKEN_AVAILABLE},
    {"BODY", TOKEN_BODY},
    {"CONNECTION", TOKEN_CONNECTION},
    {"LANGUAGES", TOKEN_LANGUAGES},
    {"USER_AGENT", TOKEN_USER_AGENT},
    {"HOST", TOKEN_HOST},
    {"HTTP", TOKEN_HTTP},
    {"HTTPS", TOKEN_HTTPS},
    {"EXTRACT", TOKEN_EXTRACT},
    {"->", TOKEN_ARROW},
    {"{", TOKEN_LBRACE},
    {"}", TOKEN_RBRACE},
    {",", TOKEN_COMMA},
    {":", TOKEN_COLON},
    {"\"", TOKEN_QUOTE},
    {" ", TOKEN_SPACE_KEY}
};

unsigned int num_keywords = sizeof(keywords_table) / sizeof(tokens);
lexer read_memory(char* buffer){
    lexer data;
    data.current_array_space = 8;
    data.total_tokens = 0;
    data.token = malloc(8 * sizeof(tokens));
    char* start = buffer;
    char* current = buffer;
    while(*current != '\0'){
        while(*current == ' ' || *current == '\n' || *current == '\t'){
            current++;
            start = current;
        };
        
        while(*current != '\0' && *current != '{' && *current != '}' && *current != ':'
        && *current != ',' && *current != ' '&& *current != '\n' && *current != '\t'){
            current++;
        };
        unsigned int longitud = current-start;
        if(longitud>0){
            TOKEN_KEYWORDS token = find_token(start, longitud);
            add_token(&data, token);

        };
        if(*current == '{' || *current == '}' || *current == ':' || *current == ',' || *current == ' '){
                TOKEN_KEYWORDS token = find_operator_token(*current);
                add_token(&data, token);
                current++;
                start = current;
        };
    };

    return data;
};


TOKEN_KEYWORDS find_token(char* word_detected, unsigned int longitud){
    for(unsigned int i = 0; i<num_keywords;i++){
        if(strlen(keywords_table[i].value) == longitud && strncmp(word_detected, 
            keywords_table[i].value, longitud) == 0){
                return keywords_table[i].TokenType;
            }
    };
    printf("buscando: longitud=%u, palabra=", longitud);
    fwrite(word_detected, 1, longitud, stdout);
    printf("\n");
    return TOKEN_STRING;
};

TOKEN_KEYWORDS find_operator_token(char operator_detected){
    for(unsigned int i = 0; i<num_keywords; i++){
        if(keywords_table[i].value[0] == operator_detected){
            return keywords_table[i].TokenType;
        }
    }
    return TOKEN_UNKNOWN;
}


void search_token(lexer *lexer){
    for(unsigned int i=0; i<lexer->total_tokens; i++){
        unsigned int found = 0;
        for(unsigned int k=0; k<num_keywords; k++){
            if(keywords_table[k].TokenType == lexer->token[i].TokenType){
                printf("%s",keywords_table[k].value);
                found ++;
                break;
            }
        }

        if (found == 0){
            printf("UNKNOWN\n");
        }
    }
}

void add_token(lexer* data, TOKEN_KEYWORDS type){
    if(data->current_array_space == data->total_tokens){
        data->current_array_space*=2;
        data->token = realloc(data->token, data->current_array_space * sizeof(tokens));
    };
    data->token[data->total_tokens].TokenType = type;
    data->total_tokens ++;
};