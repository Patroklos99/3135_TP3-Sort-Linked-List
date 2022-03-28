# TP2: Tri

## Description

Projet(suite III) d'introduction au langage C. Ce projet execute la lecture d'un fichier comme argument et fait l'affichage trié (sans doublons) du fichier lu.

Le fichier lu sera passé comme argument et traité ensuite.
L'option -S sera passé comme argument aussi.
La redirection n'est pas supportée.

*Fichier `Makefile:`*
Il contient la construction de chaque commande make (compile, link, test et plus). C'est-à-dire leur cible et leurs dépendences pour l'exécution correctet la compilation finale de l'executable

*Commandes make et leur rôle:*

* `make:` Compile le fichier `tri.c`.
* `make link:` Debut du programme, execute la commande `compile`.
* `make compile:` Execute la compilation générale avec toutes ses dependances \*.o.
* `make test:` Execute les tests du fichier `check.bats` sur `tri`. Ou Compile 
`tri.c:` s'il ne l'est pas encore et execute les tests par la suite.
* `make html:` Convertit `README.md` en fichier html.
* `make clean:` Efface les fichiers `\*.o` et/ou `\*.html` ainsi que tout autre type de fichier
ce trouvant dans le fichier `.gitignore`.

Ce travail est realisé en vue du travail TP3 dans le cadre du cours Construction et
maintenance de logiciels INF3135. Cours donné par Serge Dogny à l'Université de Québec à Montreal.

Lien vers le [README du travail](https://gitlab.info.uqam.ca/salcedo_salcedo.renzo/inf3135-hiver2022-tp3/-/blob/main/README.md).

***Tous les tests ont étés réussis sur ma machine comme sur le serveur Labunix de l'UQAM***

## Auteur

Renzo Arturo Salcedo (SALR02089408).

## Fonctionnement

Pour commencer, compilez le fichier `tri.c` avec la commande:
```sh
$ make
```
Vous obtiendrez l'exécutable `tri`. 

Par la suite, vous executez l'executable avec le fichier commme argument (i.e `./tri liste.txt`)

Voici les regles à respecter pour vos entrées:

* Le fichier doit exister.
* Un argument (le fichier à lire) ou 3 arguments, le fichier plus l'option suivi du nom du fichier à créer peuvent être utilisés.

Voici une suite de tests valides comme exemple (stdin sur la ligne de commande commmearg):
```sh
$  make 
$ ./tri liste.txt
$ ./tri liste.txt -S stats.txt
```

## Tests

Pour lancer les tests ecrivez `make test` sur la ligne de commande.
Vous obtiendrez les résultats du fichier `TODO`, qui vous informera de vos tests réussis et ceux échoués.

Si vous n'avez pas le fichier `tri` avant de lancer cette commande, la 
commande `link` sera lancée en parellèle suivie de toutes ses dependances et 
un fichier `tri` sera créé automatiquement. 
```sh
$ make test
``` 
Cette commande exécute les tests `CUNIT` sur `tri`. Ou Compile 
`tri.c` s'il ne l'est pas encore et execute les tests par la suite.

## Dépendances

* [GCC](https://gcc.gnu.org/).
* [Bats](https://github.com/bats-core/bats-core). A verifier
* [Pandoc](https://pandoc.org/).
* [Make](https://www.gnu.org/software/make/).
* [Git](https://git-scm.com/).
 

## Références

De facon générale le site [Stackoverflow](https://stackoverflow.com/) a été utilisé pour la 
compréhension de certaines fonctions. 
Des discussions sur le mattermost du cours ont aussi servis d'inspiraton dans ce travail.

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
* [X] Le fichier `Makefile` permet de compiler le projet lorsq'on entre
  `make`. Il supporte les cibles `html`, `compile`, `link`, `test` et `clean`.
* [X] L'indentation doit être de 3 espaces. Aucune tabulation n'est permise dans l'indentation.
* [X] L'en-tête du fichier main est documentée.
* [X] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [X] Gitlab-CI est implementé.
