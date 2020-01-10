#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define BUFFER 1024

typedef struct cvor* pozicija;

struct cvor {
	int el;
	pozicija lijevo;
	pozicija desno;
};

pozicija unos(int, pozicija);
int ispis(int, pozicija);
pozicija brisi(int, pozicija);
pozicija pronalazenje(int, pozicija);
int ispisIzbora();
pozicija minimum(pozicija);

int main()
{
	pozicija root = NULL;
	pozicija trazeni = NULL;
	int izbor = 0;
	int x = 0;

	ispisIzbora();

	while (izbor != 7)
	{
		printf("Izaberite redni broj uz radnju koju zelite obaviti:\n");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("Unesite element koji zelite unijeti:\n");
			scanf(" %d", &x);
			root = unos(x, root);
			break;
		case 2:
			ispis(2, root);
			break;
		case 3:
			ispis(3, root);
			break;
		case 4:
			ispis(4, root);
			break;
		case 5:
			printf("Unesite element koji zelite izbrisati:\n");
			scanf(" %d", &x);
			root = brisi(x, root);
			break;
		case 6:
			printf("Unesite element koji zelite pronaci:\n");
			scanf(" %d", &x);
			trazeni = pronalazenje(x, root);
			if (trazeni != NULL)
				printf("Trazeni element je pronadjen ");
			break;
		case 7:
			printf("IZLAZ IZ PROGRAMA!\n");
			break;
		case 8:
			ispisIzbora();
			break;
		}
	}

	return SUCCESS;
}

int ispisIzbora()
{
	printf("1. -unos elementa\n");
	printf("2. -preorder ispis stabla\n");
	printf("3. -inorder ispis stabla\n");
	printf("4. -postorder ispis stabla\n");
	printf("5. -brisanje elementa\n");
	printf("6. -pronalazak elementa\n");
	printf("7. -izlaz iz programa\n");
	printf("8. -ponovni ispis izbora\n");

	return SUCCESS;
}

pozicija unos(int x, pozicija p)
{
	if (p == NULL)
	{
		p = (pozicija)malloc(sizeof(struct cvor));
		
		p->el = x;
		p->lijevo = NULL;
		p->desno = NULL;
	}
	else if (p->el < x)
		p->desno = unos(x, p->desno);
	else if (p->el > x)
		p->lijevo = unos(x, p->lijevo);
	return p;
}

int ispis(int izbor, pozicija p)
{
	switch (izbor)
	{
	case 2:
	{
		if (p != NULL)
		{
			ispis(izbor, p->lijevo);
			printf("%d", p->el);
			ispis(2, p->desno);
		}
		break;
	}
	case 3:
	{
		if (p != NULL)
		{
			printf("%d", p->el);
			ispis(izbor, p->lijevo);
			ispis(izbor, p->desno);
		}
		break;
	}
	case 4:
	{
		if (p != NULL)
		{
			ispis(izbor, p->lijevo);
			ispis(izbor, p->desno);
			printf("%d", p->el);
		}
		break;
	}
	}
	return SUCCESS;
}

pozicija pronalazenje(int x, pozicija p)
{
	if (p == NULL);
	return p;

	if (p->el < x)
		return pronalazenje(x, p->desno);
	else if (p->el < x)
		return pronalazenje(x, p->lijevo);
	else
		return p;
}

pozicija brisi(int x, pozicija p)
{

	pozicija temp;
	if (p == NULL)
		return p;

	if (x < p->el)
		p->lijevo = brisi(x, p->lijevo);
	else if (x > p->el)
		p->desno = brisi(x, p->desno);
	else
	{
		// node with only one child or no child 
		if (p->lijevo == NULL)
		{
			temp = p->desno;
			free(p);
			return temp;
		}
		else if (p->desno == NULL)
		{
			temp = p->desno;
			free(p);
			return temp;
		}

		temp = minimum(p->desno);
		p->el = temp->el;
		p->desno = brisi(temp->el, p->desno);
	}
	return p;
}

pozicija minimum(pozicija p)
{
	if (p != NULL && p->lijevo != NULL)
	{
		return minimum(p->lijevo);
	}
	return p;
}