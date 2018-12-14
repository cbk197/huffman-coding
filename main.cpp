
#include"huffman.h"
int main(){
	FILE *f;
	char s[1000];
	Data *data;
	int count=0,i,arr[26],len = 0; 
	int ch, condition1, condition2, condition3;
   while(1)
   {  
   	  
   	  printf("\n\n======================\n");
      printf("CHUONG TRINH . . .\n");
      printf("======================\n");
      printf(" 1. Nhap du lieu tu ban phim\n");
      printf(" 2. Nhap du lieu tu file (ten vao tu ban phim)\n");
      printf(" 3. Tao du lieu ngau nhien\n");
      printf(" 4. Thoat chuong trinh\n");
      printf("----------------------\n");
      printf("Chon chuc nang nhap du lieu hoac thoat chuong trinh 1 -> 4: ");
      while(1){
      	fflush(stdin);
      	scanf("%d",&ch); 
      	if(1<=ch&&ch<=4) break;
      	printf("\nchi duoc chon so tu 1 den 4. so ban chon la : ");
	  };
	  if(ch == 4) exit(0);
	  printf("\nchon 1 de xem du lieu tren man hinh 0 de bo qua : ");
	  while(1){
      	fflush(stdin);
      	scanf("%d",&condition1); 
      	if(condition1==0|| condition1 ==1) break;
      	printf("\nchi duoc chon so tu 1 hoac 0. so ban chon la : ");
	  };
	  printf("\nchon 1 de ghi ket qua ra file va 0 de ghi ket qua ra man hinh : ");
      while(1){
      	fflush(stdin);
      	scanf("%d",&condition2); 
      	if(condition2==0|| condition2 ==1) break;
      	printf("\n chi duoc chon so tu 1 hoac 0. so ban chon la : ");
	  };
	  printf("\nchon 1 de xem ket qua trung gian 0 de bo qua : ");
	  while(1){
	  	fflush(stdin);
      	scanf("%d",&condition3); 
      	if(condition3==0|| condition3 ==1) break;
      	printf("\n chi duoc chon so tu 1 hoac 0. so ban chon la : ");
	  };
	clock_t begin;
	clock_t end ;
	double time_spent; 
	//(double)(end - begin) / CLOCKS_PER_SEC;
     begin = clock();
     switch(ch) {
        case 1: {
        	data = readConsole(&count,s);
        	quickSort(data,0,count-1);
			Tree *tree;
			tree = createTree((unsigned)(count), data);
			buildTree(tree);
			Result *result = (Result *)malloc(count*sizeof(Result));
			indexCurent =0;
			createResult(tree->tree[0], result, 0, 0);
			unsigned int enCode[95][2]; // mang chua gia tri va do dai cau result. hang 0 chua value . hang 1 chua do dai tinh theo bit
			memset(enCode,0,95*2*sizeof(char));
			for(i = 0 ; i< count ; i++){
				enCode[(int)(result[i].character)-32][0]= result[i].value;
				enCode[(int)(result[i].character)-32][1]= result[i].len;
			};
			if(condition3 == 1){
				printf("\nin ket qua trung gian(ma code sau khi tinh toan ):\n");
				printfTree(tree -> tree[0], arr, len);
			};
			encodeConsole(s,enCode,condition2);
			break;
		};
        case 2:  {
        	
        	data = readFile(&count, &f);
        	
        	quickSort(data,0,count-1);
			Tree *tree;
			tree = createTree((unsigned)(count), data);
			buildTree(tree);
			Result *result = (Result *)malloc(count*sizeof(Result));
			indexCurent =0;
			createResult(tree->tree[0], result, 0, 0);
			unsigned int enCode[96][2]; // mang chua gia tri va do dai cau result. hang 0 chua value . hang 1 chua do dai tinh theo bit
			memset(enCode,0,96*2*sizeof(char));
			for(i = 0 ; i< count ; i++){
				if(result[i].character != 10){
					enCode[(int)(result[i].character)-32][0]= result[i].value;
					enCode[(int)(result[i].character)-32][1]= result[i].len;
				}else{
					enCode[95][0]=result[i].value;
					enCode[95][1]=result[i].len;
				}
				
			};
			
			if(condition1 == 1){
				showDataFile(f);
			};
			if(condition3 == 1){
				printf("\nin ket qua trung gian(ma code sau khi tinh toan ):\n");
				printfTree(tree -> tree[0], arr, len);
			};
			encodeFile(f,enCode,condition2);
			fclose(f);
			break;
		};
		case 3:{
			data = randomData(&count,s);
        	quickSort(data,0,count-1);
			Tree *tree;
			tree = createTree((unsigned)(count), data);
			buildTree(tree);
			Result *result = (Result *)malloc(count*sizeof(Result));
			indexCurent =0;
			createResult(tree->tree[0], result, 0, 0);
			unsigned int enCode[95][2]; // mang chua gia tri va do dai cau result. hang 0 chua value . hang 1 chua do dai tinh theo bit
			memset(enCode,0,95*2*sizeof(char));
			for(i = 0 ; i< count ; i++){
				enCode[(int)(result[i].character)-32][0]= result[i].value;
				enCode[(int)(result[i].character)-32][1]= result[i].len;
			};
			if(condition1 == 1){
				showDataRand(s);
			};
			if(condition3 == 1){
				printf("\nin ket qua trung gian(ma code sau khi tinh toan ):\n");
				printfTree(tree -> tree[0], arr, len);
			};
			encodeConsole(s,enCode,condition2);
			break;
		};
     } //switch
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n time run : %f second\n", time_spent);
  } // end while

}
