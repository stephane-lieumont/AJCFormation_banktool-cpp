#include "Operation.h"

Operation::Operation(CodeOperation code, long double mont, string date){
    if(date == "null"){
        this->SetDate();
    }else{
        this->SetDate(date);
    }

    this->SetCode(code);
    this->SetMontant(mont);
}

Operation::~Operation(){
    if(debug){
        cout << "DESTRUCTION : Objet OPERATION COMPTE " << endl;
    }
}

string Operation::GetCodeString(){
     switch (Code)
     {
        case Retrait:
             return "Retrait DAB";
        break;
        case CB:
            return  "Paiement Carte Bleue";
        break;
        case Depot:
             return "Depot Guichet";
        break;
        default:
            return  "Anomalie";
     }
}

CodeOperation Operation::GetCodeFormat(int i){
     switch (i)
     {
        case Retrait:
            return CodeOperation::Retrait;
        break;
        case CB:
            return CodeOperation::CB;
        break;
        case Depot:
            return CodeOperation::Depot;
        break;
        default:
            return CodeOperation::Anomalie;
     }
}

short int Operation::GetCodeInt(){
     switch (Code)
     {
        case Retrait:
             return 1;
        break;
        case CB:
            return 2;
        break;
        case Depot:
            return 3;
        break;
        default:
            return 4;
     }
}

void Operation::SetDate() {
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    ostringstream oss;
    oss << 1900 + ltm->tm_year << setfill('0') << setw(2) << 1 + ltm->tm_mon << setfill('0') << setw(2) << ltm->tm_mday;
    Date = oss.str();
}

string Operation::AfficheOperation(){
    ostringstream oss;
    oss << this->GetFormatDate() << " " << this->GetCodeString() << " de " << fixed << setprecision(2) << GetMontant() << " Euros.";
    return oss.str();
}

string Operation::GetFormatDate(){
    //20200716
    ostringstream oss;
    string jour;
    string mois;
    string annee;

    string date = this->GetDate();
    jour.append(date,6,2);
    mois.append(date,4,2);
    annee.append(date,0,4);


    oss << jour << "/" << mois << "/" << annee;

    return oss.str();
}

