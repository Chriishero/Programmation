#include <unistd.h>

void ft_print_combn(int n){
	if(n < 0 || n > 9) return;

	char buffer[n+1];
	int i = 0;

	for (i; i < n; i++){
		buffer[i] = '0';
	}

	while (buffer[0] <= '9' - n + 1){
		write(1, &buffer, n+1);
	}
}

int main(){
	ft_print_combn(4);
	return 0;
}
