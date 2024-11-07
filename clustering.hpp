#ifndef clustering_HPP
#define clustering_HPP
#include "nuagepoint.hpp"
#include<iostream>
#include<cmath>
#include<fstream>
#include<cassert>
#include<valarray>
#include<random>

using namespace std;



template <class T> class clustering
{   
    protected:
    int nbrecluster;
    nuagepoint<T> * nuage;
    int * numero;

    public:

    // constructeurs par défaut, avec entier pour tester, et par copie
    clustering()
    {
        nbrecluster = 0;
        numero = nullptr;
        nuage = nullptr;
    }
    

    clustering(int n)
    {
        nbrecluster = n;
        nuage = nullptr;
        numero = new int[n];
        for(int i = 0; i<n ;i++)
        {
            numero[i]=-10;
        }
    }


    clustering(const clustering &n)
    {
        nbrecluster = n.nbrecluster;
        nuage = n.nuage;
        int m = nuage.nbrepnts;
        for(int i = 0; i<m; i++)
        {
            numero[i]=n.numero[i];
        }
    }

    //destructeurs
    ~ clustering()
    {
        delete[] numero;
    }



    void plot();
    void set_nbrecluster(int);
    int get_nbrecluster();
    void set_num(int, int);
    void set_num1();
    void set_nuage(nuagepoint<T> * N);
    int get_num(int);
    int get_nbre_pts_cluster(int);
   
    virtual void cluster() = 0 ;

    clustering & operator = (const clustering &);
    T operator [] (int);
    template <class O> 
    friend::ostream & operator << (std::ostream &, const clustering<O> &);

    
    /* static int testu1(); */ //

};

//opérateurs = , [] et cout

template<class T> clustering<T> & clustering<T> ::operator = (const clustering<T> &c)
{
        if (&c != this) 
        {
                if(nuage != nullptr)
                nbrecluster = c.nbrecluster;
                int m = c.nuage->get_nbrepnts();
                nuage = new nuagepoint<T>[m];

                if(c.numero != nullptr)
                        for(int i=0; i<m; i++)
                        {
                            nuage[i] = c.nuage[i];
                            numero[i] = c.numero[i];
                        }
        }

        return *this;
        

} 

template<class T> T clustering<T> ::operator [] (int i)
{
    return this->numero[i];
} 

template <class T>
std::ostream & operator << (std::ostream & out, const clustering<T> & c)
{
    out << "nombre de cluster: "<< c.nbrecluster << "nombre de points: "<< c.nuage->get_nbrepnts;
    for(int i = 0; i<c.nuage->get_nbrepnts; i++)
    {
        out << c.numero[i];
    }
    return out;

}

//fonctions plot de moodle

template <class T>
void clustering <T>::plot ()
{
// test que T est du type std::valarray, peut être changé
if (! std::is_same < T, std::valarray < double > >::value)
{
std::cerr << "type inconnu pour plot ()" << std::endl;
exit (1);
}
// création / ouverture du fichier en mode écriture
// l'option trunc dit qu'on efface le fichier avant d'écrire
std::ofstream ofile("../plot/data.txt", std::ios::out |
std::ios::trunc);
// si le fichier est ouvert
if (ofile)
{
// on écrit les coordonnées de chaque point ligne par ligne
// avec l'identifiant de cluster
int size = nuage->get_nbrepnts() ;
for (int i = 0; i < size; ++i)
{
for (auto elem : nuage->get_tabpnts(i) )
    ofile << elem << " ";
ofile << this->get_num(i) << "\n";
}
ofile << std::flush;
}
// si ofile n'a pas marché, on arrête et retourne l'erreur
else
{
std::cerr << "échec de l'ouverture de data.txt" <<
std::endl;
exit (1);
}
// exécution du script python, on vérifie la bonne exécution
int status = system("python3 ../plot/plot.py");
assert(status == EXIT_SUCCESS);
}


//acceseurs et mutateurs



template<class T>
int clustering<T>::get_nbrecluster()
{
    return this->nbrecluster;
}

template<class T>
int clustering<T>::get_num(int a)
{
    return numero[a];
}

template<class T>
void clustering<T>::set_nbrecluster(int a)
{
    nbrecluster = a;
}

template<class T>
void clustering<T>::set_num(int a, int b)
{
    numero[a] = b;
}

template<class T>
void clustering<T>::set_num1()
{
    for(int i = 0; i<this->nuage->get_nbrepnts();i++)
    {
        numero[i]=-10;
    }
}

template<class T>
void clustering<T>::set_nuage(nuagepoint<T> * N)
{
    nuage = N;
}

template<class T> 
int clustering<T>::get_nbre_pts_cluster(int i)
{   
    int k = 0 ;
    for(int j = 0; j<this->nuage->get_nbrepnts();j++)
    {
        if(numero[j]=i)
        {
            k++;
        }
    }
    return k;
}

/*
template <class T> 
int clustering <T>::testu1() 
{ 
    int res = 0;
    nuagepoint<int> N;
    N = nuagepoint<int>(2);
    clustering<int> c1;
    c1.set_nuage(N);
    c1.set_nbrecluster(2);
    clustering<int> c2;
    c2 = c1;
    if(c2.nbrecluster != 2)
    {
        res += 1;
    }
    if(c2.nuage != c1.nuage)
    {
        res +=1;
    }

    return res;
} */


//test unitaire qui ne se compile pas

#endif