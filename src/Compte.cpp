#include "Compte.h"

Compte::Compte(int num, long double solde, long double decouv, string date){
    if(date == "null"){
      this->SetDateOpen();
    }else{
        this->SetDateOpen(date);
    }

    this->SetNumeroCompte(num);
    this->SetSolde(solde);
    this->SetDecouvertAutorise(decouv);
}

Compte::~Compte(){
    if(debug){
        cout << "DESTRUCTION : Compte numero " << this->FormatNumero(this->GetNumeroCompte()) << endl;
    }

    for(long long unsigned int i = 0; i < ListOperations.size(); ++i ){
        delete ListOperations[i];
    }
}

void Compte::SetDateOpen(){
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    ostringstream oss;
    oss << setfill('0') << setw(2) << ltm->tm_mday << "-" << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" << 1900 + ltm->tm_year;
    DateOpen = oss.str();
}

void Compte::SetDateOpen(string d){
    DateOpen = d;
}

string Compte::AfficheCompte(){

    ostringstream oss;
    oss << " COMPTE N " << setfill('0') << setw(5) << this->GetNumeroCompte() << endl;
    oss << " Solde              : " << fixed << setprecision(2) << this->GetSolde() << " Euros." << endl;
    oss << " Decouvert autorise : " << fixed << setprecision(2) << this->GetDecouvertAutorise() << " Euros.";
    if(this->GetSolde() < this->GetDecouvertAutorise()){
        oss << " !!! DECOUVERT LIMIT DEPASSE ";
    }
    oss << endl;
    return oss.str();
}

string Compte::FluxFileCompte(){
    ostringstream oss;
    oss << this->FormatNumero(this->GetNumeroCompte()) << endl;
    oss << this->GetDateOpen() << endl;
    oss << fixed << setprecision(2) << this->GetDecouvertAutorise() << endl;
    oss << fixed << setprecision(2) << this->GetSolde() << endl;
    return oss.str();
}

string Compte::FluxFileOperation(){
    ostringstream oss;
    for(long long unsigned int i = 0; i < ListOperations.size(); ++i ){
        oss << this->GetNumeroCompte() << ";" << ListOperations[i]->GetDate() << ";" << ListOperations[i]->GetCodeInt() << ";" << fixed << setprecision(2) << ListOperations[i]->GetMontant() << endl;
    }
    return oss.str();
}

string Compte::FluxFileOperation(Operation* op){
    ostringstream oss;
    oss << this->GetNumeroCompte() << ";" << op->GetDate() << ";" << op->GetCodeInt() << ";" << fixed << setprecision(2) << op->GetMontant() << endl;
    return oss.str();
}

string Compte::FluxFileAnomalie(){
    ostringstream oss;
    for( long long unsigned int i = 0; i < ListOperations.size(); ++i ){
        if(ListOperations[i]->GetCodeInt() >= 4){
            oss << "ANOMALIE :" << this->GetNumeroCompte() << ";" << ListOperations[i]->GetDate() << ";" << ListOperations[i]->GetCodeInt() << ";" << fixed << setprecision(2) << ListOperations[i]->GetMontant() << endl;
        }
    }
    return oss.str();
}

void Compte::AjouterOperation(Operation* op){
    //Modification du Solde du compte en fonction du montant et du code operation
    int codeInt = op->GetCodeInt();
    long double solde = this->GetSolde();
    if(codeInt == 1 || codeInt == 2){
        solde -= op->GetMontant();//Debit du solde du compte
     }else if(codeInt == 3){
        solde += op->GetMontant();//Credit du solde du compte
    }
    this->SetSolde(solde);
    //Ajout dans la liste des operations du compte cible
    this->ListOperations.insert(ListOperations.begin(), op);
}

void Compte::SupprimerOperation(Operation* op, int id){
    //Modification du Solde du compte en fonction du montant et du code operation
    int codeInt = op->GetCodeInt();
    long double solde = this->GetSolde();
    if(codeInt == 1 || codeInt == 2){
        solde += op->GetMontant();//Debit du solde du compte
     }else if(codeInt == 3){
        solde -= op->GetMontant();//Credit du solde du compte
    }
    this->SetSolde(solde);
    //Ajout dans la liste des operations du compte cible
    this->ListOperations.erase(ListOperations.begin()+id);
    delete op;
}

string Compte::AfficherOperations(){
    ostringstream oss;
    oss << endl << "---------------------------------------------" << endl;
    oss << " COMPTE : " << this->FormatNumero(this->GetNumeroCompte()) << endl;
    oss << "---------------------------------------------" << endl;
    if (ListOperations.size() > 0)
    {
        for(long long unsigned int i = 0; i < ListOperations.size(); i++)
        {
            oss << " Mouvement " << (i+1) << " : " << ListOperations[i]->AfficheOperation() << endl;
        }
        return oss.str();
    }
    else
    {
        oss << " Aucune operation n'a ete relevee sur le compte." << endl;
        return oss.str();
    }
}

string Compte::FormatNumero(int i){
    ostringstream oss;
    oss << setfill('0') << setw(5) << i;
    return oss.str();
}
