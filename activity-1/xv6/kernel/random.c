static int next = 1046836;

int random(int max) {
    if (max < 1)
        return 0;
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % max;
}
