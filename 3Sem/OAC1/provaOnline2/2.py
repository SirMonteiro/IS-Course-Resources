def modulo_cache(endereco, num_linhas):
    # endereco = int(endereco, 16)
    bits_indice = num_linhas.bit_length() - 1  # Número de bits para o índice
    mascara = (1 << bits_indice) - 1  # Máscara para extrair os bits do índice
    indice = endereco & mascara  # Aplicar a função módulo
    return indice

# endereco = 1441792
num_linhas = 16384
array = [0,1,2,3, 1441792,1441793,1441794,1441795, 1441796,1441797,1441798,1441799, 1455004,1455005,1455006,1455007]
for i in array:
    indice_linha = modulo_cache(i, num_linhas)
    print("Índice da linha na cache:", indice_linha)
