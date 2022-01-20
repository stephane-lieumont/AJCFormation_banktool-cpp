#ifndef BANQUE_H
#define BANQUE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <map>
#include <sys/stat.h>

#include "Operation.h"
#include "Compte.h"
#include "Client.h"
#include "Particulier.h"
#include "Professionnel.h"

using namespace std;

class Banque
{
    public:
        Banque();
        virtual ~Banque();

        //GETTER
        int NBClients();
        int NBComptes();

        map<int, Client*> GetListClients(){ return this->ListClients; }
        map<int, Compte*> GetListComptesClients();

        Client* GetClientByCompteID(int);
        Client* GetClientID(int id){ return this->ListClients.find(id)->second; }
        Compte* GetComptesID(int id){ return this->GetListComptesClients().find(id)->second; }
        long double GetFondsDispo();
        string GetDateUpdate(){ return this->dateUpdate; }
        void SetDateUpdate(string val){ this->dateUpdate = val;}

        //METHODE GENERATION
        int GenerateNumCompte();
        int GenerateNumClient();

        //METHODES AFFICHAGE
        string InfosClient();
        string InfosClient(int);
        string AfficherSoldeClient(int);
        string AfficherSoldeCompte(int);

        //METHODES ADD/MODIF
        void AjouterClient(Client*, Compte*, bool file = 0);
        void ModifierClient(Client* oldC, Client* newC, bool file = 0);
        void SupprimerClient(Client*, bool file = 0);

        void AjouterCompte(Compte*, int, bool file = 0);
        void ModifierCompte(Compte*, Compte*, bool file = 0);
        void SupprimerCompte(Compte*, bool file = 0);

        void AjouterOperation(Operation*, int, bool file = 0);
        void SupprimerOperation(Operation* op, int compteID, int opID, bool file = 0);

        void EcritureFileLog(string);
        void EcritureFileUpdate();
        void SaveDataFileOpe(map<Operation*, int>);
        vector<string> splitString(string , char);

    protected:
        //METHODE LOAD DATA
        string ReadSaveDataClient();
        string ReadSaveDataCompte();
        string ReadSaveDataUpdate();

        //FONCTION INTERNE CLASS
        void EcritureFileClient(Client*);
        void EcritureFileCompte(Compte*, Client*);
        void DeleteFileClient(Client*);
        void DeleteFileCompte(Compte*, Client*);
        void InitDirectory();
    private:
        map<int, Client*> ListClients;
        static const bool debug = false;
        string dateUpdate;
};

#endif // BANQUE_H


