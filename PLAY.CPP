#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#define N 4
char warning[25]="No valido$";
char empty[25]="Esta vacio$";
char none[25]="             $";
int num[5][N] = {{1, 2, 3, 1},{1, 2, 3, 3},{2, 3, 1, 2},{0, 0, 0, 0},{0, 0, 0, 0}};
int estado=0;
char flag='t';
int coorx=0;
int coory=0;
char fila=0;
char columna=0;
char colmn=0;
char row=0;
int count=0;
int ext=0;
int number=0;
void ventana(char a,char b,char a1,char b1, char c){
	asm{
		mov ax,0600h
		mov bh,c
		mov ch,a
		mov cl,b
		mov dh,a1
		mov dl,b1
		int 10H
	}
}

void inicializa_mouse(){
	asm{
		mov ax,00
		int 33h
	}
}

void mostrar_mouse(){
	asm{
		mov ax,01h
		int 33h
	}
}

void ocultar_mouse(){
	asm{
		mov ax,02h
		int 33h
	}
}

void printText(char texto[]){
	int j;
	char letra;
	j=0;
	while(texto[j]!='$'){
		letra = texto[j];
		asm{
			mov ah,02h
			mov dl,letra
			int 21h
		}
		j++;
	}
}

void posicionar_cursor(char fila,char columna){
	asm{
		mov ah,02h
		mov bh,00
		mov dh,fila
		mov dl,columna
		int 10h
	}
}

void cls(){
	asm{
		mov ax,0600h
		mov bh,01h
		mov cx,0000h
		mov dx,184Fh
		int 10h
	}
}
void limpiar(char a, char b,char a1, char b1){
	asm{
		mov ax,0600h
		mov bh,30h
		mov cl,b
		mov ch,a
		mov dl,b1
		mov dh,a1
		int 10H
	}
}

void compare(char a,char b,char a1,char b1,int number){
	flag='t';
	if(fila>a-1&&fila<a1+1){
		if(columna>b-1&&columna<b1+1){
			//ventana(a,b,a1,b1,chang);
			count = number;
		}
	}
	if(fila==0&&columna==79){
		flag='f';
	}
}

void select(){
	int fla= 0;
	for (int i = 0; i <N; i++){
		posicionar_cursor(3,35);
		int c = num[count-1][i];
		if(c!=0 && fla==0){
			number=c;
			ext=i;
			fla= 1;
			posicionar_cursor(0,30);
			printText(none);
		}
	}
	if(fla==0){
		posicionar_cursor(0,30);
		printText(empty);
	}
}

void insert(int comp){
	//printf("(%i,%i,%i)\n",ext,count-1,number);
	int fla= 0;
	if(comp!=count-1){
		
			int nu= num[count-1][3];
			if(nu==0 && fla==0){
				num[count-1][3]=number;
				fla= 1;
				posicionar_cursor(0,30);
				printText(none);
			}
		
	}
	if(fla==0){
		num[count-1][ext] = number;
		posicionar_cursor(0,30);
		printText(warning);
	}
}

void clic(){
	flag='t';
			int y=5;
			int y1=17;
			int x=7;
			
			compare(y,x,y1,x+6,1);
			compare(y,x+15,y1,22+6,2);
			compare(y,x+30,y1,x+30+6,3);
			compare(y,x+45,y1,x+45+6,4);
			compare(y,x+60,y1,x+60+6,5);
}

void box(int x, int num[N][N],int count){
	int i;
	int j;
	
	for(i=0;i<N;i++){
			int c= 7+i*3;
			//ventana(c,11,c+1,15,10);
			posicionar_cursor(c,x+3); 
			printf("%d\n", num[count][i]); //imprime los numeros en la pila
	}
}

void load(){
	int y=5;
	int y1=17;
	int x=7;
	for(int i=0;i<N+1;i++){
			ventana(y,x,y1,x+6,33);
			box(x,num,i);
			x=x+15;
	}
}
void estado_mouse(){
	inicializa_mouse();
	mostrar_mouse();

	while(flag!='f'){
		asm{
			mov ax,03h
			int 33h
			mov estado,bx
			mov coorx,cx
			mov coory,dx
			mov ax,coorx
			mov bl,8
			div bl
			mov columna,al
			mov ax,coory
			mov bl,8
			div bl
			mov fila,al
		}
		if(estado==1){
			clic();
			select();
		}

		if (estado==2){
			num[count-1][ext] = 0;
			int comp= count-1;
			clic();
			//insert(comp);
			load();
		}
		delay(75);
	}
}

int main(){
	cls();
	load();
	estado_mouse();
	system("pause");
	return 0;
}