Make: link
compile: listechainee.o pointeurliste.o lecturefichier.o statistiques.o tri.o

listechainee.o: listechainee.c listechainee.h pointeurliste.o 
	gcc -g -Wall -Wextra --coverage -std=c11 -c listechainee.c
pointeurliste.o: pointeurliste.c pointeurliste.h lecturefichier.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c pointeurliste.c
lecturefichier.o: lecturefichier.c lecturefichier.h statistiques.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c lecturefichier.c
statistiques.o: statistiques.c statistiques.h tri.o
	gcc -g -Wall -Wextra --coverage -std=c11 -c statistiques.c
tri.o: tri.c  
	gcc -g -Wall -Wextra --coverage -std=c11 -c tri.c

test: compile
	gcc --coverage *.o -o tri
	gcc -Wall -fprofile-arcs -ftest-coverage -o test test.c -lcunit	
	./test 
	gcov test.c
html: README.md
	pandoc -s --self-contained --css=./misc/github-pandoc.css --metadata title=" " README.md -o README.html
clean: 
	rm -f *.o *.html *.gcov *.gcda *.gcno tri
	make test
link: compile
	gcc *.o -o tri
	gcc -Wall -fprofile-arcs -ftest-coverage -o test test.c -lcunit	
	./test 
	gcov test.c
