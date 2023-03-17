#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct tablica //tablica obliczen mnozenia pisemnego
{
	int **T;
	int wiersze, kolumny;
} Tablica;

typedef struct cyfry //ciag cyfr wymnazanych liczb, dziele liczby na cyfry
{
	int *C; //ciag cyfr
	int dlugosc; //dlugosc tablicy cyfr
}Cyfry;

Tablica wypelnij_puste(int w, int k) //tworzenie tablicy pustej o w wierszach i k kolumnach
{
	int i, j;
	Tablica r; //zwracana tablica
	r.wiersze=w; //zdefiniowanie w wyniku liczby wierszy w
	r.kolumny=k; //i liczby kolumn k
	r.T=(int**)malloc(w*sizeof(int*)); //przydzielenie pamieci w wierszy
	for(i=0;i<r.wiersze;i++) r.T[i]=(int*)malloc(k*sizeof(int)); // i k elementow w kazdym wierszu
	for(i=0;i<w;i++)
	for(j=0;j<k;j++) r.T[i][j]=-1; //wypelniam tablice -1 
	return r;
}

Cyfry wstaw_cyfre(Cyfry c, int x) //funkcja wstawiajaca kolejna wyjeta cyfre z liczby
{
	Cyfry r; //zwracany ciag cyfr
	int i;
	if(c.dlugosc==0) //jezeli lista jest pusta
	{
		r.dlugosc=1; //to okreslam dlugosc na 1
		r.C=(int*)malloc(sizeof(int)); //przydzielam pamiec
		r.C[0]=x; //i wstawiam cyfre
	} else //na liscie c juz cos jest
	{
		r.dlugosc=c.dlugosc+1; //okreslam dlugosc listy o 1 wiecej
		r.C=(int*)malloc(r.dlugosc*sizeof(int)); //przydzielam pamiec
		r.C[0]=x; //wstawiam cyfre na poczatek
		for(i=0;i<c.dlugosc;i++) r.C[i+1]=c.C[i]; //reszte kopiuje na nastepne pozycje
	}
	return r; //zwracam nowa tablice z dostawiona cyfra
}

void wypisz_tablice(Tablica t) ///Funkcja o nazwie "wypisz_tablice", która przyjmuje jeden argument typu "Tablica" o nazwie "t". Funkcja ta s³u¿y do wypisania na ekranie zawartoœci tablicy "t".
{
	int i, j, wypisac; //wypisac - zmienna pamietajaca czy byly w wierszu cyfry, jezeli tak to wypisze, jezeli nie, to znaczy ze jest pusta linia, bo nie bylo nic w pamieci
	printf("\n");
	for(i=0;i<t.wiersze;i++) //dla wszystkich wierszy 
	{
		wypisac=0; //zakladam, ze na razie nic nie ma, czyli sa same -1
		for(j=0;j<t.kolumny;j++) if(t.T[i][j]!=-1) wypisac=1; //znalazlem cos do wypisania, wiec bede to pisal
		if(wypisac)
		{
			for(j=0;j<t.kolumny;j++) //dla kolumn w danym wierszu 
		    {  
			  if(t.T[i][j]==-1) printf(" "); //jezeli jest -1, to wypisz spacje
			  else if(t.T[i][j]==-2) printf("*"); //jezeli jest -2, to wypisz znak mnozenia
			  else if(t.T[i][j]==-3) printf("+"); //jezeli jest -3, to wypisz znak dodawania
			  else if(t.T[i][j]==-4) printf("-"); //jezeli jest -4, to wypisz kreske, podkreslenie 
			  else printf("%d", t.T[i][j]); //wypisz cyfre, czyli wszystko co sie obliczylo
		    }
		    	printf("\n");
		}
	}
	printf("\n");
}

Cyfry int_to_cyfry(int x) //funkcja wyciagajaca cyfry liczby do tablicy
{
	int reszta;
	Cyfry r; //zwracana tablica
	r.dlugosc=0; //na poczatku ma dlugosc 0
	r.C=NULL; //i jest pusta
	while(x>0) //dopoki liczba jest dodatnia
	{
		reszta=x%10; //obliczam reszte z dzielenia przez 10, czyli osatnia cyfre
		r=wstaw_cyfre(r, reszta); //wstawiam ja do tablicy cyfr
		x=x-reszta; //odejmuje reszte od liczby, wiec na koncu jest 0
		x=x/10; //dziele liczbe przez 10, wiec usuwam ostatnie 0 i powracam do nastepnego przebiegu petli, wiek kolejno wyciagam cyfry z liczby
	}
	return r; //zwracam tablice cyfr
}


