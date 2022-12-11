read wiersze
read kolumny
read dlugosc

gcc -DWIERSZE=$wiersze -DKOLUMNY=$kolumny -DDLUGOSC=$dlugosc palindrom.c -o palindrom_do_testow
gcc -DWIERSZE=$wiersze -DKOLUMNY=$kolumny -DDLUGOSC=$dlugosc generator_testow.c -o generator_testow

./generator_testow > ./testy/test_${wiersze}_${kolumny}_${dlugosc}.in

cat ./testy/test_${wiersze}_${kolumny}_${dlugosc}.in | ./palindrom_do_testow > ./testy/test_${wiersze}_${kolumny}_${dlugosc}.out
