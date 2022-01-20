********************************
CREATION D’UNE APPLICATION
DE GESTION DE COMPTES CLIENTS
V2.1.1
********************************
 
Dans le cadre d’une application Console, créer une Gestion de Compte Clients.
On distingue différents types de clients :

- Des Clients « Particuliers »
- Des contacts « Professionnels »
Pour l’ensemble des clients, on distingue les caractéristiques suivantes :
- Nom (Chaine de 50 car. Max)
- Prénom (Chaine de 50 car. Max)
- Sexe (F/M)
- Téléphone (ex : 0000000000)
- Adresse Postale (Libellé, Complément, Code Postal, Ville)
Pour les Clients Particuliers, on stockera les informations suivantes :
- Situation familiale (C : Célibataire, M : Marié(e), D : Divorcé(e), X : Autre)
- Date de Naissance
Pour les contacts Professionnels, on stockera les informations suivantes :
- Siret (14 chiffres)
- Raison sociale (Chaine de 50 car.)
- Année de Création (Format : 2018)
- Adresse de l’entreprise (Libellé, Complément, Code Postal, Ville)
- Mail (doit contenir un @)
Il est évident que vous vérifierez la véracité de chaque information saisie et afficherez les messages
adéquats en cas de valeurs erronées.
Chaque client est doté d’un ou plusieurs comptes bancaires. Un compte bancaire se caractérise par :
- Un numéro de Compte
- Date Ouverture du compte
- Solde
- Montant du découvert autorisé

------------------------------------------------------------
De plus, la Banque reçoit chaque semaine un fichier récapitulant l’ensemble des opérations bancaires
réalisées.

Les opérations concernées sont uniquement :
1 : Retrait DAB
2 : Paiement Carte Bleue
3 : Dépôt Guichet
Les opérations d’un type différent doivent être enregistrées dans un fichier « Anomalies.log »

Pour cette application console, on veut offrir, à l’utilisateur, un certain nombre de fonctionnalités. Ces
fonctionnalités doivent être disponibles au travers d’un Menu.
- Lister l’ensemble des clients
- Consulter les soldes des comptes pour un client donné
- Ajouter/Supprimer/Modifier un Client quel que soit le type
- Ajouter/Supprimer/Modifier une Opération quel que soit le type
- Afficher l’ensemble des opérations pour un compte donné
- Importer le fichier des Opérations Bancaires
La présentation du menu est libre. Il doit être simple et convivial.
Contraintes Techniques :
- Héritage
- Surcharge d’Opérateurs
- Composition/Agrégation
- STL
- Gestionnaire d’Exception
Facultatif : Si vous avez le temps, vous exporterez l’ensemble des opérations de l’ensemble des clients
pour un jour donné vers un fichier sous la forme suivante :
- Numéro de Compte
- Date de l’Opération
- Type Opération
- Montant Opération
Votre projet devra être disponible sur GitLab. Il devra comporter au moins un commit pour chaque
fonctionnalité ajoutée et en état de fonctionnement. Vous pouvez effectuer évidemment des COMMIT
intermédiaires.
Les différents commit doivent bien être détaillés.
- Vous créerez au moins une branche pour gérer la fonctionnalité « Importer le fichier des
Opérations Bancaires ».
Vous définirez également des Tags pour chaque version stable.
- Commit 1 : Ajout Fichier README.txt comportant l’énoncé
- Commit N : …

----------------------------------------------------------------------
AJOUT DE NOUVELLE FONCTIONNALITES ( HORS PROJET ):

+ Affiche le nombre de Client dans l'entete
+ Affiche le nombre de Comptes dans l'entete
+ Affiche les fonds disponible dans la banque
+ Affiche la date de la derniere mise a jour Import
+ Fichier banque.log qui trace toute les operation echoué ou reussite avec date et heure precise
+ Ajout d'un icone de l'executable
+ Systeme de sauvegarde automatique des données

System de Sauvegarde dossier data:
- fichier ".bqp" // Fichier de données Client (bin/data/fichesClients)
- fichier ".bqc" // Fichier de données Comptes (bin/data/fichesComptes)
- fichier ".bqio" // Fichier de données Importation Operations (bin/data/fichesOperations)
- fichier ".bqie" // Fichier de données Exportation Operations (bin/data/fichesOperations)
- fichier ".bqm" // Fichier de données date Import (bin/data/fichesOperations)

Organisation du projet:
doc/ => Organisation des classes
obj/ => fichier .o de compilation
src/ => Code source Projet CodeBlocks

----------------------------------------------------------------------

