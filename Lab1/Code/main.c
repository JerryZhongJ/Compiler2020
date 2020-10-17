#include "common.h"
void yyrestart(FILE *f);
int main(int argc, char **argv)
{
	if (argc <= 1)
		return 1;
	FILE *f = fopen(argv[1], "r");
	if (!f)
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	yydebug = 1;
	if (!yyparse() && errorNum == 0)
	{
		display(start, 0);
	}
	if (lineErrorNum != 0)//print last error line
	{
		puts(bufferPtr);
	}
	return 0;
}