#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#include<time.h>
#define ll long long
#define keyUp 72
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13

const int task = 31; // Fungsinya untuk random pengerjaan task tegantung berapa player nya

int flag_exit = 0;

// Function prototype
void gotoxy(int x, int y);
void Hide();
void menu();

time_t t; // Waktu buat fungsi random

// Function random
int random(int n){
	srand(time(NULL));
	int ans = rand() % n;
	return ans;
}

// Function animasi kalo ngevote dan berhasil nge vote nya
void animasi_kick(int pemain, char nama[][255], int impostor_flag[15]){
	char kick_info[5][255] = {" was an Impostor.", " was not an Impostor."};
	char kick[255];
	strcpy(kick, nama[pemain]);
	if(impostor_flag[pemain] == 1){
		strcat(kick , kick_info[0]); // kalo yang di kick ituu impostor
	}else{
		strcat(kick , kick_info[1]); // kalo yang di kick bukan impostor
	}
	for(int i = 0; kick[i] != '\0'; i++){
		printf("%c", kick[i]);
		usleep(150000);
	}
	puts("");
}

// Funtion animasi kalo ngevote dan banyak yang skip

void animasi_skip(int flag){
	if(flag == 1){
		char info[255] = {"No one was ejected (TIE)."};	// Yang skip == vote
		for(int i = 0; info[i] != '\0'; i++){
			printf("%c", info[i]);
			usleep(150000);
		}
		puts("");
		sleep(2);
	}else{
		char info[255] = {"No one was ejected (SKIPPED)."}; // Yang skip > vote
		for(int i = 0; info[i] != '\0'; i++){
			printf("%c", info[i]);
			usleep(150000);
		}
		puts("");
		sleep(2);
	}
}

// Function buat bikin taskbar
void task_bar(int task_prog){
	gotoxy(1,1);
	printf("TASK:\n");
	gotoxy(1,2);
	printf("%c", 201);
	for(int i = 0; i < 50; i++){ // buat bikin garis tabel yang atas
		gotoxy(2 + i,2);
		printf("%c", 205);
	}
	gotoxy(52,2);
	printf("%c\n", 187);
	gotoxy(1,3);
	printf("%c", 186);
	for(int i = 0; i < task_prog; i++){ // buat bikin progress taskbar
		gotoxy(2 + i,3);
		printf("%c", 178);
	}
	for(int i = task_prog; i < 50; i++){ // kalo belum mencapai progress nya print spasi
		gotoxy(2 + i,3);
		printf(" ");
	}
	gotoxy(52,3);
	printf("%c %d%%\n", 186, task_prog * 2); // buat bikin persen progress
	gotoxy(1,4);
	printf("%c", 200);
	for(int i = 0; i < 50; i++){
		gotoxy(2 + i,4);
		printf("%c", 205); // buat bikin garis tabel bawah
	}
	gotoxy(52,4);
	printf("%c\n", 188);
}

