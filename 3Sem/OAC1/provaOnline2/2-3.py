from math import floor

def modulo_cache(endereco, num_linhas):
    return (floor(endereco/4)) % 8192

# endereco = 1441792
num_linhas = 16384
v = 8192
array = [0,1,2,3, 1441792,1441793,1441794,1441795, 1441796,1441797,1441798,1441799, 1455004,1455005,1455006,1455007]
array = [0x000000, 0x000001, 0x000002, 0x000003,
0x160000, 0x160001, 0x160002, 0x160003,
0x160004, 0x160005, 0x160006, 0x160007,
0x16339C, 0x16339D, 0x16339E, 0x16339F,
0x16FFFC, 0x16FFFD, 0x16FFFE, 0x16FFFF,
0xFFFFF8, 0xFFFFF9, 0xFFFFFA, 0xFFFFFB,
0xFFFFFC, 0xFFFFFD, 0xFFFFFE, 0xFFFFFF]

counter = 0
for i in array:
    if counter == 4:
        counter = 0
        print()
    counter = counter + 1
    indice_linha = modulo_cache(i, num_linhas)
    print("Índice da linha na cache:", hex(indice_linha))

