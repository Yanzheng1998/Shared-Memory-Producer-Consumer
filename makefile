

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

all: main.o queue.o Reader.o Munch1.o Munch2.o writer.o
	$(CC) -o $(EXE) main.o queue.o Reader.o Munch1.o Munch2.o writer.o $(PTHREAD)

main.o: main.c queue.h Reader.h Munch1.h Munch2.h writer.h
	$(CC) $(WARNING_FLAGS) -c main.c $(PTHREAD)

queue.o: queue.c 
	$(CC) $(WARNING_FLAGS) -c queue.c $(PTHREAD)

Reader.o: Reader.c queue.h
	$(CC) $(WARNING_FLAGS) -c Reader.c $(PTHREAD)

Writer.o: writer.c queue.h Reader.h
	$(CC) $(WARNING_FLAGS) -c Reader.c $(PTHREAD)

Munch1.o: Munch1.c queue.h Reader.h
	$(CC) $(WARNING_FLAGS) -c Munch1.c $(PTHREAD)

Munch2.o: Munch2.c queue.h Reader.h
	$(CC) $(WARNING_FLAGS) -c Munch2.c $(PTHREAD)


clean:
	rm -f $(EXE) *.o
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
