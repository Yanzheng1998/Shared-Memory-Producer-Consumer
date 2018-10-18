

#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = prodcomm
SCAN_BUILD_DIR = scan-build-out
PTHREAD = -lpthread

all: main.o queue.o 
	$(CC) -o $(EXE) main.o queue.o $(PTHREAD)

main.o: main.c queue.h
	$(CC) $(WARNING_FLAGS) -c main.c $(PTHREAD)

queue.o: queue.c 
	$(CC) $(WARNING_FLAGS) -c queue.c $(PTHREAD)

clean:
	rm $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
