#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include<string.h>
#include<time.h>

// cau truc node cua cay 
typedef struct Node {
	char character;
	unsigned f;
	Node *right, *left;

};

// cau truc mang chua cac node chua duoc su ly 
typedef struct Tree {
	unsigned count;  //so luong node
	Node **tree;
};

//cau tru chua data va f 
typedef struct Data {
	char character;
	unsigned f;
};

//ket qua cay huffman 
typedef struct Result{
	char character; 
	unsigned int value;
	unsigned int len;
};

// khoi tao node voi tan suat va gia tri. neu node la node internal thi gia tri la $ 
Node * createNode(char c, unsigned f, Node *right, Node * left) {
	Node * newNode = (Node *)malloc(1 * sizeof(Node));
	newNode->character = c;
	newNode->f = f;
	newNode->left = left;
	newNode->right = right;
	return newNode;
};

//khoi tao cay voi cac nut la  theo thu tu giam dan cua f 
Tree * createTree(unsigned count, Data* data) {
	Tree * tree = (Tree*)malloc(sizeof(Tree));
	tree->count = count; 
	tree->tree = (Node**)malloc(count * sizeof(Node));
	int i; 
	for (i = 0; i < count; i++) {
		tree->tree[i] = createNode(data[i].character, data[i].f, NULL, NULL);
	}
	return tree;

}

//search index insert node
int searchIdxInsert(Node **tree, unsigned f, int first , int last ) {
	if (last - first == 1) {
		if(f > tree[first]->f ) return first;
		else return last;
	}
	else {
		if (f > tree[(last - first)/2 +first]->f) {
			last = (last - first) / 2 +first;
			return searchIdxInsert(tree, f, first, last);
		}
		else {
			first = (last - first) / 2 + first;
			return searchIdxInsert(tree, f, first, last);
		}
	}
}

//chen node internal vao cay 
void insertNode(Node *node, Tree *tree) {
	int i ; 
	if (tree->count != 0) {
		int index = searchIdxInsert(tree->tree, node->f, 0, tree->count);
		for (i = tree->count; i > index; i--) { //dan cac phan tu nho hon node->f ve sau de chen node vao mang 
			tree->tree[i] = tree->tree[i - 1];
		}
		tree->tree[index] = node;
	}
	else {
		tree->tree[0] = node;
	}
	
	++tree->count;
}

//tao node intrenal tu tree 
Node *createInternalNode(Tree *tree) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->character = '$';
	node->f = tree->tree[tree->count - 1]->f + tree->tree[tree->count - 2]->f;
	node->left = tree->tree[tree->count - 2];
	node->right = tree->tree[tree->count - 1];
	--tree->count;
	--tree->count;
	return node;
}

// xay dung cay huffman
void buildTree(Tree *tree) {
	Node *internal;
	while (tree->count != 1) {
		internal = createInternalNode(tree);
		
		insertNode(internal, tree);
	}
}
// in cay ket qua ra man hinh 

void printfTree(Node *root, int arr[], int len) {
	if (root->left) {
		arr[len] = 0;
		
		printfTree(root->left, arr, len+1);
	}
	if (root->right) {
		arr[len] = 1; 
		
		printfTree(root->right, arr, len+1);
	}

	if (root->character != '$') {
		int i;
		printf("\n%c(%d) : %d :", root->character, root->character, root->f);
		for (i = 0; i < len ; i++) {
			printf("%d", arr[i]);
		}
	}
	
}

// doi cho 2 phan tu mang data 
void swap(Data *data1, Data* data2) {
	Data t; 
	t = *data1;
	*data1 = *data2; 
	*data2 = t;
};
 
// xac dinh xac dinh phan tu tru sap xep va cha lai 
int indexPivot(Data* data, int low, int high) {
	int pivot = data[high].f;
	int i = low - 1; 
	int j; 
	for (j = low; j < high ; j++) {
		if (data[j].f > pivot) {
			i++; 
			swap(&data[i], &data[j]);
		}
	};
	swap(&data[i + 1], &data[high]);
	return (i + 1);
}


// sap xep lai  danh sach cac ky tu vua doc tu file
void quickSort(Data* data, int low, int high) {
	int indexpivot; 
	if (low < high) {
		indexpivot = indexPivot(data, low, high);
		quickSort(data, low, indexpivot - 1);
		quickSort(data, indexpivot + 1, high);
	}
}

int indexCurent = 0;
// tao cay ket qua 
void createResult(Node* root, Result *result, int len,int value ) {
	if (root->character != '$') {
		
		result[indexCurent].character = root->character;
		result[indexCurent].len = len;
		result[indexCurent].value = value;
		indexCurent++;
	};
	
	if (root->left) {
		createResult(root->left, result, len + 1, value << 1);
	};

	if (root->right) {
		createResult(root->right, result, len + 1, (value << 1)+ 1);
	}
}


