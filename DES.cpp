#include <bits/stdc++.h>
using namespace std;
int plaintxt[65], ciphertxt[65], key[65], IP[65], PC1[57], PC2[48], 
    Exp[49], Permuted[33], C[29], D[29], sbox[49], SBoxRes[33], 
	Rprev[33], Rnext[33], Lprev[33], Lnext[33];
char keyIn[8];

int tableIP[] = {0, 
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7
},
tablePC1[] = {0,
57, 49, 41, 33, 25, 17, 9,
1, 58, 50, 42, 34, 26, 18,
10, 2, 59, 51, 43, 35, 27,
19, 11, 3, 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7, 62, 54, 46, 38, 30, 22,
14, 6, 61, 53, 45, 37, 29,
21, 13, 5, 28, 20, 12, 4
},
tablePC2[] = {0,
14, 17, 11, 24, 1, 5, 3, 28,
15, 6, 21, 10, 23, 19, 12, 4,
26, 8, 16, 7, 27, 20, 13, 2,
41, 52, 31, 37, 47, 55, 30, 40,
51, 45, 33, 48, 44, 49, 39, 56,
34, 53, 46, 42, 50, 36, 29, 32
},
tableExp[] = {0,
32, 1, 2, 3, 4, 5,
4, 5, 6, 7, 8, 9,
8, 9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1
},
tablePerm[] = {0,
16, 7, 20, 21, 29, 12, 28, 17,
1, 15, 23, 26, 5, 18, 31, 10,
2, 8, 24, 14, 32, 27, 3, 9,
19, 13, 30, 6, 22, 11, 4, 25
},
SBox1[] = {
14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
},
SBox2[] = {
15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
},
SBox3[] = {
10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
1, 10, 13, 0, 6, 9, 8 ,7, 4, 15, 14, 3, 11, 5, 2, 12
},
SBox4[] = {
7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
},
SBox5[] = {
2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
},
SBox6[] = {
12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
},
SBox7[] = {
4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
},
SBox8[] = {
13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
},
tableInvIP[65]= {0, 
40, 8, 48, 16, 56, 24, 64, 32,
39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30,
37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28,
35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26,
33, 1, 41, 9, 49, 17, 57, 25
};


void show(int a[], int len) {
	for (int i = 1; i < len; i++) if(i%8 == 0) cout << a[i] << endl;
								 else cout << a[i] << ' '; 
}

void decToBin(int a) { // blm slese
	int dec = a, bin[5];
	for (int i = 4; i > 0; i--) {
		bin[i] = dec%2;
		dec /= 2;
	}
	for (int i = 1; i < 5; i++) SBoxRes[i] = bin[i];
}

void initialPerm() {
	for (int i = 1; i < 65; i++) IP[i] = plaintxt[tableIP[i]];
//	cout << endl << "IP: \n"; show(IP,65);
}

void prevLR() {
	for(int i=1;i<33;i++){
		Lprev[i] = IP[i];
		for(int j=33;j<65;j++) Rprev[i] = IP[j];
	}	
}

void nextLR() {
	for(int i = 0; i < 33; i++) Lnext[i] = Rprev[i];

	for(int i = 0; i < 33; i++){
		Rprev[i] = Rnext[i];
		Lprev[i] = Lnext[i];
	}
}

void prevCD() {
	for(int i = 1; i < 29; i++){
		C[i] = PC1[i];
		D[i] = PC1[i+28];
	}
}

void leftShift(int a) {
	int tempC, tempD;
	if (a != 1 && a != 2 && a != 9 && a != 16) {
		tempC = C[1]; tempD = D[1];
		for (int i = 1; i < 28; i++) {
			C[i] = C[i+1];
			D[i] = D[i+1];
		}
		C[28] = tempC; D[28] = tempD;
	}
	tempC = C[1]; tempD = D[1];
	for (int i = 1; i < 28; i++) {
		C[i] = C[i+1];
		D[i] = D[i+1];
	}
	C[28] = tempC; D[28] = tempD;
//	cout << endl << "C: \n"; show(C,29);
//	cout << endl << "D: \n"; show(D,29);

}

void permChoice1() {
	for (int i = 1; i < 57; i++) PC1[i] = key[tablePC1[i]];
//	cout << endl << "PC1: \n"; show(PC1,57);
}

