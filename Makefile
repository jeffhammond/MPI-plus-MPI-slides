.PHONY: all clean warnings

all: main.pdf

%.pdf: %.tex
	#@rubber -d $<
	pdflatex main

clean:
	#@rubber --clean main
	-rm -f main.synctex.gz*
	-rm -f main.pdf
