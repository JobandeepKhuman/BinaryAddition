#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//Creating a global pointer that will point to argv so that other functions can access argv
char **global_argv;

//Function to check the length of the user input
//The function should only accept 8 bit binary numbers, therefore input should
//be 8 bits long
int lengthChecker(){
  //Comparing the user input to the maximum length of 9 characters
  if(strlen(global_argv[1])!=8||strlen(global_argv[2])!=8){
    //Displaying appropriate error message
    printf("ERROR: an input that was not 8 characters long was entered \n");
    //0 is returned for a failed test, 1 is returned if the inputs pass the test
    return 0;
  }
  else{
    return 1;
  }
}


//Function to test if the user entered a binary number
int typeChecker(){
  int test=0; //Initialising variable
  //Testing if the first input is a binary number
  for (int i = 0; i != strlen(global_argv[1]); i++) {
    //Variable created to make the following line of code more easily readable
    char n = global_argv[1][i];
    //Incrementing the test variable for each character from the 1st input that
    //is 1 or 0
    if(n=='0'||n=='1'){
      test++;
    }
  }
  //Testing if the second input is a binary number
  for (int i = 0; i != strlen(global_argv[2]); i++) {
    //Variable created to make the following line of code more easily readable
    char n = global_argv[2][i];
    //Incrementing the test variable for each character from the 2nd input that
    //is 1 or 0
    if(n=='0'||n=='1'){
      test++;
    }
  }
  //Checking if any of the characters from the user input were not a 1 or 0
  if(test!=strlen(global_argv[1])+strlen(global_argv[2])){
    //Displaying appropriate error message
    printf("ERROR: an input was not a binary number \n");
  //0 is returned for a failed test, 1 is returned if the inputs pass the test
    return 0;}
  else{
    return 1;
  }
}

//Function to check the number of arguments the user input
int argumentNumberChecker(int inputNumber){
  //Return 1 for correct number of arguments
  if(inputNumber==3){
    return 1;
  }
  //Return 2 for no arguments
  else if(inputNumber==1){
    printf("ERROR: No arguments have been input, 2 8-bit binary numbers need to be input\n");
    return 2;
  }
  //Return 0 for incorrect number of arguments
  else{
    printf("ERROR: Exactly 2 inputs have not been entered\n");
    return 0;
  }
}

//Function to add 2 binary values together
char * binaryAdder(char input1[8], char input2[8]) {
  //Initialising variables
  int bitholder1, bitholder2,carry=0;
  static char result[8];
  //Iterating through each character from the input, starting from the least
  //significant bit
  for(int i=7; i>-1; i--){
    //Converting each character to an integer as it is iterated through
    bitholder1=input1[i]-'0';
    bitholder2=input2[i]-'0';
    //Storing the value of carry before it is edited so that it can be used
    //in ouutput of calculations
    int oldCarry=carry;
    //Summing the current bit of each input and the carry bit, then assigining
    //The appropriate value to the carry bit and the current bit of the result
    switch (bitholder1+bitholder2+carry) {
      case 0 :
        result[i]='0';
        carry=0;
        break;
      case 1 :
        result[i]='1';
        carry=0;
        break;
      case 2 :
        result[i]='0';
        carry=1;
        break;
      case 3 :
        result[i]='1';
        carry=1;
        break;
    }
    //Outputting message that shows calculation performed for each bit
    printf("\nCalculation for bit %d\n    %d\n    %d\n+   %d\n=(%d)%c\n",i,bitholder1,bitholder2,oldCarry , carry, result[i]);
  }
  return result;
}

//Function to flip the bits of a binary number, except for the most significant bit
char * binaryFlipper(char num[8]){
  //Not flipping the Most Significant bit as that must reamin as 1 for the number
  //to be an 8-bit number in 2's complement form
  for(int i=7; i>0; i--){
    //Replacing 0's with 1's
    if(num[i]=='0'){
      num[i]='1';
    }
    else{
    //Replacing 1's with 0's
      num[i]='0';}
  }
  return num;
}


//The main function which will carry out the summation of the 2 binary numbers
//input and it will call the validation functions
int main(int argc, char *argv[]){
  //Initialising variables
  int test1=0, test2=0, test3=0, carry=0;
  char *result;
  char binaryOne[9]={'0','0','0','0','0','0','0','1','\0'};
  char output1[8], output2[8];
  //Assigining argv to the pointer
  global_argv=argv;
  //Calling the validation functions and storing the result
  test1=argumentNumberChecker(argc);//Checking the number of inputs
  //Only running the other validation functions if input was recieved
  if(test1!=2){
    test2 = lengthChecker();//Checking the length of the inputs
    test3 = typeChecker();//Checking the character type of the input
  }
  //If any of the testing conditions are not met, the program terminates
  //Otherwise the algorithm is run as a valid output can be displayed
  if(test1+test2+test3 != 3){
    printf("The program will now terminate\n");
  }
  else{
    //Assigining the values of input 1 and input 2 to new variables, because
    //the memory address that argv[1] and argv[2] point to will be overwritten
    //but the origional inputs are required for the final calculation output
    for(int i=0; i<8; i++){
      output1[i]=argv[1][i];
      output2[i]=argv[2][i];
    }
    //Checking if the first input is negative
    if(argv[1][0]=='1'){
      //Converting input1 into two's complement form
      printf("Turning input 1 into 2's complement form");
      argv[1]=binaryFlipper(argv[1]);
      argv[1]=binaryAdder(argv[1],binaryOne);
      //Updating the output1 value into the 2's complement version of input1
      for(int i=0; i<8; i++){
        output1[i]=argv[1][i];
      }
    }
    //Checking if the second input is negative
    if(argv[2][0]=='1'){
      //Converting input2 into two's complement form
      printf("Turning input 2 into 2's complement form\n");
      argv[2]=binaryFlipper(argv[2]);
      argv[2]=binaryAdder(argv[2],binaryOne);
      //Updating the output2 value into the 2's complement version of input2
      for(int i=0; i<8; i++){
        output2[i]=argv[2][i];
      }
    }
    printf("Calculating the final result:\n");
    result=binaryAdder(output1, output2);//Calculating the final result
    printf("Final Output all in 2's complement:\n ");
    //Prinitng an appropriate output message
    //Iterating through and outputting each element of output1
    for(int i=0; i<8; i++){
      printf("%c",output1[i]);
    }
    printf("\n+");
    //Iterating through and outputting each element of output2
    for(int i=0; i<8; i++){
      printf("%c",output2[i]);
    }
    printf("\n=");
    //Iterating through and outputting each elelment of the result array,
    for(int i=0; i<8; i++){
      printf("%c",*(result+i));
    }
    //Ensuring the next output in the command line is on a new line
    printf("\n");
    if(output1[0]==output2[0]&&output1[0]!=result[0]){
      printf("An overflow error has occurred\n");
    }
  }
}
