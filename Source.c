#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define BUFFER 1024

enum _TREE_PRINT { INORDER, PREORDER, POSTORDER };

typedef struct _cvor cvor;
typedef struct _cvor* poz;
struct _cvor {
	char* el;
	poz desno;
	poz lijevo;
};

typedef struct _stog stog;
typedef struct _stog* pozicija;
struct _stog {
	poz elCvora;
	pozicija next;
};

int stvoriCvor(poz*);
int stvoriElStoga(pozicija*);

int push(poz, pozicija);
int pop(poz*, pozicija);

int stabloproracuna(char*, poz*, pozicija);
int stvaranjeDatoteke(poz*);
int upisDatoteke(FILE* , poz*); 
int ispis(int, poz);

int main()
{
	char* imedatoteke = NULL;
	pozicija stack = NULL;
	poz root = NULL;
	FILE* dat = NULL;

	stvoriElStoga(&stack);

	imedatoteke = (char*)malloc(sizeof(char) * BUFFER);
	if (imedatoteke == NULL)
	{
		printf("Doslo je do greske pri alociranju memorije. ");
		return ERROR;
	}
	memset(imedatoteke, '\0', BUFFER);

	printf("Unesite ime datoteke iz koje zelite procitati postfix izraz: ");
	scanf(" %s", imedatoteke);

	stabloproracuna(imedatoteke, &root, stack);
	stvaranjeDatoteke(dat, root);

	ispis(INORDER, root);

	return SUCCESS;
}

int stvoriCvor(poz* p)
{
	poz tmp = NULL;

	tmp = (poz)malloc(sizeof(cvor));
	if (tmp == NULL)
	{
		printf("Doslo je do greske pri alociranju memorije. \n");
		return ERROR;
	}

	tmp->el = NULL;
	tmp->desno = NULL;
	tmp->lijevo = NULL;

	*p = tmp;

	return SUCCESS;
}

int stvoriElStoga(pozicija* s)
{
	pozicija temp = NULL;
	temp = (pozicija)malloc(sizeof(stog));
	if (temp == NULL)
	{
		printf("Doslo je do greske pri alociranju memorije. \n");
		return ERROR;
	}

	temp->elCvora = NULL;
	temp->next = NULL;
	*s = temp;

	return SUCCESS;
}

int push(poz p, pozicija s)
{
	pozicija q = NULL;

	stvoriElStoga(&q);

	q->elCvora = p;
	q->next = s->next;
	s->next = q;

	return SUCCESS;
}

int pop(poz* p, pozicija s)
{
	pozicija temp = NULL;
	poz q = NULL;

	temp = s->next;
	s->next = temp->next;

	q = temp->elCvora;
	free(temp);

	*p = q;

	return SUCCESS;
}

int stabloproracuna(char* imedatoteke, poz* root, pozicija stack)
{
	int broj = 0;
	int brojac = 0;
	char* buff = NULL;
	FILE* fp = NULL;
	poz q = NULL;

	buff = (char*)malloc(sizeof(char) * BUFFER);
	if(buff == NULL)
	{
		printf("Doslo je do greske pri alociranju memorije");
		return ERROR;
	}
	memset(buff, '\0', BUFFER);
	fp = fopen(imedatoteke, "r");

	while(!feof(fp))
	{
		memset(buff, '\0', BUFFER);
		stvoriCvor(&q);

		fscanf(fp, " %s", buff);
		if (buff == NULL || strlen(buff) == 0)
			continue;

		brojac = strlen(buff);
		brojac++;

		q->el = (char*)malloc(sizeof(char)*brojac);
		if (q->el == NULL)
		{
			printf("Doslo je do pogreske pri alociranju memorije. ");
			return ERROR;
		}
		memset(q->el, '\0', brojac);
		brojac--;

		strncpy(q->el, buff, brojac);
		q->desno = NULL;
		q->lijevo = NULL;

		brojac = sscanf(buff, " %d", &broj);

		if (brojac == EOF || brojac <= 0)
		{
			pop(&q->desno, stack);
			pop(&q->lijevo, stack);
		}
		push(q, stack);
	}
	fclose(fp);
	free(buff);

	pop(&q, stack);
	*root = q;

	return SUCCESS;
}

int stvaranjeDatoteke(FILE* dat, poz* root)
{
	dat = fopen("infix.txt", "w");

	upisDatoteke(dat, root);

	fclose(dat);

	return SUCCESS;
}

int upisDatoteke(FILE* dat, poz p)
{
	if (p != NULL)
	{
		if (p->lijevo != NULL)
			fprintf(dat, " (");
		upisDatoteke(dat, p->lijevo);
		fprintf(dat, " %s", p->el);
		upisDatoteke(dat, p->desno);
		if (p->desno != NULL)
			fprintf(dat, ") ");
	}

	return SUCCESS;
}

int ispis(int type, poz p)
{
	switch (type)
	{
	case INORDER:
	{
		if (p != NULL)
		{
			if (p->lijevo != NULL)
				printf(" (");
			ispis(type, p->lijevo);
			printf(" %s", p->el);
			ispis(type, p->desno);
			if (p->desno != NULL)
				printf(") ");
		}
	}
	break;
	case PREORDER:
	{
		if (p != NULL)
		{
			printf(" %s", p->el);
			ispis(type, p->lijevo);
			ispis(type, p->desno);
		}
	}
	break;
	case POSTORDER:
	{
		if (p != NULL)
		{
			ispis(type, p->lijevo);
			ispis(type, p->desno);
			printf(" %s", p->el);
		}
	}
	break;
	}
	return SUCCESS;
}