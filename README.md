# multi-dimensional-dijkstra
Popolvar - Implementing Dijkstras algorithm to save all the princeses using multiple dimensions


Zadanie - Popolvar

Príbeh:
  Popolvár je jednoduchý chlapec z dediny, ktorý celé dni nerobí nič iné ako vynášanie popola
  zo sporáka v kuchyni a programovanie pre dobročinné účely. Dnes, ako tak surfoval po
  internete, sa k nemu dostala veľmi pohoršujúca správa. V neďalekej krajine uniesol drak
  viaceré princezné a schoval sa vysoko v horách, kde je veľmi ťažký prístup a chystá sa tam
  zajtra o polnoci všetky princezné zjesť.
  Samozrejme, že sa tomu nemôžete len tak nečinne prizerať. Vďaka moderným technológiám
  máte k dispozícii aj mapu, ktorú rýchlo zverejnil kráľ – otec unesených nešťastníc. Vašou
  úlohou je teda prirodzene čo najskôr najprv zneškodniť draka a potom zachrániť všetky
  unesené princezné. Predpokladajte, že drak uniesol najviac 5 princezien.


Mapa predstavuje dvojrozmernú mriežku políčok:

      C | Lesný chodník
      
      H | Hustý lesný porast, cez ktorý idete dva-krát pomalšie ako po lesnom chodníku
      
      N | Nepriechodná prekážka (napr. príliš strmá skala)
      
      D | Drak
      
      P | Princezná
      
      0-9 | Teleport, ktorým sa môžete preniesť
      
      G | Generátor, ktorým zapnete (energiu pre) teleporty
      
      
 
Dôležité poznámky: Okrem cestovania teleportom sa Popolvár presúva len v štyroch smeroch (hore,
dole, doľava, doprava). Ak nie je zadané inak, prechod cez políčko trvá štandardne jednu jednotku
času. Teda cez políčka s drakom, princeznou, teleportom a generátorom trvá prechod tiež jednu
jednotku času. Generátor je na mape najviac jeden. Do výsledného času sa započítavajú všetky
políčka, cez ktoré Popolvár prejde. Ak teda začne na políčku (0,0), prejde cez políčko (1,0) a skončí na
políčku (1,1), pričom všetky tri políčka obsahujú lesný chodník, tak Popolvárovi to trvá 3 jednotky
času. Zneškodnenie draka, nástup do teleportu, prenos teleportom a zapnutie generátora je
okamžitá akcia, ktorých trvanie je zanedbateľné vzhľadom na čas trvania prechodu cez políčko, ich
zarátavame s nulovou dĺžkou trvania. Keďže Popolvár má celú radu ďalších princezien, ktoré musí
ešte zachrániť v iných častiach sveta (na vstupe je viacero kráľovstiev, v ktorých chce zachrániť
princezné), musíte čo najskôr zachrániť princezné (celkovo vrátane zneškodnenia draka), aby ste
mohli čím skôr prejsť do ďalšieho kráľovstva. Na zadanej mape je vyznačených najviac 5 princezien.




