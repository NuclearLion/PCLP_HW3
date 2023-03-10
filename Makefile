#Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>

CC=gcc
CFLAGS=-Wall -Wextra -std=c99
FILES=$(wildcard *.c)

TARGET = image_editor

all:
	make clean; make build; make run

build: $(TARGET)

image_editor: image_editor.c
	$(CC) $(CFLAGS) $(FILES) -g -o image_editor

pack:
	zip -FSr 311CA_StaicuDan-Dominic_Tema3.zip README Makefile *.c *.h

clean:
	rm -rf $(TARGET)

run:
	./image_editor

.PHONY: pack clean
