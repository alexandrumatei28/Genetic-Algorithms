#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int x,n,c1,c2,a,b,c,precizia,nrGeneratii;
double l, d2,random;
float probIncrucisare, probMutatie;
vector<string> cromozomi;
vector<double> X;
vector<double> f;
vector<double> maxime;
vector<double> means;
vector <double> bestX;


void incrucisare2(string& x0, string& x1, int poz)
{

    string aux(x0.size(),' ');

    for(int j=0; j<poz; j++)
    {
        aux[j]=x0[j];
    }

    for(int j=0; j<poz; j++)
    {
        x0[j]=x1[j];
    }


    for(int j=0; j<poz; j++)
    {
        x1[j]=aux[j];
    }


}

string binar(int numar)
{
    string binar = "";
    bool gasitUnu = false;
    for (int i = 31; i >= 0; --i)
    {
        if ((numar >> i) & 1)
        {
            gasitUnu = true;
        }

        if (gasitUnu)
        {
            binar += ((numar >> i) & 1) ? '1' : '0';
        }

    }

    if (!gasitUnu)
    {
        binar = "0";
    }

    return binar;
}


void TO(double x)
{

    int z=1;
    while ( c1+z*d2 < x )
    {
        //cout<<c1+z*d<<endl;
        z++;
    }
    //cout<<z<<" ";
    int rez;
    if (c1+z*d2 == x)
        rez = z;
    else
        rez = z-1;

    string rezstring = binar(rez);
    int len = rezstring.length();

    while (len < l)
    {
        rezstring.insert(0, "0");
        len++;
    }

    cromozomi.push_back(rezstring);

}


void FROM(string cmz, int j)
{
    int rez = stoi(cmz,0,2);
    double x = c1 + rez*d2;
    X[j]=x;
    double r= x*x*a + x*b + c;
    f[j]=r;
}


