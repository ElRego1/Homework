Lica Robert Mihai <robertlica21@gmail.com>

Problema 1:

Complexitate temporala O(log n)
Complexitate spatiala O(1) (marimea matricilor este constanta)

De la un vector de input, care in cazul nostru este un vector de 5 de 1, acesta
se inmulteste cu o matrice care dicteaza cum va arata vectorul la urmatorul
pas, in problema noastra pasul fiind n dat la input. Deoarece este o recurenta
si prin urmare o inmultire succesiva de matrici, am ales sa fac ridicarea la
putere matricii patratice de 5X5. Tehnica folosita este divide et impera si
calculez cu recursivitate ridicarea matricii la putere.
Am facut doua implementari a inultirii de matrice. Deoarece este o matrice
de marime constanta, putem sa scriem noi rezultatul fiecarui element si sa
facem inmultirea de mana, dar codul rezultat este greu de urmarit si verificat
de buguri. Asa ca am facut si un compromis in care am folosit un for pentru
a face codul mai lizibil. Eu am lasat pentru cod a 2-a implementare folosind
macroul "LOOP_UNROLLED" setat pe 1. Pentru a se folosi inmultirea de matrici
mai lizibila, sa se schimbe cu 0.


Problema 2:

Complexitate temporala O(n * log n)
Complexitate spatiala O(n) (vectorul citit, fara memorie auxiliara)

La aceasta problema imi citesc inputul, il sortez descrescator daca prima
coordonata nu este egala si daca este, sortez crescator dupa a 2-a folosind
functie "sort" din STL (care realizeaza sortarea in O(n * log n)). Dupa aceea
ma apuc sa vad daca apar suprapuneri dupa logica clara din cod. Dar pe scurt,
daca fostul y este peste urmatorul x, inca se suprapun, daca nu mai se intampla
asta, se updateaza fostul y, cu cel pentru cazul cand nu s-au mai suprapus.


Problema 3:

Complexitate temporala O(n * m * k)
    unde n este numarul de copii, m numarul de bomboane si k este marimea
    maxima a intervalelor de care isi aminteste Gigel  
Complexitate spatiala O(n * m)

La aceasta problema am aplicat programare dinamica si am folosit o matrice
pentru a tine minte rezultatul pentru fiecare subproblema.
- matricea initial este populata cu 0;
Cazul de baza: in matricea cu n linii si m coloane, am pus pe prima linie
'1' in locurile unde apare intervalul primului copil(dp[0][x_0 : y_0] = 1).
- dp[i][j] reprezinta numarul de moduri in care se pot imparti j bomboane
primilor i copii;
Cazul general: pentru calcularea urmatoarelor linii, merg pe linia anterioara
si la pozitia ei (adica coordonata care imi spune cate bomboane sunt pana in
momentul acela) adaug fiecare element k (unde k ia valori de la x_i la y_o
care sunt marginile unui interval) pentru a gasi noua pozitie unde adaug
ce se gasea in celula de la pozitia de pe linia anterioara de unde am plecat.
Sper ca se intelege, dar am sa mai fac o incercare la explicatie: ma aflu pe
linia i, iau de pe linia i - 1 de la pozitia j, iar ce e acolo adaug pe linia
i la pozitia j + k, k fiind pe rand fiecare element din intervalul de probleme
al copilului de pe linia i.
Schema: inca de la citire putem raspunde la intrebarea daca exista solutie sau
nu, calculand minimul intervalului si maximul. Din acest motiv la citire fac
ceva in plus pentru a verifica cazurile cand output ul este 0, dar aparent nu
exista teste pentru astea.


Problema 4:

Complexitate temporala O(n * log n)
Complexitate spatiala O(n)

La aceasta problema am aplicat metoda greedy si am folosit un vector pentru a
tine minte ganterele: perechile (greutate, repetitii). Am sortat acest vector
descrescator dupa greutati si am calculat cat ii cresc muschii lui Gigel pentru
primele gantere, de la prima pana la a M-a si pastram numai combinatia cea mai
buna.
Dupa aceea imi creez un min-heap in care imi tin la top gantera cea mai usoara.
Daca dau de o gantera (caut in vectorul sortat descrescator dupa greutate)
cu numarul de repetitii mai mare, care poate compenseaza pentru greutatea
mai mica, actualizez heapul (in log m) si verific cu solutia curenta.
