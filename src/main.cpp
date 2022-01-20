#include <iostream>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

#include "Banque.h"
#include "Console.h"
#include "Particulier.h"
#include "Professionnel.h"
#include "Compte.h"
#include "Client.h"
#include <windows.h>

using namespace std;

int main(){
    //Init Dimension fenetre console
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD a;
    a.X = 200;
    a.Y = 150;

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = 50;
    rect.Right = 80;

    SetConsoleScreenBufferSize(handle, a);
    SetConsoleWindowInfo(handle, 1, &rect);

    //Init Banque
    Banque* maBanque = new Banque;

    //Init Console
    vector<string> options;
    options.push_back("INFOS......: Liste des clients.");
    options.push_back("INFOS......: Fiche d'un client.");
    options.push_back("INFOS......: Solde des comptes d'un client.");
    options.push_back("INFOS......: Operations bancaires d'un Compte.");
    options.push_back("CLIENT.....: Nouveau Client.");
    options.push_back("CLIENT.....: Modifier Client.");
    options.push_back("CLIENT.....: Supprimer Client.");
    options.push_back("COMPTE.....: Nouveau Compte.");
    options.push_back("COMPTE.....: Modifier Compte.");
    options.push_back("COMPTE.....: Supprimer Compte.");
    options.push_back("OPERATIONS.: Nouvelle Operation.");
    options.push_back("OPERATIONS.: Modifier Operation.");
    options.push_back("OPERATIONS.: Supprimer Operation.");
    options.push_back("UPDATE.....: Operations Bancaires.");
    options.push_back("EXPORT.....: Operations Bancaires.");
    options.push_back("[<-] QUITTER");

    Console* appli = new Console(options, maBanque);

    short unsigned int exitAppli = options.size();
    short unsigned int select = 0;

    //Tant que l'utilisateur n'utilise pas l'option exit => l'application fonctionne.
    while(select != exitAppli)
    {
        switch(select){
            case 0:
                cin.clear();
                cout.clear();
                select = appli->addMenu();
            break;
            case 1:
                appli->afficheListClients();
                select = 0;
            break;
            case 2:
                appli->afficheListClients(true);
                select = 0;
            break;
            case 3:
                appli->afficheSoldeComptesClient();
                select = 0;
            break;
            case 4:
                appli->afficheOperationCompte();
                select = 0;
            break;
            case 5:
                appli->addClient();
                select = 0;
            break;
            case 6:
                appli->modClient();
                select = 0;
            break;
            case 7:
                appli->suppClient();
                select = 0;
            break;
            case 8:
                appli->addCompte();
                select = 0;
            break;
            case 9:
                appli->modCompte();
                select = 0;
            break;
            case 10:
                appli->suppCompte();
                select = 0;
            break;
            case 11:
                appli->addOperation();
                select = 0;
            break;
            case 12:
                appli->modOperation();
                select = 0;
            break;
            case 13:
                appli->suppOperation();
                select = 0;
            break;
            case 14:
                appli->importOperation();
                select = 0;
            break;
            case 15:
                appli->exportOperation();
                select = 0;
            break;
            default:
                select = 0;
        }
        cin.clear();
        cout.clear();
    }

    //Nettoyage Memoire
    delete maBanque;
    delete appli;

    return 0;
}
