/* 
Tristan Lucero () | Assignment #3 | 10/11/2020
This program is a lexical analyzer written in C to identify lexemes
and tokens found in a source code file which is provided as a 
command line arguement.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "front.h"
#include "parser.h"


/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
char getChar();
static void getNonBlank();

/*New Functions*/

//function to check if text is keyword or just identifier
int isKeyword(char *text);



/******************************************************

 main driver */
int main(int argc, char *argv[])
{
    printf("DanC Analyzer :: R11597605\n\n");
    char *fileName = NULL;
    if(argc == 2)
        fileName = argv[1];
    else
        printf("ERROR...no command line argument given...\n");

    /* Open the input data file and process its contents */
    if ((in_fp = fopen(fileName, "r")) == NULL) {
        printf("ERROR - cannot open file \n");
    } else {
        getChar();
        do {
            lex();
            //expr();
        } while (nextToken != EOF);
    }
    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators, parentheses and semicolons and return the
 * token */
static int lookup(char ch) {
	//char to hold next char value, so we can ungetc if need be
    char nextChar;
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case ':':
            addChar();
			//check if next char equals value, if so assign
			//that value, otherwise ungetc and move on
            nextChar = getChar();
            if (nextChar == '='){
                nextToken = ASSIGN_OP;
                addChar();
            }
            else
                ungetc(nextChar, in_fp);
            break;
        case '=':
            addChar();
            nextToken = EQUAL_OP;
            break;
        case '<':
            addChar();
            nextToken = LESSER_OP;
            nextChar = getChar();
            if (nextChar == '>'){
                nextToken = NEQUAL_OP;
                addChar();
            }
            else
                ungetc(nextChar, in_fp);
            nextChar = getChar();
            if (nextChar == '='){
                nextToken = LEQUAL_OP;
                addChar();
            }
            else
                ungetc(nextChar, in_fp);
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            nextChar = getChar();
            if (nextChar == '='){
                nextToken = GEQUAL_OP;
                addChar();
            }
            else
                ungetc(nextChar, in_fp);
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
		//if unknown case, just assign unknown
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
char getChar() {
    //char textArray[100] = "";
    //int i = 0;
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar)){
            charClass = LETTER;
        }
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
    return nextChar;
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

const char* numToToken(int num){
    //switch for the tokens to go from numeric value to string, returns const char pointer
    switch(num){
        case 10:
            return "INT_LIT";
            break;
        case 11:
            return "IDENT";
            break;
        case 20:
            return "ASSIGN_OP";
            break;
        case 21:
            return "ADD_OP";
            break;
        case 22:
            return "SUB_OP";
            break;
        case 23:
            return "MULT_OP";
            break;
        case 24:
            return "DIV_OP";
            break;
        case 25:
            return "LEFT_PAREN";
            break;
        case 26:
            return "RIGHT_PAREN";
            break;
        case 27:
            return "LESSER_OP";
            break;
        case 28:
            return "GREATER_OP";
            break;
        case 29:
            return "EQUAL_OP";
            break;
        case 30:
            return "NEQUAL_OP";
            break;
        case 31:
            return "LEQUAL_OP";
            break;
        case 32:
            return "GEQUAL_OP";
            break;
        case 33:
            return "SEMICOLON";
            break;
        case 34:
            return "KEY_READ";
            break;
        case 35:
            return "KEY_WRITE";
            break;
        case 36:
            return "KEY_WHILE";
            break;
        case 37:
            return "KEY_DO";
            break;
        case 38:
            return "KEY_OD";
            break;

    }
    return "UNKNOWN";
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();

            }
            nextToken = IDENT;
            //if lexeme is a keyword, then set the next token to the token
            //of that keyword
            if(isKeyword(lexeme) != 0)
                nextToken = isKeyword(lexeme);
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case OPERATOR:
            addChar();
            getChar();
            while (charClass == OPERATOR){
                addChar();
                getChar();
            }
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */

    //only print if it's not EOF, don't actually print EOF
    if(strcmp(lexeme, "EOF") != 0)
        printf("%s %s\n", lexeme, numToToken(nextToken));
    return nextToken;
} /* End of function lex */


//lookup function for keywords,
//if it matches any of them will return their code for that token
int isKeyword(char *text){
        if (strcmp(text, "read") == 0)
            return 34;
        else if (strcmp(text, "write") == 0)
            return 35;
        else if (strcmp(text, "while") == 0)
            return 36;
        else if (strcmp(text, "do") == 0)
            return 37;
        else if (strcmp(text, "od") == 0)
            return 38;
        else
            return 0;
}
