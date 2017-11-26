int foo(){
	return 1;	
}

int bar(int param1){
	int temp;
	temp = foo();
	return (param1 + temp);
}
