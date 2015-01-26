# coding: utf-8

CC = gcc
CFLAGS = -W -O2 -pg -g -pipe
CXX = g++
CXXLFAGS = -W -O2 -pg -g -pipe

TARGET = lcs

# TODO need change
ifeq (Windows_NT, $(OS))
TARGET := $(TARGET).exe
endif

all : $(TARGET)

.PHONY : all tags

lcs : lcs.c
	$(CC) $(CFLAGS) -o $@ $^

clean :
	-$(RM) lcs
