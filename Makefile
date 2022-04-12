Make:	clean link
compile: listechainee.o debutliste.o lecturefichier.o statistiques.o tri.o

listechainee.o: listechainee.c listechainee.h debutliste.o 
	gcc -g -Wall -Wextra -std=c11 -c listechainee.c
debutliste.o: debutliste.c debutliste.h lecturefichier.o
	gcc -g -Wall -Wextra -std=c11 -c debutliste.c
lecturefichier.o: lecturefichier.c lecturefichier.h statistiques.o
	gcc -g -Wall -Wextra -std=c11 -c lecturefichier.c
statistiques.o: statistiques.c statistiques.h tri.o
	gcc -g -Wall -Wextra -std=c11 -c statistiques.c
tri.o: tri.c  
	gcc -g -Wall -Wextra -std=c11 -c tri.c


compile_test: listechainee1.o debutliste1.o lecturefichier1.o statistiques1.o tri1.o

listechainee1.o: listechainee.c listechainee.h debutliste1.o 
	gcc -g -Wall -Wextra --coverage -std=c11 -c listechainee.c
debutliste1.o: debutliste.c debutliste.h lecturefichier1.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c debutliste.c
lecturefichier1.o: lecturefichier.c lecturefichier.h statistiques1.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c lecturefichier.c
statistiques1.o: statistiques.c statistiques.h tri1.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c statistiques.c
tri1.o: tri.c  
	gcc -g -Wall -Wextra --coverage -std=c11 -c tri.c

test:	clean compile_test
	gcc -g --coverage -std=c11 -o test test.c -lcunit	
	./test 
	gcov test.c
##	lcov -c -d . -o my.info
##	genhtml -o results/ my.info
##	firefox results/inf3135-hiver2022-tp3/index.html
html: README.md
	pandoc -s --self-contained --css=./misc/github-pandoc.css --metadata title=" " README.md -o README.html
clean:
	rm -rf *.o *.html *.gcov *.gcda *.gcno tri test temp.txt my.info results
link: compile
	gcc *.o -o tri
