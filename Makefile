
all:
	cd tensor;        make ;    cd ../;
	cd py;            make ;    cd ../;
#	cd ithaca;        make ;    cd ../;
#	cd interface;     make ;    cd ../;
	cd scf;           make ;    cd ../

clean:
	cd tensor; rm *.o; cd ../;
	cd scf; make clean; cd ../
