#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <windows.h>
#define N 10
#define ILE 1
using namespace std;


int tab[N];

void poka_ta_tablice(int pomoc)
{
            if(pomoc == 1)
                cout << "Tablica przed sortowaniem: \n";
            else
                cout << "Tablica po sortowaniu: \n";
            for(int i = 0 ; i< N ; i++)
            {
            cout<< tab[i] << "  ";
            }
            cout<<"\n";
}

void lacz(int poczatek, int srodek, int koniec,int t[])
{
    int i,q,_srodek;
    for(i = poczatek; i <= koniec; i++)
        t[i] = tab[i];
    i = poczatek;
    _srodek = srodek + 1;
    q = poczatek;
    while(i <= srodek && _srodek<= koniec)
    {
        if(t[i] < t[_srodek])
            tab[q++] = t[i++];
        else
            tab[q++] = t[_srodek++];
    }
    while(i <= srodek)
        tab[q++] = t[i++];
}

void sortuj_scalanie(int poczatek, int koniec,int t[])
{
    int srodek;
    if(poczatek < koniec)
    {
        srodek = (poczatek + koniec) / 2;
        sortuj_scalanie(poczatek,srodek,t);
        sortuj_scalanie(srodek+1,koniec,t);
        lacz(poczatek,srodek,koniec,t);
    }
}

void sortowanie_przez_scalanie()
{
    int t[N];

    sortuj_scalanie(0,N-1,t);
    //poka_ta_tablice(2);
}

//////////////////////////////////////////////////
////////////// quicksort

void zamien(int indeks_1, int indeks_2)
{
    int pomoc = tab[indeks_1];
    tab[indeks_1] = tab[indeks_2];
    tab[indeks_2] = pomoc;
}

int szukaj_podzialu(int poczatek, int koniec)
{
    int i = poczatek, pivot = tab[koniec], w;

    for(int j = poczatek; j < koniec; ++j)
    {
        if(tab[j] <= pivot)
        {
            w = tab[j];
            tab[j] = tab[i];
            tab[i] = w;
            i++;
        }
    }
    tab[koniec] = tab[i];
    tab[i] = pivot;
    //cout << "POKA TO " << i << endl;
    return i;

}

void sortowanie_szybkie(int poczatek, int koniec)
{
    int podzialka;

        if(poczatek < koniec)
        {
            podzialka = szukaj_podzialu(poczatek,koniec);
            sortowanie_szybkie(poczatek,podzialka - 1);
            sortowanie_szybkie(podzialka+1,koniec);
        }
}
void max_kopiec(int rozmiar, int indeks_rodzica)
{
    int maxIndex = indeks_rodzica;
    int lewa = maxIndex *2 +1;
    int prawa = maxIndex * 2 +2;

    if( lewa < rozmiar && tab[lewa] > tab[maxIndex])
    {
        maxIndex = lewa;
    }
    if(prawa < rozmiar && tab[prawa] > tab[maxIndex])
    {
        maxIndex = prawa;
    }
    if(maxIndex != indeks_rodzica)
    {
       zamien(maxIndex,indeks_rodzica);
       max_kopiec(rozmiar,maxIndex);
    }
}

void sortowanie_przez_kopcowanie(int poczatek, int koniec)
{
     int n = koniec;
    for(int i = koniec/2 - 1; i>=poczatek; i--)
    {
        max_kopiec(koniec,i);
    }

    for(int j = koniec-1; j>poczatek; j--)
    {
        zamien(poczatek,j);
        max_kopiec(--n,poczatek);
    }
}

void introsort(int _zlozonosc, int _rozmiar,int poczatek, int koniec)
{

    int n = _rozmiar;
    if(n <= 1)
        return;
    else
        if(_zlozonosc == 0)
        sortowanie_przez_kopcowanie(poczatek,koniec);
    else
    {
        int p = szukaj_podzialu(poczatek,koniec);
        int pomoc1 = p - poczatek;
        int pomoc2 = koniec - p+1;
        introsort(_zlozonosc-1,pomoc1,0,p);
        introsort(_zlozonosc-1,pomoc2,p+1,koniec);
    }
}

