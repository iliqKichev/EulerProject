#include<iostream>
#include<vector>

//int get_next_number(int n){
//    if(n == 1){
//        return 1;
//    }
//    if(n == 89){
//        counter ++;
//        return 89;
//    }
//    int sum = 0, tmp = n;
//    while(tmp > 0){
//        sum += (tmp%10)*(tmp%10);
//        tmp /= 10;
//    }
//    numbers[n] = get_next_number(sum);
//    return numbers[n];
//}

int main(){
    std::vector<int> numbers;
    numbers.resize(1024);
    for(int &i: numbers){
        i = 0;
    }

    int counter = 0;
    int tmp, sum;
    for(int i = 1; i < numbers.size(); i ++){
        tmp = i; sum = 0;

        while(true){
            while(tmp > 0){
                sum += (tmp%10)*(tmp%10);
                tmp /= 10;
            }
            if(numbers[sum]){
                numbers[i] = numbers[sum];
                break;
            }
            if(sum == 1){
                numbers[i] = 1;
                break;
            }
            if(sum == 89){
                numbers[i] = 89;
                break;
            }
            tmp = sum; sum = 0;
        }
    }
    for(int i = 1; i < 10000000; i++){
        tmp = i; sum = 0;
        while(tmp > 0){
            sum += (tmp%10)*(tmp%10);
            tmp /= 10;
        }
        if(numbers[sum] == 89){
            counter ++;
        }
    }
    std::cout << counter << std::endl;
    return 0;
}
