Lica Robert Mihai <robertlica21@gmail.com>

Problema 1:

Complexitate temporala O(n * (n + m))

M-am gandit sa verific daca din Orasul lui Robin Hood pot sa ajung intr-un oras
de unde pornesc inamicii. Astfel pornesc cu un BFS din orasul 1 si daca dau de
un oras de unde vor porni inamicii lui Robin Hood, ma opresc si mai adaug un 
oras la cele blocate. In BFS-ul meu tratez orasele blocate ca si orase deja 
vizitate si nu ne mai intereseaza sa le luam si pe acelea in frontiera BFS-
ului. Fac aceasta operatiune de maxim n - 1 ori. Stiu ca nu este cea mai optima
solutie, dar momentan am gasit numai acest n^2.


Problema 2:

Complexitate temporala O(n + m)

Deoarece nu avem cicluri in graful nostru conform enuntului, putem avea o
abordare mai eficienta decat Bellman-Ford. Realizam o sortare topologica (si
pastram aceasta sortare intr-o stiva) dupa care in ordinea sortarii trecem prin
toate nodurile si le calculam costurile minime pentru a ajunge in ele. Daca 
nodul care ne vine la rand nu a mai fost explorat, ii dam skip deoarece nu o sa
ne apara in cale si nu trebuie sa tinem cont de el. Pentru a intelege aceasta
abordare, deoarece initial am folosit Bellman-Ford, am folosit acest site care
expune avantajele foarte bine:
https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/


Problema 3:

Complexitate temporala O(m * log n)

Aceasta problema poate fi redusa la urmatoarea cerinta dupa ce scoatem tot
lore-ul despre Robin Hood. Care este drumul de la A la B de cost maxim, stiind
ca plimbandune intre 2 noduri, i si i+1, pierdem p_i_i+1% energie din cat aveam
in nodul i. Astfel am realizat un Dijkstra care foloseste un maxheap pentru a
mege mereu mai departe din nodurile cu cea mai multa energie si doar am
schimbat modul de a calcula "costul" ce se lua in considerare la algoritmul
Dijkstra clasic.


Problema 4:

Complexitate temporala O()
