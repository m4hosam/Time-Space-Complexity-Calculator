int counter[20] = {0};

int sumtest(int x,int y,int size){
    int sum;
    counter[0]++;
    for(int i = size ; i > 0 ; i/= 2){
        counter[1]++;
        sum = x+y;
    }
    counter[2]++;

    return sum;
}
