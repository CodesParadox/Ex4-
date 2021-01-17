#ifndef __FREQUENCY__H__
#define __FREQUENCY__H__
#define NUM_LETTERS ((int)26)

typedef enum
{
	FALSE = 0,
	TRUE = 1
} boolean;

#ifndef Node
#define Node
typedef struct node
{
	char letter;
	long unsigned int count;
	struct node *children[NUM_LETTERS];
	boolean EndOfWord;
	boolean hasChildren;

} node;
#endif

void insertString(node **root, char *key);
void incremental(node **n);
void mallocError(void);
node *newNode();
void freeNode(node **root);
int charToIndex(char ch);
void printWords(node **root, char *key, int index);
void printWordsReverse(node **root, char *key, int index);
//void printWord(node **root, char *key, char *index);

#endif /*__FREQUENCY__H__ */