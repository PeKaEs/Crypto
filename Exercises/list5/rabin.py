N = 122351821
c = 67625338

for i in range(0, N):
    if pow(i, 2) % N == c:
        print i
