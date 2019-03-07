make: filecopy.c matrix.c
	gcc filecopy.c -o badassexecutable
	gcc matrix.c -lpthread -o matrixexe
clean:
	rm badassexecutable
test:
	./badassexecutable fromDoc.txt toDoc.txt
run:
	./matrixexe