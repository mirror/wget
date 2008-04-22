%option case-insensitive
%option noyywrap
%option never-interactive

%{
/* Lex source for CSS tokenizing.
   Taken from http://www.w3.org/TR/CSS21/grammar.html#q2
   Copyright (C) 2006 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#include "css-tokens.h"

/* {s}+\/\*[^*]*\*+([^/*][^*]*\*+)*\/      {unput(' '); } */
/*replace by space*/
%}

h               [0-9a-f]
nonascii        [\200-\377]
unicode         \\{h}{1,6}(\r\n|[ \t\r\n\f])?
escape          {unicode}|\\[^\r\n\f0-9a-f]
nmstart         [_a-z]|{nonascii}|{escape}
nmchar          [_a-z0-9-]|{nonascii}|{escape}
string1         \"([^\n\r\f\\"]|\\{nl}|{escape})*\"
string2         \'([^\n\r\f\\']|\\{nl}|{escape})*\'
invalid1        \"([^\n\r\f\\"]|\\{nl}|{escape})*
invalid2        \'([^\n\r\f\\']|\\{nl}|{escape})*

comment         \/\*[^*]*\*+([^/*][^*]*\*+)*\/
ident           -?{nmstart}{nmchar}*
name            {nmchar}+
num             [0-9]+|[0-9]*"."[0-9]+
string          {string1}|{string2}
invalid         {invalid1}|{invalid2}
url             ([!#$%&*-~]|{nonascii}|{escape})*
s               [ \t\r\n\f]
w               ({s}|{comment})*
nl              \n|\r\n|\r|\f

A               a|\\0{0,4}(41|61)(\r\n|[ \t\r\n\f])?
C               c|\\0{0,4}(43|63)(\r\n|[ \t\r\n\f])?
D               d|\\0{0,4}(44|64)(\r\n|[ \t\r\n\f])?
E               e|\\0{0,4}(45|65)(\r\n|[ \t\r\n\f])?
G               g|\\0{0,4}(47|67)(\r\n|[ \t\r\n\f])?|\\g
H               h|\\0{0,4}(48|68)(\r\n|[ \t\r\n\f])?|\\h
I               i|\\0{0,4}(49|69)(\r\n|[ \t\r\n\f])?|\\i
K               k|\\0{0,4}(4b|6b)(\r\n|[ \t\r\n\f])?|\\k
M               m|\\0{0,4}(4d|6d)(\r\n|[ \t\r\n\f])?|\\m
N               n|\\0{0,4}(4e|6e)(\r\n|[ \t\r\n\f])?|\\n
P               p|\\0{0,4}(50|70)(\r\n|[ \t\r\n\f])?|\\p
R               r|\\0{0,4}(52|72)(\r\n|[ \t\r\n\f])?|\\r
S               s|\\0{0,4}(53|73)(\r\n|[ \t\r\n\f])?|\\s
T               t|\\0{0,4}(54|74)(\r\n|[ \t\r\n\f])?|\\t
X               x|\\0{0,4}(58|78)(\r\n|[ \t\r\n\f])?|\\x
Z               z|\\0{0,4}(5a|7a)(\r\n|[ \t\r\n\f])?|\\z

%%

{s}                     {return S;}

\/\*[^*]*\*+([^/*][^*]*\*+)*\/          {return S;} /* ignore comments */

"<!--"          {return CDO;}
"-->"                   {return CDC;}
"~="                    {return INCLUDES;}
"|="                    {return DASHMATCH;}

{w}"{"                  {return LBRACE;}
{w}"+"                  {return PLUS;}
{w}">"                  {return GREATER;}
{w}","                  {return COMMA;}

{string}                {return STRING;}
{invalid}               {return INVALID; /* unclosed string */}

{ident}                 {return IDENT;}

"#"{name}               {return HASH;}

"@import"               {return IMPORT_SYM;}
"@page"                 {return PAGE_SYM;}
"@media"                {return MEDIA_SYM;}
"@charset "             {return CHARSET_SYM;}

"!"{w}"important"       {return IMPORTANT_SYM;}

{num}{E}{M}             {return EMS;}
{num}{E}{X}             {return EXS;}
{num}{P}{X}             {return LENGTH;}
{num}{C}{M}             {return LENGTH;}
{num}{M}{M}             {return LENGTH;}
{num}{I}{N}             {return LENGTH;}
{num}{P}{T}             {return LENGTH;}
{num}{P}{C}             {return LENGTH;}
{num}{D}{E}{G}          {return ANGLE;}
{num}{R}{A}{D}          {return ANGLE;}
{num}{G}{R}{A}{D}       {return ANGLE;}
{num}{M}{S}             {return TIME;}
{num}{S}                {return TIME;}
{num}{H}{Z}             {return FREQ;}
{num}{K}{H}{Z}          {return FREQ;}
{num}{ident}            {return DIMENSION;}

{num}%                  {return PERCENTAGE;}
{num}                   {return NUMBER;}

"url("{w}{string}{w}")" {return URI;}
"url("{w}{url}{w}")"    {return URI;}
{ident}"("              {return FUNCTION;}

.                       {return *yytext;}

%%
