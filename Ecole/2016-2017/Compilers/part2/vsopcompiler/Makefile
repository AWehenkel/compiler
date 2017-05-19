# This Makefile will be used to build your compiler.

all: vsopc extension

.PHONY:	all archive clean install-tools

# Your compiler
vsopc: bison flex preprocessing g++ io

extension: bison_ext flex_ext preprocessing_ext g++_ext io

bison:
	bison -v -d vsop_grammar.y

bison_ext:
	bison -v -d vsop_grammar_ext.y

io:
	gcc -std=c99 -g -O -c Libraries/io.c -o Libraries/io.o

flex:
	flex vsop_syntax.l

flex_ext:
	flex vsop_syntax_ext.l

preprocessing :
	patch -p0 vsop_grammar.tab.c < yystate.patch
	chmod +x vsopc

preprocessing_ext :
	patch -p0 vsop_grammar_ext.tab.c < yystate.patch
	chmod +x vsopc

g++ :
	g++ -std=c++11 SyntacticTree/*.cpp SyntacticTree/Expression/*.cpp SemanticAnalysis/*.cpp Visitors/*.cpp lex.yy.c vsop_grammar.tab.c -lfl -o vsopc_exe

g++_ext :
	g++ -std=c++11 SyntacticTree/*.cpp SyntacticTree/Expression/*.cpp SemanticAnalysis/*.cpp Visitors/*.cpp lex.yy.c vsop_grammar_ext.tab.c -lfl -o vsopc_ext_exe

generation :
	./merr.linux -B -s "make vsopc" -o yyerror.c ./vsopc_exe

# Should clean built files, and keep only source code. Adapt to your language
# and folder structure. If using git, you might want to use `git clean`.
clean:
	rm -f vsopc_exe *~ *.bak *.o *.class *.pyc vsop_grammar.output vsop_grammar.tab.c vsop_grammar.tab.h lex.yy.c Libraries/io.o

# First rule called when in a new VM. Use this target to install any software
# tools or libraries needed to build your compiler. e.g. assuming a C++ project
# using flex and bison, you might do something along the lines of:
#    sudo DEBIAN_FRONTEND=noninteractive apt-get -qq install clang flex bison
# Remember to use `sudo` if you need administrator privileges.
# Obviously, `make` is already installed. It is also the case of `llvm-dev`.
install-tools:
	sudo apt-get -y install bison
	sudo apt-get -y install flex
# This target will build a new archive of this cleaned folder in its parent
# directory. You can use it to generate an archive to be submitted for
# evaluation.
archive:	clean
	cd ..; tar cvJf vsopcompiler.tar.xz --exclude=.git --exclude=.svn --exclude=.svn-base vsopcompiler
