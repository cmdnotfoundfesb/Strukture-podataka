#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VELICINATABLICE 11

#define ERROR -1
#define SUCCESS 0
#define TRUE 1

typedef struct _student* pozicija;
typedef struct _student {
	char* kljuc;
	char* ime;
	char* prezime;
	int mb;
	pozicija next;
}_student;

typedef struct {
	_student** studenti;
}tablica;

int hash(char*); //funkcija za pridjeljivanje kljuca

tablica* stvoritablicu();//funkicja za stvaranje hash tablice 

int set(tablica*, char*, char*, char*, int); // funkcija za upisivanje vrijednosti u tablicu

_student* unos(char*, char*, char*, int); //alocira potrebnu memoriju i unosi zeljene vrijednosti 

char* get(tablica*, char*); //dohvaca mjesto ("kljuc")studenta

int ispistablice(tablica*);

int main()
{
	tablica* ht = stvoritablicu();

	set(ht, "prvi", "marko", "bwalic", 1662018);
	set(ht, "drugi", "ivan", "bilic", 4452018);
	set(ht, "treci", "ante", "matic", 2832018);

	ispistablice(ht);
}

int hash(char* prezime)
{
	int kljuc = 0;
	int i;

	for (int i = 0; i < 5; i++)
	{
		kljuc = kljuc + prezime[i];
	}

	kljuc = kljuc % VELICINATABLICE;

	return kljuc;
}

tablica* stvoritablicu()
{
	tablica* hashtable;

	hashtable = (tablica*)malloc(sizeof(tablica));
	if (hashtable == NULL)
	{
		printf("Doslo je do pogreske pri alociranju memorije");
		return ERROR;
	}

	hashtable->studenti = (_student**)malloc(sizeof(_student*) * VELICINATABLICE);


	//inicijalizacija svakog studenta tablice na NULL, *(za pretrazivanje)
	for (int i = 0; i < VELICINATABLICE; i++)
	{
		hashtable->studenti[i] = NULL;
	}

	return hashtable;
}

int set(tablica* hashtable, char* kljuc, char* ime, char* prezime, int mb)
{
	int mjesto;
	_student* student;

	mjesto = hash(prezime);

	student = hashtable->studenti[mjesto];

	if (student == NULL)
	{
		hashtable->studenti[mjesto] = unos(kljuc, prezime, ime, mb);
		return SUCCESS;
	}

	_student* pret;

	pret = malloc(sizeof(student));

	while (student != NULL)
	{
		if (strcmp(student->prezime, prezime) == 0)
		{
			free(student->kljuc);
			student->kljuc = malloc(strlen(kljuc));
			strncpy(student->kljuc, kljuc, strlen(kljuc));
			return SUCCESS;
		}
		pret = student;
		student = pret->next;
	}

	pret->next = unos(kljuc, prezime, ime, mb);
}

_student* unos(char* kljuc, char* prezime, char* ime, int mb)
{
	_student* student = malloc(sizeof(student));
	if (student == NULL)
	{
		printf("Doslo je do pogreske pir alociranju memorije.\n");
		return ERROR;
	}
	student->kljuc = malloc(strlen(kljuc)+1);
	student->ime = malloc(strlen(ime)+1);
	student->prezime = malloc(strlen(prezime)+1);
	student->mb = malloc(sizeof(int));

	strcpy(student->kljuc, kljuc);
	strcpy(student->ime, ime);
	strcpy(student->prezime, prezime);

	student->mb = mb;

	student->next = NULL;

	return student;
}

char* get(tablica* hashtable, char* prezime)
{
	int mjesto = hash(prezime);

	_student* student = hashtable->studenti[mjesto];

	while (student != NULL)
	{
		if (strcmp(student->prezime, prezime) == 0)
			return student->kljuc;

		student = student->next;
	}

	return NULL;
}

int ispistablice(tablica* hashtable)
{
	for (int i = 0; i <= VELICINATABLICE; ++i)
	{
		_student* student = hashtable->studenti[i];

		if (student == NULL)
			continue;

		printf("mjesto[%d], ", i);

		for(;;)
		{
			printf("kljuc: %s => %s, %s, maticni broj: %d\n", student->kljuc, student->prezime, student->ime, student->mb);

			if (student->next == NULL)
				break;

			student = student->next;
		}

		printf("\n");
	}

	return SUCCESS;
}