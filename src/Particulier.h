#ifndef PARTICULIER_H
#define PARTICULIER_H

#include <iostream>
#include <sstream>
#include <ctype.h>

#include "Client.h"

using namespace std;

enum class SituationFamiliale {Celibataire, Marie, Divorce, Autre};

class Particulier : virtual public Client
{
    public:
        //CONSTRUCTEUR
        Particulier(string, string, char, string, Adresse*,SituationFamiliale, string, int);
        virtual ~Particulier();

        //GETTER SETTER
        string GetSituation();
        void SetSituation(SituationFamiliale val) { Situation = val; }
        string GetNaissance() { return Naissance; }
        void SetNaissance(string val) { Naissance = val; }

        //METHODES
        virtual string AfficheClient() override;
        virtual string FluxFileClient() override;

    protected:

    private:
        SituationFamiliale Situation;
        string Naissance;
};

#endif // PARTICULIER_H