void sortowanie_introspektywne(int _rozmiar)
{
    int rozmiar = _rozmiar;
    int zlozonosc = log(rozmiar)*2;
    introsort(zlozonosc,rozmiar,0,rozmiar-1);
}

void wypelnij_tabelke()
{
    //srand( time( NULL ) );
    for(int i=0 ; i< N ; i++)
    {
        tab[i] = rand()%999+1;
    }
}

void wypelnij_tabelke_odwrotnie_posortowana()
{
   int pomoc = N+1;
   for(int i=0 ; i< N ; i++)
    {
        tab[i] = pomoc;
        --pomoc;
    }
}

void wypelnij_tabelke_procenty(int procent)
{
    int pomoc = N * procent / 100;
    int pomoc1 = N+1;
    int j = 1;
    for(int i=0 ; i< pomoc ; i++)
    {
        tab[i] = j;
        j++;
    }

    for(int i=pomoc ; i< N ; i++)
    {
        tab[i] = rand()%pomoc1;
    }
}

int main()
{
    srand( time( NULL ) );
    cout.setf(ios::fixed);
    cout.precision(5);
    clock_t czas_poczatek1,czas_koniec1;
    double wynik1 = 0,roznica1,wynik2 = 0,wynik3 = 0;
    int wybor;
    do
    {
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"   KOMUNIKATOR SORTOWANIA "<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"1. Sortowanie przez scalanie (merge sort)"<<endl;
    cout<<"2. Sortowanie szybkie (quick sort)"<<endl;
    cout<<"3. Sortowanie introspektywne (introspective sort)"<<endl;
    cout<<"4. EXIT (zakonczy ten program)"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"   WYBOR: ";
    cin>>wybor;
    cout<<endl;

    switch(wybor)
    {
        case 1:
            for(int i = 0 ; i<ILE; i++)
            {
                wypelnij_tabelke();
                poka_ta_tablice(1);
                //wypelnij_tabelke_odwrotnie_posortowana();
                //wypelnij_tabelke_procenty(50);
                czas_poczatek1 = clock();
                sortowanie_przez_scalanie();
                czas_koniec1 = clock();
                roznica1 = (czas_koniec1 - czas_poczatek1)/(double)CLOCKS_PER_SEC;
                wynik1 += roznica1;
                poka_ta_tablice(2);
            }
            break;
        case 2:
            {
            for(int i = 0 ; i<ILE; i++)
            {
            wypelnij_tabelke();
            //wypelnij_tabelke_odwrotnie_posortowana();
            //wypelnij_tabelke_procenty(50);
            poka_ta_tablice(1);
            czas_poczatek1 = clock();
            sortowanie_szybkie(0, N-1);
            czas_koniec1 = clock();
            roznica1 = (czas_koniec1 - czas_poczatek1)/(double)CLOCKS_PER_SEC;
            wynik2 += roznica1;
            poka_ta_tablice(2);
            }
            }
             break;
        case 3:
            for(int i = 0 ; i<ILE; i++)
            {
            wypelnij_tabelke();
            //wypelnij_tabelke_odwrotnie_posortowana();
            //wypelnij_tabelke_procenty(50);
            poka_ta_tablice(1);
            czas_poczatek1 = clock();
            sortowanie_introspektywne(N);
            czas_koniec1 = clock();
            roznica1 = (czas_koniec1 - czas_poczatek1)/(double)CLOCKS_PER_SEC;
            wynik3 += roznica1;
            poka_ta_tablice(2);
            }
            break;
        case 4: break;
        case 5: break;
        default:
            ; break;
    }

    }while (wybor!=4);
    cout<< " PODSUMOWANIE" << endl;
    cout<< "WYNIK 1 : " << wynik1<< endl;
    cout<< "WYNIK 2 : " << wynik2<< endl;
    cout<< "WYNIK 3 : " << wynik3<< endl;
    return 0;
}
