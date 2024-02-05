#!/bin/bash
for i in $(\ls testesEntrada/)
do
    echo "Testing ${i}"
    diff <(./14746450 < testesEntrada/${i}) testesSaida/${i}.out
    if [ $? -ne 1 ]
    then
        ((success++))
    fi
done
echo -e "Tests:\t\e[32m${success} passed\e[0m, $(\ls testesEntrada/ | wc -l) total"