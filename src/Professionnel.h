#ifndef PROFESSIONNEL_H
#define PROFESSIONNEL_H

#include <iostream>
#include <sstream>

#include "Client.h"

using namespace std;

class Professionnel : virtual public Client
{
    public:
        //CONSTRUCTEUR
        Professionnel(string, string, char, string, Adresse*,string, string, unsigned short int, string, int);
        virtual ~Professionnel();

        //GETTER SETTER
        string GetSiret() { return Siret; }
        void SetSiret(string val) { Siret = val; }
        string GetRaison_sociale() { return Raison_sociale; }
        void SetRaison_sociale(string val) { Raison_sociale = val; }
        unsigned short int GetAnneeCreation() { return AnneeCreation; }
        void SetAnneeCreation(unsigned short int val) { AnneeCreation = val; }
        string GetMail() { return Mail; }
        void SetMail(string val) { Mail = val; }

        //METHODES

        virtual string AfficheClient() override;
        virtual string FluxFileClient() override;

    protected:

    private:
        string Siret;
        string Raison_sociale;
        unsigned short int AnneeCreation;
        string Mail;
};

#endif // PROFESSIONNEL_H
