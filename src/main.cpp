#include <stdio.h>

int Classify(char c) {
  if(c == ' ')
    return 0;
  else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return 1;
  else if(c >= '0' && c <= '9')
    return 2;
  else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '=')
    return 3;
  else if(c == '(' || c == ')')
    return 4;
  else
    return 5;
}

char ReadNum(FILE* fp) {
  char c;
  while ((c = fgetc(fp)) != EOF) {
    if(c >= '0' && c <= '9')
      continue;
    else
      return c;
  }
  return '\0';
}

char ReadIdentifier(FILE* fp) {
  char c;
  while ((c = fgetc(fp)) != EOF) {
    if((c >= '0' && c <= '9') ||
       (c >= 'a' && c <= 'z') ||
       (c >= 'A' && c <= 'Z'))
      continue;
    else
      return c;
  }
  return '\0';
}

int main()
{
  FILE* fread = fopen("expression.txt", "r");
  FILE *fwrite = fopen("result.txt", "w+");
  char c;
  int flag;
  printf("This is a simple compiler");
  int a;
  scanf("%d", &a);
  if (!fread) {
    printf("can't open file\n");
    return -1;
  }
  c = fgetc(fread);
  while(c != EOF && c != '\n') {
    flag = Classify(c);
    switch (flag) {
    case 0:
      c = fgetc(fread);
      break;
    case 1:
      c = ReadIdentifier(fread);
      fprintf(fwrite, "(1,i)\n");
      break;
    case 2:
      c = ReadNum(fread);
      fprintf(fwrite, "(2,c)\n");
      break;
    case 3:
      fprintf(fwrite, "(2,%c)\n", c);
      c = fgetc(fread);
      break;
    case 4:
      fprintf(fwrite, "(3,%c)\n", c);
      c = fgetc(fread);
      break;
    }
  }
  fclose(fread);
  fclose(fwrite);
  return 0;
}
