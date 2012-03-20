CC=gcc
CPP=g++
JAVAC=javac
CFLAGS=-lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE
CPPFLAGS=-lm -lcrypt -O2 -pipe -DONLINE_JUDGE
JAVAFLAGS=

%: %.c
	$(CC) $(CFLAGS) -o a.out $^

%: %.cpp
	$(CPP) $(CPPFLAGS) -o a.out $^

%: %.java
	$(JAVAC) $(JAVAFLAGS) $^
