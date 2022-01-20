#ifndef COMPTE_H
#define COMPTE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

#include "Operation.h"

using namespace std;

class Compte
{
    public:
        //CONSTRUCTEUR
        Compte(int, long double=0, long double=-500, string = "null");
        virtual ~Compte();

        //GETTER SETTER
        int GetNumeroCompte() { return NumeroCompte; }
        void SetNumeroCompte(int val) { NumeroCompte = val; }
        string GetDateOpen() { return DateOpen; }
        void SetDateOpen();
        void SetDateOpen(string);
        long double GetSolde() { return Solde; }
        void SetSolde(long double val) { Solde = val; }
        long double GetDecouvertAutorise() { return DecouvertAutorise; }
        void SetDecouvertAutorise(long double val) { DecouvertAutorise = val; }
        vector<Operation*> GetListOp(){ return ListOperations;}
        void SetListOp(vector<Operation*> val){ ListOperations = val;}

        //METHODES
        string AfficheCompte();
        string AfficherOperations();
        void AjouterOperation(Operation*);
        void SupprimerOperation(Operation*, int id);
        string FormatNumero(int);
        string FluxFileCompte();
        string FluxFileOperation();
        string FluxFileOperation(Operation*);
        string FluxFileAnomalie();

    private:
        int NumeroCompte;
        string DateOpen;
        long double Solde;
        long double DecouvertAutorise;
        vector<Operation*> ListOperations;
        static const bool debug = false;
};

#endif // COMPTE_H
