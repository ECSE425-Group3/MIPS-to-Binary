#include <stdio.h>
#include <string.h>

//printf("%#010x\n",number);

//return binary for rtype instruction
int rtype(char* operation, char* holder ){

}
//return binary for itype instruction
int itype(){

}
//return binary for jtype instruction
int jtype(){

}

//return 1 = rtype, 2 = itype, 3 = jtype
int instructionType(char* line){
  char * rtype = {"add","and","jr","nor","or","slt","sll","srl","sra","sub","div","mfhi","mflo","mfhi"};
  char *operation = strtok(line," ");
  printf("operation:%s\n",operation);

  //if()
}

//Returns 0 if instruction line, 1 if non instruction line
int instructionLine(char* line){
  int spacecheck = 0;
  if(strlen(line) == 0){
    printf("noninstruction line \n");
    return 1;
  }
  else{
    while(isspace(line[spacecheck])){
      spacecheck++;
    }
    if(line[spacecheck] == '#' || line[spacecheck] == '\0'){
      printf("noninstruction line \n");
      return 1;
    }
    return 0;
  }
}

int main(int argc, char *argv[]){
  FILE *fp;
  char buff[255];

  fp = fopen(argv[1],"r");

//count number of lines
  int numblines = 0;
  while(fgets(buff,255,(FILE*)fp)){
    numblines++;
  }
  rewind((FILE*)fp);
  printf("number of lines including noninst lines :%d\n",numblines);
  const char* lables[numblines];
  int linecounter = 0;
//Go through all lines, look for labels (PASS1)
  while(fgets(buff,255,(FILE*)fp)){
    //Check for non instruction line
    if(instructionLine(buff) == 0){
      linecounter++;
      strtok(buff,"\n");
      //printf("instruction line found :%s, line :%d \n",buff,linecounter);
      //printf("Incrementing address\n");

      //Check for lable
      if(strstr(buff,":") != NULL){
        char* lable = strtok(buff,":");
        if(lable){
          //Trim whitespace from lable
          strtok(lable," ");
          printf("lable found: %s, line:%d\n",lable,linecounter);
          //Store lable in array
          lables[linecounter] = lable;
          lable = NULL;
        }
      }
    }
  }
  printf("Labels complete\n");

  //Get insructions and begin to output binary (PASS2)
  rewind((FILE*) fp);
  linecounter = 0;
  while(fgets(buff,255,(FILE*)fp)){
    //Check instruction line
    if(instructionLine(buff) == 0){
      linecounter++;
      char *instruction;
      //Cut off lable and whitespace
      char* colon = strchr(buff,':');
      if(colon != NULL){
        int snip = (int)(colon - buff);
        instruction = buff + snip + 1;
      }
      else{
        instruction = buff;
      }
      //Trim whitespace from beginning of line
      while(isspace(instruction[0])){
        instruction++;
      }
      //printf("Snipped lable :%s",instruction);
      int instruction_type = instructionType(instruction);
    }
  }

  int fclose(fp);

}
