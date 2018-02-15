/*
    Copyright (C) 2017 CHAW-HUNG, HSIAO

---------------------------------------------------------------------------------------------------------------
    This file is part of Ollolol and Hsiaosvideo Cryptography System.

    Ollolol and Hsiaosvideo Cryptography System is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Ollolol and Hsiaosvideo Cryptography System is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ollolol and Hsiaosvideo Cryptography System.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "argv.hpp"
extern char file;
extern char *ReadFile;
int argvCheck(char* argv){
  switch (argv[0]){
      case '-':
      argvCharCheck(argv);
      break;
      default:
      if(file == 1){
        ReadFile = argv;
        file = 0;
      }
  }
  return 0;
}
int argvCharCheck(char* argv){
  int b = 1;
  for(int a = 1;;a++){
    switch (argv[a]){
        case 'f':
        file = 1;
        break;
        case '\0':
        b = 0;
        break;
    }
    if(b){
      break;
    }
  }
  return 0;
}
