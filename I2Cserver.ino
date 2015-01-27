#include <Wire.h>

//Direcciones de los dispositivos conectados al bus I2C
#define ADDR_SERVER	1
#define ADDR_LCD	2

#define NUM_DATA	5						//Num de datos que almacenara el array

//Definimos la posicion de cada dato en el array
#define data1	0
#define data2	1

volatile byte* INPUT1FloatPtr;

float data[NUM_DATA];							//Array de datos
int i=0;

void setup() {
	Serial.begin(9600);
	Wire.begin(ADDR_SERVER);               //Nos unimos al bus I2C con la direccion dada
	Wire.onRequest(requestfloat);			   //Definimos la funcion que se ejecuta cuando el master pide los datos
	inicializar_data();					   //Inicializamos el array de datos para comprobar que los datos de mandan correctamente
}

void loop() {

}


//Envia un dato de tipo float cuando lo pide el master. Dentro de esta funcion solo se puede ejecutar un Wire.write()
void requestfloat(){
	byte DatatoSend[4];						//Vamos a enviar un float, por lo que necesitaremos 4 bytes
 	INPUT1FloatPtr = (byte*) &data[i];
	DatatoSend[0] = INPUT1FloatPtr[0]; 
	DatatoSend[1] = INPUT1FloatPtr[1]; 
	DatatoSend[2] = INPUT1FloatPtr[2]; 
	DatatoSend[3] = INPUT1FloatPtr[3]; 
	Wire.write(DatatoSend, 4);

	//Cambia a la siguiente posicion del array para enviar el dato cuando lo vuelva a pedir el master
	i++;									
	if(i==NUM_DATA) i=0;
}

//Funcion para inicializar los datos. Valida unicamente para probar que los datos se envian correctamete
void inicializar_data(){
	for(int x=0; x<NUM_DATA; x++){
		data[x]=123456.789;
	}
}
