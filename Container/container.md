# Containers:
## Exercice 1 — Prise en main

Objectif : vérifier que tu sais utiliser un container, pas juste l’inclure.

Consignes

1. Écris un programme C++ qui :
   - crée un std::vector<int>
   - y ajoute les nombres : 5, 10, 15, 20
   - affiche tous les éléments dans l’ordre

2. Contraintes :
   - pas de boucle for classique avec indices
   - utilise soit :
     - une boucle range-based for
     - soit des itérateurs


## Exercice 2 — vector vs list (piège inclus)

Objectif : Tu dois stocker une suite d’entiers et effectuer des insertions au milieu.

Implémentation :
- Écris deux fonctions :
	- void test_vector(void);
	- void test_list(void);


- Chaque fonction doit :
	- créer un container (std::vector<int> pour l’une, std::list<int> pour l’autre)
	- insérer les valeurs 1 à 5
	- insérer la valeur 42 juste avant le 3ᵉ élément
	- afficher le contenu final

Contraintes :
pas d’accès par indice ([i])
insertion via itérateurs uniquement