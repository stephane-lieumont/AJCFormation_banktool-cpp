#include "Console.h"

Console::Console(vector<string> options, Banque* banque){
    this->options = options;
    this->banque = banque;
}

Console::~Console(){

}

short unsigned int Console::addMenu(){
    system("cls");
    int SelectID;

    this->HeaderConsole();
    this->Vider_buffer();
    SelectID = this->OptionsConsole();
    return SelectID;
}

void Console::afficheListClients(bool byId){
    system("cls");
    this->HeaderConsole();
    int selectID = 0;
    int selectOption;
    map<short unsigned int, string>subOptions;

    if(banque->GetListClients().size() > 0){
        if(byId){
            selectID = this->OptionsID("Client");
            cout << this->banque->InfosClient(selectID) << endl;
            this->Vider_buffer();
            subOptions[1] = "Modifier Client";
            subOptions[2] = "Supprimer Client";
            //construction du sous Menu
            selectOption = this->Retour(subOptions);
            switch(selectOption){
                case 1:
                    this->Vider_buffer();
                    this->modClient(selectID);
                break;
                case 2:
                    this->Vider_buffer();
                    this->suppClient(selectID);
                break;

            }
        }else{
            cout << this->banque->InfosClient() << endl;
            this->Vider_buffer();
            subOptions[1] = "Ajouter Client";
            subOptions[2] = "Modifier Client";
            subOptions[3] = "Supprimer Client";
            //construction du sous Menu
            selectOption = this->Retour(subOptions);
            switch(selectOption){
                case 1:
                    this->Vider_buffer();
                    this->addClient();
                break;
                case 2:
                    this->Vider_buffer();
                    this->modClient();
                break;
                case 3:
                    this->Vider_buffer();
                    this->suppClient();
                break;
            }
        }
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
        if(this->ValidAsk("Souhaitez-vous creer un nouveau Client ?")){
            system("cls");
            this->HeaderConsole();
            this->addClient();
        }else{
            cout << endl;
            this->Retour();
        }
    }
    this->Vider_buffer();
}

void Console::afficheSoldeComptesClient(){
    system("cls");
    this->HeaderConsole();
    int selectID;
    int selectOption;
    map<short unsigned int, string>subOptions;
    subOptions[1] = "Modifier Client";
    subOptions[2] = "Supprimer Client";
    subOptions[3] = "Ajouter Compte";
    subOptions[4] = "Modifier Compte";
    subOptions[5] = "Supprimer Compte";

    if(banque->GetListComptesClients().size() > 0){
        selectID = this->OptionsID("Client");
        if(this->banque->GetListClients().count(selectID) > 0){
            cout << this->banque->AfficherSoldeClient(selectID) << endl;
            this->Vider_buffer();
            selectOption = this->Retour(subOptions);
            switch(selectOption){
                case 1:
                    this->Vider_buffer();
                    this->modClient(selectID);
                break;
                case 2:
                    this->Vider_buffer();
                    this->suppClient(selectID);
                break;
                case 3:
                    this->Vider_buffer();
                    this->addCompte(selectID);
                break;
                case 4:
                    this->Vider_buffer();
                    this->modCompte();
                break;
                case 5:
                    this->Vider_buffer();
                    this->suppCompte();
                break;
            }
        }else{
            cout << " Le numero du client est incorrecte!" << endl << endl;
        }
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
        if(this->ValidAsk("Souhaitez-vous creer un nouveau Client ?")){
            this->Vider_buffer();
            system("cls");
            this->HeaderConsole();
            this->addClient();
        }else{
            cout << endl;
            this->Vider_buffer();
            this->Retour();
        }
    }
}

void Console::afficheOperationCompte(){
    system("cls");
    this->HeaderConsole();
    int selectID;
    int selectOption;
    map<short unsigned int, string>subOptions;
    subOptions[1] = "Ajouter Operation";
    subOptions[2] = "Modifier Operation";
    subOptions[3] = "Supprimer Operation";


    if(banque->GetListComptesClients().size() > 0){
        selectID = this->OptionsID("Compte");
        cout << this->banque->GetListComptesClients()[selectID]->AfficherOperations() << endl;
        this->Vider_buffer();
        selectOption = this->Retour(subOptions);
        switch(selectOption){
            case 1:
                this->Vider_buffer();
                this->addOperation(selectID);
            break;
            case 2:
                this->Vider_buffer();
                this->modOperation(selectID);
            break;
            case 3:
                this->Vider_buffer();
                this->suppOperation(selectID);
            break;
        }
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
        this->Vider_buffer();
        this->Retour();
    }
}

void Console::addClient(){
    system("cls");
    this->HeaderConsole();
    cout << " ----------- AJOUT NOUVEAU CLIENTS ----------------" << endl << endl;
    Client* c = this->GenerateClient();
    Compte* cpt = this->GenerateCompte();
    this->Save(c, cpt);
    this->Retour();
}

void Console::addCompte(int clientID){
    system("cls");
    this->HeaderConsole();

    cout << " ----------- OUVRIR UN COMPTE ---------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(clientID == 0){
            clientID = this->OptionsID("Client");
            cout << endl;
        }

        Compte* cpt = this->GenerateCompte();
        this->Save(cpt,clientID);
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
    }
    this->Retour();
}

