#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define BUFFER 1024

typedef struct _Cvor Cvor;
typedef struct _Cvor* pozicija;

struct _Cvor {
	int elem;
	pozicija next;
};
 
int stvorimjesto(pozicija*);
int citajizdatoteke(pozicija);
int ispisilistu(pozicija);
int presjek(pozicija, pozicija, pozicija);
int unija(pozicija, pozicija, pozicija);

int main()
{
	pozicija p;

	ispisilistu(p);
}

int stvorimjesto(pozicija* p)
{
	pozicija q = NULL;

	p = (pozicija)malloc(sizeof(pozicija)*BUFFER);

	if (p = NULL)
	{
		printf("Greska, memorija nije alocirana.");
	}
	q =*p;
	q->next = NULL;

	return 0;
}

int ispisilistu(pozicija p)
{
	while (p != NULL)
	{
		printf("%d ", p->elem);

		p = p->next;
	}
	return 0;
}

int presjek(pozicija p1, pozicija p2, pozicija presjek)
{
	pozicija q = NULL;

	//dok ne dodjemo do kraja jedne ili druge liste
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->elem > p2->elem)
		{
			q->elem = p1->elem;
			p1 = p1->next;
		}
		else if (p1->elem < p2->elem)
		{
			q->elem = p2->elem;
			p2 = p2->next;
		}
		else
		{
			stvorimjesto(&q);

			q->elem = presjek->elem;

			q->next = presjek;
			presjek->next = q;
			presjek = q;

			p1 = p1->next;
			p2 = p2->next;
		}
	}

	return 0;
}

int unija(pozicija p1, pozicija p2, pozicija unija)
{
	pozicija q = NULL;
	pozicija tmp = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->elem > p2->elem)
		{
			q->elem = p1->elem;
			p1 = p1->next;
		}
		else if (p1->elem < p2->elem)
		{
			q->elem = p1->elem;
			p2 = p2->next;
		}
		else
		{
			q->elem = p1->elem;
			p1 = p1->next;
			p2 = p2->next;
		}

		// fali dio algortima ???
	}

	if (p1 != NULL)
		tmp = p1;
	else
		tmp = p2;

	while (tmp != NULL)
	{
		stvorimjesto(&q);

		q->elem = tmp->elem;

		// fali dio algortima ???

		tmp = tmp->next;
	}

	return 0;
}