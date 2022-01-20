#include "Banque.h"

Banque::Banque(){
    ostringstream log;
    log << "Execution de l'application" << endl;
    if(this->debug){
        log << "-----------------------------------" << endl;
        log << "=>Chargement des fichiers Clients :" << endl;
        log << this->ReadSaveDataClient();
        log << "=>Chargement des fichiers Comptes :" << endl;
        log << this->ReadSaveDataCompte();
        log << "-----------------------------------" << endl;
    }else{
        this->ReadSaveDataClient();
        this->ReadSaveDataCompte();
    }

    this->SetDateUpdate(this->ReadSaveDataUpdate());
    this->EcritureFileLog(log.str());
    this->InitDirectory();
}

Client* Banque::GetClientByCompteID(int id){
    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++){
        map<int,Compte*> tmp_cpts = map_i->second->GetComptes();
        for(map<int,Compte*>::iterator map_j = tmp_cpts.begin(); map_j != tmp_cpts.end(); map_j++){
            if(map_j->first == id){
                return map_i->second;
            }
        }
    }
    return nullptr;
}

map<int, Compte*> Banque::GetListComptesClients(){
    map<int, Compte*>ListComptesClients;

    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++){
        map<int,Compte*> tmp_cpts = map_i->second->GetComptes();
        for(map<int,Compte*>::iterator map_j = tmp_cpts.begin(); map_j != tmp_cpts.end(); map_j++){
            ListComptesClients[map_j->first] = map_j->second;
        }
    }

    return ListComptesClients;
}

string Banque::InfosClient(){
    ostringstream oss;

    if (ListClients.size() > 0)
    {
        for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
        {
            oss << map_i->second->AfficheClient();
        }

        return oss.str();
    }
    else
    {
        oss << " Il n'y a pas de Clients dans la banque" << endl;
        return oss.str();
    }
}

string Banque::InfosClient(int num){
    ostringstream oss;

    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
    {
        if(map_i->second->GetNumeroClient() == num){
            oss << map_i->second->AfficheClient();
            return oss.str();
        }
    }

    oss << " Le numero du client est incorrecte!" << endl;
    return oss.str();
}

