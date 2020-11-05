// Copyright Robert Lica robertlica21@gmail.com

Pentru rezolvarea temei am impartit-o in mai multe parti:

1) Jucatorii

Am creat idea abstracta de jucator si am implementat pe baza ei cele 3 strategii. Pentru sortarea cartilor dupa frecventa etc, am facut ca intr-un boardgame adevarat si am grupat cartile identice impreuna (obiectul "Cards").

2) Jocul efectiv

Crearea jocului se face prin 2 metode in "main" si clasa "Game" am realizat-o singleton deoarece cu acelasi joc (boardgame) poti juca doar o data pe rand. Asa ca exista pregatirea jocului si jocul efectiv in care fiecare ia rolul de serif consecutiv.

3) Bonusurile

Aplicarea bonusurilor si printarea clasamentului este facuta imediat dupa terminarea partii de joc si se face automat dupa finalul ultimei runde.

//============================================================

La acest link am sa adaug diagrama UML creata in IntelliJ. Aceasta se afla si in arhiva trimisa pe VMChecker atat ca si png cat si ca fisier "diagram.uml"
diagram.uml https://drive.google.com/file/d/1sch9MzW6S2LSmxYc9s-MevCUvN3XgNdw/view?usp=sharing
uml.png https://drive.google.com/file/d/1tVRhPKneZ69aARB5oYRTpD2Lw-KsUviX/view?usp=sharing