int myGlobal;

int foo(int myParam){
	int myLocal;
	myLocal = myParam;
	return myGlobal;
}
