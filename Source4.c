#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define BUFFER 1024
#define ERROR -1

typedef struct _Cvor *pozicija;
typedef struct _Cvor Cvor;

struct _Cvor {
	int eksponent;
	int koeficijent;
	pozicija next;
};

int stvorimjesto(pozicija*);
int citajizdatoteke(pozicija);
int ispisipolinom(pozicija);
int zbrojipolinome(pozicija, pozicija, pozicija);
int mnozipolinome(pozicija, pozicija, pozicija);

int main()
{
	Cvor P1, P2, suma, umnozak;
	P1.next = NULL;
	P2.next = NULL;
	suma.next = NULL;
	umnozak.next = NULL;

	citajizdatoteke(&P1);
	citajizdatoteke(&P2);

	printf("Prvi polinom: ");
	ispisipolinom(&P1);

	printf("\nDrugi polinom: ");
	ispisipolinom(&P2);

	zbrojipolinome(&P1, &P2, &suma);
	mnozipolinome(&P1, &P2, &umnozak);

	printf("Zbroj polinoma je : %d", ispisipolinom(&suma));
	printf("Umnozak polinoma je : %d", ispisipolinom(&umnozak));


	return 0;
}

int stvorimjesto(pozicija* p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Cvor)*BUFFER);

	if (q == NULL)
	{
		printf("Memorija nije alocirana.\n");
		return ERROR;
	}

	return 0;
}

int citajizdatoteke(pozicija p)
{
	pozicija q = NULL;
	pozicija tmp = NULL;
	char *imedatoteke = NULL;
	FILE *fp = NULL;

	printf("Unesite ime datoteke iz koje citate polinome: \n");
	scanf(" %s", imedatoteke);

	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
	{
		printf("Greska, datoteka nije otvorena.\n");
		return ERROR;
	}

	while (!feof(fp))
	{
		stvorimjesto(&q);

		fscanf(fp, " %d %d", &q->koeficijent, &q->eksponent);
	}

	tmp = p;

	while (tmp->next != NULL && tmp->next->eksponent > q->eksponent)
	{
		tmp = tmp->next;
	}

	if (tmp->next != NULL && tmp->next->eksponent == q->eksponent)
	{
		tmp->next->koeficijent = tmp->next->koeficijent + q->koeficijent;
		free(q);
		if (tmp->next->koeficijent == 0)
		{
			q = tmp->next;
			tmp->next = q->next;
			free(q);
		}
	}
	else
	{
		q->next = tmp->next;
		tmp->next = q;
	}
	fclose(fp);

	return 0;
}

int ispisipolinom(pozicija p)
{
	int prviclan = 1;
	while (p != NULL)
	{
		if (prviclan)
		{
			printf("%dx^%d", p->koeficijent, p->eksponent);
			prviclan = 0;
		}
		else
		{
			if (p->koeficijent > 0)
				printf(" +%dx^%d", p->koeficijent, p->eksponent);
			else
				printf(" %dx^%d", p->koeficijent, p->eksponent);
		}

		p = p->next;
	}

	return 0;
}

int zbrojipolinome(pozicija p1, pozicija p2, pozicija suma)
{
	pozicija q = NULL;
	pozicija temp = NULL;

	if (p1->next != NULL && p2->next != NULL) // polinomi mogu biti razlicitih duzina stoga provjeravamo kad je kraj jednog od ovih polinoma
	{
		stvorimjesto(&q);

		//provjeravamo koji clan polinoma ima veci eksponent
		//ako eksponenti nisu jednaki u q vezanu listu spremamo veci eksponent (if i prvi if else)
		if (p1->eksponent > p2->eksponent)
		{
			q->eksponent = p1->eksponent;
			q->koeficijent = p1->koeficijent;
		}
		else if (p1->eksponent < p2->eksponent)
		{
			q->eksponent = p2->eksponent;
			q->koeficijent = p2->koeficijent;
		}
		else if (p1->eksponent = p2->eksponent) //ako su eksponenti jedanki zbrojimo koeficijente a eksponent uzmemo iz proizvoljnog polinoma
		{
			q->eksponent = p2->eksponent;
			q->koeficijent = p1->koeficijent + p2->koeficijent;
		}
		p1 = p1->next; //prelazimo na iduci element
		p2 = p2->next;

		suma = q;
		q->next = suma->next;
		suma->next = q;



	}

	/*kada dodjemo do kraja jednog od dvaju polinoma provjeravamo kod kojeg polinoma smo dosli do kraja
	te onaj koji nije dosao do kraja unesemo u temp vezanu listu*/


	if (p1 == NULL)
		temp = p2;
	else
		temp = p1;

	while (temp->next != NULL)
	{
		stvorimjesto(&q);

		q->eksponent = temp->eksponent;
		q->koeficijent = temp->koeficijent;

		temp = temp->next;
	}

}

int mnozipolinome(pozicija p1, pozicija p2, pozicija umn)
{
	pozicija q = NULL;
	pozicija temp = NULL;
	pozicija i = NULL;
	pozicija j = NULL;

	i = p1;

	while (i != NULL)
	{
		//uzimamo prvi clan prvog polinoma i ostajemo u petlji sve dok se taj clan en izmnozi sa svim ostalim u drugom polinomu
		//kada zavrsimo s prvim na kraj while petlje stavljamo i = i->next kako bi presli na iduci, sve dok ne dodjemo do zadnjeg (NULL) elementa
		j = p2;
		while (j != NULL)
		{
			//prolazimo kroz j element tj. drugi polinom sve dok ne dodjemo do NULL
			//kada izadjemo iz while petlje j opet incijaliziramo na pocetak polinoma

			stvorimjesto(&q);

			//kada mnozimo dva polinoma eksponenti se zbrajaju a koeficijenti mnoze

			q->eksponent = i->eksponent + j->eksponent;
			q->koeficijent = i->koeficijent * j->koeficijent;

			temp = umn;

			//iduce linije koda u funkciji mnozipolinome sluze kako bi sortirali dobiveni umnozak
			//u svakoj provjeri provjerava se jesmo li dosli do kraja vezane liste

			//najprije provjeravamo ima li dobiveni polinom manji eksponent od vec dobivenog clana umnoska
			//ako ima prelazimo na iduci sve dok ne dodjemo do manjeg clana umnoska ili do kraja liste
			while (temp->next != NULL && temp->next->eksponent > q->eksponent)
				temp = temp->next;

			//ako imaju jednanke eksponente zbrojimo njihove koeficijente 
			if (temp->next != NULL && temp->next->eksponent == q->eksponent)
			{
				temp->next->koeficijent += q->koeficijent;
				free(q);

				//ako smo zbrajanjem (oduzimanjem) dobili koeficijent nula nema potrebe da ga sacuvamo pa ga brisemo iz vezane liste
				if (temp->next->koeficijent == 0)
				{
					q = temp->next;
					temp->next = q->next;

					free(q);
				}
			}
			//ako nismo naisli na zajednicki koeficijent dodamo dobiveni umnozak u konacnu vezanu listu
			else
			{
				q->next = temp->next;
				temp->next = q;
			}

			j = j->next;
		}	
		i = i->next;
	}
	return 0;
}