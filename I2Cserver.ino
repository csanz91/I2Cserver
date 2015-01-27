#include <Wire.h>

//Direcciones de los dispositivos conectados al bus I2C
#define ADDR_SERVER	1
#define ADDR_LCD	2

#define NUM_DATA	5						//Num de datos que almacenara el array

//Definimos la posicion de cada dato en el array
#define data1	0
#define data2	1


int data[NUM_DATA];							//Array de datos
int i=0;

void setup() {
	Serial.begin(9600);
	Wire.begin(ADDR_SERVER);               //Nos unimos al bus I2C con la direccion dada
	Wire.onRequest(request);			   //Definimos la funcion que se ejecuta cuando el master pide los datos
	inicializar_data();					   //Inicializamos el array de datos para comprobar que los datos de mandan correctamente
}

void loop() {

}


//Envia un dato de tipo int cuando lo pide el master. Dentro de esta funcion solo se puede ejecutar un Wire.write()
void request(){

	//Convertimos el array en un string. El array almacenara como maximo 5 digitos mas el signo
	char buffer[6];    					
	sprintf(buffer, "%06d", data[i]);		//Generamos el array y rellenamos las posiciones vacias con ceros
	Wire.write(buffer);						//Envia el array al master

	//Cambia a la siguiente posicion del array para enviar el dato cuando lo vuelva a pedir el master
	i++;									
	if(i==NUM_DATA) i=0;
}


//Funcion para inicializar los datos. Valida unicamente para probar que los datos se envian correctamete
void inicializar_data(){
	for(int x=0; x<NUM_DATA; x++){
		data[x]=x-2;
	}
}
