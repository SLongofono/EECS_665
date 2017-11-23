int globby;

int foo(){
	int i;
	for(i = 0; i < 4; i += 1){
		if(i == 2){
			break;
		}
	}

	for(i = 0; i<4; i+= 1){
		if(i%2==0){
			globby = 1;
		}
		else{
			continue;
		}
	}
}

int main(){
	return foo();	
}
