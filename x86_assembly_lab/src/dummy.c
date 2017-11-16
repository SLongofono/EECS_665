#include <stdio.h>

int nothing(int i, int j){
	return 1;
}


int main(){

	int i, j;
	
	i = nothing( 100, 10);
	j = i + 1;

}
