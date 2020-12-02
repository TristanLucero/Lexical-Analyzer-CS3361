/* 
Tristan Lucero () | Assignment #3 | 10/11/2020
This program is a lexical analyzer written in C to identify lexemes
and tokens found in a source code file which is provided as a 
command line arguement.

this parser file is to declare parser functions and nextTokens
*/

#ifndef PARSER_H
#define PARSER_H

void expr();
void term();
void factor();

extern int nextToken;
#endif
