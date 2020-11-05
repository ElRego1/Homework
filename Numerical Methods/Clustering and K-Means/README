Rezolvare:

Task 1: Citesc datele din fisier folosind functia "dlmread"
Task 2: Imi aleg random centroizii si am grija sa nu fie aceiasi, apoi calculam niste clustere temporare. Ulterior recalculam noile pozitii ale centroizilr si verificam daca am ajuns la o precizie convenabil de mare.
	Probleme: Uneori gaseste niste centroizi care impart clusterele intr-un mod neeficient (au costul mare) si pica testul 2 mai ales uneori.
	Solutie: Fac gasirea de noi centroizi de mai multe ori, de cate ori vreau numai prin schimbarea variabilei "no_of_checks" si imi calzuleaza la final "no_of_checks" * numarul de centroizi doriti si stocheaza costul lor, iar ulterior aleg centroizii cu cel mai mic cost dupa cum calculez folosind task-ul 4.
Task 3: Imi recreez "norii" de puncte cele mai apropiate de centroizii gasiti si apoi folosesc functia "scatter3" ca sa ii afisez vizibil.
Task 4: Imi fac un vector cu normele euclidiene pt fiecare punct la fiecare centroid si aleg norma cea mai mica si o adaug la costul final.

Task 5: ma folosesc de functiile create la task-ul 2 si 4 si un contor de la 1 la 10 si plotuiesc in grafic costul in functie de numerele de centroizi alesi.