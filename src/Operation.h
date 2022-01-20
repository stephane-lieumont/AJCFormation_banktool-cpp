#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;
enum CodeOperation {Retrait=1, CB=2, Depot=3, Anomalie=4};

class Operation
{
    public:
        //CONSTRUCTEUR
        Operation(CodeOperation, long double, string = "null");
        virtual ~Operation();

        //GETTER
        string GetCodeString();
        short int GetCodeInt();
        CodeOperation GetCodeFormat(){ return Code; };
        CodeOperation GetCodeFormat(int);
        string GetDate() { return Date; }
        long double GetMontant() { return Montant; }
        string GetFormatDate();

        //SETTER
        void SetCode(CodeOperation val) { Code = val; }
        void SetDate(string val) { Date = val; }
        void SetDate();
        void SetMontant(long double val) { Montant = val; }

        //METHODE
        string AfficheOperation();

    protected:

    private:
        string Date;
        CodeOperation Code;
        long double Montant;
        static const bool debug = false;
};

#endif // OPERATION_H
