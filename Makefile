.PHONY: link clean
CFLAGS:=-g -Wall -Wextra -std=c11

Make:	clean link
compile: listechainee.o debutliste.o lecturefichier.o statistiques.o tri.o

#listechainee.o: listechainee.c listechainee.h 
#debutliste.o: debutliste.c debutliste.h 
#lecturefichier.o: lecturefichier.c lecturefichier.h 
#statistiques.o: statistiques.c statistiques.h 
#tri.o: tri.c  
#toutes les lignes en haut remplacees par la ligne en bas
%.o: %.c %h

compile_test: listechainee1.o debutliste1.o lecturefichier1.o statistiques1.o tri1.o

listechainee1.o: listechainee.c listechainee.h 
	gcc -g -Wall -Wextra --coverage -std=c11 -c listechainee.c
debutliste1.o: debutliste.c debutliste.h 
	gcc -g -Wall -Wextra --coverage -std=c11 -c debutliste.c
lecturefichier1.o: lecturefichier.c lecturefichier.h 
	gcc -g -Wall -Wextra --coverage -std=c11 -c lecturefichier.c
statistiques1.o: statistiques.c statistiques.h 
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
