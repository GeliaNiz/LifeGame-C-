#include <stdio.h>
#include <Windows.h>
#include <time.h>
char** createField(int wd, int hg) {
	char** field = (char**)malloc(hg * sizeof(char*));
	for (int i = 0; i < hg; i++) {
		field[i] = (char*)malloc(wd * sizeof(char));
	}
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			field[i][j] = ' ';
		}
	}
	return field;
}

char** initField(int wd, int hg, int alive) {
	char** field = createField(wd, hg);
	while(alive>0){
		field[rand() % hg][rand() % wd] = '*';
		alive--;
		}
	return field;
}

void printField(int wd, int hg, char** field) {
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			printf("%c ", field[i][j]);
		}
		printf("\n");
	}
}
char** copyField(int wd, int hg, char** field) {
	char** copy_field = (char**)malloc(hg * sizeof(char*));
	for (int i = 0; i < hg; i++) {
		copy_field[i] = (char*)malloc(wd * sizeof(char));
	}
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			copy_field[i][j] = field[i][j];
		}
	}
	return copy_field;
}

int countNeighbours(int x, int y, char** field, int wd, int hg) {
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(i == 0 && j == 0)) {
				if (field[(x + i+hg)%hg][(y + j+wd)%wd] == '*') count++;
			}
		}
	}
	return count;
}

char** update(int wd, int hg, char** field) {
	char** current = copyField(wd, hg, field);
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			int neigh = countNeighbours(i, j, field,wd,hg);
			if (field[i][j] == '*') {
				if ((neigh< 2) || (neigh > 3)) {
					current[i][j] = ' ';
				}
			}
			else {
				if (neigh == 3) {
					current[i][j] = '*';	
				}
			}
		}
	}
	if (comparison(field, current, wd, hg) == 1) {
		exit(0);
	}
	return current;
}
int comparison(char** field1, char** field2,int wd,int hg) {
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			if (field1[i][j] != field2[i][j])return 0;
		}
	}
	return 1;
}
int count_alive(char** field,int wd, int hg) {
	for (int i = 0; i < hg; i++) {
		for (int j = 0; j < wd; j++) {
			if (field[i][j] == '*')return 1;
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));
	int wd = 0, hg = 0;
	int init = 0;
	scanf_s("%d%d%d", &wd, &hg, &init);
	char** field = initField(wd, hg, init);
	while (1) {
		printField(wd, hg, field);
		field = update(wd, hg, field);
		if (count_alive(field, wd, hg) == 0)exit(0);
			system("cls");
		Sleep(1);

	}
}
