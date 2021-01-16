O sa incep descrierea programului prin a descrie cele 3 fisiere.
Copii.txt-aici se afla datele despre copii si dorintele acestora. Separatorii sunt foarte importanti: datele despre copii sunt separate 
	  prin virgula, iar cadourile sunt separate intre ele prin liniuta
Status.txt-aici se afla numele si prenumele fiecarui copil, statusul acestuia (cuminte/rau) si bugetul alocat fiecaruia
Jucarii.txt-aici se afla jucariile existente in stoc si pretul fiecareia
In fisierul cpp sunt 3 clase cu atribute private si constructori realizati in asa fel incat sa poata ajuta la stocarea informatiilor din fisierele enumerate mai sus
in vectori lista. Aceste clase(copii,jucarii,status) o sa fie friend class cu clasele Elf,Troli si Dna Craciun deoarece acestia pot avea acces la informatiile stocate pentru
a-si realiza task-urile.
Elfii-impart cadourile in functie de buget, dorinte, status.
Trolii le impacheteaza in functie de gen si status.
Dna Craciun calculeaza bugetul extra de care este nevoie.
Mos Craciun isi calculeaza cea mai scurta ruta pentru a se deplasa in mod eficient.
