#ifndef dbscan_HPP
#define dbscan_HPP
#include "nuagepoint.hpp"
#include "clustering.hpp"
#include<vector>
#include<valarray>
#include<iostream>
#include<cmath>
#include<random>
#include <map>
using namespace std;

template <class T>
class dbscan : public clustering<T>
{
    public:

    double e;
    int min;
    bool * visite;


    //constructeurs par défaut
    dbscan():clustering<T>()
    {
        e = 0.;
        min = 0;
        visite = nullptr;
    }

    //constructeur pour tester qui prend n le nombre de point du nuage;
    dbscan(int n): clustering<T>(n)
    {
        e = 0.;
        min = 0;
        visite = new bool[n];
    }

    //constructeur par copie
    dbscan(const dbscan & db): clustering<T>(db)
    {
        e = db.e;
        min = db.min;
        visite = new bool[db.nuage->get_nbrepnts()];
        for(int i = 0; i<db.nuage->get_nbrepnts() ; i++)
        {
            visite[i]=db.visite[i];
        }
    }

  
    ~dbscan()
    {
        delete[] visite;
    }

    
    double get_e();
    int get_min();
    bool get_visite(int);
    void set_e(double);
    void set_min(int);
    void set_visite(int, bool);
    void set_taille_visite(int);

   
    dbscan & operator = (const dbscan &);    
    template<class O>
    friend::ostream & operator << (std::ostream &, const dbscan<O> &);

    
    vector<int> voisinage(T);
    vector<int> new_voisin(int, int, vector<int>);
    void cluster();

    


};

//operateur = et cout 

template<class T> dbscan<T> & dbscan<T> :: operator = (const dbscan & db) 
{
    if (&db != this)
    {
        e = db.e;
        min = db.min;
        if (visite != nullptr)
        {
            delete [] visite;
        }
        if(db.visite != nullptr)
        {
            visite = new bool[db.nuage->get_nbrepnts()];
            for (int i = 0 ; i<db.nuage->get_nbrepnts(); i++)
            {
                visite[i]=db.visite[i];
            }
        }
    }
    return *this;
}


template <class T>
std::ostream & operator << (std::ostream & out, const dbscan<T> & db)
{
    out << "eps : "<< db.e ;
    for(int i = 0; i<db.nuage->get_nbrepnts(); i++)
    {
        out << "le point "<< db.nuage->get_tabpnts(i) << " a été visité : " <<db.visite[i];
    }
    return out;


}


// fonction voisinage qui a a partir d'un point, va trouver les points qui sont dans le cercle de rayon epsilon 

template<class T>
vector<int> dbscan<T>::voisinage(T point)
{
    vector<int> num_voisin;
    for(int i = 0; this->nuage->get_nbrepnts();i++) // boucle sur le nombre de points pour comparer la distance entre le point pris par la fonction et tout les points du nuage
    {
        if(this->nuage->get_distance(point,this->nuage->get_tabpnts(i))>=get_e()) // si la distance entre le point pris par la fonction et un point du nuage est inférieur a la distance entre point et le rayon
        {
            num_voisin.push_back(i); // on ajoute ce point au vecteur 
        }
    }
    return num_voisin;
}

template<class T>
vector<int> dbscan<T>::new_voisin(int indice, int cluster, vector<int> nv)
{

    if(visite[indice] != true) // on regarde si le point est visité 
    {
    vector<int> res = voisinage(this->nuage->get_tabpnts(indice)); // on regarde les voisins du point d'indice indice.
    visite[indice] = true; // le point devient visité
    int a = res.size(); // "res.size()"" est un "long unsigned int" on le rend int pour pas que ça beug
        for(int i = 0; i<a ; i++)
            {
                nv.push_back(res[i]); //on ajoute au vecteur les nouveux points du clusters
            }
         
    } 
    if (this->get_num(indice) == -10) //on regarde si le point a deja un cluster si il  n'en a pas 
    {
        this->set_num(indice,cluster); // on associe le point a son cluster
    }  
    return nv; //on retourne le nouveau voisin
}    

template<class T>
void dbscan<T>::cluster()
{
    int c = 0; //compteur qui parcours les clusters 
    vector<int> voisin;
    for(int i = 0; i<this->nuage->get_nbrepnts();i++) //on boucle pour parcourir tout les points
    {
        if(visite[i] == false) //on regarde si le point a deja été visité pour éviter de tourner en boucle;
        {

            voisin = new_voisin(i,c,voisinage(this->nuage->get_tabpnts(i))); //on regarde les voisins du points
            int b = voisin.size();
            if(b<min)
            {
                this->numero[i] = -10; // si la taille du clusters est inférieur au minimum de points alors on associe le point a aucun clusters
            }
            else
            {
                c++;
                new_voisin(i,c,voisin); //
            }
        }


    }


}

//accesseurs & mutateurs

template <class T>
double dbscan<T>::get_e()
{
    return this->e;
} 

template <class T>
int dbscan<T>::get_min()
{
    return this->min;
} 

template <class T> 
bool dbscan<T>::get_visite(int i)
{
    return this->visite[i];
}
template<class T>
void dbscan<T>::set_e(double f)
{
    e = f;
}

template<class T>
void dbscan<T>::set_min(int m)
{
    min = m;
}

template<class T>
void dbscan<T>::set_visite(int i, bool t)
{
    visite[i] = t;
}


//mutateurs pour essayer mes fonctions

template<class T>
void dbscan<T>::set_taille_visite(int i)
{
    delete[] visite;
    visite = new bool[i];
    for(int j = 0; j<i ; j++)
    {
        visite[j]= false;
    }
}


#endif