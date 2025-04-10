#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token types
#define TYPE_TOKEN 1
#define MAIN_TOKEN 2
#define IF_TOKEN 3
#define ELSE_TOKEN 4
#define WHILE_TOKEN 5
#define ID_TOKEN 6
#define NUMBER_TOKEN 7
#define LEFTPAREN_TOKEN 8
#define RIGHTPAREN_TOKEN 9
#define LEFTBRACE_TOKEN 10
#define RIGHTBRACE_TOKEN 11
#define SEMICOLON_TOKEN 12
#define ASSIGN_TOKEN 13
#define EQUAL_TOKEN 14
#define PLUS_TOKEN 15
#define MINUS_TOKEN 16
#define GREATER_TOKEN 17
#define LESS_TOKEN 18
#define GREATEREQUAL_TOKEN 19
#define LESSEQUAL_TOKEN 20
#define LITERAL_TOKEN 21

// Structure to hold token information
typedef struct {
    int type;
    char lexeme[256];
    int value;  // For number tokens
} Token;

// Check if character is a letter (a-z, A-Z) or underscore
int isalpha_(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// Check if character is a digit (0-9)
int isdigit_(char c) {
    return c >= '0' && c <= '9';
}

// Check if character is alphanumeric or underscore
int isalnum_(char c) {
    return isalpha_(c) || isdigit_(c);
}

// Check if character is whitespace
int isspace_(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Get next token from input file
Token getNextToken(FILE *file) {
    Token token;
    char c;
    char buffer[256];
    int i = 0;
    
    // Skip whitespace
    do {
        c = fgetc(file);
        if (c == EOF) {
            token.type = -1;  // EOF token
            strcpy(token.lexeme, "EOF");
            return token;
        }
    } while (isspace_(c));
    
    // Identifier or keyword
    if (isalpha_(c)) {
        buffer[i++] = c;
        
        while ((c = fgetc(file)) != EOF && isalnum_(c)) {
            buffer[i++] = c;
        }
        
        ungetc(c, file);  // Put back the character that's not part of the identifier
        buffer[i] = '\0';
        
        // Check for keywords
        if (strcmp(buffer, "int") == 0) {
            token.type = TYPE_TOKEN;
        } else if (strcmp(buffer, "main") == 0) {
            token.type = MAIN_TOKEN;
        } else if (strcmp(buffer, "if") == 0) {
            token.type = IF_TOKEN;
        } else if (strcmp(buffer, "else") == 0) {
            token.type = ELSE_TOKEN;
        } else if (strcmp(buffer, "while") == 0) {
            token.type = WHILE_TOKEN;
        } else {
            token.type = ID_TOKEN;
        }
        
        strcpy(token.lexeme, buffer);
    }
    // Number
    else if (isdigit_(c)) {
        buffer[i++] = c;
        
        while ((c = fgetc(file)) != EOF && isdigit_(c)) {
            buffer[i++] = c;
        }
        
        ungetc(c, file);
        buffer[i] = '\0';
        
        token.type = NUMBER_TOKEN;
        strcpy(token.lexeme, buffer);
        token.value = atoi(buffer);
    }
    // Special characters and operators
    else {
        switch (c) {
            case '(':
                token.type = LEFTPAREN_TOKEN;
                strcpy(token.lexeme, "(");
                break;
            case ')':
                token.type = RIGHTPAREN_TOKEN;
                strcpy(token.lexeme, ")");
                break;
            case '{':
                token.type = LEFTBRACE_TOKEN;
                strcpy(token.lexeme, "{");
                break;
            case '}':
                token.type = RIGHTBRACE_TOKEN;
                strcpy(token.lexeme, "}");
                break;
            case ';':
                token.type = SEMICOLON_TOKEN;
                strcpy(token.lexeme, ";");
                break;
            case '=':
                c = fgetc(file);
                if (c == '=') {
                    token.type = EQUAL_TOKEN;
                    strcpy(token.lexeme, "==");
                } else {
                    ungetc(c, file);
                    token.type = ASSIGN_TOKEN;
                    strcpy(token.lexeme, "=");
                }
                break;
            case '+':
                token.type = PLUS_TOKEN;
                strcpy(token.lexeme, "+");
                break;
            case '-':
                token.type = MINUS_TOKEN;
                strcpy(token.lexeme, "-");
                break;
            case '>':
                c = fgetc(file);
                if (c == '=') {
                    token.type = GREATEREQUAL_TOKEN;
                    strcpy(token.lexeme, ">=");
                } else {
                    ungetc(c, file);
                    token.type = GREATER_TOKEN;
                    strcpy(token.lexeme, ">");
                }
                break;
            case '<':
                c = fgetc(file);
                if (c == '=') {
                    token.type = LESSEQUAL_TOKEN;
                    strcpy(token.lexeme, "<=");
                } else {
                    ungetc(c, file);
                    token.type = LESS_TOKEN;
                    strcpy(token.lexeme, "<");
                }
                break;
            default:
                // Unrecognized character
                token.type = -2;  // Error token
                buffer[0] = c;
                buffer[1] = '\0';
                strcpy(token.lexeme, buffer);
        }
    }
    
    return token;
}

// Function to get token type name
const char* getTokenTypeName(int type) {
    switch (type) {
        case TYPE_TOKEN: return "TYPE_TOKEN";
        case MAIN_TOKEN: return "MAIN_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case ELSE_TOKEN: return "ELSE_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case NUMBER_TOKEN: return "NUMBER_TOKEN";
        case LEFTPAREN_TOKEN: return "LEFTPAREN_TOKEN";
        case RIGHTPAREN_TOKEN: return "RIGHTPAREN_TOKEN";
        case LEFTBRACE_TOKEN: return "LEFTBRACE_TOKEN";
        case RIGHTBRACE_TOKEN: return "RIGHTBRACE_TOKEN";
        case SEMICOLON_TOKEN: return "SEMICOLON_TOKEN";
        case ASSIGN_TOKEN: return "ASSIGN_TOKEN";
        case EQUAL_TOKEN: return "EQUAL_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MINUS_TOKEN: return "MINUS_TOKEN";
        case GREATER_TOKEN: return "GREATER_TOKEN";
        case LESS_TOKEN: return "LESS_TOKEN";
        case GREATEREQUAL_TOKEN: return "GREATEREQUAL_TOKEN";
        case LESSEQUAL_TOKEN: return "LESSEQUAL_TOKEN";
        case LITERAL_TOKEN: return "LITERAL_TOKEN";
        case -1: return "EOF_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}

int main() {
    FILE* file = fopen("main.c", "r");
    if (!file) {
        printf("Unable to open file!\n");
        return 1;
    }
    
    Token token;
    
    // Read and process tokens until EOF
    while (1) {
        token = getNextToken(file);
        
        if (token.type == -1) { // EOF
            break;
        }
        
        // Print token information
        printf("Token: %s, Type: %s", token.lexeme, getTokenTypeName(token.type));
        if (token.type == NUMBER_TOKEN) {
            printf(", Value: %d", token.value);
        }
        printf("\n");
    }
    
    fclose(file);
    return 0;
}