// function buat bikin tabel pilih player
void pemain_pilih(char status[][255], char opsi[][255], int i, int o, int l, char dead_stat[][255], char nama[][255], int *y, int you[15]){
	gotoxy(o * 28, l);
	printf("%c", 201);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 187);
	gotoxy(o * 28, l + 1);
	printf("%c                  %c %c\n", 186, you[i] == 1 ? 'P' : ' ', 186); // buat pilih player diri sendiri
	for(int k = 0; k < 3; k++){
		gotoxy(o * 28, l + 2 + k);
		printf("%c", 186);
		printf(" %s", status[k]);
		if(k == 0){
			printf("%-12s%c", opsi[i], 186);
		}else if(k == 1){
			if(strcmp(nama[i], "KOSONG") == 0){
				printf("             %c",186);
			}else{
				printf("%-13s%c", nama[i], 186);
			}
		}else if(k == 2){
			if(strcmp(dead_stat[i], "ALIVE") == 0){
				printf("\e[0;32m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}else{
				printf("\e[0;31m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}
		}
		puts("");
	}
	gotoxy(o * 28, l + 5);
	printf("%c                    %c\n", 186, 186);
	gotoxy(o * 28, l + 6);
	*y = l + 6;
	printf("%c", 200);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 188);
}
// function tabel buat vote
void pemain_game(char status[][255], char opsi[][255], int i, int o, int l, char dead_stat[][255], char nama[][255], int you[15], int poscurr, int *y){
	gotoxy(o * 28, l);
	printf("%c", 201);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 187);
	gotoxy(o * 28, l + 1);
	printf("%c                  %c %c\n", 186, you[i] == 1 ? 'P' : ' ', 186);
	for(int k = 0; k < 3; k++){
		gotoxy(o * 28, l + 2 + k);
		printf("%c", 186);
		printf(" %s", status[k]);
		if(k == 0){
			printf("%-12s%c", opsi[i], 186);
		}else if(k == 1){
			printf("%-13s%c", nama[i], 186);
		}else if(k == 2){
			if(strcmp(dead_stat[i], "ALIVE") == 0){
				printf("\e[0;32m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}else{
				printf("\e[0;31m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}
		}
		puts("");
	}
	gotoxy(o * 28, l + 5);
	printf("%c                    %c\n", 186, 186);
	gotoxy(o * 28, l + 6);
	printf("%c        %s        %c\n", 186, poscurr == i && strcmp(dead_stat[i], "DEAD") != 0 ? "VOTE" : "    ", 186);
	gotoxy(o * 28, l + 7);
	*y = l + 7;
	printf("%c", 200);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 188);
}
// function tabel buat kill player
void pemain_kill(char status[][255], char opsi[][255], int i, int o, int l, char dead_stat[][255], char nama[][255], int you[15], int poscurr, int impostor_flag[15], int *y){
	gotoxy(o * 28, l);
	printf("%c", 201);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 187);
	gotoxy(o * 28, l + 1);
	printf("%c                  %c %c\n", 186, you[i] == 1 ? 'P' : ' ', 186);
	for(int k = 0; k < 3; k++){
		gotoxy(o * 28, l + 2 + k);
		printf("%c", 186);
		printf(" %s", status[k]);
		if(k == 0){
			printf("%-12s%c", opsi[i], 186);
		}else if(k == 1){
			if(impostor_flag[i] == 1){
				printf("\e[0;31m");
				printf("%-13s", nama[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}else{
				printf("%-13s%c", nama[i], 186);
			}
		}else if(k == 2){
			if(strcmp(dead_stat[i], "ALIVE") == 0){
				printf("\e[0;32m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}else{
				printf("\e[0;31m");
				printf("%-11s", dead_stat[i]);
				printf("\e[0;37m");
				printf("%c", 186);
			}
		}
		puts("");
	}
	gotoxy(o * 28, l + 5);
	printf("%c                    %c\n", 186, 186);
	gotoxy(o * 28, l + 6);
	printf("%c        %s        %c\n", 186, poscurr == i && strcmp(dead_stat[i], "DEAD") != 0 && impostor_flag[i] != 1 ? "KILL" : "    ", 186); // jika cursor ada di posisi yang sekarang print KILL kalo gak print spasi biar keliatan kosong
	gotoxy(o * 28, l + 7);
	*y = l + 7;
	printf("%c", 200);
	for(int j = 0; j < 20; j++){
		printf("%c", 205);
	}
	printf("%c\n", 188);
}
// function buat permainan among us nya berlangsung dan disini gua agak males jelasin soal nya panjang bangetttt wkwkwk
void game(int number_player, char nama[][255], char status[][255], char warna[][255], int impostor_flag[15], int number_impostor, char info[][255], int you[15], int pos_validation){
	char game_nama[15][255] = {'\0'}, doing[25][255] = {"Cafetaria", "Electrical", "Navigation", "Reactor", "Upper Engine", "Lower Engine", 
	"Storage", "O2", "Shield", "Security", "Weapon", "Communications", "Medbay", "Admin"}, do_it[25][255] = {"berlari ke arah ", "sedang mengerjakan task di ", 
	"diam saja di ", "sedang melakukan pengecekan di "};
	bool impostor = false, ketauan = false, playing = true;
	int flag = 1, dead = 0, index = 0, temp1 = 0, sisa_cm = number_player - number_impostor,
	 temp_kill = 0, total_kill = 0, poscurr = 0, posx = 24, posy = 3, y = 0, currpos = 0, 
	 count_kill = 0, p = 0, sisa_vote = 0, impostor_left = number_impostor, do_task = 0;
	for(int i = 0; i < number_player; i++){
		if(you[i] == 1 && impostor_flag[i] == 1){
			impostor = true;
		}
		if(you[i] == 1){
			p = i;
		}
	}
	while(true){
		total_kill = 0, posx = 24, posy = 3, poscurr = 0, currpos = 0, sisa_vote = 0;
		int flag_kick[15] = {0};
		for(int i = 0; i < number_player; i++){
			if(strcmp(status[i], "ALIVE") == 0){
				++sisa_vote;
			}
		}
		
		if(strcmp(status[p], "DEAD") == 0 && impostor_flag[p] == 1){
			impostor = false;
			playing = false;
		}else if(strcmp(status[p], "DEAD") == 0){
			playing = false;
		}
		// KILL KILL
		if(impostor == true){
			while(true){
				Hide();
				for(int i = 0, j = 0, l = 0; i < number_player; i++, j = (j + 1) % 3){
					if(currpos == i){
						gotoxy(posx, posy);
						printf("<<");
					}
					if(i >= 3 && i % 3 == 0){
						l += 9;
					}
					pemain_kill(info, warna, i, j, l, status, nama, you, currpos, impostor_flag, &y);
				}
				gotoxy(58, y + 2);
				printf("Press S for skip!\n");
				if(kbhit){
					char button = getch();
					if(currpos > 2 && button == keyUp){
						gotoxy(posx, posy);
						printf("  ");
						posy -= 9;
						currpos -= 3;
					}else if(currpos + 3 < number_player && button == keyDown){
						gotoxy(posx, posy);
						printf("  ");
						posy += 9;
						currpos += 3;
					}else if(currpos < number_player - 1 && button == keyRight && currpos != 2 && currpos != 5 && currpos != 8 ){
						gotoxy(posx, posy);
						printf("  ");
						posx += 28;
						currpos += 1;
					}else if(currpos % 3 != 0 && button == keyLeft && currpos > 0){
						gotoxy(posx, posy);
						printf("  ");
						posx -= 28;
						currpos -= 1;
					}else if(button == 's' || button == 'S'){
						system("CLS");
						temp_kill = random(46);
						if(temp_kill % 2 != 0 && sisa_cm > 2){
							total_kill = 2;
						}else{
							total_kill = 1;
						}
						for(int i = 0; i < total_kill; i++){
							task_bar(do_task);
							gotoxy(53, 14);
							printf("PLEASE WAIT\n");
							do{
								flag = 1;
								dead = random(number_player);
								if(strcmp(status[dead], "DEAD") == 0 || impostor_flag[dead] == 1){
									flag = 0;
									continue;
								}
								strcpy(status[dead], "DEAD");
							}while(flag == 0);
							--sisa_cm;
							system("CLS");
						}
						break;
					}else if(button == keyEnter && strcmp(status[currpos], "DEAD") != 0 && impostor_flag[currpos] != 1 && currpos != p){
						int chance_rate = random(92);
						if(count_kill > 2 && chance_rate % 2 != 0){
							impostor = false;
							ketauan = true;
							strcpy(status[currpos], "DEAD");
							--sisa_cm;
						}else{
							strcpy(status[currpos], "DEAD");
							++count_kill;
							--sisa_cm;
						}
						system("CLS");
						task_bar(do_task);
						gotoxy(53, 14);
						printf("PLEASE WAIT\n");
						sleep(1);
						break;
					}
				}
			}
			posx = 24;
			posy = 3;
			system("CLS");
		}else{
			system("CLS");
			temp_kill = random(46);
			if(temp_kill % 2 != 0 && sisa_cm > 2){
				total_kill = 2;
			}else{
				total_kill = 1;
			}
			for(int i = 0; i < total_kill; i++){
				task_bar(do_task);
				gotoxy(53, 14);
				printf("PLEASE WAIT\n");
				do{
					flag = 1;
					dead = random(number_player);
					if(strcmp(status[dead], "DEAD") == 0 || impostor_flag[dead] == 1){
						flag = 0;
						continue;
					}
					strcpy(status[dead], "DEAD");
				}while(flag == 0);
				system("CLS");
				--sisa_cm;
			}
		}
		
		// CHECK WIN STAGE 1
		do_task += random(task - number_player);
		if((sisa_cm < impostor_left) || (sisa_cm <= 2 && impostor_left > 1)){
			int l = 0;
			system("CLS");
			gotoxy(2, 2);
			puts(" /$$$$$$ /$$      /$$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$$     /$$      /$$ /$$$$$$ /$$   /$$");
			gotoxy(2, 3);
			puts("|_  $$_/| $$$    /$$$| $$__  $$ /$$__  $$ /$$__  $$|__  $$__//$$__  $$| $$__  $$   | $$  /$ | $$|_  $$_/| $$$ | $$");
			gotoxy(2, 4);
			puts("  | $$  | $$$$  /$$$$| $$  \\ $$| $$  \\ $$| $$  \\__/   | $$  | $$  \\ $$| $$  \\ $$   | $$ /$$$| $$  | $$  | $$$$| $$");
			gotoxy(2, 5);
			puts("  | $$  | $$ $$/$$ $$| $$$$$$$/| $$  | $$|  $$$$$$    | $$  | $$  | $$| $$$$$$$/   | $$/$$ $$ $$  | $$  | $$ $$ $$");
			gotoxy(2, 6);
			puts("  | $$  | $$  $$$| $$| $$____/ | $$  | $$ \____  $$    | $$  | $$  | $$| $$__  $$   | $$$$_  $$$$  | $$  | $$  $$$$");
			gotoxy(2, 7);
			puts("  | $$  | $$\\  $ | $$| $$      | $$  | $$ /$$  \\ $$   | $$  | $$  | $$| $$  \\ $$   | $$$/ \\  $$$  | $$  | $$\\  $$$");
			gotoxy(2, 8);
			puts(" /$$$$$$| $$ \\/  | $$| $$      |  $$$$$$/|  $$$$$$/   | $$  |  $$$$$$/| $$  | $$   | $$/   \\  $$ /$$$$$$| $$ \\  $$");
			gotoxy(2, 9);
			puts("|______/|__/     |__/|__/       \\______/  \\______/    |__/   \\______/ |__/  |__/   |__/     \\__/|______/|__/  \\__/");
			gotoxy(39, 11);
			printf("WARNA          NAMA           STATUS\n");
			for(int i = 0; i < number_player; i++, l++){
				if(impostor_flag[i] == 1){
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					printf("\e[0;31m");
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}else{
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}
			}
			++l;
			gotoxy(45, 13 + l);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
			menu();
			if(flag_exit == 1){
				return;
			}
		}else if(do_task >= 50 || impostor_left == 0){
			int l = 0;
			system("CLS");
			gotoxy(1, 2);
			puts(" $$$$$$\\  $$$$$$$\\  $$$$$$$$\\ $$\\      $$\\ $$\\      $$\\  $$$$$$\\ $$$$$$$$\\ $$$$$$$$\\   /$$      /$$ /$$$$$$ /$$   /$$");
			gotoxy(1, 3);
			puts("$$  __$$\\ $$  __$$\\ $$  _____|$$ | $\\  $$ |$$$\\    $$$ |$$  __$$\\\\__$$  __|$$  _____| | $$  /$ | $$|_  $$_/| $$$ | $$");
			gotoxy(1, 4);
			puts("$$ /  \__| $$ |  $$ |$$ |      $$ |$$$\\ $$ |$$$$\\  $$$$ |$$ /  $$ |  $$ |   $$ |       | $$ /$$$| $$  | $$  | $$$$| $$");
			gotoxy(1, 5);
			puts("$$ |      $$$$$$$  |$$$$$\\    $$ $$ $$\\$$ |$$\\$$\\$$ $$ |$$$$$$$$ |  $$ |   $$$$$\\     | $$/$$ $$ $$  | $$  | $$ $$ $$");
			gotoxy(1, 6);
			puts("$$ |      $$  __$$< $$  __|   $$$$  _$$$$ |$$ \\$$$  $$ |$$  __$$ |  $$ |   $$  __|    | $$$$_  $$$$  | $$  | $$  $$$$");
			gotoxy(1, 7);
			puts("$$ |  $$\\ $$ |  $$ |$$ |      $$$  / \\$$$ |$$ |\\$  /$$ |$$ |  $$ |  $$ |   $$ |       | $$$/ \\  $$$  | $$  | $$\\  $$$");
			gotoxy(1, 8);
			puts("\\$$$$$$  |$$ |  $$ |$$$$$$$$\\ $$  /   \\$$ |$$ | \\_/ $$ |$$ |  $$ |  $$ |   $$$$$$$$\\  | $$/   \\  $$ /$$$$$$| $$ \\  $$");
			gotoxy(1, 9);
			puts(" \\______/ \\__|  \\__|\\________|\\__/     \\__|\\__|     \\__|\\__|  \\__|  \\__|   \\________| |__/     \\__/|______/|__/  \\__/");
			gotoxy(39, 11);
			printf("WARNA          NAMA           STATUS\n");
			for(int i = 0; i < number_player; i++, l++){
				if(impostor_flag[i] == 1){
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					printf("\e[0;31m");
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}else{
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}
			}
			++l;
			gotoxy(45, 13 + l);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
			menu();
			if(flag_exit == 1){
				return;
			}
		}
		
		gotoxy(45, 14);
		printf("SESEORANG TELAH MELIHAT MAYAT!\n");
		sleep(2);
		
		system("CLS");
		task_bar(do_task);
		gotoxy(41, 6);
		
		// LAPORAN LAPORAN
		printf("LAPORAN:\n");
		for(int i = 0, j = 1; i < 10; i++, j++){
			gotoxy(41, 7 + i + j);
			while(true){
				index = random(number_player);
				if(strcmp(status[index], "DEAD") != 0 && temp1 != index){
					temp1 = index;
					break;
				}
			}
			index = random(4);
			int temp = index;
			if(temp > 2){
				while(true){
					index = random(14);
					if(index == 9 || index == 13){
						printf("- %s %s%s\n", warna[temp1], do_it[temp], doing[index]);
						break;
					}
				}
			}else{
				printf("- %s %s%s\n", warna[temp1], do_it[temp], doing[index]);
			}
		}
		gotoxy(46, 28);
		printf("PRESS ENTER TO CONTINUE!\n");
		getchar();
		system("CLS");
		
		for(int i = 0; i < number_player; i++){
			if(strcmp(status[i], "ALIVE") == 0){
				++sisa_vote;
			}
		}
		
		if(strcmp(status[p], "DEAD") == 0 && impostor_flag[p] == 1){
			impostor = false;
			playing = false;
		}else if(strcmp(status[p], "DEAD") == 0){
			playing = false;
		}
		// VOTING VOTING
		if(playing == true){
			while(true){
				Hide();
				for(int i = 0, j = 0, l = 0; i < number_player; i++, j = (j + 1) % 3){
					if(poscurr == i){
						gotoxy(posx, posy);
						printf("<<");
					}
					if(i >= 3 && i % 3 == 0){
						l += 9;
					}
					pemain_game(info, warna, i, j, l, status, nama, you, poscurr, &y);
				}
				gotoxy(58, y + 2);
				printf("Press S for skip!\n");
				if(kbhit){
					char button = getch();
					if(poscurr > 2 && button == keyUp){
						gotoxy(posx, posy);
						printf("  ");
						posy -= 9;
						poscurr -= 3;
					}else if(poscurr + 3 < number_player && button == keyDown){
						gotoxy(posx, posy);
						printf("  ");
						posy += 9;
						poscurr += 3;
					}else if(poscurr < number_player - 1 && button == keyRight && poscurr != 2 && poscurr != 5 && poscurr != 8 ){
						gotoxy(posx, posy);
						printf("  ");
						posx += 28;
						poscurr += 1;
					}else if(poscurr % 3 != 0 && button == keyLeft && poscurr > 0){
						gotoxy(posx, posy);
						printf("  ");
						posx -= 28;
						poscurr -= 1;
					}else if(button == 'S' || button == 's'){
						// BUTTON S
						system("CLS");
						int j = 0;
						for(int i = 0, k = 0, l = 0; i < number_player; i++, k = (k + 1) % 3){
							if(i >= 3 && i % 3 == 0){
								l += 9;
							}
							pemain_game(info, warna, i, k, l, status, nama, you, poscurr, &y);
						}
						if(ketauan == true){
							gotoxy(1, pos_validation + 3);
							printf("VOTING:\n");
							for(int i = 0; i < number_player; i++){
								if(strcmp(status[i], "DEAD") != 0 && i != p){
									gotoxy(1, pos_validation + 5 + j);
									printf("%s : %s\n", warna[i], warna[p]);
									++j;
								}else if(strcmp(status[i], "DEAD") != 0 && i == p){
									gotoxy(1, pos_validation + 5 + j);
									printf("%s : Skipped voting\n", warna[i]);
									++j;
								}
								usleep(220000);
							}
							gotoxy(1, pos_validation + 5 + j);
							printf("PRESS ENTER TO CONTINUE!\n");
							getchar();
							system("CLS");
							gotoxy(50, 14);
							animasi_kick(p, nama, impostor_flag);
							if(impostor_flag[p] == 1){
								--impostor_left;
								gotoxy(50, 16);
								printf("%d Impostor remains.\n", impostor_left);
							}
							sleep(2);
							strcpy(status[p], "DEAD");
							system("CLS");
						}else{
							gotoxy(1, pos_validation + 3);
							printf("VOTING:\n");
							int random_kick = 0, skip = 0, voting = 0;
							for(int i = 0; i < number_player; i++){
								if(strcmp(status[i], "DEAD") != 0 && i != p){
									int flag_skip = 0;
									while(true){
										random_kick = random(number_player + 1);
										if(random_kick > number_player - 1){
											flag_skip = 1;
											++skip;
											break;
										}
										if(strcmp(status[random_kick], "DEAD") != 0){
											++flag_kick[random_kick];
											++voting;
											break;
										}
									}
									if(flag_skip == 0){
										gotoxy(1, pos_validation + 5 + j);
										printf("%s : %s\n", warna[i], warna[random_kick]);
										++j;
									}else{
										gotoxy(1, pos_validation + 5 + j);
										printf("%s : Skipped voting\n", warna[i]);
										++j;
									}
								}else if(strcmp(status[i], "DEAD") != 0 && i == p){
									gotoxy(1, pos_validation + 5 + j);
									printf("%s : Skipped voting\n", warna[i]);
									++skip;
									++j;
								}
								usleep(220000);
							}
							int max = 0, temp_kick = 0, sama = 0;
							for(int i = 0; i < number_player; i++){
								if(max < flag_kick[i]){
									max = flag_kick[i];
									temp_kick = i;
								}
							}
							for(int i = 0; i < number_player; i++){
								if(flag_kick[i] == max && i != temp_kick){
									sama = 1;
								}
							}
							if(voting < skip){
								gotoxy(1, pos_validation + 5 + j);
								printf("PRESS ENTER TO CONTINUE!\n");
								getchar();
								system("CLS");
								gotoxy(50, 14);
								animasi_skip(0);
								system("CLS");
							}else if(sama == 1 || voting == skip){
								gotoxy(1, pos_validation + 5 + j);
								printf("PRESS ENTER TO CONTINUE!\n");
								getchar();
								system("CLS");
								gotoxy(50, 14);
								animasi_skip(1);
								system("CLS");
							}else{
								gotoxy(1, pos_validation + 5 + j);
								printf("PRESS ENTER TO CONTINUE!\n");
								getchar();
								system("CLS");
								gotoxy(50, 14);
								animasi_kick(temp_kick, nama, impostor_flag);
								if(impostor_flag[temp_kick] == 1){
									--impostor_left;
									gotoxy(50, 16);
									printf("%d Impostor remains.\n", impostor_left);
								}else{
									--sisa_cm;
									gotoxy(50, 16);
									printf("%d Impostor remains.\n", impostor_left);
								}
								sleep(2);
								strcpy(status[temp_kick], "DEAD");
								system("CLS");
							}
						}
						break;
					}else if(button == keyEnter && strcmp(status[poscurr], "DEAD") != 0){
						// ENTER
						char valid_vote;
						int j = 0;
						gotoxy(40, pos_validation + 5);
						printf("Are you sure y/n: _\b");
						scanf("%c", &valid_vote);
						getchar();
						system("CLS");
						for(int i = 0, k = 0, l = 0; i < number_player; i++, k = (k + 1) % 3){
							if(i >= 3 && i % 3 == 0){
								l += 9;
							}
							pemain_game(info, warna, i, k, l, status, nama, you, poscurr, &y);
						}
						if(valid_vote == 'y' || valid_vote == 'Y'){
							if(ketauan == true){
								gotoxy(1, pos_validation + 3);
								printf("VOTING:\n");
								for(int i = 0; i < number_player; i++){
									if(strcmp(status[i], "DEAD") != 0 && i != p){
										gotoxy(1, pos_validation + 5 + j);
										printf("%s : %s\n", warna[i], warna[p]);
										++j;
									}else if(strcmp(status[i], "DEAD") != 0 && i == p){
										gotoxy(1, pos_validation + 5 + j);
										printf("%s : %s\n", warna[i], warna[poscurr]);
										++j;
									}
									usleep(220000);
								}
								gotoxy(1, pos_validation + 5 + j);
								printf("PRESS ENTER TO CONTINUE!\n");
								getchar();
								system("CLS");
								gotoxy(50, 14);
								animasi_kick(p, nama, impostor_flag);
								if(impostor_flag[p] == 1){
									--impostor_left;
									gotoxy(50, 16);
									printf("%d Impostor remains.\n", impostor_left);
								}
								sleep(2);
								strcpy(status[p], "DEAD");
								system("CLS");
							}else{
								gotoxy(1, pos_validation + 3);
								printf("VOTING:\n");
								int random_kick = 0, skip = 0, voting = 0;
								for(int i = 0; i < number_player; i++){
									if(strcmp(status[i], "DEAD") != 0 && i != p){
										int flag_skip = 0;
										while(true){
											random_kick = random(number_player + 1);
											if(random_kick > number_player - 1){
												++skip;
												flag_skip = 1;
												break;
											}
											if(strcmp(status[random_kick], "DEAD") != 0){
												++flag_kick[random_kick];
												++voting;
												break;
											}
										}
										if(flag_skip == 0){
											gotoxy(1, pos_validation + 5 + j);
											printf("%s : %s\n", warna[i], warna[random_kick]);
											++j;
										}else{
											gotoxy(1, pos_validation + 5 + j);
											printf("%s : Skipped voting\n", warna[i]);
											++j;
										}
									}else if(strcmp(status[i], "DEAD") != 0 && i == p){
										++flag_kick[poscurr];
										++voting;
										gotoxy(1, pos_validation + 5 + j);
										printf("%s : %s\n", warna[i], warna[poscurr]);
										++j;
									}
									usleep(220000);
								}
								int max = 0, temp_kick = 0, sama = 0;
								for(int i = 0; i < number_player; i++){
									if(max < flag_kick[i]){
										max = flag_kick[i];
										temp_kick = i;
									}
								}
								for(int i = 0; i < number_player; i++){
									if(flag_kick[i] == max && i != temp_kick){
										sama = 1;
									}
									
								}if(voting < skip){
									gotoxy(1, pos_validation + 5 + j);
									printf("PRESS ENTER TO CONTINUE!\n");
									getchar();
									system("CLS");
									gotoxy(50, 14);
									animasi_skip(0);
									system("CLS");
								}else if(sama == 1 || voting == skip){
									gotoxy(1, pos_validation + 5 + j);
									printf("PRESS ENTER TO CONTINUE!\n");
									getchar();
									system("CLS");
									gotoxy(50, 14);
									animasi_skip(1);
									system("CLS");
								}else{
									gotoxy(1, pos_validation + 5 + j);
									printf("PRESS ENTER TO CONTINUE!\n");
									getchar();
									system("CLS");
									gotoxy(50, 14);
									animasi_kick(temp_kick, nama, impostor_flag);
									if(impostor_flag[temp_kick] == 1){
										--impostor_left;
										gotoxy(50, 16);
										printf("%d Impostor remains.\n", impostor_left);
									}else{
										--sisa_cm;
										gotoxy(50, 16);
										printf("%d Impostor remains.\n", impostor_left);
									}
									sleep(2);
									strcpy(status[temp_kick], "DEAD");
									system("CLS");
								}
							}
							break;
						}
					}
				}
			}
		}else{
			int j = 0;
			for(int i = 0, k = 0, l = 0; i < number_player; i++, k = (k + 1) % 3){
				if(i >= 3 && i % 3 == 0){
					l += 9;
				}
				pemain_game(info, warna, i, k, l, status, nama, you, poscurr, &y);
			}
			gotoxy(1, pos_validation + 3);
			printf("VOTING:\n");
			int random_kick = 0, skip = 0, voting = 0;
			for(int i = 0; i < number_player; i++){
				if(strcmp(status[i], "DEAD") != 0 && i != p){
					int flag_skip = 0;
					while(true){
						random_kick = random(number_player + 2);
						if(random_kick > number_player - 1){
							flag_skip = 1;
							++skip;
							break;
						}
						if(strcmp(status[random_kick], "DEAD") != 0){
							++voting;
							++flag_kick[random_kick];
							break;
						}
					}
					if(flag_skip == 0){
						gotoxy(1, pos_validation + 5 + j);
						printf("%s : %s\n", warna[i], warna[random_kick]);
						++j;
					}else{
						gotoxy(1, pos_validation + 5 + j);
						printf("%s : Skipped voting\n", warna[i]);
						++j;
					}
				}
				usleep(220000);
			}
			int max = 0, temp_kick = 0, sama = 0;
			for(int i = 0; i < number_player; i++){
				if(max < flag_kick[i]){
					max = flag_kick[i];
					temp_kick = i;
				}
			}
			for(int i = 0; i < number_player; i++){
				if(flag_kick[i] == max && i != temp_kick){
					sama = 1;
				}
			}if(voting < skip){
				gotoxy(1, pos_validation + 5 + j);
				printf("PRESS ENTER TO CONTINUE!\n");
				getchar();
				system("CLS");
				gotoxy(50, 14);
				animasi_skip(0);
				system("CLS");
			}else if(sama == 1 || voting == skip){
				gotoxy(1, pos_validation + 5 + j);
				printf("PRESS ENTER TO CONTINUE!\n");
				getchar();
				system("CLS");
				gotoxy(50, 14);
				animasi_skip(1);
				system("CLS");
			}else{
				gotoxy(1, pos_validation + 5 + j);
				printf("PRESS ENTER TO CONTINUE!\n");
				getchar();
				system("CLS");
				gotoxy(50, 14);
				animasi_kick(temp_kick, nama, impostor_flag);
				if(impostor_flag[temp_kick] == 1){
					--impostor_left;
					gotoxy(50, 16);
					printf("%d Impostor remains.\n", impostor_left);
				}else{
					--sisa_cm;
					gotoxy(50, 16);
					printf("%d Impostor remains.\n", impostor_left);
				}
				sleep(2);
				strcpy(status[temp_kick], "DEAD");
				system("CLS");
			}
		}
		// CHECK WIN STAGE 2
		if((sisa_cm < impostor_left) || (sisa_cm <= 2 && impostor_left > 1)){
			int l = 0;
			system("CLS");
			gotoxy(2, 2);
			puts(" /$$$$$$ /$$      /$$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$$     /$$      /$$ /$$$$$$ /$$   /$$");
			gotoxy(2, 3);
			puts("|_  $$_/| $$$    /$$$| $$__  $$ /$$__  $$ /$$__  $$|__  $$__//$$__  $$| $$__  $$   | $$  /$ | $$|_  $$_/| $$$ | $$");
			gotoxy(2, 4);
			puts("  | $$  | $$$$  /$$$$| $$  \\ $$| $$  \\ $$| $$  \\__/   | $$  | $$  \\ $$| $$  \\ $$   | $$ /$$$| $$  | $$  | $$$$| $$");
			gotoxy(2, 5);
			puts("  | $$  | $$ $$/$$ $$| $$$$$$$/| $$  | $$|  $$$$$$    | $$  | $$  | $$| $$$$$$$/   | $$/$$ $$ $$  | $$  | $$ $$ $$");
			gotoxy(2, 6);
			puts("  | $$  | $$  $$$| $$| $$____/ | $$  | $$ \____  $$    | $$  | $$  | $$| $$__  $$   | $$$$_  $$$$  | $$  | $$  $$$$");
			gotoxy(2, 7);
			puts("  | $$  | $$\\  $ | $$| $$      | $$  | $$ /$$  \\ $$   | $$  | $$  | $$| $$  \\ $$   | $$$/ \\  $$$  | $$  | $$\\  $$$");
			gotoxy(2, 8);
			puts(" /$$$$$$| $$ \\/  | $$| $$      |  $$$$$$/|  $$$$$$/   | $$  |  $$$$$$/| $$  | $$   | $$/   \\  $$ /$$$$$$| $$ \\  $$");
			gotoxy(2, 9);
			puts("|______/|__/     |__/|__/       \\______/  \\______/    |__/   \\______/ |__/  |__/   |__/     \\__/|______/|__/  \\__/");
			gotoxy(39, 11);
			printf("WARNA          NAMA           STATUS\n");
			for(int i = 0; i < number_player; i++, l++){
				if(impostor_flag[i] == 1){
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					printf("\e[0;31m");
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}else{
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}
			}
			++l;
			gotoxy(45, 13 + l);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
			menu();
			if(flag_exit == 1){
				return;
			}
		}else if(do_task >= 50 || impostor_left == 0){
			int l = 0;
			system("CLS");
			gotoxy(1, 2);
			puts(" $$$$$$\\  $$$$$$$\\  $$$$$$$$\\ $$\\      $$\\ $$\\      $$\\  $$$$$$\\ $$$$$$$$\\ $$$$$$$$\\   /$$      /$$ /$$$$$$ /$$   /$$");
			gotoxy(1, 3);
			puts("$$  __$$\\ $$  __$$\\ $$  _____|$$ | $\\  $$ |$$$\\    $$$ |$$  __$$\\\\__$$  __|$$  _____| | $$  /$ | $$|_  $$_/| $$$ | $$");
			gotoxy(1, 4);
			puts("$$ /  \__| $$ |  $$ |$$ |      $$ |$$$\\ $$ |$$$$\\  $$$$ |$$ /  $$ |  $$ |   $$ |       | $$ /$$$| $$  | $$  | $$$$| $$");
			gotoxy(1, 5);
			puts("$$ |      $$$$$$$  |$$$$$\\    $$ $$ $$\\$$ |$$\\$$\\$$ $$ |$$$$$$$$ |  $$ |   $$$$$\\     | $$/$$ $$ $$  | $$  | $$ $$ $$");
			gotoxy(1, 6);
			puts("$$ |      $$  __$$< $$  __|   $$$$  _$$$$ |$$ \\$$$  $$ |$$  __$$ |  $$ |   $$  __|    | $$$$_  $$$$  | $$  | $$  $$$$");
			gotoxy(1, 7);
			puts("$$ |  $$\\ $$ |  $$ |$$ |      $$$  / \\$$$ |$$ |\\$  /$$ |$$ |  $$ |  $$ |   $$ |       | $$$/ \\  $$$  | $$  | $$\\  $$$");
			gotoxy(1, 8);
			puts("\\$$$$$$  |$$ |  $$ |$$$$$$$$\\ $$  /   \\$$ |$$ | \\_/ $$ |$$ |  $$ |  $$ |   $$$$$$$$\\  | $$/   \\  $$ /$$$$$$| $$ \\  $$");
			gotoxy(1, 9);
			puts(" \\______/ \\__|  \\__|\\________|\\__/     \\__|\\__|     \\__|\\__|  \\__|  \\__|   \\________| |__/     \\__/|______/|__/  \\__/");
			gotoxy(39, 11);
			printf("WARNA          NAMA           STATUS\n");
			for(int i = 0; i < number_player; i++, l++){
				if(impostor_flag[i] == 1){
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					printf("\e[0;31m");
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}else{
					gotoxy(39, 13 + l);
					if(i == p){
						printf("%s (%s)%-12s", warna[i], "You", " ");
					}else{
						printf("%-15s", warna[i]);
					}
					gotoxy(54, 13 + l);
					printf("%-15s", nama[i]);
					if(strcmp(status[i], "ALIVE") == 0){
						printf("\e[0;32m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}else{
						printf("\e[0;31m");
						gotoxy(69, 13 + l);
						printf("%s\n", status[i]);
						printf("\e[0;37m");
					}
				}
			}
			++l;
			gotoxy(45, 13 + l);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
			menu();
			if(flag_exit == 1){
				return;
			}
		}
	}
}

// function buat permainan mau dimulai
void play(){
	char opsi[15][255] = {"Red", "Blue", "Green", "Pink", "Orange", "Yellow", "Black", "White", "Cyan", "Brown"}, max_player[15], valid, nama[15][255] = {'\0'}, 
	status[15][255] = {"Color: ", "Name: ", "Status: "}, dead_stat[15][255] = {'\0'}, max_impostor[15];
	int number_player = 0, poscurr = 0, check[15] = {0}, proceed = 0, posx = 24, posy = 3, ctr = 0, y = 0, number_impostor = 0,
	 impostor[15] = {0}, you[15] = {0}, flag_player = 1, flag_proceed = 0;
	system("CLS");
	while(true){
		gotoxy(35, 10);
		number_player = 0;
		int flag = 0;
		printf("How many player ? Minimal Player is 6: _\b");
		scanf("%s", &max_player);
		getchar();
		system("CLS");
		int len = strlen(max_player);
		for(int i = 0; i < len; i++){
			if((max_player[i] >= 'a' && max_player[i] <= 'z') || (max_player[i] >= 'A' && max_player[i] <= 'Z')){
				flag = 1;
			}else{
				number_player = number_player * 10 + max_player[i] - '0';
			}
		}
		if(flag == 1){
			gotoxy(35, 10);
			printf("The input must number with the minimum number is 6\n");
			puts("");
			gotoxy(47, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(number_player < 6){
			gotoxy(47, 10);
			printf("Number not less than 6\n");
			puts("");
			gotoxy(46, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(number_player > 10){
			gotoxy(47, 10);
			printf("Number not more than 10\n");
			puts("");
			gotoxy(47, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(flag == 0 && number_player >= 6 && number_player <= 10){
			gotoxy(43, 10);
			printf("%d player are playing this game\n", number_player);
			puts("");
			gotoxy(48, 12);
			printf("Are you sure ? y/n _\b");
			scanf("%c", &valid);
			getchar();
			if((valid == 'n') || (valid == 'N')){
				system("CLS");
				continue;
			}
			gotoxy(46, 14);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
			break;
		}
	}
	while(true){
		number_impostor = 0;
		gotoxy(35, 10);
		printf("How many impostor are playing this game (Max 3) ? _\b");
		scanf("%s", &max_impostor);
		getchar();
		system("CLS");
		int len = strlen(max_impostor), flag = 0;
		for(int i = 0; i < len; i++){
			if((max_impostor[i] >= 'a' && max_impostor[i] <= 'z') || (max_impostor[i] >= 'A' && max_impostor[i] <= 'Z')){
				flag = 1;
			}else{
				number_impostor = number_impostor * 10 + max_impostor[i] - '0';
			}
		}
		if(flag == 1){
			gotoxy(35, 10);
			printf("The input must number with the minimum number is 1\n");
			puts("");
			gotoxy(47, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(number_player < 1){
			gotoxy(47, 10);
			printf("Number not less than 1\n");
			puts("");
			gotoxy(46, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(number_impostor > 3){
			gotoxy(47, 10);
			printf("Number not more than 3\n");
			puts("");
			gotoxy(47, 12);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			system("CLS");
		}else if(flag == 0 && number_impostor > 0 && number_impostor <= 3){
			gotoxy(43, 10);
			printf("%d Impostor are playing this game\n", number_impostor);
			puts("");
			gotoxy(48, 12);
			printf("Are you sure ? y/n _\b");
			scanf("%c", &valid);
			getchar();
			if(valid != 'y' && valid != 'Y'){
				system("CLS");
				continue;
			}
			gotoxy(46, 14);
			printf("PRESS ENTER TO CONTINUE!\n");
			getchar();
			int temp = 0;
			for(int i = 0; i < number_impostor; i++){
				gotoxy(53, 14);
				printf("PLEASE WAIT");
				int flag_impostor;
				do{
					flag_impostor = 1;
					temp = random(number_player);
					if(impostor[temp] == 1){
						flag_impostor = 0;
						continue;
					}
					impostor[temp] = 1;
				}while(flag_impostor == 0);
				system("CLS");
			}
			system("CLS");
			break;
		}
	}
	for(int i = 0; i < number_player; i++){
		strcpy(dead_stat[i], "ALIVE");
	}
	for(int i = 0; i < number_player; i++){
		strcpy(nama[i], "KOSONG");
	}
	while(true){
		Hide();
		for(int i = 0, j = 0, l = 0; i < number_player; i++, j = (j + 1) % 3){
			if(poscurr == i){
				gotoxy(posx, posy);
				printf("<<");
			}
			if(i >= 3 && i % 3 == 0){
				l += 9;
			}
			pemain_pilih(status, opsi, i, j, l, dead_stat, nama, &y, you);
		}

		if(ctr == number_player && flag_player == 0){
			flag_proceed = 1;
			gotoxy(40, y + 3);
			printf("Press P for Proceed\n");
		}
		if(kbhit){
			char button = getch();
			if(poscurr > 2 && button == keyUp){
				gotoxy(posx, posy);
				printf("  ");
				posy -= 9;
				poscurr -= 3;
			}else if(poscurr + 3 < number_player && button == keyDown){
				gotoxy(posx, posy);
				printf("  ");
				posy += 9;
				poscurr += 3;
			}else if(poscurr < number_player - 1 && button == keyRight && poscurr != 2 && poscurr != 5 && poscurr != 8 ){
				gotoxy(posx, posy);
				printf("  ");
				posx += 28;
				poscurr += 1;
			}else if(poscurr % 3 != 0 && button == keyLeft && poscurr > 0){
				gotoxy(posx, posy);
				printf("  ");
				posx -= 28;
				poscurr -= 1;
			}else if(button == keyEnter){
				system("CLS");
				char temp_nama[255];
				int flag_nama = 0;
				system("CLS");
				gotoxy(50, 10);
				printf("Color: %s\n", opsi[poscurr]);
				gotoxy(50, 12);
				printf("Input Name: _\b");
				scanf("%s", temp_nama);
				getchar();
				for(int i = 0; i < number_player; i++){
					if(strcmp(temp_nama, nama[i]) == 0){
						flag_nama = 1;
						break;
					}
				}
				if(flag_nama == 1){
					gotoxy(35, 14);
					printf("Nama sudah digunakan silahkan gunakan yang lain!\n");
					getchar();
				}else{
					system("CLS");
					if(flag_player == 1){
						char valid_player;
						gotoxy(30, 12);
						printf("Apakah anda ingin character ini sebagai player anda ? y/n _\b");
						scanf("%c", &valid_player);
						getchar();
						if(valid_player == 'y' || valid_player == 'Y'){
							flag_player = 0;
							you[poscurr] = 1;
						}
					}
					if(strcmp(nama[poscurr], "KOSONG") == 0){
						if(ctr < number_player){
							++ctr;
						}
					}
					strcpy(nama[poscurr], temp_nama);
				}
				system("CLS");
			}else if((button == 'p' && flag_proceed == 1) || (button == 'P' && flag_proceed == 1)){
				system("CLS");
				game(number_player, nama, dead_stat, opsi, impostor, number_impostor, status, you, y);
				if(flag_exit == 1){
					return;
				}
			}
		}
	}
}
// function buat opsi how to play
void how(){
	char str[500][500] = {'\0'};
	int delay;
	FILE *fptr = fopen("HTP.txt", "r");
	int ctr = 0;
	while(fscanf(fptr,"%[^\n]\n", &str[ctr]) != EOF){
		++ctr;
	}
	fclose(fptr);
	puts("");
	for(int i = 0; i < ctr; i++){
		puts("\t /$$   /$$                               /$$$$$$$$              /$$$$$$$  /$$");
		puts("\t| $$  | $$                              |__  $$__/             | $$__  $$| $$                    ");
		puts("\t| $$  | $$  /$$$$$$  /$$  /$$  /$$         | $$  /$$$$$$       | $$  \\ $$| $$  /$$$$$$  /$$   /$$");
		puts("\t| $$$$$$$$ /$$__  $$| $$ | $$ | $$         | $$ /$$__  $$      | $$$$$$$/| $$ |____  $$| $$  | $$");
		puts("\t| $$__  $$| $$  \\ $$| $$ | $$ | $$         | $$| $$  \\ $$      | $$____/ | $$  /$$$$$$$| $$  | $$");
		puts("\t| $$  | $$| $$  | $$| $$ | $$ | $$         | $$| $$  | $$      | $$      | $$ /$$__  $$| $$  | $$");
		puts("\t| $$  | $$|  $$$$$$/|  $$$$$/$$$$/         | $$|  $$$$$$/      | $$      | $$|  $$$$$$$|  $$$$$$$");
		puts("\t|__/  |__/ \\______/  \\_____/\\___/          |__/ \\______/       |__/      |__/ \\_______/ \\____  $$");
		puts("\t                                                                                        /$$  | $$");
		puts("\t                                                                                       |  $$$$$$/");
		puts("\t                                                                                        \\______/ ");
		puts("");
		puts("");
		delay = 50000;
		printf("\t\t\t");
		if(i == 3){
			printf("\t   ");
		}
		for(int j = 0; str[i][j] != '\0'; j++){
			printf("%c", str[i][j]);
			if(kbhit()){
				char get = getch();
				if(get == keyEnter){
					delay = 0;
				}
			}
			usleep(delay);
		}
		printf("\n\n\t\t\t\t\tPress enter to continue!");
		getchar();
		system("CLS");
		printf("\n");
	}
}

// function buat ngilangin cursor karena kalo gak nanti cursor nya ngeprint segala arah
void Hide(){
	printf("\e[?25l");
	COORD Curp;
	Curp.X = 0;
	Curp.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Curp);
}

// function buat menu awal
void menu(){
	if(flag_exit == 1){
		return;
	}
	char opsi[100][100] = {"Start The Game", "          ", "How To Play", "           ", "EXIT"};
	int poshome = 0;
	puts("  /$$$$$$                 /$$$$$$             /$$$$$$        /$$   /$$    ");
	puts("/$$__  $$               /$$__  $$           /$$__  $$      | $$  | $$          ");
	puts("| $$  \\ $$ /$$$$$$/$$$$ | $$  \\ $$ /$$$$$$$ | $$  \\__/      | $$  | $$  /$$$$$$$");
	puts("| $$$$$$$$| $$_  $$_  $$| $$  | $$| $$__  $$| $$ /$$$$      | $$  | $$ /$$_____/");
	puts("| $$__  $$| $$ \\ $$ \\ $$| $$  | $$| $$  \\ $$| $$|_  $$      | $$  | $$|  $$$$$$ ");
	puts("| $$  | $$| $$ | $$ | $$| $$  | $$| $$  | $$| $$  \\ $$      | $$  | $$ \\____  $$");
	puts("| $$  | $$| $$ | $$ | $$|  $$$$$$/| $$  | $$|  $$$$$$/      |  $$$$$$/ /$$$$$$$/");
	puts("|__/  |__/|__/ |__/ |__/ \\______/ |__/  |__/ \\______/        \\______/ |_______/ ");
	system("CLS");
	while(true){
		printf("\e[0;36m");
		Hide();
		puts("           .+GM###MHG*+.");
		puts("          +&%%%%&%%%%%%%M*");
		puts("         +%%#MMHHHHHMM#&%%M-");
		puts("       .#%&MMM#&%%%%%%&&%%%*");
		puts("       +%%#MM&%%&MHHM##&&%%%w");
		printf("       G%%&MM#%%&w*");
		printf("\e[0;37m");
		printf("-...  ..-");
		printf("\e[0;36m");
		printf("w%%+\n");
		printf("   +GHH&%%&MM&%%H*w");
		printf("\e[0;37m");
		printf("+--.......");
		printf("\e[0;36m");
		printf("H%%H\n");
		printf("  M%%%%%%%%%%%%%%%%%%%%&MM&%#*ww*");
		printf("\e[0;37m");
		printf("+------.");
		printf("\e[0;36m");
		printf("w%%%%#\n");
		printf(" *%%%%MHM%%%%##MM%%%%H");
		printf("\e[0;37m");
		printf("********+**");
		printf("\e[0;36m");
		printf("#%%H\n");
		puts(" M%&MM#%%##MM#%%#HHHHHHM#&%%%-");
		puts(" #%&##&%%###MMM&%%%%%%%%%%%%M");
		puts(" &%###&%%###MMMMMMMMMMMMMH&%H");
		puts(" &%###&%%####MMMMMMMMMMMMM&%H");
		puts(" &%###&%%####MMMMMMMMMMMMM&%M");
		puts(" &%###&%%#####MMMMMMMMMMM#&%#");
		puts(" #%&##&%%#######MMMMMMMM##&%#");
		puts(" H%&#M&%%##########M######&%#");
		puts(" -&%%%%%%#################&%H");
		puts("   GM&%%%######&%%%%&&&###%%*");
		puts("      *%%######%%MH%%####&%#");
		puts("      -%%######%%w.%%####%%*");
		puts("       #%&#####%%w M%%#&%%H");
		puts("       +%%%&&&%%&- .M%%%%G.");
		puts("        -G#&%%&M- .. -*+");	
		puts("");
		puts("");
		printf("\e[0;37m");
		gotoxy(35, 4);
		puts("/$$$$$$                /$$$$$$             /$$$$$$        /$$   /$$    ");
		puts("\t\t\t\t /$$__  $$               /$$__  $$           /$$__  $$      | $$  | $$          ");
		puts("\t\t\t\t| $$  \\ $$ /$$$$$$/$$$$ | $$  \\ $$ /$$$$$$$ | $$  \\__/      | $$  | $$  /$$$$$$$");
		puts("\t\t\t\t| $$$$$$$$| $$_  $$_  $$| $$  | $$| $$__  $$| $$ /$$$$      | $$  | $$ /$$_____/");
		puts("\t\t\t\t| $$__  $$| $$ \\ $$ \\ $$| $$  | $$| $$  \\ $$| $$|_  $$      | $$  | $$|  $$$$$$ ");
		puts("\t\t\t\t| $$  | $$| $$ | $$ | $$| $$  | $$| $$  | $$| $$  \\ $$      | $$  | $$ \\____  $$");
		puts("\t\t\t\t| $$  | $$| $$ | $$ | $$|  $$$$$$/| $$  | $$|  $$$$$$/      |  $$$$$$/ /$$$$$$$/");
		puts("\t\t\t\t|__/  |__/|__/ |__/ |__/ \\______/ |__/  |__/ \\______/        \\______/ |_______/ ");
		puts("");
		puts("");
		printf("\t\t\t\t\t%c", 201);
		
		for(int i = 0; i < 29; i++){
			printf("%c", 205);
		}
		printf("%c\n", 187);
		printf("\t\t\t\t\t%c                             %c\n", 186, 186);
		for(int i = 0; i < 5; i++){
			printf("\t\t\t\t\t%c", 186);
			if(poshome == i){
				printf("    >>");
			}else{
				printf("      ");
			}
			printf("  %s", opsi[i]);
			int len = strlen(opsi[i]);
			for(int j = len; j < 16; j++){
				printf(" ");
			}
			if(poshome == i){
				printf("<< ");
			}else{
				printf("   ");
			}
			printf("  %c", 186);
			puts("");
		}
		printf("\t\t\t\t\t%c                             %c\n", 186, 186);
		printf("\t\t\t\t\t%c", 200);
		for(int i = 0; i < 29; i++){
			printf("%c", 205);
		}
		printf("%c\n", 188);
		puts("");
		printf("\t\t\t\t\t     Press 'R' to refresh");
		if(kbhit(){
			char button = getch();
			if(poshome!= 0 && button == keyUp){
				poshome -= 2;
			}else if(poshome != 4 && button == keyDown){
				poshome += 2;
			}else if(button == keyEnter){
				system("CLS");
				switch(poshome){
					case 0:
						flag_exit = 0;
						play();
						if(flag_exit == 1){
							return;
						}
					break;
					case 2:
						how();
					break;
					case 4:
						flag_exit = 1;
						return;
					break;
				}
				system("CLS");
			}else if(button == 'r' || button == 'R'){
				system("CLS");
			}
		}
	}
}

// function buat placing apapun dimana aja misal mau placing tabel nya di tengah bisa pake ini
void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}