void Console::addOperation(int compteID){
    system("cls");
    this->HeaderConsole();

    cout << " ----------- NOUVELLE OPERATION -------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(compteID == 0){
            compteID = this->OptionsID("Compte");
            cout << endl;
        }

        Operation* op = this->GenerateOperation();
        this->Save(op,compteID);
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
    }
    this->Retour();
}

void Console::modClient(int clientID){
    system("cls");
    this->HeaderConsole();

    cout << " ----------- MODIFICATION CLIENT ------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(clientID == 0){
            clientID = this->OptionsID("Client");
        }
        cout << this->banque->InfosClient(clientID) << endl;
        Client* oldC = this->banque->GetClientID(clientID);
        Client* newC = this->GenerateClient(oldC);
        this->Save(newC);
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
        if(this->ValidAsk("Souhaitez-vous creer un nouveau Client ?")){
            system("cls");
            this->HeaderConsole();
            this->addClient();
        }else{
            this->Retour();
        }
    }
}

void Console::modCompte(){
    system("cls");
    this->HeaderConsole();
    int selectID;

    cout << " ----------- MODIFICATION COMPTE -------------" << endl << endl;
    if(banque->GetListComptesClients().size() > 0){
        selectID = this->OptionsID("Compte");
        cout << this->banque->GetComptesID(selectID)->AfficheCompte() << endl;
        Compte* oldC = this->banque->GetComptesID(selectID);
        Compte* newC = this->GenerateCompte(oldC);
        this->Save(newC);
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::modOperation(int compteID){
    system("cls");
    this->HeaderConsole();
    int selectIDop;

    cout << " ----------- MODIFIER OPERATION ------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(compteID == 0){
            compteID = this->OptionsID("Compte");
        }

        cout << this->banque->GetComptesID(compteID)->AfficherOperations() << endl;
        vector<Operation*> listOp = this->banque->GetComptesID(compteID)->GetListOp();
        selectIDop = this->OptionsID("Operation", listOp.size());
        cout << endl;
        Operation* op = this->GenerateOperation();
        this->Save(compteID, selectIDop, false);
        this->Save(op,compteID);
        cout << endl;
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::suppClient(int clientID){
    system("cls");
    this->HeaderConsole();

    cout << " ----------- SUPPRIMER CLIENT ---------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(clientID == 0){
            clientID = this->OptionsID("Client");
        }
        cout << this->banque->InfosClient(clientID) << endl;
        this->Delete(this->banque->GetClientID(clientID));
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::suppCompte(){
    system("cls");
    this->HeaderConsole();
    int selectID;

    cout << " ----------- SUPPRIMER COMPTE --------------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        selectID = this->OptionsID("Compte");
        cout << this->banque->GetComptesID(selectID)->AfficheCompte() << endl;
        this->Delete(this->banque->GetComptesID(selectID));
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::suppOperation(int compteID){
    system("cls");
    this->HeaderConsole();
    int selectIDop;

    cout << " ----------- SUPPRIMER OPERATION -----------------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        if(compteID == 0){
            compteID = this->OptionsID("Compte");
        }
        cout << this->banque->GetComptesID(compteID)->AfficherOperations() << endl;
        selectIDop = this->OptionsID("Operation");
        this->Save(compteID, selectIDop);
        cout << endl;
    }else{
        cout << " Aucun Compte dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::importOperation(){
    system("cls");
    this->HeaderConsole();
    string source;

    cout << " ----------- IMPORT FICHIER OPERATIONS -----------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        source = this->CheckSourceOperation();
        this->SaveImportOperation(source);
        cout << endl;
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::exportOperation(){
    system("cls");
    this->HeaderConsole();
    int selectID;
    map<Operation*, int> listOp;

    this->Vider_buffer();

    cout << " ----------- EXPORT FICHIER OPERATIONS -----------" << endl << endl;
    if(banque->GetListClients().size() > 0){
        selectID = this->OptionsID("Client");
        //Creation d'un list des operations;
        map<int, Compte*> listComptes = this->banque->GetListClients()[selectID]->GetComptes();
        for(map<int, Compte*>::iterator map_i = listComptes.begin(); map_i != listComptes.end(); map_i++ ){
            vector<Operation*> listOpCompte = map_i->second->GetListOp();
            for(unsigned int i = 0; i < listOpCompte.size(); i++)
            {
                listOp[listOpCompte[i]] = map_i->first;
            }
        }
        this->SaveExportOperation(listOp);

        cout << endl;
    }else{
        cout << " Aucun Client dans la Banque." << endl << endl;
    }

    this->Retour();
}

void Console::HeaderConsole(){
    cout << "                                                   " << endl;
    cout << " **************************************************" << endl;
    cout << " **************************************************" << endl;
    cout << " ********** GESTION COMPTES CLIENTS ***************" << endl;
    cout << " **************************************************" << endl;
    cout << " **************************************************" << endl;
    cout << " *****  Nombre de Clients :       " << setfill('0') << setw(5) << this->banque->NBClients() << "   *********" << endl;
    cout << " *****  Nombre de Comptes :       " << setfill('0') << setw(5) << this->banque->NBComptes() << "   *********" << endl;
    cout << " *****  Fonds disponibles : " << setfill(' ') << setw(11) << fixed << setprecision(2) << this->banque->GetFondsDispo() << " E *********" << endl;
    cout << " **************************************************" << endl;
    cout << " **************************************************" << endl;
    cout << "  Update operations : "<< banque->GetDateUpdate() << endl;
    cout << " **************************************************" << endl << endl;
}

Client* Console::GenerateClient(Client* oldC){
    Adresse* newAdd = new Adresse;
    SituationFamiliale situation = SituationFamiliale::Autre;
    char sexe;
    int anneeSociete;
    int type;
    int numeroClient = banque->GenerateNumClient();
    string nom;
    string prenom;
    string telephone;
    string naissance;
    string siret;
    string societe;
    string email;

    //Saisie du type de Client
    if(oldC == nullptr){
        while(true){
            cout << " TYPE DE COMPTE : " << endl;
            cout << " ( 1:Particulier | 2:Professionnel ) => ";
            cin >> type;

            if(this->CheckCin() == false){ continue; }
            if(type != 1 && type != 2){
                cerr << " Erreur -> veuillez saisir une des options." << endl << endl;
                this->Vider_buffer();
                continue;
            }

            cout << endl;
            this->Vider_buffer();
            break;
        }

        //Saisie du Numero Client
        while(true){
            int inputNum;
            cout << " NUMERO CLIENT : " << endl;
            cout << " ( 1:Automatique | 2:Manuel ) => ";
            cin >> inputNum;

            if(this->CheckCin() == false){ continue; }
            if(inputNum != 1 && inputNum != 2){
                cerr << " Erreur -> Veuillez saisir une des options." << endl << endl;
                this->Vider_buffer();
                continue;
            }
            if(inputNum == 2){
                cout << " Saisir le nouveau numero Client : ";
                cin >> numeroClient;
                if(this->CheckCin() == false){ continue; }
                if(numeroClient <= 0 || numeroClient >= 10000){
                    cerr << " Erreur (Numero) -> Veuillez saisir un numero à 5 chiffres maximum." << endl << endl;
                    this->Vider_buffer();
                    continue;
                }
                if(banque->GetListClients().count(numeroClient) > 0){
                    cerr << " Erreur (Numero) -> Ce numero client existe deja." << endl << endl;
                    this->Vider_buffer();
                    continue;
                }
            }else if(inputNum == 1){
                cout << " Numero Automatique : " << setfill('0') << setw(5) << numeroClient << endl;
            }

            cout << endl;
            this->Vider_buffer();
            break;
        }
    }else{
        typeid(Particulier).name() == typeid(*oldC).name() ? type = 1 : type = 2;
        numeroClient = oldC->GetNumeroClient();
    }

    //Saisie Infos Client
    while(true){
        cout << " INFOS CLIENT : " << endl;

        cout << " - Nom          : ";
        getline(cin, nom);
        if(this->CheckCin() == false || this->CheckCinSize(nom,50) == false){ continue; }//Verif saisie

        cout << " - Prenom       : ";
        getline(cin, prenom);
        if(this->CheckCin() == false || this->CheckCinSize(prenom,50) == false){ continue; }//Verif saisie

        cout << " - Sexe ( M/F ) : ";
        cin >> sexe;
        if(this->CheckCin() == false){ continue; }//Verif saisie
        //Verif du sexe de la personne
        if(sexe != 'F' && sexe != 'M'){
            cerr << endl << " Erreur (sexe) -> Veuillez saisir M ou F." << endl << endl;
            this->Vider_buffer();
            continue;
        }

        cout << " - Telephone    : ";
        cin >> telephone;
        if(this->CheckCin() == false){ continue; }//Verif saisie
        //Verif saisie telephone
        try{
            stoi(telephone);
            if(telephone.length() != 10){
                cerr << endl << " Erreur (Telephone) -> Veuillez saisir 10 Chiffre (ex:0611223344)." << endl << endl;
                this->Vider_buffer();
                continue;
            }
        }catch(const exception& e){
            cerr << endl << " Erreur (Telephone) -> Veuillez saisir 10 Chiffre (ex:0611223344)." << endl << endl;
            this->Vider_buffer();
            continue;
        }

        if(type == 1){
            short unsigned int inputSitu;

            cout << " - Date de naissance (01/01/1900): ";
            cin >> naissance;
            if(this->CheckCin() == false || this->CheckDate(naissance) == false){ continue; }//Verif saisie
            //Verification caracteres Naissance

            cout << " - Situation Familiale : " << endl;
            cout << " ( 1:Celibataire | 2:Marie(e) | 3:Divorce(e) | 4:Autre ) => ";
            cin >> inputSitu;
            if(this->CheckCin() == false){ continue; }//Verif saisie
            //Verif Situation familiale
            switch(inputSitu)
            {
                case 1:
                    situation = SituationFamiliale::Celibataire;
                break;
                case 2:
                    situation = SituationFamiliale::Marie;
                break;
                case 3:
                    situation = SituationFamiliale::Divorce;
                break;
                case 4:
                    situation = SituationFamiliale::Autre;
                break;
                default :
                    cerr << endl << " Erreur (Situation) -> Veuillez saisir une option (1<->4)." << endl << endl;
                    this->Vider_buffer();
                    continue;
            }
        }

        if(type == 2){
            cout << " - Numero de siret   : ";
            cin >> siret;
            if(this->CheckCin() == false || this->CheckCinSize(siret, 15) == false){ continue; }//Verif saisie
            //Verif siret
            try{
                if(stoll(siret) <= 10000000000000 || stoll(siret) >= 100000000000000){
                    cerr << endl << " Erreur (Siret) -> Veuillez saisir un numero a 14 chiffres valide.PROBLEME NOMBRE" << endl << endl;
                    this->Vider_buffer();
                    continue;
                }
            }catch(const exception& e){
                cerr << endl << " Erreur (Siret) -> Veuillez saisir un numero a 14 chiffres valide.PROBLEME WHAT STOI" << endl << endl;
                this->Vider_buffer();
                continue;
            }

            cout << " - Nom de la societe : ";
            getline(cin, societe);
            if(this->CheckCin() == false || this->CheckCinSize(societe, 50) == false){ continue; }//Verif saisie

            time_t actuel = time(0);
            tm *ltm = localtime(&actuel);
            cout << " - Annee de creation : ";
            cin >> anneeSociete;
            if(this->CheckCin() == false){ continue; }//Verif saisie
            //Verif saisie Année
            if(anneeSociete < 1000 || anneeSociete > (1900 + ltm->tm_year + 1)){
                cerr << endl << " Erreur (Annee de Creation) -> Veuillez saisir une annee valide." << endl << endl;
                this->Vider_buffer();
                continue;
            }

            char* pch;
            cout << " - Email             : ";
            cin >> email;
            if(this->CheckCin() == false){ continue; }//Verif saisie
            pch = strchr(email.c_str(), '@');
            //Verification Email
            if(pch == NULL){
                cerr << endl << " Erreur (Email) -> Veuillez saisir un Email valide." << endl << endl;
                this->Vider_buffer();
                continue;
            }
            pch = strchr(email.c_str(), '.');
            if(pch == NULL){
                cerr << endl << " Erreur (Email) -> Veuillez saisir un Email valide." << endl << endl;
                this->Vider_buffer();
                continue;
            }
        }

        cout << endl;
        this->Vider_buffer();
        break;
    }

    //Saisie de l'adresse
    while(true){
        cout << " ADRESSE : " << endl;
        cout << " - Libelle      : ";
        getline(cin, newAdd->libelle);
        if(this->CheckCin() == false || this->CheckCinSize(newAdd->libelle, 150) == false){ continue; }//Verif saisie
        cout << " - Complement   : ";
        getline(cin, newAdd->complement);
        if(this->CheckCin() == false){ continue; }//Verif saisie
        cout << " - Code Postale : ";
        cin >> newAdd->code_postale;
        if(this->CheckCin() == false || this->CheckCinSize(newAdd->code_postale, 5) == false){ continue; }//Verif saisie
        //Verif du code postale
        try{
            if(stoi(newAdd->code_postale) < 10000 || stoi(newAdd->code_postale) > 100000){
                cerr << endl << " Erreur (CP) -> Veuillez saisir des informations correctes." << endl << endl;
                this->Vider_buffer();
                continue;
            }
        }catch(const exception& e){
            cerr << endl << " Erreur (CP) -> Veuillez saisir des informations correctes." << endl << endl;
            this->Vider_buffer();
            continue;
        }

        cout << " - Ville        : ";
        getline(cin, newAdd->ville);
        if(this->CheckCin() == false){ continue; }//Verif saisie

        cout << endl;
        this->Vider_buffer();
        break;
    }

    //CREATION DE LOBJET CLIENT
    if(type == 1){
        Client* p1 = new Particulier(nom, prenom, sexe, telephone, newAdd, situation,naissance,numeroClient);
        return p1;
    }
    Client* pr1 = new Professionnel(nom, prenom, sexe, telephone, newAdd, siret, societe, anneeSociete, email,numeroClient);
    return pr1;
}

Compte* Console::GenerateCompte(Compte* oldC){
    int numeroCompte = banque->GenerateNumCompte();
    long double decouvert;

    if(oldC == nullptr){
        while(true){
            int inputNum;
            cout << " NOUVEAU COMPTE CLIENT : " << endl;
            cout << " Numero : ";
            cout << " ( 1:Automatique | 2:Manuel ) => ";
            cin >> inputNum;

            if(this->CheckCin() == false){ continue; }
            if(inputNum != 1 && inputNum != 2){
                cerr << " Erreur -> Veuillez saisir une des options." << endl << endl;
                this->Vider_buffer();
                continue;
            }
            if(inputNum == 2){
                cout << " Saisir le nouveau numero du Compte Client : ";
                cin >> numeroCompte;
                if(this->CheckCin() == false){ continue; }
                if(numeroCompte <= 0 || numeroCompte >= 10000){
                    cerr << " Erreur (Numero) -> Veuillez saisir un numero à 5 chiffres maximum." << endl << endl;
                    this->Vider_buffer();
                    continue;
                }
                if(banque->GetListComptesClients().count(numeroCompte) > 0){
                    cerr << " Erreur (Numero) -> Ce numero de compte existe deja." << endl << endl;
                    this->Vider_buffer();
                    continue;
                }
            }else if(inputNum == 1){
                cout << " Numero Automatique : " << setfill('0') << setw(5) << numeroCompte << endl;
            }

            cout << endl;
            this->Vider_buffer();
            break;
        }
    }

    while(true){
        oldC == nullptr ? cout << " Decouvert autorise : " : cout << " Nouveau decouvert autorise : ";
        cin >> decouvert;
        if(this->CheckCin() == false){ continue; }
        if(decouvert < 0){
            cerr << " Erreur (Decouvert) -> Le montant doit etre superieur ou égale à 0." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        cout << endl;
        this->Vider_buffer();
        break;
    }

    if(oldC == nullptr ){
        Compte* cpt = new Compte(numeroCompte, 0, (0 - decouvert));
        return cpt;
    }else{
        Compte* cpt = new Compte(oldC->GetNumeroCompte(), oldC->GetSolde(), (0 - decouvert));
        return cpt;
    }

    return nullptr;
}

Operation* Console::GenerateOperation(){
    short unsigned int inputCode;
    long double montant;
    while(true){
        cout << " NOUVELLE OPERATION : " << endl;
        cout << " Code Operation : " << endl;
        cout << " ( 1:Retrait | 2:Carte Bleu | 3:Depot ) => ";
        cin >> inputCode;
        if(this->CheckCin() == false){ continue; }
        if(inputCode != 1 && inputCode != 2 && inputCode != 3){
            cerr << " Erreur (Code)-> Veuillez saisir une des options." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        cout << " Montant : ";
        cin >> montant;
        if(this->CheckCin() == false){ continue; }
        if(montant < 0){
            cerr << " Erreur (montant) -> Le montant doit etre superieur ou égale à 0." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    CodeOperation code;

    switch (inputCode)
    {
        case 1:
            code = CodeOperation::Retrait;
        break;
        case 2:
            code = CodeOperation::CB;
        break;
        case 3:
            code = CodeOperation::Depot;
        break;
        default:
            code = CodeOperation::Anomalie;
    }

    Operation* op = new Operation(code, montant);

    return op;
}

void Console::Delete(Client* c){
    char input;

    while(true){
        cout << " Souhaitez-vous supprimer ce Client ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            this->banque->SupprimerClient(c, true);
            cout << " Client supprime." << endl << endl;
        }else{
            cout << " Annulation." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Delete(Compte* c){
    char input;

    while(true){
        cout << " Souhaitez-vous supprimer ce Compte ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            this->banque->SupprimerCompte(c, true);
            cout << " Compte supprime." << endl << endl;
        }else{
            cout << " Annulation." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(Client* newC){
    char input;
    Client* oldC = banque->GetClientID(newC->GetNumeroClient());

    cout << endl << "---------------" << endl;
    cout << " RECAPITULATIF" << endl;
    cout << "---------------" << endl;
    cout << newC->AfficheClient() << endl;

    while(true){
        cout << " Souhaitez-vous sauvegarder la saisie ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            banque->ModifierClient(oldC,newC,true);
            cout << " Client enregistree." << endl << endl;
        }else{
            delete newC;
            cout << " Annulation saisie client." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(Compte* newC){
   char input;

    cout << endl << "---------------" << endl;
    cout << " RECAPITULATIF" << endl;
    cout << "---------------" << endl;
    cout << newC->AfficheCompte() << endl;

    while(true){
        cout << " Souhaitez-vous sauvegarder la saisie ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            banque->ModifierCompte(banque->GetComptesID(newC->GetNumeroCompte()), newC,true);
            cout << " Compte enregistre." << endl << endl;
        }else{
            delete newC;
            cout << " Annulation saisie compte." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(Compte* cpt, int idClient){
    char input;

    cout << endl << "---------------" << endl;
    cout << " RECAPITULATIF" << endl;
    cout << "---------------" << endl;
    cout << banque->GetClientID(idClient)->AfficheClient() << endl;
    cout << banque->GetClientID(idClient)->AfficheAllComptes() << endl;
    cout << " NOUVEAU COMPTE : " << endl << endl;
    cout << cpt->AfficheCompte() << endl;

    while(true){
        cout << " Souhaitez-vous sauvegarder la saisie ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            banque->AjouterCompte(cpt,idClient,true);
            cout << " Compte enregistre." << endl << endl;
        }else{
            delete cpt;
            cout << " Annulation saisie compte." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(Client* c, Compte* cpt){
    char input;

    cout << endl << "---------------" << endl;
    cout << " RECAPITULATIF" << endl;
    cout << "---------------" << endl;
    cout << c->AfficheClient() << endl;
    cout << cpt->AfficheCompte() << endl;

    while(true){
        cout << " Souhaitez-vous sauvegarder la saisie ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            banque->AjouterClient(c,cpt,true);
            cout << " Client enregistree." << endl << endl;
        }else{
            delete c;
            delete cpt;
            cout << " Annulation saisie client." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(Operation* op, int idCompte){
    char input;

    cout << endl << "---------------" << endl;
    cout << " RECAPITULATIF" << endl;
    cout << "---------------" << endl;
    cout << banque->GetComptesID(idCompte)->AfficherOperations();
    cout << " Solde du compte : " << banque->GetComptesID(idCompte)->GetSolde() << " Euros" << endl;
    cout << " Nouvelle operation : ";
    cout << op->AfficheOperation() << endl << endl;

    while(true){
        cout << " Souhaitez-vous sauvegarder la saisie ? (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    try{
        if(input == 'y'){
            banque->AjouterOperation(op,idCompte,true);
            cout << " Operation enregistree."  << endl << endl;
            cout << " Nouveau solde du compte : " << banque->GetComptesID(idCompte)->GetSolde() << " Euros" << endl << endl;
        }else{
            delete op;
            cout << " Operation annulee." << endl << endl;
        }
    }catch(const exception& e){
        cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
    }
}

void Console::Save(int idCompte, int idOp, bool confirm){
    char input;

    if(confirm){
        while(true){
            cout << " Confirmation de la suppression ? (y/n) : ";
            cin >> input;

            if(this->CheckCin() == false){ continue; }
            if(input != 'y' && input != 'n'){
                cerr << " Erreur (sauvegarde) -> veuillez saisir 'y' ou 'n'." << endl << endl;
                this->Vider_buffer();
                continue;
            }
            this->Vider_buffer();
            break;
        }

        try{
            if(input == 'y'){
                cout << endl << "---------------" << endl;
                cout << " RECAPITULATIF" << endl;
                cout << "---------------" << endl;

                Compte* cpt = this->banque->GetComptesID(idCompte);
                this->banque->SupprimerOperation(cpt->GetListOp()[idOp-1], idCompte, idOp-1, true);
                cout << " Operation supprimee."  << endl << endl;
                cout << " Nouveau solde du compte : " << banque->GetComptesID(idCompte)->GetSolde() << " Euros" << endl << endl;
            }
        }catch(const exception& e){
            cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
        }
    }else{
        try{
            Compte* cpt = this->banque->GetComptesID(idCompte);
            this->banque->SupprimerOperation(cpt->GetListOp()[idOp-1], idCompte, idOp-1, true);
        }catch(const exception& e){
            cout << " ERREUR SAUVEGARDE : " << e.what() << endl;
        }
    }
}

void Console::SaveAs(string fileSrc, string fileName){
    string input;
    ostringstream file;
    ostringstream log;
    ifstream inExtract;
    ofstream outExtract;

    while(true){
        cout << " Saisir le chemin de destination de l'extract : " << endl;
        getline(cin, input);
        if(this->CheckCin() == false){ continue; }


        DIR* rep = opendir(input.c_str());
        if(rep == NULL){
            cout << " ERREUR : Le dossier de destination n'existe pas. " << endl << endl;
            continue;
        }

        file << input << fileName;

        inExtract.open(fileSrc.c_str(), ios::binary );
        outExtract.open(file.str().c_str(), ios::binary );

        if(inExtract && outExtract){
            outExtract << inExtract.rdbuf();

            cout << endl << " Exportation du fichier '" << file.str() << "' reussit."  << endl;
            log << "Extract des operation du fichier " << file.str() << " reussit.";

        }else{
            cout << endl << " Exportation du fichier '" << file.str() << "' a echoue."  << endl;
            log << "Extract des operation du fichier " << file.str() << " a echoue.";
        }


        this->banque->EcritureFileLog(log.str());
        this->Vider_buffer();
        break;
    }
    outExtract.close();
    inExtract.close();
}

short unsigned int Console::OptionsConsole(){
    short unsigned int inputOption;

    for(long long unsigned int i = 0; i < options.size(); i++){
        cout << " " << setfill(' ') << setw(2) << i+1 << ") " << options[i] << endl;
        //Ajout de Saut de ligne
        if(i == 3 || i == 6 || i == 9 || i == 12 || i == 14){
            cout << "------------------------------------------------" << endl;
        }
    }
    cout << "------------------------------------------------" << endl;

    while(true){
        cout << endl << " Choisir une option (" << 1 << "-" << this->options.size() << ") : ";
        cin >> inputOption;

        if(cin.eof() || cin.bad()){
            cerr << "   Erreur -> Une erreur interne est survenue.";
            if(cin.eof()){ break; }
            this->Vider_buffer();
            continue;
        }else if(cin.fail()){
            cerr << "   Erreur -> Veuillez saisir une option existante.";
            this->Vider_buffer();
            continue;
        }
        break;
    }
    return inputOption;
}

short unsigned int Console::OptionsID(string type, int maxData){
    short unsigned int input;

    while(true){
        cout << " Saisir un numero " << type << " : ";
        cin >> input;

        if(cin.eof() || cin.bad()){
            cerr << "   Erreur -> Une erreur interne est survenue." << endl << endl;
            if(cin.eof()){ break; }
            this->Vider_buffer();
            continue;
        }else if(cin.fail()){
            cerr << "   Erreur -> Veuillez saisir un chiffre entier." << endl << endl;
            this->Vider_buffer();
            continue;
        }else if(!this->CheckOptionID(input, type)){
            cerr << " Erreur : Le " << type << " n " << setfill('0') << setw(5) << input << " n'existe pas" << endl << endl;
            this->Vider_buffer();
            continue;
        }else if(maxData > 0 && input > maxData ){
             cerr << " Erreur : L' " << type << " n " << input << " n'existe pas" << endl << endl;
            this->Vider_buffer();
            continue;
        }
        break;
    }
    this->Vider_buffer();
    return input;
}

string Console::CheckSourceOperation(){
    string source;
    ifstream fichier;
    bool formatOK = false;

    while(true){
        cout << " Saisir le chemin complet du fichier du fichier source : " << endl;
        if(this->CheckCin() == false){ continue; }
        getline(cin, source);

        fichier.open(source.c_str());

        if(!fichier){
            cerr << " ERREUR : Le fichier '" << source << "' n'a pas ete trouve." << endl << endl;
            continue;
        }else{
            //VERIFICATION DU CONTENUR DU FORMAT DES DONNEES (UNIQUEMENT NOMBRE DE CARACTERES)
            int cpt = 0;
            map<int, vector<string>> data;
            vector<string> OpString;
            string ligne;

            while(getline(fichier, ligne))
            {
                //Decoupage de chaque ligne avec separateur ;
                data[cpt] = banque->splitString(ligne, ';');
                //Verif de chacune des données( si erreur on redemande le chemin du fichier )
                if(data[cpt][0].length() <= 0 || data[cpt][0].length() > 5 ){
                    formatOK = false;
                    break;
                }else if(data[cpt][1].length() != 8 ){
                    formatOK = false;
                    break;
                }else if(data[cpt][2].length() != 1 ){
                    formatOK = false;
                    break;
                }else if(data[cpt][3].length() <= 0){
                    formatOK = false;
                    break;
                }else{
                    formatOK = true;
                }

                cpt++;
            }

            if(!formatOK){
                cerr << " ERREUR : Le format des donnees sont incorrectes '" << source << "'." << endl << endl;
                continue;
            }

            fichier.close();
            break;
        }
        break;
    }

    this->Vider_buffer();
    return source;
}

void Console::SaveImportOperation(string source){
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    ostringstream oss;
    ostringstream log;
    this->Vider_buffer();

    //Nom du fichier d'importation
    oss << "data/fichesOperations/Import/IOP_" << 1900 + ltm->tm_year << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << setfill('0') << setw(2) << ltm->tm_mday << ".bqio";
    string FileName = oss.str();

    ifstream importFile{source.c_str(), ios::binary };

    if(importFile){
        //Affichage des operations a importer
        map<Operation*, int> opData;
        vector<string> OpString;
        string ligne;

        cout << endl;
        while(getline(importFile, ligne))
        {
            vector<string> data = banque->splitString(ligne,';');
            Operation* op = new Operation(CodeOperation::Anomalie,stold(data[3]), data[1]);
            CodeOperation code = op->GetCodeFormat(stoi(data[2]));
            op->SetCode(code);
            cout << "  Compte n " << setfill('0') << setw(5) << stoi(data[0]) << " : "<< op->AfficheOperation() << endl;

            opData[op] = stoi(data[0]);
        }
        cout << endl;
        importFile.close();

        if(this->ValidAsk("Confirmation de l'importation ?")){
            //Sauvegarde du fichier importation
            ifstream in(source.c_str(), ios::binary );
            ofstream out(FileName.c_str(), ios::binary );
            if(in && out){
                out << in.rdbuf();
                log << "Importation du fichier '" << source << "' reussit.";
                banque->EcritureFileUpdate();
                //Sauvegarde des operations dans la banque
                this->banque->SaveDataFileOpe(opData);
                out.close();
                in.close();
            }else{
                cout << " ERREUR : Une erreur c'est produite lors de l'importation du fichier." << endl << endl;
                log << "ERREUR : Une erreur c'est produite lors de l'importation du fichier '" << source << "'.";
            }
        }else{
            cout << " Annulation de l'importation des operations." << endl << endl;
            log << "Annulation de l'importation des operations'" << source << "'.";
        }
    }else{
        cout << " ERREUR : Une erreur c'est produite lors de l'importation du fichier." << endl << endl;
        log << "ERREUR : Une erreur c'est produite lors de l'importation du fichier '" << source << "'.";
    }


    banque->EcritureFileLog(log.str());
}

void Console::SaveExportOperation(map<Operation*, int> listOp){
    string date;
    string opDate;
    ostringstream log;
    int compteID = 0;

    map<Operation*, int> listOpFilter;
    //Saisir la date des operation a exporter
    while(true){
        cout << " Saisir la date des operations a exporter (01/01/1900) : ";
        cin >> date;
        if(this->CheckCin() == false){ continue; }//Verif saisie
        if(this->CheckDate(date) == false) { continue; } //Verifier format de saisie

        //Verification caracteres
        if(date.length() != 10){
            cerr << endl << " Erreur -> Veuillez saisir la date au format (01/01/1900)." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        cout << endl;
        this->Vider_buffer();
        break;
    }

    //Filtrer les operations en fonction de la date
    for(map<Operation*, int>::iterator map_i = listOp.begin(); map_i != listOp.end(); map_i++ ){
        if(date == map_i->first->GetFormatDate()){
            listOpFilter[map_i->first] = map_i->second;
            compteID = map_i->second;
            opDate = map_i->first->GetDate();
            cout << " - Compte " << setfill('0') << setw(5) << map_i->second << " : " << map_i->first->AfficheOperation() << endl;
        }
    }

    cout << endl;
    this->Vider_buffer();

    //Creation fichier Exportation
    if(listOpFilter.size() > 0 ){
        ostringstream fileName;
        ostringstream directoryfileName;
        string directory = "data/fichesOperations/Extract/";

        Client* c = this->banque->GetClientByCompteID(compteID);
        fileName << "EOP_" << setfill('0') << setw(5) << c->GetNumeroClient() << "_" << c->GetNom() << "-" << c->GetPrenom() << "_" << opDate << ".bqeo";
        directoryfileName << directory << fileName.str();

        ofstream ExtractFile;
        ExtractFile.open(directoryfileName.str().c_str());
        if(ExtractFile){
            for(map<Operation*, int>::iterator map_i = listOpFilter.begin(); map_i != listOpFilter.end(); map_i++ ){
                ExtractFile << this->banque->GetComptesID(map_i->second)->FluxFileOperation(map_i->first);
            }
            ExtractFile.close();
            this->SaveAs(directoryfileName.str(),fileName.str());
        }else{
            cout << " ERREUR : Probleme lors de la creation du fichier 'bqeo' " << fileName.str() << endl;
            log << "Erreur lors de la creation du fichier 'bqeo'";
        }
        cout << endl << " Exportation de " << listOpFilter.size() << " Operation(s)." << endl;
        log << "Exportation de " << listOpFilter.size() << " Operation(s).";
    }else{
        cout << " Aucune Operations ne correspondent a cette date." << endl;
    }

    banque->EcritureFileLog(log.str());
}

bool Console::CheckOptionID(int i, string type){
    if(type == "Client" && banque->GetListClients().count(i) > 0){
        return true;
    }else if(type == "Compte" && banque->GetListComptesClients().count(i) > 0){
        return true;
    }else if(type == "Operation"){
        return true;
    }

    return false;
}

bool Console::CheckCin(){
    if(cin.eof() || cin.bad()){
        cerr << endl << " Erreur -> Une erreur interne est survenue." << endl << endl;
        this->Vider_buffer();
        return false;
    }else if(cin.fail()){
        cerr << endl << " Erreur -> Veuillez saisir des informations valide." << endl << endl;
        this->Vider_buffer();
        return false;
    }
    this->Vider_buffer();
    return true;
}

bool Console::CheckCinSize(string s, long long unsigned int maxSize){
    if(s.size() <= 0 || s.size() > maxSize){
        cerr << endl << " Erreur -> Erreur de saisie veuillez recommencer." << endl << endl;
        this->Vider_buffer();
        return false;
    }

    return true;
}

bool Console::CheckDate(string d){
    if(d.length() != 10){
        cerr << endl << " Erreur (date) -> Veuillez saisir la date au format (01/01/1900)." << endl << endl;
        this->Vider_buffer();
        return false;
    }

    //Recherche de premier slash
    size_t found = d.find("/");
    if (found!=2){
        cerr << endl << " Erreur (date) -> Veuillez saisir la date au format (01/01/1900)." << endl << endl;
        this->Vider_buffer();
        return false;
    }
    //Recherche de deuxieme slash
    found = d.find("/", found+1, 1);
    if (found!=5){
        cerr << endl << " Erreur (date) -> Veuillez saisir la date au format (01/01/1900)." << endl << endl;
        this->Vider_buffer();
        return false;

    }

    return true;
}

bool Console::ValidAsk(string output){
    char input;
    while(true){

        cout << " " << output << " (y/n) : ";
        cin >> input;

        if(this->CheckCin() == false){ continue; }
        if(input != 'y' && input != 'n'){
            cerr << " Erreur : veuillez saisir 'y' ou 'n'." << endl << endl;
            this->Vider_buffer();
            continue;
        }
        this->Vider_buffer();
        break;
    }

    return input == 'y' ? true : false;
}

void Console::Vider_buffer(){
    cin.clear();
    cin.seekg(0, ios::end);

    if(!cin.fail()){
        cin.ignore(numeric_limits<streamsize>::max());
    }else{
        cin.clear();
    }
}

void Console::Retour(){
    this->Vider_buffer();
    this->pause = "";
    cout << " <== Retour (Appuyer sur entree) ...";
    getline(cin, this->pause);
    this->Vider_buffer();
}

int Console::Retour(map<short unsigned int, string>subOptions){
    string input;

    while(true){
        cout << endl << "-----------------OPTIONS--------------------" << endl;
        for(map<short unsigned int, string>::iterator map_i = subOptions.begin(); map_i != subOptions.end(); map_i++){
            cout << " [ " << map_i->first << ":" << map_i->second << " ]" << endl;
        }
        cout << " [ ENTER ] Menu principal." << endl;
        cout << "--------------------------------------------" << endl;
        cout << " Choisir une option :" << endl;
        getline(cin, input);
        if(this->CheckCin() == false){ continue; }
        if(input == "" ||  !stoi(input)){
            return 0;
        }

        this->Vider_buffer();
        break;
    }

    this->Vider_buffer();
    return stoi(input);
}

