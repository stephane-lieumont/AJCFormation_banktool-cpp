#include "Particulier.h"

Particulier::Particulier(string nom, string prenom, char sexe, string tel, Adresse* addressClient, SituationFamiliale situ, string naiss, int num)
 :Client(num, nom,prenom,sexe,tel,addressClient){
    this->SetSituation(situ);
    this->SetNaissance(naiss);
}

Particulier::~Particulier(){

}

string Particulier::GetSituation(){
    switch(Situation)
    {
        case SituationFamiliale::Celibataire:
            return "Celibataire";
            break;
        case SituationFamiliale::Marie:
            return "Marie(e)";
            break;
        case SituationFamiliale::Divorce:
            return "Divorce(e)";
            break;
        default:
            return "Autre";
    }
}

string Particulier::AfficheClient(){
    ostringstream oss;
    oss << endl << "---------------------------------------------" << endl;
    oss << " " << "CLIENT Particulier : " << this->FormatNumero(this->GetNumeroClient()) << endl;
    oss << "---------------------------------------------" << endl;
    oss << " " << this->GetSexe() << this->GetNom() << " " << this->GetPrenom() << endl;
    oss << Client::AfficheClient();
    oss << " " << "Telephone : " << this->GetTelephone() << endl;
    oss << " " << "Situation Familiale : " << this->GetSituation() << endl;
    oss << " " << "Date de naissance : " << this->GetNaissance() << endl;

    return oss.str();
}

string Particulier::FluxFileClient(){
    ostringstream oss;
    oss << this->FormatNumero(this->GetNumeroClient()) << endl;
    oss << "particulier" << endl;
    oss << this->GetSexe() << endl;
    oss << this->GetNom() << endl;
    oss << this->GetPrenom() << endl;
    oss << this->GetAdresseClient()->libelle << endl;
    oss << this->GetAdresseClient()->complement << endl;
    oss << this->GetAdresseClient()->code_postale << endl;
    oss << this->GetAdresseClient()->ville << endl;
    oss << this->GetTelephone() << endl;
    oss << this->GetSituation() << endl;
    oss << this->GetNaissance() << endl;
    return oss.str();
}


