
 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
# debug=-g
debug=
exec=exec
dane=dat


__ : $(exec)/main
	$(exec)/main -h  
	$(exec)/main -i $(dane)/populacja.txt -o $(dane)/populacja-czworkowa.out -r 0.5 -w 0.2 -k 10 -p 10

	
$(exec)/main : $(exec)/main.o   $(exec)/ZestawFunkcji.o  $(exec)/Listy.o $(exec)/TestArgumentow.o
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
	            
$(exec)/main.o : main.cpp 
	if [ ! -d $(exec) ] ; then mkdir $(exec) ; fi 
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 
	
$(exec)/ZestawFunkcji.o : ZestawFunkcji.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		

$(exec)/Listy.o : Listy.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
		
$(exec)/TestArgumentow.o : TestArgumentow.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -c -o $@ $^ 		
		
	
clear :
	rm *.o
	rm main	
	
	
doxy: 
	doxygen Doxyfile
	