void permChoice2() {
	int keyShifted[57];
	for (int i = 1; i < 29; i++) {
		keyShifted[i] = C[i];
		keyShifted[i+28] = D[i];
	}
	for (int i = 1; i < 49; i++) PC2[i] = keyShifted[tablePC2[i]];
//	cout << endl << "PC2: \n"; show(PC2,49);
}

void expansion() {
	for(int i = 1; i < 49; i++) Exp[i] = Rprev[tableExp[i]];	
//	cout << endl << "Exp: \n"; show(Exp,49);
}

void doXOR(int a[], int b[], int c[]) {
	for(int i = 1; i < 49; i++)	if(a[i] != b[i]) c[i] = 1;
								else c[i] = 0;
}

int SBoxPosition(int a[7]) {
	int rrow[3], rcol[5], rowdec = 0, coldec = 0;
	rrow[1] = a[1];
	rrow[2] = a[6];
	for(int i = 1; i <= 4; i++) rcol[i] = a[i+1];
	
	for(int i = 1 ; i < 3; i++) rowdec = rowdec + rrow[i] * pow(2,2-i);
	
	for(int i = 1; i<5 ; i++) coldec = coldec + rcol[i] * pow(2,4-i);

	return rowdec * 16 + coldec;
}

void SBox() {
	int s1[7], s2[7], s3[7], s4[7], s5[7], s6[7], s7[7], s8[7];
	int dec1, dec2, dec3, dec4, dec5, dec6, dec7, dec8;
	for(int i = 1; i < 7; i++) {
		s1[i]=sbox[i];
		s2[i]=sbox[6*1+i];
		s3[i]=sbox[6*2+i];
		s4[i]=sbox[6*3+i];
		s5[i]=sbox[6*4+i];
		s6[i]=sbox[6*5+i];
		s7[i]=sbox[6*6+i];
		s8[i]=sbox[6*7+i];
	}
	
	dec1 = SBoxPosition(s1);
	decToBin(dec1);
	dec2 = SBoxPosition(s2);
	decToBin(dec2);
	dec3 = SBoxPosition(s3);
	decToBin(dec3);
	dec4 = SBoxPosition(s4);
	decToBin(dec4);
	dec5 = SBoxPosition(s5);
	decToBin(dec5);
	dec6 = SBoxPosition(s6);
	decToBin(dec6);
	dec7 = SBoxPosition(s7);
	decToBin(dec7);
	dec8 = SBoxPosition(s8);
	decToBin(dec8);
}

void Perm() {
	for (int i = 1; i < 33; i++) Permuted[i] = SBoxRes[tablePerm[i]];
}

void generateCipher() {
	int temp[65];
//	cout << endl ; show(Lnext,33);
//	cout << endl ; show(Rnext,33);
	for (int i = 1; i < 33; i++) {
		ciphertxt[i] = Lnext[i];
		ciphertxt[i+32] = Rnext[i];
	}
	
}
void generateKey() {
	int dec, index = 1, temp[8];
	if (strlen(keyIn) < 8) for (int i = strlen(keyIn); i < 8; i++) keyIn[i] = '*'; 
	for (int i = 0; i < 8; i++) {
		dec = keyIn[i];
		int j = 7;
		while(j >= 0){
			temp[j] = dec%2;
			dec /= 2;
			j--;
		}
		j = 0;
		while(j < 8) {
			key[index] = temp[j];
			j++;
			index++;
		}
	}
}

int main() {
	srand(time(NULL));
	int round = 1;
	for (int i = 1; i < 65; i++) plaintxt[i] = rand()%2;	// generate plain text
//	for (int i = 1; i < 65; i++) key[i] = rand()%2;			// generate key
	
	cout << "PLAIN TEXT:" << endl;
	show(plaintxt,65);
	
	cout << "Insert 8 digits key: " ;
	cin.getline(keyIn,8);
	generateKey();
	
	cout << endl << "KEY: " << endl;
	show(key,65);
	
//	PLAIN TEXT
	initialPerm();		
	prevLR();
	
//	KEY
	permChoice1();
	prevCD();
	
	while(round <= 16) {
		
//		PLAINTEXT		KEY
						leftShift(round);
		expansion();	permChoice2();
		
					doXOR(Exp, PC2, sbox);
					SBox();
					Perm();
					doXOR(Lprev, Permuted, Rnext);
		
		nextLR();
		round++;
	}
	
	generateCipher();
	cout << endl << "CIPHERTEXT:" << endl;
	show(ciphertxt,65);

	
	return 0;
}