int main()
{
    ifstream fin("date.in");

    //cout<<"Numarul de cromozomi: ";
    fin>>n;
    //cout<<"Domeniul de definitie: ";
    fin>>c1>>c2;
    //cout<<"Parametrii pentru functia de maximizat: ";
    fin>>a>>b>>c;
    //cout<<"Precizia: ";
    fin>>precizia;
    //cout<<"Probabilitatea de incrucisare (crossover): ";
    fin>>probIncrucisare;
    //cout<<"Probabilitatea de mutatie: ";
    fin>>probMutatie;
    //cout<<"Numarul de generatii: ";
    fin>>nrGeneratii;

    //PT RANDOM
    srand(time(nullptr));

    // FORMULA CODIFICARE
    double fl = log2((c2-c1)*pow(10,precizia));
    l = ceil(fl);
    d2 = (c2-c1)/pow(2,l);

    double x;
    for(int i=1; i<= n ; i++)
    {
        x = static_cast<double>(rand() % (RAND_MAX + 1)) / RAND_MAX;
        X.push_back(x);
        TO(x);
        //cout<<"x: "<<x<<endl;
    }


    //Calculez fitnessul pt fiecare cromozom
    for(double x : X)
    {
        double rez;
        rez= x*x*a + x*b + c;
        f.push_back(rez);
    }


    cout<<"Populatia initiala"<<endl;
    int i;
    for( i=0; i<n; i++)
    {
        cout<<i+1<<": "<<cromozomi[i]<<" x= "<<X[i]<<" f= "<<f[i]<<endl;
    }


    // DE AICI INCEP GENERATIILE URMATOARE
    for(int e=0; e<nrGeneratii; e++)
    {

        double F=0;
        for(double fit : f)
        {
            F=F+fit;
        }

        // cout<<"Fitnessul total: "<<F<<endl;

        //PROBABILITATI SELECTIE


        vector<double> prob_selectie;
        for(double fit : f)
        {
            double sel;
            sel = fit/F;
            prob_selectie.push_back(sel);
        }

        if(e==0)
        {
            cout<<endl<<"Probabilitati selectie:"<<endl;
            for(int i=0; i<n; i++)
            {
                cout<<"cromozom "<<i+1<<" probabilitate "<<prob_selectie[i]<<endl;
            }
        }


        //INTERVALE SELECTIE

        double s=0;
        vector<double> intervale_sel;
        intervale_sel.push_back(0);

        for(double ps : prob_selectie)
        {
            s=s+ps;
            intervale_sel.push_back(s);
        }

        if(e==0)
        {
            cout<<endl<<"Intervale probabilitati selectie: "<<endl;
            for(double in : intervale_sel)
            {
                cout<<in<<" ";
            }
            cout<<endl;
        }

        int interval;
        i=1;

        vector<int> selectati;
        double u;

        for(int j=0; j<n; j++)
        {
            u = static_cast<double>(rand() % (RAND_MAX + 1)) / RAND_MAX;
            if(e==0)
                cout<<"u= "<<u<<" ";
            while(u >= intervale_sel[i])
            {
                interval=i;
                i++;
            }
            if(e==0)
                cout<<"selectam cromozomul "<<interval+1<<endl;
            selectati.push_back(interval+1);
            i=1;
        }

        //inlocuiesc generatia initiala cu cei selectati
        vector<string> copy_string;
        vector<double> copy_X;
        vector<double> copy_f;
        for(int h : selectati)
        {
            copy_string.push_back(cromozomi[h-1]);
            copy_X.push_back(X[h-1]);
            copy_f.push_back(f[h-1]);
        }


        for(int i=0; i<n; i++)
        {
            cromozomi[i]=copy_string[i];
            X[i]=copy_X[i];
            f[i]=copy_f[i];
        }



        //DUPA SELECTIE
        if(e==0)
        {

            cout<<endl<<"Dupa selectie:"<<endl;
            for(int i=0; i<n; i++)
            {

                cout<<i+1<<":"<<cromozomi[i]<<" x= "<<X[i]<<" f= "<<f[i]<<endl;
            }
        }

        //PROBABILITATEA DE INCRUCISARE

        vector<string> incrucisare;
        vector<int> indici;

        if(e==0)
            cout<<endl<<"Probabilitatea de incrucisare 0.25"<<endl;
        for(i=0; i<n; i++)
        {
            u = static_cast<double>(rand() % (RAND_MAX + 1)) / RAND_MAX;
            if(u<0.25)
            {
                if(e==0)
                    cout<<i+1<<": "<<cromozomi[i]<<" u="<<u<<"<0.25 participa"<<endl;
                incrucisare.push_back(cromozomi[i]);
                indici.push_back(i+1);
            }
            else if(e==0)
            {
                cout<<i+1<<": "<<cromozomi[i]<<" u="<<u<<endl;
            }
        }


        int ind1,ind2,d;
        d=incrucisare.size()/2;
        vector<bool> vizInd(incrucisare.size(),false);


        for(i=0; i<d; i++)
        {
            ind1=rand() % incrucisare.size();

            while (vizInd[ind1] == true)
            {

                ind1=rand() % incrucisare.size();
            }

            vizInd[ind1] = true;



            ind2=rand() % incrucisare.size();

            while (vizInd[ind2] == true)
            {
                ind2=rand() % incrucisare.size();;
            }

            vizInd[ind2] = true;

            string loc1=cromozomi[indici[ind1]-1], loc2= cromozomi[indici[ind2]-1];
            string &cr1=cromozomi[indici[ind1]-1], &cr2= cromozomi[indici[ind2]-1];
            int punct = rand() % cr1.size();;

            incrucisare2(cr1,cr2,punct);

            if(e==0)
            {

                cout<<"Recombinare dintre cromozomul "<<indici[ind1]<<" cu cromozomul "<<indici[ind2]<<": "<<endl;
                cout<<loc1<<" "<<loc2<<" "<<"punct "<< punct<<endl;
                cout<<"Rezultat "<<cr1<<" "<<cr2<<endl;
            }


        }


        //DUPA RECOMBINARE

        //transform din binar in nr real
        // ADICA AFLU X-urile si aflu si fitness-urile


        for(int i=0; i<n; i++)
        {
            FROM(cromozomi[i],i);
        }

        if(e==0)
        {
            cout<<endl<<"Dupa recombinare: "<<endl;
            for(int i=0; i<n; i++)
            {

                cout<<i+1<<":"<<cromozomi[i]<<" x= "<<X[i]<<" f= "<<f[i]<<endl;
            }
        }

        if(e==0)
        {
            cout<<endl<<"Probabilitate de mutatie pentru fiecare gena "<<probMutatie<<endl;
            cout<<"Au fost modificati cromozomii: "<<endl;
        }


        int OK=0;
        for(int i=0; i<n; i++)
        {

            for(int k=0; k<cromozomi[i].size(); k++)
            {
                random = static_cast<double>(rand() % (RAND_MAX + 1)) / RAND_MAX;
                if(random < probMutatie)
                {
                    if(cromozomi[i][k] == '0')
                        cromozomi[i][k] = '1';
                    else
                        cromozomi[i][k] = '0';

                    OK=1;
                }

            }

            if(OK)
            {
                if(e==0)
                    cout<<i+1<<endl;
                //cout<<cromozomi[i]<<endl<<endl;
                OK=0;
                FROM(cromozomi[i],i);

            }
        }



        //DUPA MUTATIE
        if(e==0)
        {
            cout<<"Dupa mutatie: "<<endl;
            //i=0;
            for(int i=0; i<n; i++)
            {
                cout<<i+1<<":"<<cromozomi[i]<<" x= "<<X[i]<<" f= "<<f[i]<<endl;
            }
        }

        double maxim=0;
        double sum=0;
        double maxim_X=0;
        double minim = f[0];
        double indice_max;

        for(int i=0;i<n;i++)
        {
            sum += f[i];
            if(f[i]>maxim){
                maxim=f[i];
                maxim_X=X[i];
                indice_max=i;
            }
        }

        for(int i=1;i<n;i++)
        {
            if(f[i]<minim)
                minim=f[i];
        }

        if(e==0){
        cout<<endl<<"Cel mai slab cromozom este cel cu fitness-ul "<<minim<<endl;
        cout<<"Cel mai bun cromozom este cel cu fitness-ul "<< maxim<<endl;}

        for(int i=0;i<n;i++)
        {
            if(f[i]==minim){
                f[i]=f[indice_max];
                X[i]=X[indice_max];
                cromozomi[i]=cromozomi[indice_max];
                }
        }

        if(e==0)
        {
            cout<<endl<<"Dupa inlocuirea celui mai slab cu elitist: "<<endl;
            //i=0;
            for(int i=0; i<n; i++)
            {
                cout<<i+1<<":"<<cromozomi[i]<<" x= "<<X[i]<<" f= "<<f[i]<<endl;
            }
        }


        maxime.push_back(maxim);
        means.push_back(sum/f.size());
        bestX.push_back(maxim_X);
        //cout<<"Maximul: "<<maxim<<endl;
        //cout<<"Average: "<<sum/selectati.size()<<endl<<endl;




    }

    /*
    cout<<endl<<"Evolutia maximului"<<endl;
    cout<<"X-ul fiecarei generatii: "<<endl;
       for (double ic : bestX)
        cout<<ic<<endl;

    cout<<"Maximul fiecarei generatii:"<<endl;
    for (double maxi : maxime)
        cout<<maxi<<endl;

    cout<<"Mean-ul fiecarei generatii:"<<endl;
    for (double mean : means)
        cout<<mean<<endl;
    */

    cout<<endl<<endl;
    for(int i=0;i<maxime.size();i++)
        cout<<"x: "<<bestX[i]<<" fitness maxim: "<<maxime[i]<<" average fitness "<<means[i]<<endl;

    return 0;

}
