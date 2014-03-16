ABOOK Parser
================

Abook is a great program to manage contacts. But I wanted to
add some external features, like a program to merge two
addressbooks, to make easier synchronising addressbooks from
various devices. This repo include a small library, written
in c++ using only the standard c++ library, to parse and
modify abook addressbooks, and an example program merging
two or more addressbooks.

To compile it, just hit ``make``, it will be compiled with
gcc. You can tune the compilation by editing the param.mk
file. To compile the merging program, hit ``make test``, it
will be compiled as merger.prog.

All the files are under the MIT licence, copyright Luc
Chabassier 2014. See the LICENCE file for the complete text
of the licence.

