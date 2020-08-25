//Jogo: Mahjong 2d, para fazer, eu me baseei no numero dos caracteres da tabela ASCII
#include <stdio.h>
#include <stdlib.h>//Para utilizar os comandos rand e srand
#include <time.h>//Para usar o time
#include <locale.h>//Permitir acentua��o
#include <windows.h>//Para usar sons de beeps
int main(){
	int r = 's';
	while(r == 's' || r == 'S'){
		//m1 receber� o total de pe�as do jogo de forma ordenada. 
		//m2 receber� o total de pe�as do jogo de forma desordenada, sendo eles os valores de m1.
		//l receber� primeiramente o o valor da tabela ASCII que corresponde ao caracter A
		//n representa a quatidade de determinada pe�a/letra
		//r resposta do usuario se quer ou nao continuar o jogo
		int m1[10][10], m2[10][10], i, j, k=0, l=65, n=10;
		setlocale(LC_ALL,"Portuguese");//Permitir acentua��o
		//Para gerar numeros aleat�rios
		srand(time(NULL));
		//i representar� a linha da matriz
		for(i=0; i<10; i++){
			//j indicar� quantas vezes cada pe�a deve aparecer, segundo o n
			for(j=0; j<n; j++){
				//k representar� a coluna da matriz, e comparamos k<10 para n�o estourar o �ndice da coluna
				if(k<10){
					m1[i][k] = l;
					k++; 
				}else{
					i++;//Se k estiver estourado increentamos a linha i
					j--;//Decrementamos o j para manter a contagem
					k=0;//Renicializamos a coluna em 0
				}
			}
			l++;
			//Alterar a quantidade de pe�as n-=2, a partir da primeira pe�a de cada grupo
			if(l==67 || l==71 || l==75 || l==79)
				n -= 2;
			if(k==10)//Vemos se k estourou
				k=0;
			else
				i--;//Decrementamos o i para manter a linha
		}
		//o sera a linha de m1
		//p sera a coluna de m1
		int o=0, p=0;
		for(i=0; i<10; i++){
			for(j=0; j<10; j++){
				//Ambos os indices receber�o numeros aleat�rios entre 0 e 9
				o = rand()%10;
				p = rand()%10;
				if(m1[o][p] != 32){
					m2[i][j] = m1[o][p];
					//m1[o][p] = 32 (que � o valor do espa�o em branco na tabela ASCII), quando m1[i][j] for adicionado em m2[o][p]
					m1[o][p] = 32; 
				}else
					j--;//Caso os indices sejam de m1[k][l] == 32, mantemos o indice de j
			}
		}
		//l1 e c1 s�o a linha e coluna da primeira pe�a
		//l2 e c2 s�o a linha e coluna da segunda pe�a
		//igual1 verificar� se a matriz est� vazia ou n�o
		//igual2 verificaar� se as condi��es do usu�rio s�o v�lidas
		int l1, c1, l2, c2, igual1, igual2=1;
		do{//Utilizei o do para facilitar a manipula��o do igual1 (ver o final)
			printf("      _________  ______  _    _  _______  ______  _____  ______     ______       _\n");
			printf("     |  _   _  ||  __  || |  | ||_   ___||  __  ||  _  ||  ____|   |____  |     | |\n"); 
			printf("     | | | | | || |__| || |__| |  | |  _ | |  | || | | || | ___     ____| | ____| |\n");
			printf("     | | | | | ||  __  ||  __  |  | |_| || |__| || | | || ||_  |   |  ____||  __  |\n");
			printf("     | | |_| | ||_|  |_||_|  |_|  |_____||______||_| |_|| |__| |   | |____ | |__| |\n");
			printf("     |_|     |_|                                        |______|   |______||______|\n");
			igual1=1;//Acreditamos que a matriz est� vazia
			printf("\n\n\t");
			for(i=0; i<10; i++)
				printf("%d\t",i);//Mostrar os indices das colunas
			printf("\n\n\n\n");
			//Mostrar a matriz para o usu�rio
			for(i=0; i<10; i++){
				printf("%d\t",i);//Mostrar os �ndices das linhas
				for(j=0; j<10; j++){
					printf("%c\t",m2[i][j]);
				}
				printf("%d\n\n",i);//Mostrar os �ndices das linhas
			}
			printf("\n\n\t");
			for(i=0; i<10; i++)
				printf("%d\t",i);//Mostrar os indices das colunas
			printf("\n\n");
			//Pergunta para o usu�rio as posi��es das duas pe�as
			printf("\nDigite a linha e a coluna da primeira pe�a:\n");
			scanf("%d %d",&l1,&c1);
			printf("\nDigite a linha e a coluna da segunda pe�a:\n");
			scanf("%d %d",&l2,&c2);
			/*Verica se os �ndices da matriz estouraram ou n�o, e se as duas posi��es que o usu�rio informou s�o iguais
			e se n�o � a mesma pe�a que o usu�rio est� digitando, e se o usario digitar espa�os que est�o vazios*/
			if(l1>=0 && l1<10 && c1>=0 && c1<10 && l2>=0 && l2<10 && c2>=0 && c2<10 && m2[l1][c1] == m2[l2][c2] && (l1 != l2 || c1 != c2) && (m2[l1][c1] != 32 || m2[l2][c2] != 32)){
				//Vericar as linhas e colunas da primeira pe�a s�o iguais a 0 ou 9
				if(l1==0 || l1==9 || c1==0 || c1==9){
					//Vericamos se as linhas ou colunas da primeira pe�a s�o iguais a 0 ou 9
					if(l2==0 || l2==9 || c2==0 || c2==9){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					/*Se n�o for igual a 0 ou 9, verificamos se a pe�a anterior ou posterior das linhas ou colunas 
					da segunda pe�a, � igual a ' '(32)*/
					}else if(m2[l2+1][c2]==32 || m2[l2-1][c2]==32 || m2[l2][c2+1]==32 || m2[l2][c2-1]==32){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					}else
						igual2=0;//N�o respeita as restri��es
				/*Se n�o for igual a 0 ou 9, verificamos se a pe�a anterior ou posterior das linhas ou colunas 
				da primeira pe�a, � igual a ' '(32)*/
				}else if(m2[l1+1][c1]==32 || m2[l1-1][c1]==32 || m2[l1][c1+1]==32 || m2[l1][c1-1]==32){
					//Vericamos se as linhas ou colunas da segunda pe�a s�o iguais a 0 ou 9
					if(l2==0 || l2==9 || c2==0 || c2==9){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					/*Se n�o for igual a 0 ou 9, verificamos se a pe�a anterior ou posterior das linhas ou colunas 
					da segunda pe�a, � igual a ' '(32)*/
					}else if(m2[l2+1][c2]==32 || m2[l2-1][c2]==32 || m2[l2][c2+1]==32 || m2[l2][c2-1]==32){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					}else
						igual2=0;//N�o respeita as restri��es
				}else
					igual2=0;//N�o respeita as restri��es
			}else
				igual2=0;//N�o respeita as restri��es
			//Verificamos se a jogada � v�lida ou n�o	
			if(igual2==1){
				printf("\nBela jogada!");
				Beep (392, 800);//Comando para sons
			}
			else{
				printf("\nJogada inv�lida!");
				Beep (293, 800);//Comando para sons
				igual2=1;
			}
			sleep(2);//Por 2 segundos mostrar� uma mensagem na tela	
			system("cls");//Da� limpar� a tela
			//Verificar se a matriz est� ou n�o vazia
			for(i=0; i<10; i++){
				for(j=0; j<10; j++){
					if(m2[i][j] != 32){
						igual1=0;
						break;
					}
				}
				if(igual1==0)
					break;
			}
		}while(igual1==0);//Pois se a matriz n�o estiver vazia, o igual1 = 1 no come�o do "do"*/
		printf("      _________  ______  _    _  _______  ______  _____  ______     ______       _\n");
		printf("     |  _   _  ||  __  || |  | ||_   ___||  __  ||  _  ||  ____|   |____  |     | |\n"); 
		printf("     | | | | | || |__| || |__| |  | |  _ | |  | || | | || | ___     ____| | ____| |\n");
		printf("     | | | | | ||  __  ||  __  |  | |_| || |__| || | | || ||_  |   |  ____||  __  |\n");
		printf("     | | |_| | ||_|  |_||_|  |_|  |_____||______||_| |_|| |__| |   | |____ | |__| |\n");
		printf("     |_|     |_|                                        |______|   |______||______|\n"); 
		printf("\n\n\t\t\tParab�ns campe�o!!! Voc� conseguiu!!!");
		//Apenas um toque que inventei 
		Beep (293, 1000);
		Beep (349, 500);
		Beep (392, 1000);
		Beep (440, 1500);
		printf("\n\nDeseja jogar novamente?[S/N]\n");
		fflush(stdin);//Limpar a entrada
		scanf("%c",&r);
		system("cls");
	}
	printf("      _________  ______  _    _  _______  ______  _____  ______     ______       _\n");
	printf("     |  _   _  ||  __  || |  | ||_   ___||  __  ||  _  ||  ____|   |____  |     | |\n"); 
	printf("     | | | | | || |__| || |__| |  | |  _ | |  | || | | || | ___     ____| | ____| |\n");
	printf("     | | | | | ||  __  ||  __  |  | |_| || |__| || | | || ||_  |   |  ____||  __  |\n");
	printf("     | | |_| | ||_|  |_||_|  |_|  |_____||______||_| |_|| |__| |   | |____ | |__| |\n");
	printf("     |_|     |_|                                        |______|   |______||______|\n");
	printf("\n\n\t\t\t\tObrigado por jogar!!!");
	printf("\n\t\t\t      Jardel Pauluka agradece!!\n\n"); 
	system("pause");
	return 0;
}
