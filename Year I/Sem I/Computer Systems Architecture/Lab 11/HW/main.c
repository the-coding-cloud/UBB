#include <stdio.h>
#include <string.h>

char* MergeStrings(int, char*, int, char*);

int main()
{
	char sir1[101];
	char sir2[101];
	int len1 = 0;
	int len2 = 0;

	fgets(sir1, 100, stdin);
	len1 = strlen(sir1) - 1; // We subtract /n from the length

	fgets(sir2, 100, stdin);
	len2 = strlen(sir2)-1;

	char missing[100] = "";

	//The follwing part is needed if we unfortunately don't enter two strings that are the same length

	if (len1 > len2)
	{
		for (int i = 0; i < len1 - len2; i++)
			sir2[len2 + i] = ' ';
		sir2[len1] = '\0';
		len2 = len1;
	}

	if (len2 > len1)
	{
		for (int i = 0; i < len2 - len1; i++)
			sir1[len1 + i] = ' ';
		sir1[len2] = '\0';
		len1 = len2;
	}

	printf("The merged strings are: %s", MergeStrings(len1, sir1, len2, sir2));
	printf("\nAnd the second version: %s", MergeStrings(len2, sir2, len1, sir1));
}