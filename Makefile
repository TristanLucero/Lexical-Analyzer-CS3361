## Tristan Lucero () | Assignment #3 | 10/11/2020
## This is a make file to put together 
## front.h parser.h and Tristan_Lucero_R11597605_Assignment3.c
## The code is for a lexical analyzer

#I would strongly recommend NOT changing any lines below except the CC and MYFILE lines.
#Before running this file, run the command:   module load gnu


EXECS=danc_analyzer

#Replace the g++ with gcc if using C
CC=gcc

#Replace with the name of your C or C++ source code file.
MYFILE=Tristan_Lucero_R11597605_Assignment3.c
MYFILE2=parser.h
MYFILE3=front.h

all: ${EXECS}

${EXECS}: ${MYFILE} ${MYFILE2} ${MYFILE3}
	${CC} -o ${EXECS} ${MYFILE} ${MYFILE2} ${MYFILE3}

clean:
	rm -f ${EXECS}