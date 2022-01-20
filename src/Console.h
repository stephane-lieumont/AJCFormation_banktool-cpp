#ifndef CONSOLE_H
#define CONSOLE_H

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <typeinfo>

#include "Banque.h"

using namespace std;

class Console
{
    public:
        Console(vector<string>, Banque*);
        ~Console();

        //AFFICHAGE
        short unsigned int addMenu();

        void afficheListClients(bool selectById = 0);
        void afficheSoldeComptesClient();
        void afficheOperationCompte();
        void addClient();
        void addCompte(int=0);
        void addOperation(int=0);
        void modClient(int=0);
        void modCompte();
        void modOperation(int=0);
        void suppClient(int=0);
        void suppCompte();
        void suppOperation(int=0);
        void importOperation();
        void exportOperation();

    protected:
        void HeaderConsole();
        Client* GenerateClient(Client* = nullptr);
        Compte* GenerateCompte(Compte* = nullptr);
        Operation* GenerateOperation();

        void Save(Client*);
        void Delete(Client*);
        void Save(Compte*);
        void Delete(Compte*);
        void Save(Compte*, int idClient);
        void Save(Client*, Compte*);
        void Save(Operation*, int idCompte);
        void Save(int idCompte, int idOp, bool confirm = true);
        void SaveAs(string fileSrc, string filName );
        void SaveImportOperation(string);
        void SaveExportOperation(map<Operation*, int> listOp);

        short unsigned int OptionsConsole();
        short unsigned int OptionsID(string, int=0);
        string CheckSourceOperation();
        bool CheckOptionID(int, string);
        bool CheckCin();
        bool CheckCinSize(string,  long long unsigned int);
        bool CheckDate(string d);
        bool ValidAsk(string);
        void Vider_buffer();
        void Retour();
        int Retour(map<short unsigned int, string>);

    private:
        vector<string> options;
        string pause;
        Banque* banque;
};

#endif // CONSOLE_H
