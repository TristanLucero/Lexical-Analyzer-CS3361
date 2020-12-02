/* 
Tristan Lucero () | Assignment #3 | 10/11/2020
This program is a lexical analyzer written in C to identify lexemes
and tokens found in a source code file which is provided as a 
command line arguement.

This front.h file is to define values for each of the token codes and character classes
*/

#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define OPERATOR 2
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

#define LESSER_OP 27
#define GREATER_OP 28
#define EQUAL_OP 29
#define NEQUAL_OP 30
#define LEQUAL_OP 31
#define GEQUAL_OP 32
#define SEMICOLON 33
#define KEY_READ 34
#define KEY_WRITE 35
#define KEY_WHILE 36
#define KEY_DO 37
#define KEY_OD 38



int lex();

#endif
