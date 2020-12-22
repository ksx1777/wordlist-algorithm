/*
criado por ksx1777 21/12/2020

algoritmo de brute force, gerador de wordlists
com qualquer cadeia de caracteres, numero minimo
e máximo de digitos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* funçao para mostrar as combinações uma por uma */
/*
void
show_words(char *s, int charset_n[], short max, short min){
	for(short i = (max-min); i < max; i++){
		printf("%c", s[charset_n[i]]);
	}
	printf("\n");
}
*/

void
write_to_file(FILE *f, char *s, int charset_n[], short max, short min){
	for(short i = (max-min); i < max; i++){
		fprintf(f, "%c", s[charset_n[i]]);
	}
	fprintf(f, "\n");
}

short
gen_words(FILE *f, char *charset, short max_l, short min_l){
	if(max_l < min_l){
		printf("[!] o numero maximo de digitos nao pode ser inferior ao numero minimo\n");
		return -1;
	}

	printf("[*] char list: %s\n"
		   "[*] max combination lenght: %hi\n"
		   "[*] min combination lenght: %hi\n", charset, max_l, min_l);

	/* variáveis iniciais */
	int charset_n[max_l];
	int i, p, count = 0;
	short last_pos = max_l - 1;
	short charset_len = strlen(charset);
	if(charset_len < 2){
		printf("[!] quantidade de caracteres invalida\n");
		return -1;
	}

	/* colocar o valor 0 no vetor */
	memset(charset_n, 0x0, sizeof(charset_n));

	/* inicio do algoritmos de combinações */
	for(i = min_l; i <= max_l; /* vazio */){
		write_to_file(f, charset, charset_n, max_l, i);

		/* aumentar os valores usados para formar as combinaçoes */
		charset_n[last_pos]++;

		for(int c = last_pos; c > 0; c--){
			if(charset_n[c] == charset_len){
				charset_n[c] = 0;
				charset_n[c-1]++;
			}
		}
		/* quando todas as combinações forem feitas com uma quantidade de digitos, aumentar +1 na quantidade de digitos */
		count = 0;
		for(p = max_l - i; p < max_l; p++){
			count+= charset_n[p] + 1;
		}
		if(count == charset_len*i){
			write_to_file(f, charset, charset_n, max_l, i);
			i++;
			memset(charset_n, 0x0, sizeof(charset_n));
		}
	}
	return 0;
}

int
main(int argc, char **argv){
	FILE *f = fopen("wordlist.txt", "a+");
	time_t now = time(0);
	if(argc < 4){ printf("[!] argumentos nao foram digitados\n"); printf("Como usar: %s <caracteres> <num max. digitos> <num min. digitos>\n"
		   "Ex: %s abcde 4 2\n", argv[0], argv[0]); return -1; }
	if(gen_words(f, argv[1], atoi(argv[2]), atoi(argv[3])) == -1) { printf("[!] o programa encerrou com um erro\n"); return -1; }
	fclose(f);
	printf("[*] tempo decorrido: %0.2fs\n", (float)(time(0) - now));
	return 0;
}