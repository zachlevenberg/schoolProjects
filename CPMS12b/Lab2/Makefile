#------------------------------------------------------------------------------
# A Makefile for Search.java
#------------------------------------------------------------------------------
JAVASRC = Search.java //insert .java source files here
SOURCES = README Makefile $(JAVASRC) //insert other files to include in submit
MAINCLASS = Search//insert the name of the main class
CLASSES = Search.class //insert .class source files here
JARFILE = Search//name the JARfile here
SUBMIT = submit cmps012b-pt.s15 pa2

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(CLASSES) $(JARFILE)

submit: $(SOURCES)
	$(SUBMIT) $(SOURCES)
