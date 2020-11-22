all: clean msort m2bit

msort: MergeSort.cpp
	g++ MergeSort.cpp -o msort


m2bit: BranchStats.h MergeSort_2Bit.cpp
	g++ BranchStats.h MergeSort_2Bit.cpp -o m2bit

clean:
	rm -f msort
	rm -f m2bit


