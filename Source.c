#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

#define BUFFER 1024

#define error -1

#define SUCCESS 0

typedef struct Cvor *pozicija;

struct Cvor {
	int el;
	pozicija next;
};

int randomBroj(int, int);

int push(int, pozicija);

int popRed(pozicija);
int popStog(pozicija);

int ispis(pozicija);

int main()
{
	int a, b, c, d;
	int e, f, g, h;

	struct Cvor head;
	head.next = NULL;

	struct Cvor head1;
	head1.next = NULL;
	
	a = randomBroj(10, 100);
	b = randomBroj(10, 100);
	c = randomBroj(10, 100);
	d = randomBroj(10, 100);

	e = randomBroj(10, 100);
	f = randomBroj(10, 100);
	g = randomBroj(10, 100);
	h = randomBroj(10, 100);

	push(a, &head);
	push(b, &head);
	push(c, &head);
	push(d, &head);

	popStog(&head);

	ispis(&head);


	push(e, &head1);
	push(f, &head1);
	push(g, &head1);
	push(h, &head1);

	popRed(&head1);

	ispis(&head1);

	return SUCCESS;
}

int randomBroj(int dgran, int ggran)
{
	int a;

	a = rand() % (ggran - dgran + 1) + dgran;

	return a;
}

int push(int x, pozicija p)
{
	pozicija q;

	q = (pozicija)malloc(sizeof(struct Cvor)* BUFFER);

	if (q == NULL)
		return error;

	q->el = x;

	while (p->next != NULL)
		p = p->next;

	q->next = p->next;
	p->next = q;

	return SUCCESS;
}

int popStog(pozicija p)
{
	pozicija tmp = NULL;

	while (p->next->next != NULL)
		p = p->next;
	tmp = p->next;
	p->next = NULL;

	free(tmp);

	return SUCCESS;
}

int popRed(pozicija p)
{
	pozicija tmp = NULL;

	tmp = p->next;

	p->next = p->next->next;

	free(tmp);

	return SUCCESS;
}

int ispis(pozicija p)
{
	if (p == NULL)
	{
		printf("Lista je prazna.\n");
		return SUCCESS;
	}
	
	p = p->next;

	while (p != NULL)
	{
		printf("%d ", p->el);
		p = p->next;
	}

	printf("\n");

	return SUCCESS;
}

