#include <Wire.h>

#define ADDR_SERVO	1
#define ADDR_LCD	2
#define NUM_DATA	5


#define data1	0
#define data2	1


int data[NUM_DATA];
int i=0;

void setup() {
	Serial.begin(9600);
	Wire.begin(ADDR_SERVO);                // join i2c bus
	Wire.onRequest(request);
	inicializar_data();
}

void loop() {

	inicializar_data(); //Prueba commit

}


void request(){

	char buffer[5];
	sprintf(buffer, "%05d", data[i]);
	Wire.write(buffer);
	i++;
	if(i>=NUM_DATA) i=0;
}

void inicializar_data(){
	for(int i=0; i<NUM_DATA; i++){
		data[i]=i;
	}
}
