# This Makefile will be used to build your compiler.

all:	vsopc

.PHONY:	all archive clean install-tools

# Your compiler
vsopc:
	bison -v -d vsop_grammar.y
	flex vsop_syntax.l
	g++ -std=c++11 SemanticAnalysis/*.cpp SyntacticTree/*.cpp SyntacticTree/Expression/*.cpp lex.yy.c vsop_grammar.tab.c -lfl -o vsopc

# Should clean built files, and keep only source code. Adapt to your language
# and folder structure. If using git, you might want to use `git clean`.
clean:
	rm -f vsopc *~ *.bak *.o *.class *.pyc

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
