#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "lexer.h"
int main(){
    FILE* fptr;
    fptr = fopen("./beta.kkx","r");
    if (fptr == NULL){
        return -1;
    };

    fseek(fptr,0, SEEK_END);
    long char_amount = ftell(fptr);
    char* buffer = (char*)malloc(char_amount + 1);
    rewind(fptr);
    fread(buffer, 1, char_amount, fptr);
    buffer[char_amount] = '\0';
    lexer l = read_memory(buffer);
    search_token(&l);
    fptr=NULL;
    free(buffer);
    free(l.token);

    return 0;


}