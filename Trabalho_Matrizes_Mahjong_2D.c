//Jogo: Mahjong 2d, para fazer, eu me baseei no numero dos caracteres da tabela ASCII
#include <stdio.h>
#include <stdlib.h>//Para utilizar os comandos rand e srand
#include <time.h>//Para usar o time
#include <locale.h>//Permitir acentuação
#include <windows.h>//Para usar sons de beeps
int main(){
	int r = 's';
	while(r == 's' || r == 'S'){
		//m1 receberá o total de peças do jogo de forma ordenada. 
		//m2 receberá o total de peças do jogo de forma desordenada, sendo eles os valores de m1.
		//l receberá primeiramente o o valor da tabela ASCII que corresponde ao caracter A
		//n representa a quatidade de determinada peça/letra
		//r resposta do usuario se quer ou nao continuar o jogo
		int m1[10][10], m2[10][10], i, j, k=0, l=65, n=10;
		setlocale(LC_ALL,"Portuguese");//Permitir acentuação
		//Para gerar numeros aleatórios
		srand(time(NULL));
		//i representará a linha da matriz
		for(i=0; i<10; i++){
			//j indicará quantas vezes cada peça deve aparecer, segundo o n
			for(j=0; j<n; j++){
				//k representará a coluna da matriz, e comparamos k<10 para não estourar o índice da coluna
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
			//Alterar a quantidade de peças n-=2, a partir da primeira peça de cada grupo
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
				//Ambos os indices receberão numeros aleatórios entre 0 e 9
				o = rand()%10;
				p = rand()%10;
				if(m1[o][p] != 32){
					m2[i][j] = m1[o][p];
					//m1[o][p] = 32 (que é o valor do espaço em branco na tabela ASCII), quando m1[i][j] for adicionado em m2[o][p]
					m1[o][p] = 32; 
				}else
					j--;//Caso os indices sejam de m1[k][l] == 32, mantemos o indice de j
			}
		}
		//l1 e c1 são a linha e coluna da primeira peça
		//l2 e c2 são a linha e coluna da segunda peça
		//igual1 verificará se a matriz está vazia ou não
		//igual2 verificaará se as condições do usuário são válidas
		int l1, c1, l2, c2, igual1, igual2=1;
		do{//Utilizei o do para facilitar a manipulação do igual1 (ver o final)
			printf("      _________  ______  _    _  _______  ______  _____  ______     ______       _\n");
			printf("     |  _   _  ||  __  || |  | ||_   ___||  __  ||  _  ||  ____|   |____  |     | |\n"); 
			printf("     | | | | | || |__| || |__| |  | |  _ | |  | || | | || | ___     ____| | ____| |\n");
			printf("     | | | | | ||  __  ||  __  |  | |_| || |__| || | | || ||_  |   |  ____||  __  |\n");
			printf("     | | |_| | ||_|  |_||_|  |_|  |_____||______||_| |_|| |__| |   | |____ | |__| |\n");
			printf("     |_|     |_|                                        |______|   |______||______|\n");
			igual1=1;//Acreditamos que a matriz está vazia
			printf("\n\n\t");
			for(i=0; i<10; i++)
				printf("%d\t",i);//Mostrar os indices das colunas
			printf("\n\n\n\n");
			//Mostrar a matriz para o usuário
			for(i=0; i<10; i++){
				printf("%d\t",i);//Mostrar os índices das linhas
				for(j=0; j<10; j++){
					printf("%c\t",m2[i][j]);
				}
				printf("%d\n\n",i);//Mostrar os índices das linhas
			}
			printf("\n\n\t");
			for(i=0; i<10; i++)
				printf("%d\t",i);//Mostrar os indices das colunas
			printf("\n\n");
			//Pergunta para o usuário as posições das duas peças
			printf("\nDigite a linha e a coluna da primeira peça:\n");
			scanf("%d %d",&l1,&c1);
			printf("\nDigite a linha e a coluna da segunda peça:\n");
			scanf("%d %d",&l2,&c2);
			/*Verica se os índices da matriz estouraram ou não, e se as duas posições que o usuário informou são iguais
			e se não é a mesma peça que o usuário está digitando, e se o usario digitar espaços que estão vazios*/
			if(l1>=0 && l1<10 && c1>=0 && c1<10 && l2>=0 && l2<10 && c2>=0 && c2<10 && m2[l1][c1] == m2[l2][c2] && (l1 != l2 || c1 != c2) && (m2[l1][c1] != 32 || m2[l2][c2] != 32)){
				//Vericar as linhas e colunas da primeira peça são iguais a 0 ou 9
				if(l1==0 || l1==9 || c1==0 || c1==9){
					//Vericamos se as linhas ou colunas da primeira peça são iguais a 0 ou 9
					if(l2==0 || l2==9 || c2==0 || c2==9){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					/*Se não for igual a 0 ou 9, verificamos se a peça anterior ou posterior das linhas ou colunas 
					da segunda peça, é igual a ' '(32)*/
					}else if(m2[l2+1][c2]==32 || m2[l2-1][c2]==32 || m2[l2][c2+1]==32 || m2[l2][c2-1]==32){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					}else
						igual2=0;//Não respeita as restrições
				/*Se não for igual a 0 ou 9, verificamos se a peça anterior ou posterior das linhas ou colunas 
				da primeira peça, é igual a ' '(32)*/
				}else if(m2[l1+1][c1]==32 || m2[l1-1][c1]==32 || m2[l1][c1+1]==32 || m2[l1][c1-1]==32){
					//Vericamos se as linhas ou colunas da segunda peça são iguais a 0 ou 9
					if(l2==0 || l2==9 || c2==0 || c2==9){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					/*Se não for igual a 0 ou 9, verificamos se a peça anterior ou posterior das linhas ou colunas 
					da segunda peça, é igual a ' '(32)*/
					}else if(m2[l2+1][c2]==32 || m2[l2-1][c2]==32 || m2[l2][c2+1]==32 || m2[l2][c2-1]==32){
						m2[l1][c1] = 32;
						m2[l2][c2] = 32;
					}else
						igual2=0;//Não respeita as restrições
				}else
					igual2=0;//Não respeita as restrições
			}else
				igual2=0;//Não respeita as restrições
			//Verificamos se a jogada é válida ou não	
			if(igual2==1){
				printf("\nBela jogada!");
				Beep (392, 800);//Comando para sons
			}
			else{
				printf("\nJogada inválida!");
				Beep (293, 800);//Comando para sons
				igual2=1;
			}
			sleep(2);//Por 2 segundos mostrará uma mensagem na tela	
			system("cls");//Daí limpará a tela
			//Verificar se a matriz está ou não vazia
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
		}while(igual1==0);//Pois se a matriz não estiver vazia, o igual1 = 1 no começo do "do"*/
		printf("      _________  ______  _    _  _______  ______  _____  ______     ______       _\n");
		printf("     |  _   _  ||  __  || |  | ||_   ___||  __  ||  _  ||  ____|   |____  |     | |\n"); 
		printf("     | | | | | || |__| || |__| |  | |  _ | |  | || | | || | ___     ____| | ____| |\n");
		printf("     | | | | | ||  __  ||  __  |  | |_| || |__| || | | || ||_  |   |  ____||  __  |\n");
		printf("     | | |_| | ||_|  |_||_|  |_|  |_____||______||_| |_|| |__| |   | |____ | |__| |\n");
		printf("     |_|     |_|                                        |______|   |______||______|\n"); 
		printf("\n\n\t\t\tParabéns campeão!!! Você conseguiu!!!");
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