// doc file tra ve data[] 
Data* readFile(int *count, FILE **f) {
	*count =0;
	char c;
	int i; 
	Data data[96];
	for (i = 0; i < 95; i++){
		data[i].character = (char)(i + 32);
		data[i].f = 0; 
	};
	data[95].character = (char)(10);
	data[95].f = 0; 
	do {
		char s[256];
		memset(s,0,256);
		printf("\nnhap duong dan file : ");
		fflush(stdin);
		scanf("%s", &s);
		*f = fopen(s, "rt");
		if (*f == NULL) {
			perror("\nERROR open file :");

		};
	} while (*f == NULL);
	
		c = fgetc(*f);
		do{
			
			
			if (31 < (unsigned int)c && (unsigned int)c< 127 || (unsigned int)c == 10 || (unsigned int)c ==13 ) {
				if ((unsigned int)c != 36 ){
					if((unsigned int)c != 10 && (unsigned int)c != 13){
						if (data[(int)c - 32].f == 0) {
							(*count)++;
						};
						(data[(int)c - 32].f)++;
					}else{
						if(data[95].f==0){
							(*count)++;
						};
						(data[95].f)++;
					}
					
					
					c = fgetc(*f);
					continue;
				};
				if (data[(int)c - 32-1].f == 0) {
						(*count)++;
				};
				(data[(int)c - 32 - 1].f)++; // neu gap ky tu $ thi thay bang ky tu # 
				c = fgetc(*f);
			};
			c = fgetc(*f);
			
		}while (!feof(*f));
	
	Data *dataReturn;
	int index = 0; 
	dataReturn = (Data*)malloc((*count)*sizeof(Data));
	for (i = 0; i < 96; i++) {
		if (data[i].f != 0) {
			
			dataReturn[index].character = data[i].character;
			dataReturn[index].f = data[i].f;
			index++; 
		}
	};
	return dataReturn; 
}

// doc du lieu tu console 
Data* readConsole(int *count,char s[]){
	*count =0 ;
	printf("\n nhap du lieu dau vao <1000 ky tu : \n");
	Data *dataReturn;
	Data data[95];
	memset(data,0,95*sizeof(Data));
	char c;
	int len = 0, i, index =0; 
	fflush(stdin);
	while(len <1000){
		c = getc(stdin);
		if((int)c!=10 ){
			if(c != '$' && (31 < (int)c && (int)c<127)){
				s[len]= c; 
				len++;	
			};
			
		}else break;
		
	};
	for(i = 0 ; i<len ; i++){
		if(data[(int)s[i]-32].f==0){
			data[(int)s[i]-32].character = s[i];
			(*count)++;
			data[(int)s[i]-32].f++;
		}else{
			data[(int)s[i]-32].f++;
		}
	};
	
	dataReturn = (Data *) malloc ((*count)*sizeof(Data));
	for (i = 0; i < 95; i++) {
		if (data[i].f != 0) {
			
			dataReturn[index].character = data[i].character;
			dataReturn[index].f = data[i].f;
			index++; 
		}
	};
	return dataReturn ;
};

// ham ma hoa du lieu doc tu file 
void encodeFile( FILE* f,unsigned int encode[][2], int condition ){
	int  value=0,len=0, remainder=0;
	char character=0,c;
	fseek(f,0,SEEK_SET);
	if(condition == 1){
		
		FILE* f1; // file result 
		char filename[256];
		printf("\nnhap ten file ban muon luu : ");
		fflush(stdin);
		scanf("%s",&filename);
		f1 = fopen(filename,"wt");
		if(f1 == NULL ){
			
			perror("ERROR open file");
			return;
		};
		
		
		do{
			c = fgetc(f);
			if((unsigned int)c != 10 && (unsigned int)c != 13 && (unsigned int)c >31 &&(unsigned int)c <127){
				if(len + encode[(unsigned int)c-32][1]<8){
					len = len + encode[(int)c-32][1];
					character = (character<<(encode[(unsigned int)c-32][1]))+ encode[(unsigned int)c-32][0];
				
				}else{
					remainder = encode[(unsigned int)c-32][1] - (8 - len);
					character = (character<<(8-len)) + (encode[(unsigned int)c-32][0] >>remainder);
					fputc(character,f1);
					character = (encode[(unsigned int)c -32][0])<<(32 -remainder)>>(32 -remainder);
					len = remainder;
				}
			}else{
				if((unsigned int)c == 10 || (unsigned int)c == 13){
					if(len + encode[95][1]<8){
						len = len + encode[95][1];
						character = (character<<(encode[95][1]))+ encode[95][0];
				
					}else{
						remainder = encode[95][1] - (8 - len);
						character = (character<<(8-len)) + (encode[95][0] >>remainder);
						fputc(character,f1);
						character = (encode[95][0])<<(32 -remainder)>>(32 -remainder);
						len = remainder;
					}
				}
			}
			
		}while(!feof(f));
		
		if(len > 0){
			character = character<<(8-len);
			fputc(character,f1);
		};
		fclose(f1);
	}else{
		printf("\n ket qua : \n");
		do{
			c = fgetc(f);
			if(len + encode[(int)c-32][1]<8){
				len = len + encode[(int)c-32][1];
				character = (character<<(encode[(int)c-32][1]))+ encode[(int)c-32][0];
				
			}else{
				remainder = encode[(int)c-32][1] - (8 - len);
				character = (character<<(8-len)) + (encode[(int)c-32][0] >>remainder);
				printf("%c", character);
				character = (encode[(int)c -32][0])<<(32 -remainder)>>(32 -remainder);
				len = remainder;
			}
		}while(!feof(f));
		
		if(len > 0){
			character = character<<(8-len);
			printf("%c", character);
		};
	};

	fclose(f);
	
};

