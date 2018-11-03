#!/bin/sh

echo -e "\033[32m \n  
Menu Kompilacji:
Lista mozliwosci kompilacji: \n 
1 - DB & GAME\n 
2 - DB\n
3 - GAME\n
4 - Automatycznia Podmiana DB & GAME\n
 


Wpisz wybrana cyfre:"
read wybor
case $wybor in 

	1*)
		cd /usr/src/mainline_released/mainline_sg/Srcs/Server/db/src
		sh build_db.sh
		sleep 2
		cd /usr/src/mainline_released/mainline_sg/Srcs/Server/game/src
		sh build.sh
		echo "########### Budowanie DB & GAME Zakoñczone ###########"
	;;
	2*)
		cd /usr/src/mainline_released/mainline_sg/Srcs/Server/db/src
		sh build_db.sh
	;;
	3*)
		cd /usr/src/mainline_released/mainline_sg/Srcs/Server/game/src
		sh build.sh
	;;
	4*)
		mv -f /usr/src/mainline_released/mainline_sg/Srcs/Server/db/db /usr/home/mt2/db/ 2>/dev/null
		echo "########### Plik DB Zosta³ Przeniesiony ###########"
		sleep 2
		mv -f /usr/src/mainline_released/mainline_sg/Srcs/Server/game/game /usr/home/mt2/share 2>/dev/null
		echo "########### Plik GAME Zosta³ Przeniesiony ###########"
		sleep 2
	;;

esac
