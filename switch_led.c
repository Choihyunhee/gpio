#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define HIGH 	1
#define LOW 	0
#define INPUT 	1
#define OUTPUT 0
int inputPin =32;
int outputPin =38;

bool digitalPinMode(int pin, int dir){
	FILE * fd;
	char fName[128];
  
	if(( fd = fopen("/sys/class/gpio/export", "w")) == NULL) {
		printf("Error: unable to export pin\n");
		return false;
	}
	fprintf(fd, "%d\n", pin);
	fclose(fd);

	sprintf(fName, "/sys/class/gpio/gpio%d/direction", pin);
	if((fd = fopen(fName, "w")) == NULL) {
		printf("Error: can't open pin direction\n");
		return false;
	}
	if(dir == OUTPUT) {
		fprintf(fd, "out\n");
	}
	else {
		fprintf(fd, "in\n");
	}
	fclose(fd);

	return true;
}
int digitalRead(int pin) {
	FILE * fd;
	char fName[128];
	char val[2];

	sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
	if((fd = fopen(fName, "r")) == NULL) {
		printf("Error: can't open pin value\n");
		return false;
	}
	fgets(val, 2, fd);
	fclose(fd);

	return atoi(val);
}

bool digitalWrite(int pin, int val) {
	FILE * fd;
	char fName[128];

	sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
	if((fd = fopen(fName, "w")) == NULL) {
		printf("Error: can't open pin value\n");
		return false;
	}
	if(val == HIGH) {
		fprintf(fd, "1\n");
	}
	else {
		fprintf(fd, "0\n");
	}
	fclose(fd);

	return true;
}
int setup(){
        if(!digitalPinMode(inputPin,INPUT)) return -1;
        if(!digitalPinMode(outputPin,OUTPUT)) return -1;
        return 0;
}
int main(void){
        if(setup()==-1) exit(1);
         while(1)
        {
	int sensorVal=digitalRead(inputPin);
	if(sensorVal==0)
                                digitalWrite(outputPin,1);
	else
                                digitalWrite(outputPin,0);
         }
        return 0;
}

