#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>

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
	pozicija L1 = NULL, L2 = NULL, pres = NULL, un = NULL;

	citajizdatoteke(L1);
	citajizdatoteke(L2);

	printf("Prva lista:\n");
	ispisilistu(L1);
	printf("Druga lista:\n");
	ispisilistu(L2);

	presjek(L1, L2, pres);
	printf("Presjek dviju lista:\n");
	ispisilistu(pres);

	unija(L1, L2, un);
	printf("Unija dviju lista:\n");
	ispisilistu(un);

	return 0;

}

int stvorimjesto(pozicija* p)
{
	pozicija q = NULL;

	p = (pozicija*)malloc(sizeof(pozicija*)*BUFFER);

	if (p = NULL)
	{
		printf("Greska, memorija nije alocirana.");
	}
	q = *p;
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

		if (unija->elem == q->elem)
			free(q);
		else
		{
			q->next = unija->next;
			unija->next = q;
			unija = q;
		}
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
