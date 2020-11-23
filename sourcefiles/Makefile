all: clean  gnum msort m2bit m3bit


gnum: gen_numbers.cpp
	g++ gen_numbers.cpp -o gnum


msort: MergeSort.cpp
	g++ -std=c++11 MergeSort.cpp -o msort


m2bit: BranchStats_2Bits.h MergeSort_2Bit.cpp
	g++ -std=c++11 BranchStats_2Bits.h MergeSort_2Bit.cpp -o m2bit


m3bit: BranchStats_3Bits.h MergeSort_3Bit.cpp
	g++ -std=c++11 BranchStats_3Bits.h MergeSort_3Bit.cpp -o m3bit


clean:
	rm -f gnum
	rm -f msort
	rm -f m2bit
	rm -f m3bit


