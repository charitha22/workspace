all  : g++ clang++ 

g++ :
	g++ -O3 -fopenmp blur.cpp -o blur_g++

clang++ :
	clang++ -O3 -fopenmp blur.cpp -o blur_clang

clean : 
	rm -f blur