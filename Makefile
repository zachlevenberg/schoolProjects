#------------------------------------------------------------------------------
# A Makefile with macros
#------------------------------------------------------------------------------
JAVASRC = //insert .java source files here
SOURCES =  $(JAVASRC) //insert other files to include in submit
MAINCLASS = //insert the name of the main class
CLASSES = //insert .class source files here
JARFILE = //name the JARfile here
SUBMIT = submit cmps012b-pt.s15 lab1

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