Tablica mnozenie(Cyfry pierwsza, Cyfry druga)
{
    Tablica r;
	int i, j, nr, nr1, nr2, pamiec, iloczyn, reszta; //nr1, nr2 numery wierszy gdzie sa cyfry liczb do wymnozenia, nr to numer kolumny od ktorego znajduje sie wypisywanie wyniku mnozenia 
	int wiersz_pamiec, kolumna_pamiec, wiersz_obliczenia, kolumna_obliczenia, nrwp, nrkp, nrwo, nrko;
	//wiersz_pamiec, kolumna_pamiec - wiersz lub kolumna gdzie beda zapisywane liczby z pamieci, czyli przekroczono 9
	//wiersz_obliczenia, kolumna obliczenia - aktualna cyfra, ktora jest "widziana" do obliczen	
	//nrwp, nrkp, nrwo, nrko; numery wierszy kolumn w pamieci i w obliczeniach
    r=wypelnij_puste(2*druga.dlugosc+5, pierwsza.dlugosc+druga.dlugosc+2); //wypelnienie tablicy samymi -1, czyli jest pusta
    nr1=druga.dlugosc; //polozenie pierwszej liczby do wymnozenia, numer wiersza 
	nr2=nr1+1; //polozenie drugiej liczby do wymnozenia
	nr=r.kolumny-1; //zaczynam od prawej strony wypelniac
	for(i=pierwsza.dlugosc-1;i>=0;i--)
	{
		r.T[nr1][nr]=pierwsza.C[i]; //wpisanie cyfr pierwszej liczby
		nr--;
	}
	nr=r.kolumny-1;
	for(i=druga.dlugosc-1;i>=0;i--)
	{
		r.T[nr2][nr]=druga.C[i]; //wpisanie cyfr drugiej liczby
		nr--;
	}
	r.T[nr2][2]=-2; //znak mnozenia
	r.T[r.wiersze-3][0]=-3; //znak dodawania
	nr=r.kolumny-1;
	for(i=pierwsza.dlugosc+1;i>=0;i--)
	{
		r.T[nr2+1][nr]=-4; //kreski po obu liczbach
		nr--;
	}
	for(i=r.kolumny-1;i>-1;i--)
	{
		r.T[r.wiersze-2][i]=-4; //kreski z dodawaniem
	
	}
	//tutaj zaczynam mnozyc
	pamiec=0; //pamiec jest zerowa na poczatku
	wiersz_pamiec=nr1-1; //zapamietuje wiersz pamieci, potem bede pisac coraz wyzej , powyzej liczby pierwszej
	kolumna_pamiec=r.kolumny-2; //zapamietanie kolumny pamieci ,druga kolumna od konca tablicy
	wiersz_obliczenia=nr2+2; //nr wiersza do obliczen, czyli mnozenia, dwa wiersze ponizej liczby drugiej
	kolumna_obliczenia=r.kolumny-1; //numer kolumny gdzie zaczynam mnozyc, ostatnia kolumna 
	for(i=druga.dlugosc-1;i>=0;i--) //petla zagniezdzona mnozenia, mnozenie kazdej cyfry z liczby drugiej przez kazda cyfre z liczby pierwszej
	{
		nrwo=wiersz_obliczenia; //nr wieersza obliczen i kolumny obliczen, tam bede wpisywac wynik
		nrko=kolumna_obliczenia;
		nrwp=wiersz_pamiec; //tak samo z pamiecia
	    nrkp=kolumna_pamiec;
		for(j=pierwsza.dlugosc-1;j>=0;j--) //wymnazam wszystkie cyfry z pierwszej liczby przez aktualnie rozwazana cyfre z liczby drugiej 
		{
			iloczyn=druga.C[i]*pierwsza.C[j]+pamiec; //przez cyfre z drugiej od prawej strony, czyli iloczyn cyfr + pamiec
			//przeniesienia
			if(iloczyn>=10) //jezeli wynik jest wiekszy od 9
			{
				reszta=iloczyn%10; //biore reszte z dzielenia przez 10 np. 3x4=12 reszta 2 
				pamiec=iloczyn/10; //do pamieci trafia pierwsza cyfra z iloczynu 3x4=12 do pamieci 1
				r.T[nrwo][nrko]=reszta; //wpisuje reszte do komorki mnozen
				r.T[nrwp][nrkp]=pamiec; //a do wiersza pamieci zawartosci pamieci
			} else 
			{
				r.T[nrwo][nrko]=iloczyn; //do komorki wpisuje iloczyn
				pamiec=0; //zeruje pamiec
			}
			nrko--; //zmniejszam kolumne obliczen i pamieci o 1, bo przesuwam sie w lewo
			nrkp--;
		}
		if(pamiec>0) //jezeli pamiec cos zachowala
		{
			r.T[nrwo][nrko]=pamiec; //to do wiersza obliczen wpisuje pamiec
			pamiec=0; //i ja zeruje, poniewaz przeliczylem mnozenie przez jedna cyfre
		}
		wiersz_obliczenia++; //przesuwam sie z wierszem obliczen na nastepny
		kolumna_obliczenia--; //kolumne o 1 mniej, bo przesuniece w lewo
		wiersz_pamiec--; //wiersz pamieci przesuwam do gory czyli o 1 mniej
//		kolumna_pamiec--; //kolumna pamieci przesuwa sie o 1 w lewo
	}
	//tutaj dodaje wyniki mnozenia, czyli dodawanie pisemne
	int dodano;  //zmianna pamietajaca czy dodano cokolwiek, czyli byly cyfry, a nie same puste pola czyli -1
	int suma; //suma cyfr w kolumnie juz po mnozeniu
	for(j=r.kolumny-1;j>=0;j--) //dla wszystkich kolumn
	{
		suma=0; //zakladam, ze suma jest 0
		dodano=0; //i zakladam ze nic nie dodano
		for(i=0;i<druga.dlugosc;i++)
		{
			if(r.T[nr2+2+i][j]>-1) //jezeli komorka niepusta, czyli cos tam sie pojawilo z obliczen
			{
				suma=suma+r.T[nr2+2+i][j]; //to dodaje do sumy
				dodano=1; //i zapamietuje ze cos dodano
			}
		}
		if(dodano) //jezeli dodano
		{
			suma=suma+pamiec; //to dodaje zawartosc pamieci
			if(suma>=10) //jezeli suma jest wieksza od 9
			{
				reszta=suma%10; //licze reszte
				r.T[r.wiersze-1][j]=reszta; //wpisuje jako wynik dodawania pisemnego w danej kolumnie
				suma=suma-reszta; //odejmuje reszte
				pamiec=suma/10; //i do pamieci trafia cyfra dziesiatek po dadawaniu
			} else
			{ //suma byla jednocyfrowa
				r.T[r.wiersze-1][j]=suma; //to ja wpisuje
				pamiec=0; //zeruje pamiec
			}
		}
	}
	return r;
}

