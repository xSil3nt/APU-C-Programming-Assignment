unsigned long hash(char *input) {
    //Prime number = 5381
    //We use a prime number as the starting seed value
    unsigned long hash = 5381;
    int modifier;

    
    //We store each char in the input string in modifier
    //Loop until we reach the end
    while((modifier = *input++)) {
        hash = hash * 33 + modifier;
    }

    return hash;
}