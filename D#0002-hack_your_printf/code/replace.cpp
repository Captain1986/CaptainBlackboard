//replace.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//replace.cpp
int main(int argc, char* argv[])
{
  char keyword[] = {"this is a log printed from _3rd_lib_func."};
  int len = sizeof(keyword);

  FILE * fin = fopen(argv[1], "rb");

  fseek (fin , 0 , SEEK_END);
  long lSize = ftell (fin);
  printf("lSize[%ld].\n", lSize);
  rewind (fin);

  int num = lSize/sizeof(char);
  char * buffer = (char*) malloc (sizeof(char)*num);

  long result = fread(buffer, sizeof(char), num, fin);

  for( int i = 0; i < lSize; i++) {
     char curStr[len] = {"\0"};
	 memcpy(curStr, buffer + i, len);
     if(strstr(curStr, keyword)) {
		 printf("find curStr[%s].\n", curStr);
		 char hack_info[] = {"O Captain!My Captain!"};
		 memcpy(buffer + i, hack_info, sizeof(hack_info));
		 break;
	 }
  }

  FILE * fout = fopen(argv[2], "wb");
  fwrite(buffer, sizeof(char), num, fout);

  free(buffer); buffer = NULL;
  fclose(fin);  fin = NULL;
  fclose(fout); fout = NULL;

  return 0;
}