int main()
{
	int a, b, temp; //a, b liczby wejsciowe, temp do zamiany, tak aby pierwsza byla wieksza
	Cyfry ca, cb; //listy cyfr liczb a i b
	Tablica tx; //tablica obliczen
	ca.dlugosc=0; //na poczatku listy cyfr sa puste
	cb.dlugosc=0;
	ca.C=NULL;
	cb.C=NULL;
		printf("Mnozenie pisemne\n");
	do
	{ //wczytuje tak dlugo dopoki przynajmniej jedna liczba jest niedodatnia
	  printf("a = "); // petla do while, wpisanie cyfry a i b, jezeli cyfra jest ujemna lub jest zerem wypisuje blad 
	  scanf("%d",&a);
	  printf("b = ");
	  scanf("%d",&b);	
	  if(a<=0 || b<=0) printf("Liczby musza byc dodatnie \n");
	}while(a<=0 || b<=0 );
	if(a<b) //jezeli pierwsza liczba jest mniejsza od drugiej zamieniam je miejscami
	{
		temp=a;
		a=b;
		b=temp;
	}
	ca=int_to_cyfry(a); //wyjecie cyfr z pierwszej liczby
	cb=int_to_cyfry(b); //rowniez z drugiej
	tx=mnozenie(ca, cb); //wykonanie mnozenia pisemnego
	wypisz_tablice(tx); //wypisanie liczb
	return 0;
}
