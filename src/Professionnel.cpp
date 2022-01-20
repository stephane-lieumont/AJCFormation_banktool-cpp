#include "Professionnel.h"
Professionnel::Professionnel( string nom, string prenom, char sexe, string tel, Adresse* addressClient,
                             string siret, string rsocial,unsigned short int annee, string mail, int num)
 :Client(num, nom,prenom,sexe,tel,addressClient){
    this->SetSiret(siret);
    this->SetRaison_sociale(rsocial);
    this->SetAnneeCreation(annee);
    this->SetMail(mail);
}

Professionnel::~Professionnel(){

}

string Professionnel::AfficheClient(){
    ostringstream oss;
    oss << endl << "---------------------------------------------" << endl;
    oss << " " << "CLIENT Professionnel : " << this->FormatNumero(this->GetNumeroClient()) << endl;
    oss << "---------------------------------------------" << endl;
    oss << " " << "Siret : " << this->GetSiret() << endl;
    oss << " " << "Nom de l'entreprise : " << this->GetRaison_sociale() << endl;
    oss << " " << "Annee de creation : " << this->GetAnneeCreation() << endl;
    oss << Client::AfficheClient();
    oss << " " << this->GetSexe() << this->GetNom() << " " << this->GetPrenom() << endl;
    oss << " " << "Telephone : " << this->GetTelephone() << endl;
    oss << " " << "Mail : " << this->GetMail() << endl;


    return oss.str();
}

string Professionnel::FluxFileClient(){
    ostringstream oss;
    oss << this->FormatNumero(this->GetNumeroClient()) << endl;
    oss << "professionnel" << endl;
    oss << this->GetSexe() << endl;
    oss << this->GetNom() << endl;
    oss << this->GetPrenom() << endl;
    oss << this->GetAdresseClient()->libelle << endl;
    oss << this->GetAdresseClient()->complement << endl;
    oss << this->GetAdresseClient()->code_postale << endl;
    oss << this->GetAdresseClient()->ville << endl;
    oss << this->GetTelephone() << endl;
    oss << this->GetMail() << endl;
    oss << this->GetSiret() << endl;
    oss << this->GetRaison_sociale() << endl;
    oss << this->GetAnneeCreation() << endl;
    return oss.str();
}

