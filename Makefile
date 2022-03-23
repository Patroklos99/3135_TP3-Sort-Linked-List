tri:  tri.c 
	gcc -o tri -Wall -Wextra -std=c11 tri.c
test: tri
	bats check.bats
html: README.md
	pandoc -s --self-contained --css=./misc/github-pandoc.css --metadata title=" " README.md -o README.html
clean: 
	rm -f *.o *.html tri

