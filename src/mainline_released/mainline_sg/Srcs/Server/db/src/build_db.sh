echo "### Budowa Pliku DB Rozpocz�ta ###"
echo "### Czyszczenie ###"
gmake clean
echo "### Budowanie ###"
gmake -j20 > ../DB_BUILD_LOG.txt 2> ../DB_ERROR_LOG.txt
echo "### Zako�czono Budow� Pliku DB ###"