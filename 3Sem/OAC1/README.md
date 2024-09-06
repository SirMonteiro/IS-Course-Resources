
** Assuntos abordados e referências até 15 de abril

- Relação entre código-fonte em C e código-fonte em alguma linguagem de montagem (assembly) - referência: https://docs.google.com/presentation/d/1cRi9s4D9oYduHI_91IurZJ8yha-Y6sNJaRYFs1lKHsY/edit?usp=drive_link (apresentação da aula 1)

- Bases numéricas (para entender a relação entre números inteiros em base decimal, binária, hexadecimal e facilitar a compreensão dos números no material da disciplina) - referência: STALLINGS, 10ed. capítulo 9;

- Eletricidade, circuitos e sinais elétricos, relé, transisitor como chave (sobre a interpretação dada para sinais elétricos como passagem de corrente ou níveis de tensão como "zero" ou "um" e componentes que controlam sinais elétricos). Referência: https://github.com/FNakano/OAC1/blob/main/oProblema.md , https://github.com/FNakano/CFA/blob/master/eletricidade.md , https://github.com/FNakano/CFA/blob/master/circuitosEletricos.md , https://docs.google.com/presentation/d/1QHRb8vf_1OvE2vgKSVSb5ou90LHJsztSrkDR-NVQGgA/edit?usp=drive_link (aula 2)

- Portas lógicas, circuitos combinacionais, comparador, somador. referências: STALLINGS, 10ed. capítulo 11; https://docs.google.com/presentation/d/1YxbRucKSIKNXmLzSXzQWaA0J6PSNvZrU6dt-5Emb_Vw/edit?usp=drive_link (apresentação aula três) https://docs.google.com/presentation/d/1i80VvU0Krr8AMFxAnDmJNveDx2lgw6vd74Bz_xBqBZw/edit?usp=drive_link (apresentação  aula 4) https://docs.google.com/presentation/d/1mLhbhf50bP29N2rKVy5e9Jux_k-vC75SJZl5dbpGS2k/edit?usp=drive_link (apresentação aula 5) https://docs.google.com/presentation/d/13siwvhsqEcJ4bJ7VTVNY3Lszty61Uc8_yK_1hYwDGDY/edit?usp=drive_link (apresentação aula 7 parte 1)

- Flip-flops, circuitos sequenciais, autômato finito, memórias: EPROM e SRAM. Referências: STALLINGS, 10ed. capítulo 11; https://docs.google.com/presentation/d/12vNTVsrl7R6PWSwlq80xfv_48tmbt61xPl7OXQhKxss/edit?usp=drive_link (apresentação aula 6), https://docs.google.com/presentation/d/1ii8AxzFLW6DzPJJ5NEsLRRsOpS6p9aUxaqW0ZgeUjGg/edit?usp=drive_link (apresentação aula 7 parte 2) , https://docs.google.com/presentation/d/19J4FAQp0MSWTCK49rLGkLQ7Cp3nxK8hvlftvnL0_NVU/edit?usp=drive_link (apresentação aula 8) , https://edisciplinas.usp.br/mod/page/view.php?id=5244018 (construção do autômato do verbete da Wikipedia) , https://docs.google.com/presentation/d/1pZj072lju7J209gopQjqnPhu5pzy13ta4As_lO8o8Vk/edit?usp=drive_link (apresentação da aula 9)

- Revisão e conexão dos assuntos da disciplina. Referência https://docs.google.com/presentation/d/1OUgvjTNS9iu4_btxAJXA19Msu1b7mpjpc2O_eRNqch8/edit?usp=drive_link (apresentação da aula 10)

- Construção incremental de uma unidade de processamento. Referência: https://github.com/FNakano/OAC1/tree/main/meuProcessador

- Planejamento para próximas aulas: ISA de várias arquiteturas, compilação, EPs.

** Construção do autômato da wikipedia

Aceita se quantidade de zeros na entrada for par (https://en.wikipedia.org/wiki/Automata_theory#/media/File:DFAexample.svg).



Tabela de transição

Entrada 	Estado atual 	Próximo Estado
0 	1 	2
1 	1 	1
0 	2 	1
1 	2 	2
Passando para binário

Entrada 	Estado atual 	Próximo Estado

	Estado=1 	Estado=2 	Estado=1 	Estado=2
0 	1 	0 	0 	1
1 	1 	0 	1 	0
0 	0 	1 	1 	0
1 	0 	1 	0 	1


Expressões lógicas dos próximos estados

PróximoEstado=1    ((Entrada e Estado=1 e não(Estado=2) ou(não(Entrada) e não(Estado=1) e Estado=2))
PróximoEstado=2    (Entrada e não(Estado=1) e Estado=2) ou (não(Entrada) e Estado=1 e não(Estado=2))



Colocando todas as combinações de entrada, daria para simplificar a expressão lógica, mas a idéia aqui é manter claro e com poucas etapas.
Também daria para representar os estados com só um bit, mas isso atrapalharia o entendimento dos autômatos não determinísticos.
