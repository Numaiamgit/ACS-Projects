# Copyright PCLP Team, 2025

# Compiler setup.
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# Define targets, e.g., ninel, codeinvim, vectsecv, nomogram.
TARGETS=window akari helicopters

# Manually define all targets.
build: $(TARGETS)

window: window_join.c.c
	$(CC) $(CFLAGS) window_join.c.c -o window_join

akari: akari.c.c
	$(CC) $(CFLAGS) akari.c.c -o akari

helicopters: helicopters.c.c
	$(CC) $(CFLAGS) helicopters.c.c -o helicopters



# Pack the solution into a zip file.
pack:
	zip -FSr 3XYCA_FirstnameLastname_Tema0.zip README Makefile *.c *.h

# Clean the solution.
clean:
	rm -f $(TARGETS)

.PHONY: pack clean
