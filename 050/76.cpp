#include <iostream>
#include <vector>

int main(){
	int N = 100;
	std::vector<int> P(128, 0);
	P[0] = 1;

	for(int n = 1; n < N; n ++){
		for(int k = n; k <= N; k ++){
			P[k] += P[k-n];
		}	
		// std::cout << "n= " << n << " : "; 
		// for(int i = 0; i <= N; i++){
		// 	std::cout << P[i] << " ";
		// }
		// std::cout << "\n";
	}
	
	std::cout << P[N] << std::endl;

	return 0;
}
