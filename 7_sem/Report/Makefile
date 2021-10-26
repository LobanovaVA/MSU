SRC = report

all: create clean_tmp

create:
	pdflatex $(SRC).tex
	pdflatex $(SRC).tex

clean_tmp:
	rm -f $(SRC).log $(SRC).dvi $(SRC).aux $(SRC).out $(SRC).toc
clean:
	rm -f $(SRC).log $(SRC).aux $(SRC).out $(SRC).toc $(SRC).pdf

