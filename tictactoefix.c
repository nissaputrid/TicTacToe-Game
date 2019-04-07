// Anissa Putri Dinanti
// 13517121
// K-01
// TUGAS BESAR I - TBFO
// TIC TAC TOE

#include <stdio.h>
#include <string.h>

// DEFINE BOOLEAN
#define boolean unsigned char
#define true 1
#define false 0

// TIPE DATA //

/* Definisi elemen dan koleksi objek */
typedef char ElType;   /* type elemen tabel */
typedef struct { 
	char TI[10]; /* memori tempat penyimpan elemen (container) */
	int Neff; /* >=0, banyaknya elemen efektif */
} TabInt;

// PROSEDUR //
void CetakTicTacToe(TabInt board);
/* I.S. state terdeifinisi
 * F.S. tercetak board yang sesuai dengan state yang masuk */

int main()
{	
	// KAMUS 
	boolean sama;
	
	char state[10];
	char del[1000];
	char TempState[150][10];
	char SaveState[100][10];
	char CurrentState[100][10];
	char status[5][100];
	char CurrentStatus;
	char mainlagi;
	
	TabInt board;
	
	int i,j,k;
	int inp;
	int count;
	
	FILE * pFile;

	// ALGORITMA UTAMA
	
	
	do{
	pFile = fopen ("states.txt", "r");

	if (pFile == NULL) // JIKA FILE EKSTERNAL KOSONG ATAU TIDAK TERBACA
		perror ("Error opening file");
	else
	{	// MAIN MENU PERMAINAN //
		printf("Selamat Datang di Game TicTacToe!\n");
		
			// RULES
		printf("Peraturan dari permainan ialah kotak dapat diisi sesuai dengan format berikut!\n");
		
		board.TI[1] = '1';
		board.TI[2] = '2';
		board.TI[3] = '3';
		board.TI[4] = '4';
		board.TI[5] = '5';
		board.TI[6] = '6';
		board.TI[7] = '7';
		board.TI[8] = '8';
		board.TI[9] = '9';
		
		CetakTicTacToe(board);
		
		printf("> Kamu akan mendapatkan simbol X dan aku simbol O\n");
		printf("> Kamu hanya boleh mengisi kotak di tempat yang kosong\n");
		
		printf("> Sudah siap?\n");
		//END
		
		
		// OPTION PERMAINAN
		printf("PILIHAN PERMAINAN\n");
		printf("1. Aku (CPU) main duluan\n");
		printf("2. Kamu main duluan\n");
		printf("Silakan pilih yang kamu suka!\n");
		printf("Jadi kamu pilih yang mana nih? ");
		
		do{
			scanf("%d",&inp);
			
			if (inp != 1 && inp != 2)
				printf("Ups! Masukkan salah, kamu melanggar peraturan silakan ulangi masukan\n");
				
		} 
		while (inp < 1 && inp > 2);
		// END
		
		
		// FIRST INPUT. INPUT DIGANTI UNTUK MASUK KE INPUT C DAN P
		if (inp == 1)
			inp = 10; 						// UNTUK INPUT C (CPU DULUAN)
		else if (inp == 2)
			inp = 11; 						// UNTUK INPUT P (PLAYER DULUAN)
		// END
		
		
		// DEKLARASI INITIAL STATE
		CurrentStatus = 'p'; 				// STATUS DIDEKLARASI UNTUK BERMAIN
		i = 1;
		fgets(del, 123, pFile); 			// MENGHAPUS BARIS PERTAMA DARI FILE EKSTERNAL
		fgets(state, 10, pFile); 			// MENGAMBIL STATE 
		strcpy(TempState[i], state); 		// STATE DISIMPAN UNTUK MELANJUTKAN PERMAINAN
		strcpy(SaveState[i], state); 		// MENYIMPAN STATE UNTUK MEMORI STATE SELAMA PERMAINAN
		fclose(pFile); 						// FILE DI CLOSE KEMBALI
		//END
		
		
		// MULAI LOOPING PERMAINAN
		while (CurrentStatus == 'p') 		// JIKA STATUS MASIH BERMAIN
		{	
			pFile = fopen ("states.txt", "r"); // FILE DIBUKA KEMBALI DAN DILAKUKAN HAL SERUPA DARI INITIAL STATE
			fgets(del, 123, pFile); 		// DELETE BARIS PERTAMA FILE
			
			
			// SEARCH STATE YANG SAMA DENGAN TEMPSTATE
			fgets(state, 10, pFile);
			strcpy(CurrentState[i], state);
			fgets(del,4, pFile);
			
			sama = false;
			while (sama == false){
				count = 0;
				for (j=0;j<=8;j++){
					if (CurrentState[i][j] == TempState[i][j])
						count++;
				}
			
				if (count == 9){
					sama = true;
				}
				else{ // JIKA TIDAK SAMA MAKA MENGAMBIL STATE BARU
					fgets(del,111, pFile);
					fgets(state, 10, pFile);
					strcpy(CurrentState[i], state);
					fgets(del, 2, pFile);
					
					fgets(state, 2, pFile);
					strcpy(status[i], state);
					CurrentStatus = status[i][0];
					fgets(del, 2, pFile);
				}	
			}
			//END
			
			
			//MENERIMA INPUT  STATE
			if (i != 1 && CurrentStatus == 'p'){
				printf("Giliranmu! (Masukkan input dari 1-9)\n");
				
				do{
				printf("> ");
				scanf("%d", &inp);
					if ((inp <1 || inp >9) && i != 1){
						printf("Ups! Masukkan salah, kamu melanggar peraturan silakan ulangi masukan\n");
					}
				}while ((inp <1 || inp >9) && i != 1);	
			}
			
				// LOOP UNTUK MENGAMBIL STATE BERIKUTNYA YANG SESUAI INPUT
			for (j=1; j<= inp; j++){
				fgets(state, 10, pFile);
				fgets(del, 2, pFile);
			}
			strcpy(TempState[i+1], state);
			//END
			
			
			// VALIDASI INPUT
			count = 0;
			for (j=0;j<=8;j++){
				if (CurrentState[i][j] == TempState[i+1][j])
					count++;
				}
			
			if (count != 9)
				strcpy(SaveState[i+1],state);
			else{
				printf("Ups! Masukkan salah, kamu melanggar peraturan silakan ulangi masukan\n");
				i--;
			}
			// END
			
			
			// TRANSLATE STATE KE BOARD DAN MENCETAK JIKA MASIH BERMAIN
			k = 0;
			for (j=1; j<=9; j++){
				board.TI[j] = TempState[i+1][k];
				k++;
			}
			if (CurrentStatus == 'p'){
				CetakTicTacToe(board);	
				printf("\n");
			}
			// END
			
			
			// MENGECEK KONDISI PERMAINAN (APAKAH MENANG/SERI/MASIH BERMAIN)
			if (CurrentStatus == 'p'){
				fgets(del, 2, pFile);
				i++;
			} else if (CurrentStatus == 'w'){
				printf("Yeay, aku menang! Kamu kalah deh :p\n");
			} else if (CurrentStatus == 'd'){
				printf("Wow kita seri!\n");
			}
			//END
			fclose(pFile);
		}
	}
	
	// MENULISKAN STATE YANG DILEWATI SELAMA PERMAINAN
	printf("State yang dilewati selama permainan adalah\n");
	for (j=1; j<=i; j++){
			printf("%d. ", j);		
			printf("%s\n", SaveState[j]);
	}
	// END
	
	printf("Mau main lagi? (y/n) > ");
	scanf("%s", &mainlagi);
	
	}while (mainlagi == 'y');
}	

void CetakTicTacToe(TabInt board){
	
	int i;
	
	for (i=1; i<=9;i++){
		if (i%3 != 0){
			if (board.TI[i] == '#')
				printf("   |");
			else
				printf(" %c |", board.TI[i]);
		}else{
			if (i != 9){
				if (board.TI[i] == '#')
					printf("   \n");
				else
					printf(" %c \n", board.TI[i]);
				
				printf("---|---|---\n");
			} else{
				if (board.TI[i] == '#')
					printf("   \n");
				else
					printf(" %c \n", board.TI[i]);
			}
		}  
	}
}
