#ifndef CLIENT_H
#define CLIENT_H
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <ctype.h>
#include <algorithm>

#include "Compte.h"

using namespace std;

struct Adresse{
    string libelle;
    string complement;
    string code_postale;
    string ville;
};

class Client
{
    public:
        //CONSTRUCTEUR
        Client(int, string, string, char, string, Adresse*);
        virtual ~Client();

        //GETTER SETTER
        int GetNumeroClient() { return NumeroClient; }
        void SetNumeroClient(int val) { NumeroClient = val; }
        string GetNom();
        void SetNom(string val);
        string GetPrenom();
        void SetPrenom(string val);
        string GetSexe();
        void SetTelephone(string val);
        Adresse* GetAdresseClient();
        void SetSexe(char val) { Sexe = val; }
        string GetTelephone() { return Telephone; }
        void SetAdresseClient(Adresse* val);
        void SetComptes(map<int, Compte*> val){ ListComptes = val; }
        map<int, Compte*> GetComptes(){ return ListComptes; }

        virtual string AfficheClient();
        virtual string FluxFileClient();
        virtual string AfficheSoldeComptes();
        virtual string AfficheAllComptes();
        virtual string FormatNumero(int);

    protected:

    private:
        int NumeroClient;
        string Nom;
        string Prenom;
        char Sexe;
        string Telephone;
        Adresse* AdresseClient;
        map<int, Compte*> ListComptes;
        static const bool debug = false;
};

#endif // CLIENT_H
