// Copyright Robert Lica robertlica21@gmail.com

    Am scris un README destul de lung deoarece am dorit sa se vada ca am
inteles notiunide de OOP. Puncete importante sunt marcate cu "->"
    Am adaugat si o poza cu o diagrama UML pentru a fi mai clar cum se leaga
tot programul.

    In "Main" mi imi creez un obiect "Game" si ii dau play si dupa aceea il inchid
pentru a salva output-ul in fisier. Am dorit aceasta abordare deoarece consider
ca pot porni mai multe jocuri si nu am nevoie de de un Singleton, dar
GmaeFactory-ul este Singleton deoarece crearea de jocri am vrut sa fie
secventiala.

    -> "Map" reprezinta obiectul harta cu grid-ul de celule ("Cell") in care se
afla eroii si se bat. Am vrut o abordare de matrice in care sa am un obiect
ce tine cont cine se afla in el si de coordonatele lui in matrice deoarece
daca in joc ar exista abilitati "Area of Effect", ar fi mai inregula sa
afectam ce se afla in zona de pe harta decat sa cautam printre toti playerii
jocului.

	"Enviroments" este un enum cu diferitele tipuri de biomuri care se pot afla
pe harta. De asemena aici sunt si metode pentru a lua modifier-ul de teren sau
tipul de biom pe care se afla un player.

	-> "AbstractPlayer" este ce spune si numele si este ideea abstracta de
player unde de asemenea sunt implementate si metode generale pe care nu este
nevoie sa le redefineasca tipurile de eroi (cel putin in mod logic,
functional).
Am intampinat o problema cu metodele "applyModifiers", "calculateFinalDamage"
si "calculateDeflectedDamage" deoarece ma folosesc de supraincarcarea metodelor
din "Enviroments" pentru a imi obtine modifier-ul de teren si daca le-as
apela din "AbstractPlayer" as avea acces la un "this" de tipul "AbstractPlayer"
asa ca le-am redefinit in clasele fiecarui erou. Asta ar putea fi un avantaj de
asemenea deoarece daca regulile de interactiuni intre eroi la combat ar fi mai
diferite am avea mai multa flexibilitate. De asemenea, din aceasta dorinta de
flexibilitate a aparut urmatoarea problema de Codingstyle:
    -> Nu am vrut sa comasez calculele damageurilor din clasele eroilor deoarece
poate in viitor daca regulile de interactiuni din combat s-ar schimba ca sa
fie mai diferite interactiunile intre tipurile de eroi, ar fi o problema. Asa,
desi exista cod duplicat, putem avea flexibilitate daca un Rogue nu isi mai
da un atac pe un knight spre exemplu. Nu mi-a fost lene sa las IntelliJ-ul
sa imi creeze o metoda automat ca sa nu mai am cod duplicat.

   -> DoubleDispatch: L-am folosit la batalii, atunci cand o clasa (denumirea
diferitelor tipuri de eroi in D&D, nu clasa din Java) ataca pe alta pentru a
putea modifica usor daca ulterior regulile se vor schimba in etapa a 2-a (si
pentru ca am intarziat, am un avantaj deoarece am citit-o si pe aceea si mi-am
structurat bine lucrurile pentru a extinde).
    Am pastrat si partea in care un erou isi da acceptul de a fi atatac, putin
cam inutila chestia la prima vedere, dar am facut-o intentionat deoarece daca
regulile se vor schimba o sa fie foarte util. Spre exemplu in D&D exista ideea
de "ready an action" si daca esti atacat dar ai dat "ready" la actiunea ta, o
sa ataci inaintea celuilalt care vrea sa te atace.

	-> Damage over time: L-am implementat cu un observer folosind
"PropertyChangeSupport". Acesta imi anunta playerii inca in viata sa verifice
daca au damage de luat si sa si-l ia daca este cazul.
    