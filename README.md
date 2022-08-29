# TP3: Tri

## Description

Projet(suite III) d'introduction au langage C. Ce projet execute la lecture d'un fichier comme argument et fait l'affichage trié (sans doublons) du fichier lu.

Le fichier lu sera passé comme argument et traité ensuite.
L'option -S sera passé comme argument suivie du *.txt de sortie.
La redirection n'est pas supportée.

*Fichier `Makefile:`*
Il contient la construction de chaque commande make (compile, link, test et plus). C'est-à-dire leur cible et leurs dépendences pour l'exécution correctet la compilation finale de l'executable

*Commandes make et leur rôle:*

* `make:` Par l'exécution sur le fichier `tri.c`.
* `make link:` Debut du programme, execute la commande `compile`.
* `make compile:` Execute la compilation générale avec toutes ses dependances \*.o.
* `make test:` Execute les tests du fichier `test.c` sur `tri`. Ou Compile 
`tri.c` à partir de `compile_test` pour eviter les erreurs de l'edition des liens s'il ne l'est pas encore et execute les tests par la suite.
* `make html:` Convertit `README.md` en fichier html.
* `make clean:` Efface les fichiers `*.o` et/ou `*.html` ainsi que tout autre type de fichier
ce trouvant dans le fichier `.gitignore`.

Ce travail est realisé en vue du travail TP3 dans le cadre du cours Construction et
maintenance de logiciels INF3135. Cours donné par Serge Dogny à l'Université de Québec à Montreal.

Lien vers le [README du travail](https://gitlab.info.uqam.ca/salcedo_salcedo.renzo/inf3135-hiver2022-tp3/-/blob/main/README.md).

***Tous les tests ont étés réussis sur ma machine comme sur le serveur Labunix de l'UQAM***

## Auteur

Renzo Arturo Salcedo (SALR02089408)

## Fonctionnement

Pour commencer, compilez le fichier `tri.c` avec la commande:
```sh
$ make
```
Vous obtiendrez l'exécutable `tri`. 

Par la suite, vous executez l'executable avec le fichier à lire commme argument (i.e `./tri liste.txt`)

Voici les regles à respecter pour vos entrées:

* Le fichier doit exister.
* Un argument (le fichier à lire) ou 3 arguments et le fichier plus l'option suivi du nom du fichier à créer peuvent être utilisés.

Voici une suite d'executions valides comme exemple (stdin sur la ligne de commande):
```sh
$  make 
$ ./tri liste.txt
$ ./tri liste.txt -S stats.txt
```

## Tests

Pour lancer les tests ecrivez `make test` sur la ligne de commande.
Vous obtiendrez les tous les résultats du fichier `test.c`, qui vous informera de tests réussis et ceux échoués.

Si vous n'avez pas le fichier `test` avant de lancer cette commande, la 
commande `compile_test` sera lancée en parellèle suivie de toutes ses dependances et 
un fichier `test` sera créé automatiquement. 
```sh
$ make test
``` 
Cette commande exécute les tests `CUNIT` sur `test.c`. Ou Compile 
`test.c` s'il ne l'est pas encore et execute les tests par la suite.

### Optionel (Visualiser les tests)
Vous devez `absolument` installer `lcov` et avoir accès à `firefox`:
```sh
$ sudo apt install lcov
``` 
Une fois lcov installé, vous devez decommenter cette partie de la cible `test` dans le Makefile
```Makefile
test:   clean compile_test
        gcc -g --coverage -std=c11 -o test test.c -lcunit       
        ./test 
        gcov test.c
 ##      lcov -c -d . -o my.info
 ##      genhtml -o results/ my.info
 ##      firefox results/inf3135-hiver2022-tp3/index.html
``` 

## Dépendances

* [GCC](https://gcc.gnu.org/).
* [Bats](https://github.com/bats-core/bats-core). A verifier
* [Pandoc](https://pandoc.org/).
* [Make](https://www.gnu.org/software/make/).
* [CUnit](http://cunit.sourceforge.net/).
* [Gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html).
* [Valgrind](https://valgrind.org/).
* [lcov](http://ltp.sourceforge.net/coverage/lcov.php).
* [gdb](https://www.sourceware.org/gdb/).
* [Git](https://git-scm.com/).
 

## Références

De facon générale le site [Stackoverflow](https://stackoverflow.com/) a été utilisé pour la 
compréhension de certaines fonctions. 

## État du projet

* [X] Le programme compile sans erreurs dans le serveur Java de l'UQAM (Pénalité de
  **20%**).
* [X] Le nom du dépôt GitLab est exactement `inf3135-hiver2022-tp3` (Pénalité de
  **20%**).
* [X] L'URL du dépôt GitLab est exactement `https://gitlab.info.uqam.ca/<utilisateur>/inf3135-hiver2022-tp3`
https://gitlab.info.uqam.ca/salcedo_salcedo.renzo/inf3135-hiver2022-tp3
  (Pénalité de **20%**).
* [X] L'utilisateur `dogny_g` et les correcteurs ont accès au projet en mode *Developer*
  (Pénalité de **20%**).
* [X] Le dépôt GitLab est privé (Pénalité de **20%**).
* [X] Cunit implementé avec une couverture d'au moins 80% (Pénalité de **20%**).
* [X] Un fichier README est fourni et respecte le format Markdown **20%**.
* [X] Le dépôt contient au moins un fichier `.gitignore`.
* [X] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre
  `make`. Il supporte les cibles `html`, `compile`, `link`, `test` et `clean`.
* [X] L'indentation doit être de 3 espaces. Aucune tabulation n'est permise dans l'indentation.
* [X] L'en-tête du fichier main est documentée.
* [X] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [X] Gitlab-CI est implementé.
