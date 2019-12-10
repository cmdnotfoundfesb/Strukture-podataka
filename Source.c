#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#define BUFFER 1024

#define SUCCESS 0
#define ERROR -1

typedef struct cvor* pozicija;
struct cvor {
	float el;
	pozicija next;
};

int push(float, pozicija);
pozicija pop(pozicija, float*);

int unosdatoteke(char*);

int racunajpostfix(char*, pozicija);

int jelioperator(char*, float*);
int kalkulator(float, float, char*, float*);

int main()
{
	struct cvor head;
	head.next = NULL;
	char* imedatoteke;

	imedatoteke = (char*)malloc(sizeof(char) * BUFFER);

	unosdatoteke(imedatoteke);

	racunajpostfix(imedatoteke, &head);

	printf("Rezultat: %f", head.next->el);

	return SUCCESS;
}

int push(float x, pozicija p)
{
	pozicija q;
	q = (pozicija)malloc(sizeof(struct cvor) * BUFFER);

	while (p->next != NULL)
		p = p->next;

	q->el = x;

	p->next = q;
	q->next = NULL;

	return SUCCESS;

}

pozicija pop(pozicija p, float* x)
{
	pozicija tmp = NULL;

	if (p == NULL)
		printf("Lista je prazna. ");


	while (p->next->next != NULL)
		p = p->next;

	*x = p->next->el;

	tmp = p->next;

	p->next = NULL;

	free(tmp);

	return SUCCESS;
}

int unosdatoteke(char* imedatoteke)
{
	printf("Unesite ime datoteke iz koje zelite procitati postfix izraz: ");
	scanf(" %s", imedatoteke);

	return SUCCESS;
}

int racunajpostfix(char* imedatoteke, pozicija p)
{
	float broj;
	float prvib, drugib;
	char* buff;
	FILE* fp = NULL;

	fp = fopen(imedatoteke, "r");

	buff = (char*)malloc(sizeof(char) * BUFFER);

	while (!feof(fp))
	{
		fscanf(fp, " %s", buff);

		if (jelioperator(buff, &broj))
		{
			pop(p, &prvib);
			pop(p, &drugib);
			kalkulator(prvib, drugib, buff, &broj);
		}

		push(broj, p);
	}

	fclose(fp);

	return SUCCESS;
}

int jelioperator(char* buff, float* x)
{
	int a;

	a = sscanf(buff, " %f", x);

	if (a == 1)
		return SUCCESS;
	else
		return ERROR;
}

int kalkulator(float a, float b, char* op, float* rez) 
{
	switch (*op)
	{
		case '+':
			*rez = a + b;
			break;
		case '-':
			*rez = a - b;
			break;
		case '*':
			*rez = a * b;
			break;
		case '/':
			*rez = a / b;
			break;
	}

	return SUCCESS;

}