// ham ma hoa du lieu tu console 
void encodeConsole(char s[],unsigned int encode[][2], int condition ){
	int  value=0,len=0, remainder=0, lenOfStr = 0;
	char character=0,c;
	if(condition == 1 ){
		FILE* f1; // file result 
		char filename[256];
		printf("\nnhap ten file ban muon luu : ");
		fflush(stdin);
		scanf("%s",&filename);
		f1 = fopen(filename,"wt");
		if(f1 == NULL ){
			
			perror("ERROR open file");
			return;
		};
		do{
			c = s[lenOfStr];
			lenOfStr++;
			if(len + encode[(int)c-32][1]<8){
				len = len + encode[(int)c-32][1];
				character = (character<<(encode[(int)c-32][1]))+ encode[(int)c-32][0];
				
			}else{
				remainder = encode[(int)c-32][1] - (8 - len);
				character = (character<<(8-len)) + (encode[(int)c-32][0] >>remainder);
				fputc(character,f1);
				character = (encode[(int)c -32][0])<<(32 -remainder)>>(32 -remainder);
				len = remainder;
			}
		}while(lenOfStr <= strlen(s));
		if(len > 0){
			character = character<<(8-len);
			fputc(character,f1);
		};
		fclose(f1);
		
	}else{
		printf("\n ket qua : \n");
		do{
			c = s[lenOfStr];
			lenOfStr++;
			if(len + encode[(int)c-32][1]<8){
				len = len + encode[(int)c-32][1];
				character = (character<<(encode[(int)c-32][1]))+ encode[(int)c-32][0];
				
			}else{
				remainder = encode[(int)c-32][1] - (8 - len);
				character = (character<<(8-len)) + (encode[(int)c-32][0] >>remainder);
				printf("%c", character);
				character = (encode[(int)c -32][0])<<(32 -remainder)>>(32 -remainder);
				len = remainder;
			}
		}while(lenOfStr<= strlen(s));
		
		if(len > 0){
			character = character<<(8-len);
			printf("%c", character);
		};
	}
};


// tao du lieu ngau nhien 
Data* randomData( int *count, char s[]){
	printf("\n du lieu ngau nhien duoc tao la : \n");
	unsigned int i,c,index =0;
	for(i = 0; i<999; i++){
		c = rand() % 127;
		if(c < 32){
			c = c +32 ;
			if(c == 36){
				c = 37;
			}
		};
		s[i] = (char)c;
	};
	Data *dataReturn;
	Data data[95];
	memset(data,0,95*sizeof(Data));
	for(i = 0 ; i<999 ; i++){
		if(data[(int)s[i]-32].f==0){
			data[(int)s[i]-32].character = s[i];
			(*count)++;
			data[(int)s[i]-32].f++;
		}else{
			data[(int)s[i]-32].f++;
		}
	};
	
	dataReturn = (Data *) malloc ((*count)*sizeof(Data));
	for (i = 0; i < 95; i++) {
		if (data[i].f != 0) {
			
			dataReturn[index].character = data[i].character;
			dataReturn[index].f = data[i].f;
			index++; 
		}
	};
	return dataReturn ;
};

//xem du lieu file tren man hinh 
void showDataFile(FILE *f){
	fseek(f,0,SEEK_SET);
	char c;
	printf("\ndu lieu can ma hoa : \n");
	do{
		c = fgetc(f);
		printf("%c",c);
	}while(!feof(f));
	fseek(f,0,SEEK_SET);
	printf("\n\n");
};

//show data random 
void showDataRand(char s[]){
	int i ; 
	printf("\ndu lieu duoc tao ngau nhien : \n");
	for( i =0; i< 999 ; i++){
		printf("%c",s[i]);
	};
	printf("\n\n");
};

