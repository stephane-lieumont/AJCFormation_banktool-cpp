#include "Client.h"
Client::Client(int numClient, string nom, string prenom, char sexe, string tel, Adresse* addressClient){
    //Configuration du client
    this->SetNumeroClient(numClient);
    this->SetNom(nom);
    this->SetPrenom(prenom);
    this->SetSexe(sexe);
    this->SetTelephone(tel);
    this->SetAdresseClient(addressClient);
}

Client::~Client(){
    if(debug){
        cout << "DESTRUCTION : Client numero " << this->FormatNumero(GetNumeroClient()) << endl;
    }
    for(map<int,Compte*>::iterator map_j = ListComptes.begin(); map_j != ListComptes.end(); map_j++)
    {
       delete map_j->second;
    }
}

string Client::GetNom() {
    char char_array[Nom.length() + 1];
    strcpy(char_array, Nom.c_str());
    for (int i = 0; i < (int)(Nom.size() + 1); i++)
        char_array[i] = toupper(char_array[i]);
    return char_array;
}

void Client::SetNom(string val){
    if(val.size() <= 50 && val.size() > 0)
    {
        Nom = val;
    }
    else
    {
        throw logic_error("Le nom doit comprendre maximum 50 caractères et minimum 3 caractères.");
    }
}

string Client::GetPrenom(){

    transform(Prenom.begin(), Prenom.end(), Prenom.begin(), (int (*)(int))tolower);
    Prenom[0] =  toupper(Prenom[0]);
    return Prenom;


}

void Client::SetPrenom(string val){
    if(val.size() <= 50 && val.size() > 0)
        Prenom = val;
    else
        throw logic_error("Le prenom doit comprendre maximum 50 caractères et minimum 3 caractères.");
}

string Client::GetSexe(){

    if(Sexe == 'F')
        return "Mme ";
    return "M. ";

}

void Client::SetTelephone(string val){
    if(val.size() == 10)
        Telephone = val;
    else
        throw logic_error("Le numero de telephone doit comprendre 10 chiffres.");
}

Adresse* Client::GetAdresseClient() {
    return this->AdresseClient;
}

void Client::SetAdresseClient(Adresse* val) {
    char char_array[val->ville.length() + 1];
    strcpy(char_array, val->ville.c_str());
    for (int i = 0; i < (int)(val->ville.length() + 1); i++)
        char_array[i] = toupper(char_array[i]);
    val->ville = char_array;

    AdresseClient = val;
}

string Client::AfficheClient(){
    ostringstream oss;
    oss << " " << this->GetAdresseClient()->libelle << " " << this->GetAdresseClient()->complement << endl;
    oss << " " << this->GetAdresseClient()->code_postale << " " << this->GetAdresseClient()->ville << endl;
    return oss.str();
}

string Client::FluxFileClient(){
    ostringstream oss;
    oss << this->GetAdresseClient()->libelle << " " << this->GetAdresseClient()->complement << endl;
    oss << this->GetAdresseClient()->code_postale << " " << this->GetAdresseClient()->ville << endl;
    return oss.str();
}

string Client::AfficheSoldeComptes(){
    ostringstream oss;

    for(map<int,Compte*>::iterator map_i = ListComptes.begin(); map_i != ListComptes.end(); map_i++)
    {
        oss << " Solde du compte n " << FormatNumero(map_i->second->GetNumeroCompte()) << " : " << fixed << setprecision(2) << setfill(' ') << setw(13) << map_i->second->GetSolde() << " Euros." ;
        if(map_i->second->GetSolde()< map_i->second->GetDecouvertAutorise())
        {
            oss << " !!! DECOUVERT LIMIT DEPASSE " << endl;
        }else{
            oss << endl;
        }
    }

    return oss.str();
}

string Client::AfficheAllComptes(){
    ostringstream oss;
    oss << "--------------------" << endl;
    for(map<int,Compte*>::iterator map_i = ListComptes.begin(); map_i != ListComptes.end(); map_i++)
    {
        oss << map_i->second->AfficheCompte();
        oss << "--------------------" << endl;
    }

    return oss.str();
}

string Client::FormatNumero(int i){
    ostringstream oss;
    oss << setfill('0') << setw(5) << i;
    return oss.str();
}