void Banque::AjouterClient(Client* c, Compte* cpt, bool file){
    bool vf_num = 0;
    bool vf_nom = 0;


    //Verfification de la presence su meme numero client
    vf_num = ListClients.count(c->GetNumeroClient());

    //Verfification de la presence du nom complet du client
    for ( map<int, Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
    {
        if(map_i->second->GetPrenom() == c->GetPrenom() && map_i->second->GetNom() == c->GetNom() && (typeid(*map_i->second) == typeid(*c))){
            vf_nom = 1;
        }
    }

    //Ajout du nouveau Client dans la liste si aucune erreurs
    if(vf_num > 0 || vf_nom > 0){
        throw logic_error("Ce client existe deja dans la banque.");
    }else{
        //Ajout Nouveau Client
        if(file){
            this->EcritureFileClient(c);
        }
        ListClients[c->GetNumeroClient()] = c;

        //Creation d'un nouveau Compte Client
        this->AjouterCompte(cpt,c->GetNumeroClient(),file);
    }
}

void Banque::ModifierClient(Client* oldC, Client* newC, bool file){
    map<int, Compte*> tmpListCompteOld = oldC->GetComptes();

    //copier les comptes de oldC
    newC->SetComptes(tmpListCompteOld);
    this->ListClients[oldC->GetNumeroClient()] = newC;

    //vider list des compte oldC
    tmpListCompteOld.clear();
    oldC->SetComptes(tmpListCompteOld);

    if(file){
        //supprime les fichiers comptes oldC
        for(map<int,Compte*>::iterator map_i = tmpListCompteOld.begin(); map_i != tmpListCompteOld.end(); map_i++){
           this->DeleteFileCompte(map_i->second, oldC);
           this->EcritureFileCompte(map_i->second, newC);
        }
        this->DeleteFileClient(oldC);
        this->EcritureFileClient(newC);
    }

    //supprimer objet oldC
    delete oldC;
}

void Banque::SupprimerClient(Client* c, bool file){
    if(file){
        this->DeleteFileClient(c);
        map <int, Compte*> tmp = c->GetComptes();
        for(map<int,Compte*>::iterator map_i = tmp.begin(); map_i != tmp.end(); map_i++){
            this->DeleteFileCompte(map_i->second, c);
        }
    }

    this->ListClients.erase(c->GetNumeroClient());

    delete c;
}

void Banque::AjouterCompte(Compte* c, int clientID, bool file){
    Client* cl = this->GetClientID(clientID);

    int verifNum = this->GetListComptesClients().count(c->GetNumeroCompte());

    if( verifNum > 0){
        throw logic_error("Ce numero de compte existe deja dans la banque.");
    }else{
        if(file){
           this->EcritureFileCompte(c, cl);
        }
        //Ajouter Compte a la list des comptes de la banque
        map<int, Compte*> newListCompte = this->GetClientID(clientID)->GetComptes();
        newListCompte[c->GetNumeroCompte()] = c;
        ListClients.find(clientID)->second->SetComptes(newListCompte);
    }
}

void Banque::ModifierCompte(Compte* c,Compte* tmpC, bool file){
    c->SetDecouvertAutorise(tmpC->GetDecouvertAutorise());
    c->SetSolde(tmpC->GetSolde());
    if(file){
        this->EcritureFileCompte(c, this->GetClientByCompteID(c->GetNumeroCompte()));
    }
    delete tmpC;
}

void Banque::SupprimerCompte(Compte* c, bool file){

    //Suppression du fichier Compte et de l'objet
    if(file){
        this->DeleteFileCompte(c, this->GetClientByCompteID(c->GetNumeroCompte()));
    }

    //Suppression du compte de Client
    Client* cl = this->GetClientByCompteID(c->GetNumeroCompte());
    map<int, Compte*> tmp = cl->GetComptes();
    tmp.erase(c->GetNumeroCompte());
    cl->SetComptes(tmp);

    delete c;
}

void Banque::AjouterOperation(Operation* op, int compteID, bool file){
    if(this->GetListComptesClients().count(compteID) > 0){
            this->GetComptesID(compteID)->AjouterOperation(op);
        if(file){
            this->EcritureFileCompte(this->GetListComptesClients().find(compteID)->second, this->GetClientByCompteID(compteID));
        }
    }else{
        throw logic_error("Ce numero de compte n'existe pas dans la banque.");
    }
}

void Banque::SupprimerOperation(Operation* op, int compteID, int opID, bool file){
    if(this->GetListComptesClients().count(compteID) > 0){
            this->GetComptesID(compteID)->SupprimerOperation(op, opID);
        if(file){
            this->EcritureFileCompte(this->GetListComptesClients().find(compteID)->second, this->GetClientByCompteID(compteID));
        }
    }else{
        throw logic_error("Ce numero de compte n'existe pas dans la banque.");
    }
}

string Banque::AfficherSoldeClient(int num){
    ostringstream oss;
    short int compteur = 0;
    oss << endl <<  "---------------SOLDE DES COMPTES---------------- " << endl;
    oss << endl << " Titulaire : " << ListClients.find(num)->second->GetSexe() <<ListClients.find(num)->second->GetNom() << " " << ListClients.find(num)->second->GetPrenom() << endl;
    oss << " Numero Client : " << ListClients.find(num)->second->FormatNumero(num) << endl;
    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
    {
        if(map_i->second->GetNumeroClient() == num){
            oss << endl << map_i->second->AfficheSoldeComptes();
            compteur++;
        }
    }
    if(compteur == 0)
        oss << " Le numero du client est incorrecte!" << endl;

    oss << endl << "------------------------------------------------ " << endl;

    return oss.str();
}

string Banque::AfficherSoldeCompte(int num){
    ostringstream oss;

    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
    {
        map<int,Compte*> tmp_comptes = map_i->second->GetComptes();

        for(map<int,Compte*>::iterator map_j = tmp_comptes.begin(); map_j != tmp_comptes.end(); map_j++)
        {
            if(map_j->second->GetNumeroCompte() == num){
                oss << "---------------------------------------------" << endl;
                oss << " Compte : " << map_i->second->FormatNumero(num) << endl;
                oss << "---------------------------------------------" << endl;
                oss << " Titulaire : " << map_i->second->GetSexe() << map_i->second->GetNom() << " " << map_i->second->GetPrenom() << endl;
                oss << map_j->second->AfficherOperations();
                oss << map_j->second->AfficheCompte();
                return oss.str();
            }
        }
    }

    oss << " Le numero de compte " << num << " est invalide.";
    return oss.str();
}

long double Banque::GetFondsDispo(){
    map<int, Compte*> allCpt = GetListComptesClients();
    long double fonds = 0;

    for(map<int, Compte*>::iterator map_i = allCpt.begin(); map_i != allCpt.end(); map_i++){
        fonds += map_i->second->GetSolde();
    }

    return fonds;
}

int Banque::NBClients(){
    return ListClients.size();
}

int Banque::NBComptes(){
    return this->GetListComptesClients().size();
}

void Banque::EcritureFileClient(Client* c){
    ostringstream log;
    string nomFichier("data/fichesClients/" + c->FormatNumero(c->GetNumeroClient()) + "__" + c->GetNom() + "_" + c->GetPrenom() + ".bqp");
    ofstream monFlux;
    monFlux.open(nomFichier.c_str());
    if(monFlux){
        monFlux << c->FluxFileClient();
    }else{
        log << "[ERR] SAVE client n " << setfill('0') << setw(5) << c->GetNumeroClient() << endl;
        this->EcritureFileLog(log.str());
        throw logic_error("Impossible d'ouvrir ou de creer un fichier client.");
    }
    monFlux.close();
    //Log Banque
    log << "[OK] SAVE client n " << setfill('0') << setw(5) << c->GetNumeroClient() << endl;
    this->EcritureFileLog(log.str());
}

void Banque::EcritureFileCompte(Compte* c, Client* cl){
    ostringstream log;

    string nomFichier("data/fichesComptes/" + c->FormatNumero(c->GetNumeroCompte()) + "__" + c->GetDateOpen() + "__" + cl->GetNom() + "-" + cl->GetPrenom() + ".bqc");
    ofstream monFlux;
    monFlux.open(nomFichier.c_str());
    if(monFlux){
        monFlux << "NUMERO CLIENT     : " << endl;
        monFlux << "-------------------" << endl;
        monFlux << cl->FormatNumero(cl->GetNumeroClient()) << endl;
        monFlux << "-------------------" << endl;
        monFlux << "INFOS COMPTE      : " << endl;
        monFlux << "-------------------" << endl;
        monFlux << c->FluxFileCompte();
        monFlux << "-------------------" << endl;
        monFlux << "INFOS OPERATIONS  : " << endl;
        monFlux << "-------------------" << endl;
        monFlux << c->FluxFileOperation();
        log << "[OK] SAVE compte n " << setfill('0') << setw(5) << c->GetNumeroCompte() << endl;
    }else{
        log << "[ERR] SAVE compte n " << setfill('0') << setw(5) << c->GetNumeroCompte() << endl;
        this->EcritureFileLog(log.str());
        throw logic_error("Impossible d'ouvrir ou de creer un fichier de type compte.");
    }
    monFlux.close();

    //Ecriture log anomalie operation
    string nomFichierLogAnomalie("Anomalie.log");
    ofstream monFluxAnomalie;
    monFluxAnomalie.open(nomFichierLogAnomalie.c_str());
    if(monFluxAnomalie){
        map<int,Compte*> ListComptes = this->GetListComptesClients();
        for(map<int,Compte*>::iterator map_i = ListComptes.begin(); map_i != ListComptes.end(); map_i++){
            monFluxAnomalie << map_i->second->FluxFileAnomalie();
        }
    }else{
        throw logic_error("Impossible d'ouvrir ou de creer un fichier Anomalie.log.");
    }
    monFluxAnomalie.close();

    this->EcritureFileLog(log.str());
}

void Banque::EcritureFileLog(string logFlux){
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    ostringstream log;

    string nomFichier("Banque.log");
    ifstream OldLog;

    OldLog.open(nomFichier.c_str());
    if(OldLog)
    {
      string ligne;
      while(getline(OldLog, ligne)){
         log << ligne << endl;
      }
    }
    OldLog.close();

    ofstream NewLog(nomFichier.c_str());

    if(NewLog){
        NewLog << log.str();
        NewLog << setfill('0') << setw(2) << ltm->tm_mday << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year << " " << setfill('0') << setw(2) << ltm->tm_hour << ":" << setfill('0') << setw(2) << ltm->tm_min << " : ";
        NewLog << logFlux;
        NewLog.close();
    }else{
        throw logic_error("Impossible d'ouvrir ou de creer un fichier Banque.log.");
    }
}

void Banque::EcritureFileUpdate(){
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    ostringstream updateFlux;
    ostringstream dateUpdate;
    dateUpdate << setfill('0') << setw(2) << ltm->tm_mday << "/" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " " << setfill('0') << setw(2) << ltm->tm_hour << ":" << setfill('0') << setw(2) << ltm->tm_min;

    string nomFichier("data/fichesOperations/update.bqm");
    ifstream OldLog;

    OldLog.open(nomFichier.c_str());
    if(OldLog)
    {
      string ligne;
      while(getline(OldLog, ligne)){
         updateFlux << ligne << endl;
      }
    }
    OldLog.close();

    ofstream NewLog(nomFichier.c_str());
    if(NewLog){
        NewLog << updateFlux.str();
        NewLog << dateUpdate.str();
        this->SetDateUpdate(dateUpdate.str());
    }else{
        throw logic_error("Impossible d'ouvrir ou de creer un fichier update.bqm");
    }
}

void Banque::DeleteFileClient(Client* c){
    ostringstream log;
    string nomFichier("data/fichesClients/" + c->FormatNumero(c->GetNumeroClient()) + "__" + c->GetNom() + "_" + c->GetPrenom() + ".bqp");
    remove (nomFichier.c_str());

    //Log Banque
    bool failed = !ifstream(nomFichier);
    if(failed) {
        log << "[OK] REMOVE client n " << setfill('0') << setw(5) << c->GetNumeroClient() << endl;
    }else{
        log << "[KO] REMOVE client n " << setfill('0') << setw(5) << c->GetNumeroClient() << endl;
    }

    this->EcritureFileLog(log.str());
}

void Banque::InitDirectory(){

    DIR* repData = opendir("data/");
    DIR* repDataClient = opendir("data/fichesClients/");
    DIR* repDataCompte = opendir("data/fichesComptes/");
    DIR* repDataOperation = opendir("data/fichesOperations/");
    DIR* repDataOperationImport = opendir("data/fichesOperations/Import");
    DIR* repDataOperationExport = opendir("data/fichesOperations/Extract");

    map<string, DIR*> directorys;
    directorys["data/"] =  repData;
    directorys["data/fichesClients/"] =  repDataClient;
    directorys["data/fichesComptes/"] =  repDataCompte;
    directorys["data/fichesOperations/"] =  repDataOperation;
    directorys["data/fichesOperations/Import/"] =  repDataOperationImport;
    directorys["data/fichesOperations/Extract/"] =  repDataOperationExport;

    for(map<string, DIR*>::iterator map_i = directorys.begin(); map_i != directorys.end(); map_i++){
        ostringstream log;
        if(map_i->second == NULL){
            log << "Creation du dossier " << map_i->first << ".";
            mkdir(map_i->first.c_str());
            closedir(map_i->second);
            this->EcritureFileLog(log.str());
        }
    }
}

void Banque::DeleteFileCompte(Compte* c, Client* cl){
    ostringstream log;
    string nomFichier("data/fichesComptes/" + c->FormatNumero(c->GetNumeroCompte()) + "__" + c->GetDateOpen() + "__" + cl->GetNom() + "-" + cl->GetPrenom() + ".bqc");
    remove (nomFichier.c_str());

    //Log Banque
    bool failed = !ifstream(nomFichier);
    if(failed) {
        log << "[OK] REMOVE compte n " << setfill('0') << setw(5) << c->GetNumeroCompte() << endl;
    }else{
        log << "[KO] REMOVE compte n " << setfill('0') << setw(5) << c->GetNumeroCompte() << endl;
    }

    this->EcritureFileLog(log.str());
}

string Banque::ReadSaveDataClient(){
    DIR* rep = opendir("data/fichesClients");
    map<int, string> listFileClient;
    int it = 0;

    if ( rep != NULL )
    {
        struct dirent* ent;

        while ( (ent = readdir(rep) ) != NULL )
        {
            if(strlen(ent->d_name) > 5){
                listFileClient[it] = ent->d_name;
                it++;
            }
        }
    }

    ostringstream oss;
    for(map<int, string>::iterator map_i = listFileClient.begin(); map_i != listFileClient.end(); map_i++)
    {
        Client* c = nullptr;

        //Ouverture du fichier et creation du Client dans la Banque
        string nomFichier("data/fichesClients/" + map_i->second);
        ifstream fichier;
        fichier.open(nomFichier.c_str());

        if(fichier){
            oss << "[OK] Traitement Fichier " << map_i->first << " : " << map_i->second <<  endl;
            //Lecture du fichier txt et recuperation des données
            int cpt = 0;
            map<int, string> data;
            string ligne;

            while(getline(fichier, ligne))
            {
                data[cpt] = ligne;
                cpt++;
            }

            //Creation des clients dans la banques
            //Creation d'adresse
            Adresse* Add = new Adresse;
            Add->libelle = data[5];
            Add->complement = data[6];
            Add->code_postale = data[7];
            Add->ville = data[8];

            if(data[1] == "particulier"){
                SituationFamiliale situ;
                if(data[10] == "Celibataire"){situ = SituationFamiliale::Celibataire;}
                else if(data[10] == "Marie(e)"){situ = SituationFamiliale::Marie;}
                else if(data[10] == "Divorce(e)"){situ = SituationFamiliale::Divorce;}
                else{situ = SituationFamiliale::Autre;}

                c = new Particulier (data[3], data[4], data[2].at(0), data[9], Add, situ, data[11], stoi(data[0]));
            }else{
                c = new Professionnel(data[3],data[4],data[2].at(0),data[9],Add,data[11],data[12],stoi(data[13]),data[10], stoi(data[0]));
            }
        }else{
            oss << "[OK] Traitement Fichier " << map_i->first << " : " << map_i->second <<  endl;
            throw ("Une erreur est survenu lors de l'ouverture du fichier : Client");
        }

        //Ajout Client dans la liste de la banque
        ListClients[c->GetNumeroClient()] = c;
        fichier.close();
    }

    closedir(rep);
    return oss.str();
}

string Banque::ReadSaveDataCompte(){
    DIR* rep = opendir("data/fichesComptes");
    map<int, string> listFileComptes;

    int it = 0;

    if ( rep != NULL )
    {
        struct dirent* ent;

        while ( (ent = readdir(rep) ) != NULL )
        {
            if(strlen(ent->d_name) > 5){
                listFileComptes[it] = ent->d_name;
                it++;
            }
        }
    }

    ostringstream oss;

    for(map<int, string>::iterator map_i = listFileComptes.begin(); map_i != listFileComptes.end(); map_i++)
    {
        map<int, Compte*> newListCompte;


        //Ouverture du fichier et creation du Client dans la Banque
        string nomFichier("data/fichesComptes/" + map_i->second);
        ifstream fichier;
        fichier.open(nomFichier.c_str());

        if(fichier){
            oss << "[OK] Traitement Fichier " << map_i->first << " : " << map_i->second <<  endl;
            //Lecture du fichier txt et recuperation des données
            int cpt = 0;
            map<int, string> data;
            string ligne;

            while(getline(fichier, ligne))
            {
                data[cpt] = ligne;
                cpt++;
            }

            Compte* compte = new Compte(stoi(data[6]), stod(data[9]), stod(data[8]), data[7]);
            Client* client = ListClients.find(stoi(data[2]))->second;
            //On recupere la liste des compte avant modification
            newListCompte = ListClients.find(stoi(data[2]))->second->GetComptes();

            //On injecte le compte dans les map
            newListCompte[stoi(data[6])] = compte;//UPDATE LIST COMPTES CLIENTS
            client->SetComptes(newListCompte);

            //On traite toutes les operations du compte
            map<int, string>::iterator it_beginOp = data.begin();
            advance(it_beginOp, 13);

            for(map<int, string>::iterator map_j = it_beginOp ; map_j != data.end(); map_j++){
                vector<string> OpString = this->splitString(map_j->second, ';');

                Operation* op = new Operation(op->GetCodeFormat(stoi(OpString[2])),stold(OpString[3]),OpString[1]);
                vector <Operation*> ListOp = this->GetComptesID(stoi(data[6]))->GetListOp();
                ListOp.insert(ListOp.begin(), op);
                this->GetComptesID(stoi(data[6]))->SetListOp(ListOp);
            }
        }else{
            oss << "[ERR] Traitement Fichier " << map_i->first << " : " << map_i->second <<  endl;
            throw ("Une erreur est survenu lors de l'ouverture du fichier : Compte");
        }

        fichier.close();
    }

    closedir(rep);
    return oss.str();
}

string Banque::ReadSaveDataUpdate(){
    string date = "aucune mise a jour";
    ostringstream UpdateData;
    string nomFichier("data/fichesOperations/update.bqm");
    ifstream updateFile;
    updateFile.open(nomFichier.c_str());

    if(updateFile)
    {
      string ligne;
      while(getline(updateFile, ligne)){
         date = ligne;
      }
    }
    updateFile.close();

    return date;
}

void Banque::SaveDataFileOpe(map<Operation*, int> dataOp){
    ostringstream log;
    for(map<Operation*, int>::iterator map_i = dataOp.begin(); map_i != dataOp.end(); map_i++){
        ostringstream log;
        try{
            this->AjouterOperation(map_i->first, map_i->second, true);
            log << "SAVE operation : " << "compte " << map_i->second << " | " << map_i->first->AfficheOperation() << endl;
            this->EcritureFileLog(log.str());
        }catch(const exception& e){
            cout << " ERREUR COMPTE N " << map_i->second << " : " << e.what() << endl;
            log << "SAVE operation : " << "compte " << map_i->second << " | " << e.what() <<endl;
            this->EcritureFileLog(log.str());
        }
    }
}

vector<string>  Banque::splitString(string input, char delimiter) {
    vector<string> internal;

    char cstr[input.size() + 1];
    strcpy(cstr, input.c_str());
    char * pch;
    pch = strtok (cstr,";");

    while (pch != NULL)
    {
        internal.push_back (pch);
        pch = strtok (NULL,";");
    }

    return internal;
}

int Banque::GenerateNumCompte(){
    int num = 1;

    map<int,Compte*> ListComptes = this->GetListComptesClients();

    for(map<int,Compte*>::iterator map_i = ListComptes.begin(); map_i != ListComptes.end(); map_i++){
        if(map_i->first != num && num > 0){
            return num;
        }
        num ++;
    }

    return num;
}

int Banque::GenerateNumClient(){
    int num = 1;

    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++){
        if(map_i->first != num && num > 0){
            return num;
        }
        num ++;
    }
    return num;
}

Banque::~Banque(){

    ostringstream log;
    log << "Fermeture de l'application" << endl;
    this->EcritureFileLog(log.str());

    if(debug){
        cout << "***********SUPPRESSION DE LA BANQUE **************" << endl;
        cout << "DESTRUCTION : Objet BANQUE " << endl << endl;
    }

    for(map<int,Client*>::iterator map_i = ListClients.begin(); map_i != ListClients.end(); map_i++)
    {
        delete map_i->second;
    }
}


