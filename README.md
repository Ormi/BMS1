# BMS1
Project for BMS - Wireless and Mobile Networks


#Projekt 1
Naprogramujte v jazyce C++/Python jednoduchou konzolovou aplikaci (bms1), která bude realizovat demultiplexing a analýzu transportního streamu vysílání digitální televize.

#Parametry programu:
./bms1 nazev_souboru.ts

#Funkce programu:
Načítá vstupní soubor (nazev_souboru.ts), který obsahuje data transportního streamu DVB-T vysílání. Výstupem aplikace bude soubor s názvem nazev_souboru.txt, která bude obsahovat detaily pro každý vyextrahovaný kanál ze zpracovávaného transportního streamu.

#Obsah a formát výstupu
*	Soubor bude obsahovat v hlavičce informace o zpracovávaném multiplexu získané z NIT servisní tabulky, detaily o jednotlivých programech získané z tabulek PAT a SDT, které budou doplněny o souhrnnou statistiku přenosové rychlosti pro 	všechny kanály, které patří k jednomu programu.

*	Každý řádek popisující jeden program multiplexu bude mít následující formát:
PID-service_provider-service_name: <bitrate> Mbps

*	Jednotlivé řádky budou seřazeny podle hodnoty PID.

*	Bitrate počítejte na základě počtu paketů daného programu vzhledem k celkovému počtu paketů. Teda podle vzorce:
bitrate_programu = pocet_paketu_pro_program/celkovy_pocet_paketu*bitrate_streamu
V případě, že program obsahuje více video/audio stop případně servisní informace, sčítejte bitrate všech těchto kanálu do společné hodnoty.
*	Přenosovou rychlost zaokrouhlete na 2 desetinné místa.