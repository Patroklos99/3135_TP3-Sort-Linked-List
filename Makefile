Make: link
compile: listechainee.o pointeurliste.o lecturefichier.o statistiques.o tri.o

listechainee.o: listechainee.c listechainee.h pointeurliste.o 
	gcc -Wall -Wextra -std=c11 -c listechainee.c
pointeurliste.o: pointeurliste.c pointeurliste.h lecturefichier.o
	gcc -Wall -Wextra -std=c11 -c pointeurliste.c
lecturefichier.o: lecturefichier.c lecturefichier.h statistiques.o
	gcc -Wall -Wextra -std=c11 -c lecturefichier.c
statistiques.o: statistiques.c statistiques.h tri.o
	gcc -Wall -Wextra -std=c11 -c statistiques.c
tri.o: tri.c  
	gcc -Wall -Wextra -std=c11 -c tri.c

test: link
	bats check.bats
html: README.md
	pandoc -s --self-contained --css=./misc/github-pandoc.css --metadata title=" " README.md -o README.html
clean: 
	rm -f *.o *.html tri
link: compile
	gcc *.o -o tri
