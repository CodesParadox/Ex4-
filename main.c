#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "frequency.h"
int main(int argc, char *argv[])
{
	node *root = newNode();
	int capacity = 300;
	char indexTav = getchar();
	int count = 0;
	int num = 32;
	char *Checker = NULL;
	boolean Temp = FALSE;
	char *CharKey = (char *)malloc(sizeof(char) * capacity);
	boolean optionToBe = (indexTav != EOF && Temp != TRUE);
	//insertion to trie
	while (indexTav != EOF || optionToBe)
	{

		if (indexTav >= 'A' && indexTav <= 'Z')
		{
			indexTav = indexTav + num;
		}

		if (indexTav >= 'a' && indexTav <= 'z')
		{
			if (indexTav != ' ' && indexTav != '\n')
			{
				if (indexTav != '\0' && indexTav != '\t')
				{
					if (count == capacity)
					{
						Checker = (char *)realloc(CharKey, sizeof(char) * (capacity + (num - 12)));
						if (Checker == NULL && CharKey != NULL) //the realloc didnt succeed
						{
							free(CharKey);
							return -1;
						}
						capacity = capacity + (num - 12);
						CharKey = (char *)calloc(capacity, sizeof(char));
						strcpy(CharKey, Checker);
						free(Checker);
					}
					CharKey[count] = indexTav;
					count++;
				}
			}
		}

		if (indexTav == EOF || indexTav == '\n' || indexTav == '\t' || indexTav == ' ' || indexTav == '\0')
		{

			CharKey[count] = '\0';
			if (CharKey[0] != ' ' && count >= 1)
			{
				insertString(&root, CharKey);
			}
			count = 0;
		}

		if (!(indexTav == EOF))
		{
			Temp = FALSE;
		}
		else
		{
			Temp = TRUE;
		}
		optionToBe = (indexTav != EOF && Temp != TRUE);
		indexTav = getchar();
	}

	//direct the arguments to the correct print (default or reverse)
	if (argc == 2 && strcmp(argv[1], "r") != 0)
	{
		printWords(&root, CharKey, 0);
	}
	else
	{
		printWordsReverse(&root, CharKey, 0);
	}

	//free malloc
	freeNode(&root);
	free(CharKey);
	return 0;
}
