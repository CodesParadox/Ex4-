#include "frequency.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//print an error if malloc has a problem.
void mallocError()
{
	printf("Memory error\n");
	exit(1);
}

//Crates a new node, insert all his parameters.
node *newNode()
{
	int i = 0;
	node *nodep = NULL;
	nodep = (node *)malloc(sizeof(node));
	if (!nodep)
		mallocError();
	else
	{ //malloc finished right, nodep isnt null
		//nodep->letter = letter;
		nodep->count = 0;
		nodep->EndOfWord = FALSE;
		nodep->hasChildren = TRUE;
		while (i < NUM_LETTERS)
		{
			nodep->children[i] = NULL;
			i++;
		}
	}
	return nodep;
}

//This method clear the memory of a node and his kids,
// if he got any.
void freeNode(node **n)
{
	int i = 0;
	node *PointerOfNode = *n;
	if (PointerOfNode == NULL)
		return;

	if (FALSE == PointerOfNode->hasChildren)
	{
		free(n);
	}
	else
	{
		if (PointerOfNode->hasChildren)
		{
			while (i < NUM_LETTERS)
			{
				if (PointerOfNode->children[i] != NULL)
					freeNode(&(PointerOfNode->children)[i]);
				i++;
			}
		}
	}
	free(PointerOfNode);
}

//Convert char type to an index number.
int charToIndex(char c)
{
	return c - 'a';
}

//Insert text to the Trie.
void insertString(node **root, char *Word)
{
	node *Proot = *root; // head of the node
	if (Proot == NULL)
		return;
	if (strlen(Word) == 0)
		return;
	int i = 0;
	while (i < strlen(Word))
	{
		if (Proot->children[(Word[i] - 'a')] == NULL)
		{ // check if the path exists, otherwise creat a new node
			Proot->children[(Word[i] - 'a')] = newNode();
			Proot->children[(Word[i] - 'a')]->letter = Word[i];
			//Proot->children[(Word[i] - 'a')]->hasChildren = FALSE;
			//Proot->count++;
		}
		Proot = Proot->children[(Word[i] - 'a')]; // move to the next node
		i++;
	}
	// end of the correct word
	Proot->EndOfWord = TRUE;
	Proot->count++; // mark the node as leaf in the trie
}

//print all the words in the trie
void printWords(node **root, char *word, int index)
{
	node *checkchild = *root;
	if (checkchild == NULL)
	{ // check if the tree exist
		printf("The tree is empty like my brain");
		return;
	}
	int i = 0;
	if (checkchild->EndOfWord == TRUE)
	{
		*(word + index++) = '\0'; // adding an end of the string
		printf("%s\t%ld\n", word, checkchild->count);

		// if (checkchild->hasChildren) // remainder child
		// 	word = word + index;
		// else

		// 	index--;
	}

	while (i < NUM_LETTERS)
	{
		if (checkchild->children[i] != NULL)
		{
			*(word + index) = checkchild->children[i]->letter;
			printWords(&(checkchild->children[i]), word, index + 1);
		}
		i++;
	}
}

// increment the counter of the node (end of word)
void incremental(node **n)
{
	node *proot = *n;
	proot->count++;
}

//Print the words in reverse.
void printWordsReverse(node **root, char *word, int index)
{
	node *checkchild = *root;
	if (checkchild == NULL)
	{ // check if the tree exist
		printf("The tree is empty like my brain");
		return;
	}
	//int reverse = NUM_LETTERS - 1;

	int reverse = NUM_LETTERS - 1;
	while (reverse >= 0)
	{
		if (checkchild->children[reverse] != NULL)
		{
			*(word + index) = checkchild->children[reverse]->letter;
			printWordsReverse(&(checkchild->children[reverse]), word, index + 1);
		}
		reverse = reverse - 1;
	}
	if (checkchild->EndOfWord == TRUE)
	{
		*(word + index++) = '\0'; // adding an end of the string
		printf("%s\t%ld\n ", word, checkchild->count);

		// if (checkchild->hasChildren) // remainder child
		// 	word = word + index;
		// else

		// 	index--;
	}
}

/**
 * function that direct the arguments to the correct print (default or reverse)
 * by checking type
 */
// void printWord(node **root, char *word, char *key)
// {
// 	unsigned int index = 0;
// 	if (key == 'r')
// 		printWordsReverse(root, word, index);
// 	else
// 		printWords(root, word, index);
// }