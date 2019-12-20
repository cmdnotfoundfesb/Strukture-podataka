#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SUCCESS 0

#define BUFFER 1024

typedef struct cvor* pozicija;
struct cvor
{
	char* ime;
	int isRoot;
	pozicija Next;
	pozicija Child;
};

typedef struct stog* poz;
struct stog
{
	pozicija Node;
	poz Next;
};

int CreateNewDirectoryNode(pozicija*);
int PrintDirectory(pozicija, char*);
pozicija UpDirectory(pozicija, char*, poz);
pozicija InDirectory(pozicija, char*, char*, poz);
int MakeDirectory(pozicija, char*);
pozicija InsertDirectory(pozicija, pozicija);
int CreateNewStackNode(poz*);
int push(poz, pozicija);
int pop(poz, pozicija*);
int alokacijabuffera(char**, char**, char**, char**, char**);
int PrintPath(char*);


int main(int argc, char* argv[])
{
	char* path = NULL;
	char* command = NULL;
	char* imedir = NULL;
	char* naredba = NULL;
	char* buff = NULL;
	char* i = NULL;
	char* j = NULL;
	pozicija root = NULL;
	poz stack = NULL;
	pozicija upDir = NULL;

	alokacijabuffera(&path, &command, &imedir, &naredba, &buff);
	CreateNewDirectoryNode(&root);

	while (1)
	{
		printf("Unesite ime pocetnog direktorija: \n ");
		fgets(buff, BUFFER, stdin);

		if (strlen(buff) != 0)
			break;
	}

	root->ime = (char*)malloc(sizeof(char) * (strlen(buff) + 1));
	memset(root->ime, '\0', sizeof(root->ime));
	sscanf(buff, " %s", root->ime);
	root->isRoot = 1;
	root->Child = NULL;
	root->Next = NULL;
	upDir = root;

	CreateNewStackNode(&stack);

	stack->Next = NULL;

	strcat(path, root->ime);
	strcat(path, ":\\");

	while (_stricmp(naredba, "exit") != 0)
	{
		PrintPath(path);

		memset(command, 0, BUFFER);
		memset(imedir, 0, BUFFER);
		memset(naredba, 0, BUFFER);

		fgets(command, BUFFER, stdin);

		sscanf(command, " %s %s", naredba, imedir);

		if (strcmp(naredba, "dir"))
		{
			PrintDirectory(upDir, path);
		}
		else if (strcmp(naredba, "cd..") == 0 )
		{
			upDir = UpDirectory(upDir, path, stack);
		}
		else if (strcmp(naredba, "cd") == 0)
		{
			upDir = InDirectory(upDir, imedir, path, stack);
			if (upDir == NULL)
			{
				break;
			}
		}
		else if (strcmp(naredba, "md") == 0 )
		{
			if (upDir == NULL)
			{
				break;
			}
			
			else
				MakeDirectory(upDir, imedir);
		}
		else if (strcmp(naredba, "exit") == 0 )
		{
			printf("Izlaz iz programa.");
		}
		else if (strcmp(naredba, "help") == 0 )
		{
			printf("1. dir - ispisuje poddirektorije direktorija u kojem se nalazite\n");
			printf("2. cd - promjena direktorija\n");
			printf("3. md - napraviti novi poddirektorij\n");
			printf("4. exit - izlaz iz programa\n");
		}
		else
		{
			printf("Naredba nije prepoznata, pokusajte ponovno.\n");
		}
	}

	return 0;
}

int alokacijabuffera(char** path, char** naredba, char** imedir, char** command, char** buff)
{
	*path = (char*)malloc(sizeof(char) * BUFFER);
	*naredba = (char*)malloc(sizeof(char) * BUFFER);
	*imedir = (char*)malloc(sizeof(char) * BUFFER);
	*command = (char*)malloc(sizeof(char) * BUFFER);
	*buff = (char*)malloc(sizeof(char) * BUFFER);

	memset(*path, '\0', BUFFER);
	memset(*naredba, '\0', BUFFER);
	memset(*imedir, '\0', BUFFER);
	memset(*command, '\0', BUFFER);
	memset(*buff, '\0', BUFFER);

	return SUCCESS;
}

int PrintPath(char* path)
{
	printf("%s>", path);
	return SUCCESS;
}

int PrintDirectory(pozicija node, char* path)
{
	int i = 0;
	printf("\r\nDirectory of %s", path);

	node = node->Child;
	while (node != NULL)
	{
		printf("\r\n\t<DIR> %s", node->ime);
		node = node->Next;
		i++;
	}
	printf("\r\n");
	printf("\r\n\t\t %d Dir(s)", i);

	printf("\r\n\r\n");

	return SUCCESS;
}

int CreateNewDirectoryNode(pozicija* q)
{
	pozicija tmp = NULL;

	tmp = (pozicija)malloc(sizeof(struct cvor));

	tmp->isRoot = 0;
	tmp->Child = NULL;
	tmp->Next = NULL;

	*q = tmp;
	return SUCCESS;
}

pozicija UpDirectory(pozicija node, char* path, poz S)
{
	int result = SUCCESS;
	pozicija temp = NULL;
	char* a = NULL;

	result = Pop(S, &temp);
	if (result)
	{
		return node;
	}

	a = strrchr(path, '\\');
	if (temp->isRoot)
	{
		a++;
	}
	*a = '\0';

	return temp;
}

pozicija InDirectory(pozicija node, char* name, char* path, poz S)
{
	pozicija current = NULL;
	char* a = NULL;

	if (node == NULL)
	{
		return NULL;
	}

	current = node->Child;

	while (current != NULL && _stricmp(current->ime, name) != 0)
		current = current->Next;

	if (NULL == current)
	{
		return node;
	}

	Push(S, node);
	if (!node->isRoot)
		strcat(path, "\\");
	strcat(path, current->ime );

	return current;
}

pozicija InsertDirectory(pozicija q, pozicija child)
{
	pozicija prev = NULL;

	if (child == NULL) return q;

	if (strcmp(q->ime, child->ime) < 0)
	{
		q->Next = child;
		return q;
	}

	prev = child;

	while (prev->Next != NULL && strcmp(q->ime, prev->Next->ime) > 0)
	{
		prev = prev->Next;
	}

	q->Next = prev->Next;
	prev->Next = q;

	return child;
}

int MakeDirectory(pozicija node, char* ime)
{
	int result = SUCCESS;
	pozicija q = NULL;

	if (node == NULL)
	{
		return 0;
	}

	result = CreateNewDirectoryNode(&q);

	q->ime = (char*)malloc(sizeof(char) * (strlen(ime) + 1));

	memset(q->ime, '\0', (strlen(ime) + 1));

	strncpy(q->ime, ime, strlen(ime));

	node->Child = InsertDirectory(q, node->Child);

	return SUCCESS;
}

int CreateNewStackNode(poz* q)
{
	poz tmp = NULL;

	tmp = (poz)malloc(sizeof(struct stog));

	tmp->Next = NULL;
	*q = tmp;

	return SUCCESS;
}

int Push(poz S, pozicija T)
{
	int result = SUCCESS;
	poz q = NULL;

	result = CreateNewStackNode(&q);

	q->Node = T;
	q->Next = S->Next;
	S->Next = q;

	return SUCCESS;
}

int Pop(poz S, pozicija* node)
{
	poz tmp = NULL;

	if (NULL == S->Next)
		return 0;

	tmp = S->Next;
	if (tmp == NULL)
		return 0;

	S->Next = tmp->Next;
	if (tmp->Node == NULL)
		return 0;

	*node = tmp->Node;
	free(tmp);

	return SUCCESS;
}