/*
Zadanie 2.
Dla zadanej tablicy liczb całkowitych, wypisz wszystkie podtablice, których suma wynosi 0.

Przykład.
Wejście: [3, 4, -7, 3, 1, 3, 1, -4, -2, -2]
    Wyjście:
    Istnieją podtablice, których suma wynosi 0.
    Tablice te to:
    [3,4,-7]
    [4,-7,3]
    [-7,3,1,3]
    [3,1,-4]
    [3,1,3,1,-4,-2,-2]
    [3,4,-7,3,1,3,1,-4,-2,-2]
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;


void wypisz(int T[],int p,int q){
    cout<<"[ ";
    for(int i=p;i<=q-1;i++)
        cout << T[i]<< ", ";
    cout << T[q]<<" ]"<<endl;

}  //funkcja wypisująca podtablice, których suma wynosi 0

void zapisz(int T[],int p,int q,fstream &plik){
    plik<<"[ ";
    for(int i=p;i<=q-1;i++)
        plik << T[i]<< ", ";
    plik << T[q]<<" ]"<<endl;

}  //funkcja zapisujaca podtablice [T[p],T[p+1]....T[q]] do pliku

bool czy_sie_powtarza(int T[],int poczatek,int koniec){
    int n=koniec-poczatek+1;        //długość podtablicy
    for(int i=0;i<poczatek;i++){    //sprawdzamy, czy podtablica o długości n zaczynająca się w T[i] jest taka sama jak tablica o długości n zaczynająca się w T[poczatek]
            int j=0;
        while(T[i+j]==T[poczatek+j]&&j<n)
            j++;
        if(j==n)
            return true;
    }
    return false;
}   //funkcja sprawdzająca, czy dana podtablica wystąpiła więcej niż jeden raz

void szukaj(int T[],int n, fstream &plik)
{
    bool czy_istnieje=0;    //zmienna sprawdzajacaa czy funkcja znalazla podtablice o sumie 0
    for(int i=0;i<n;i++)
    {
        int S=0;            //suma podtablicy
        for(int j=i;j<n;j++)
        {
            S+=T[j];
            if(S==0&&czy_sie_powtarza(T,i,j)==0)    //wypisujemy podtablice, gdy jej suma wynosi 0 i nie wypisalismy wczesniej identycznej podtablicy
            {
                    if(czy_istnieje==0)
                    {
                        cout<<"Istnieja podtablice, ktorych suma wynosi 0.\nTablice te to:"<<endl;
                        plik<<"Istnieja podtablice, ktorych suma wynosi 0.\nTablice te to:"<<endl;


                        czy_istnieje=1;
                    }
                    wypisz(T,i,j);
                    zapisz(T,i,j,plik);

            }
        }
    }
    if(czy_istnieje==0)
    {
        cout<<"Brak podtablic, ktorych suma wynosi 0.";
        plik<<"Brak podtablic, ktorych suma wynosi 0.";
    }
}   //funkcja znajdujaca podtablice, ktorych suma wyrazow to 0
void test(int n, int wmin, int wmax, fstream &plik)
{
    srand(time(NULL));
    int T[n];
    for(int i=0;i<n;i++)
        T[i]=rand()%(wmax-wmin+1)+wmin;
    cout<<"    #### TEST ####\n";
    cout<<"Wygenerowana podtablica to: \n";
    wypisz(T,0,n-1);
    szukaj(T,n,plik);
    cout<<"    #### TEST ####\n\n";

}   //funkcja generujaca losowo tablice T[n], sluzy do wykonywania testow na duzych danych

int main()
{
    fstream plik;
    plik.open("Dane.txt",ios::out);
    test(10,-5,5,plik);
    int n,tryb;
    cout<<"W jaki sposob chcesz wprowadzic dane?\n1. Z pliku\n2. Z konsoli\nWybierz 1 lub 2: ";
    cin>>tryb;
    int *T;
    switch(tryb)
    {
        case 1:
            {
            fstream dane;
            dane.open("Dane_wejsciowe.txt",ios::in);
            dane>>n;
            T=new int[n];
            for(int i=0;i<n;i++)
                dane>>T[i];
            dane.close();
            break;
            }
        case 2:
            {
            cout<<"Ile tablica ma miec znakow? ";
            string tmp;
            stringstream ss;
            cin>>tmp;
            ss<<tmp;
            if(!(ss>>n))
            {
                cout<<"Podano niewlasciwy typ danych"<<endl;
                plik.close();
                return 1;

            }
            ss.clear();
            T=new int[n];
            for(int i=0; i<n; i++)
            {
                int a; //zmienna pomocnicza
                cout<<"Podaj "<<i+1<<" liczbe: ";
                cin>>tmp;
                ss<<tmp;
                if(!(ss>>a))
                {
                    cout<<"Podano niewlasciwy typ danych"<<endl;
                    plik.close();
                    return 1;
                }
                 T[i]=a;
                ss.clear();
            }
            break;
            }
        default:
            cout<<"Blad!";
            plik.close();
            return 404;
    }
    cout<<"Zadana tablica: ";
    plik<<"Zadana tablica: ";
    wypisz(T,0,n-1);
    zapisz(T,0,n-1,plik);
    szukaj(T,n,plik);
    plik.close();
    delete[] T;
    cout<<endl;
    return 0;
}
