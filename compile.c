#include <stdio.h>
#include <string.h>

//printf("%#010x\n",number);

//Return the decimal address of the line the lable is found on

char* jumpcalc(int linenum){
  linenum = linenum*4;
  char *ret = (char*)malloc(26);
  int c = 25;
  int i = 0;
  int k;
  while(c >= 0){
    k = linenum >> c;
    if(k & 1){
      ret[i] = '1';
    }
    else{
      ret[i] = '0';
    }
    i++;
    c--;
  }
  return ret;
}

char* immediateCalc(int imm){
  //Fixes seg fault for some reason
  int twos = 0;
  if(imm < 0){
    twos = 1;
    imm = imm * -1;
  }
  char *ret = (char*)malloc(16);
  int c = 15;
  int i = 0;
  int k;
  while(c >= 0){
    k = imm >> c;
    if(k & 1){
      ret[i] = '1';
    }
    else{
      ret[i] = '0';
    }
    i++;
    c--;
  }
  //Find twos comp if applies
  if(twos == 1){
    i = 0;
    while(i < 16){
      if(ret[i] == '0'){
        ret[i] = '1';
      }
      else{
        ret[i] = '0';
      }
      i++;
    }

    i = 15;
    c = 1;
    while(i >= 0){
      if(ret[i]=='1' && c == 1){
        ret[i] = '0';
      }
      else if(ret[i] == '0' && c == 1){
        ret[i] = '1';
        c = 0;
      }
      i--;
    }
  }
  return ret;
}

int lableline(const char* lables[], char* lable,int numlines){
  int i = 0;
  //printf("Looking up line number for lable: %s \n",lable);
  while(i < numlines){
    //printf("Lables[%d] = %s\n",i,lables[i]);
    if(lables[i] != NULL){
      if(strcmp(lables[i],lable) == 0){
        return i;
      }
    }
    i++;
  }
  return 0;
}

//return 1 = rtype, 2 = itype, 3 = jtype
int instructionType(char* line){
  char *rtype[] = {"add","and","jr","nor","or","slt","sll","srl","sra","sub","div","mfhi","mflo","mfhi","mult"};
  char *itype[]= {"addi","andi","beq","bne","lb","lw","ori","sw","sb","lui","slti","xori"};
  char *jtype[] = {"j","jal"};
  char *operation = strtok(line," ");
  //printf("operation:%s\n",operation);
  int i = 0;
  while(i < 15){
    if(i < 2){
      if(strcmp(operation,jtype[i]) == 0){
        return 3;
      }
    }
    if(i < 12){
      if(strcmp(operation,itype[i]) == 0){
        return 2;
      }
    }
    if(strcmp(operation,rtype[i]) == 0){
      return 1;
    }
    i++;
  }
  return 0;
}

//Returns 0 if instruction line, 1 if non instruction line
int instructionLine(char* line){
  int spacecheck = 0;
  if(strlen(line) == 0){
    //printf("noninstruction line \n");
    return 1;
  }
  else{
    while(isspace(line[spacecheck])){
      spacecheck++;
    }
    if(line[spacecheck] == '#' || line[spacecheck] == '\0'){
      //printf("noninstruction line \n");
      return 1;
    }
    return 0;
  }
}



char* regToBinary(char* reg){
  reg++;
  int number = atoi(reg);
  char *bin = "00000";
  switch(number){
    case 1:
      bin = "00001";
      break;
    case 2:
      bin = "00010";
      break;
    case 3:
      bin = "00011";
      break;
    case 4:
      bin = "00100";
      break;
    case 5:
      bin = "00101";
      break;
    case 6:
      bin = "00110";
      break;
    case 7:
      bin = "00111";
      break;
    case 8:
      bin = "01000";
      break;
    case 9:
      bin = "01001";
      break;
    case 10:
      bin = "01010";
      break;
    case 11:
      bin = "01011";
      break;
    case 12:
      bin = "01100";
      break;
    case 13:
      bin = "01101";
      break;
    case 14:
      bin = "01110";
      break;
    case 15:
      bin = "01111";
      break;
    case 16:
      bin = "10000";
      break;
    case 17:
      bin = "10001";
      break;
    case 18:
      bin = "10010";
      break;
    case 19:
      bin = "10011";
      break;
    case 20:
      bin = "10100";
      break;
    case 21:
      bin = "10101";
      break;
    case 22:
      bin = "10110";
      break;
    case 23:
      bin = "10111";
      break;
    case 24:
      bin = "11000";
      break;
    case 25:
      bin = "11001";
      break;
    case 26:
      bin = "11010";
      break;
    case 27:
      bin = "11011";
      break;
    case 28:
      bin = "11100";
      break;
    case 29:
      bin = "11101";
      break;
    case 30:
      bin = "11110";
      break;
    case 31:
      bin = "11111";
      break;
    case 0:
      bin = "00000";
      break;
    default:
      printf("not within range\n");
  }
  return bin;
}

//Gets the binary string for the opcode
char* opcode(char* reg){

  char *ops[] = {"add","sub","addi","mult","div","slt","slti","and","or","nor","xor","andi","ori","xori","mfhi","mflo","lui","sll","srl","sra","lw","lb","sw","sb"
                  "beq","bne","j","jr","jal"};
  int i = 0;
  while(i < 29){
    if(strcmp(ops[i],reg) == 0){
      break;
    }
    i++;
  }
  char code[2];
  //Recycled regToBinary
  sprintf(code,"$%d",i);
  //printf("%s\n",code);
  return regToBinary(&code);
}

char* funcode(char* reg){
  if(strcmp(reg,"add") == 0){
    return "100000";
  }
  if(strcmp(reg,"sub") == 0){
    return "100010";
  }
  if(strcmp(reg,"mult") == 0){
    return "011000";
  }
  if(strcmp(reg,"div") == 0){
    return "011010";
  }
  if(strcmp(reg,"slt") == 0){
    return "101010";
  }
  if(strcmp(reg,"or") == 0){
    return "100101";
  }
  if(strcmp(reg,"and") == 0){
    return "100100";
  }
  if(strcmp(reg,"nor") == 0){
    return "011011";
  }
  if(strcmp(reg,"xor") == 0){
    return "100110";
  }
  if(strcmp(reg,"mfhi") == 0){
    return "010000";
  }
  if(strcmp(reg,"mflo") == 0){
    return "010010";
  }
  if(strcmp(reg,"sll") == 0){
    return "000000";
  }
  if(strcmp(reg,"srl") == 0){
    return "000010";
  }
  if(strcmp(reg,"srl") == 0){
    return "000010";
  }
  if(strcmp(reg,"sra") == 0){
    return "000011";
  }
}

void translateRType(char* instruction){
  //printf("R-instruction:%s\n",instruction);
  char *operation = strtok(instruction," ");
  char *code;
  char rs[5];
  char rt[5];
  char rd[5];
  char shamt[5];
  char func[6] = "000000";
  char* arg1 = strtok(NULL,", ");
  char* arg2 = strtok(NULL,", ");
  char* arg3 = strtok(NULL,"\n ");
  //printf("operation:%s\n",operation);
  //printf("arg1:%s\n",arg1);
  //printf("arg2:%s\n",arg2);
  //printf("arg3:%s\n",arg3);
  if(strcmp(operation,"add")==0 || strcmp(operation,"and")==0 || strcmp(operation,"nor")==0 || strcmp(operation,"or")==0 || strcmp(operation,"xor")==0 ||
      strcmp(operation,"slt")==0 || strcmp(operation,"sub")==0){
    code = opcode(operation);
    sprintf(rs,"%s",regToBinary(arg2));
    sprintf(rt,"%s",regToBinary(arg3));
    sprintf(rd,"%s",regToBinary(arg1));
    sprintf(shamt,"00000");
    sprintf(shamt,"00000");
    //printf("%s,%s,%s,%s,%s,%s\n",code,rs,rt,rd,shamt,func);
    //printf("%s%s%s%s%s%s\n",code,rs,rt,rd,shamt,func);
  }
  else if(strcmp(operation,"jr")==0){
    code = opcode(operation);
    sprintf(rs,"%s",regToBinary(arg1));
    sprintf(rt,"00000");
    sprintf(rd,"00000");
    sprintf(shamt,"00000");
    //printf("%s,%s,%s,%s,%s,%s\n",code,rs,rt,rd,shamt,func);
  }
  else if(strcmp(operation,"sll")==0 || strcmp(operation,"srl")==0 || strcmp(operation,"sra")==0){
    code = opcode(operation);
    char *temp[2];
    sprintf(temp,"$%s",arg3);
    sprintf(rs,"00000");
    sprintf(rt,"%s",regToBinary(arg2));
    sprintf(rd,"%s",regToBinary(arg1));
    sprintf(shamt,"00000");
    sprintf(shamt,"%s",regToBinary(temp));
    //printf("%s,%s,%s,%s,%s,%s\n",code,rs,rt,rd,shamt,func);
  }
  else if(strcmp(operation,"div")==0 || strcmp(operation,"mult")==0){
    code = opcode(operation);
    sprintf(rs,"%s",regToBinary(arg1));
    sprintf(rt,"%s",regToBinary(arg2));
    sprintf(rd,"00000");
    sprintf(shamt,"00000");
    //printf("%s,%s,%s,%s,%s,%s\n",code,rs,rt,rd,shamt,func);
  }
  else if(strcmp(operation,"mflo")==0 || strcmp(operation,"mfhi")==0){
    code = opcode(operation);
    sprintf(rs,"00000");
    sprintf(rt,"00000");
    sprintf(rd,"%s",regToBinary(arg1));
    sprintf(shamt,"00000");
    //printf("%s,%s,%s,%s,%s,%s\n",code,rs,rt,rd,shamt,func);
  }
  printf("%s%s%s%s%s%s\n",code,rs,rt,rd,shamt,func);
}

void translateIType(char* instruction,int linec,const char* lables[],int numlines){
  //printf("I-instruction:%s\n",instruction);
  char *operation = strtok(instruction," ");
  char *code;
  char rs[5];
  char rt[5];
  char immediate[16];
  char* arg1 = strtok(NULL,", ");
  char* arg2 = strtok(NULL,", ");
  char* arg3 = strtok(NULL,"\n ");
  if(strcmp(operation,"addi")==0 || strcmp(operation,"andi")==0 || strcmp(operation,"ori")==0 || strcmp(operation,"xori")==0 || strcmp(operation,"slti")==0){
    code = opcode(operation);
    sprintf(rs,"%s",regToBinary(arg2));
    sprintf(rt,"%s",regToBinary(arg1));
    int temp = atoi(arg3);
    sprintf(immediate,"%s",immediateCalc(temp));
    //printf("%s,%s,%s,%s\n",code,rs,rt,immediate);
  }
  if(strcmp(operation,"lui")==0){
    code = opcode(operation);
    sprintf(rs,"00000");
    sprintf(rt,"%s",regToBinary(arg1));
    int temp = atoi(arg2);
    sprintf(immediate,"%s",immediateCalc(temp));
    //printf("%s,%s,%s,%s\n",code,rs,rt,immediate);
  }
  if(strcmp(operation,"bne")==0 || strcmp(operation,"beq")==0){
    code = opcode(operation);
    sprintf(rs,"%s",regToBinary(arg1));
    sprintf(rt,"%s",regToBinary(arg2));
    int dest = lableline(lables,arg3,numlines);
    int jump = dest - linec - 1;
    sprintf(immediate,"%s",immediateCalc(jump));
    //printf("%s,%s,%s,%s\n",code,rs,rt,immediate);
  }
  if(strcmp(operation,"lb")==0 || strcmp(operation,"lw")==0 || strcmp(operation,"lb")==0 || strcmp(operation,"sw")==0 || strcmp(operation,"sb")==0){
    code = opcode(operation);
    strtok(arg2,"(");
    arg3 = strtok(NULL,")");
    sprintf(rs,"%s",regToBinary(arg3));
    sprintf(rt,"%s",regToBinary(arg1));
    int temp = atoi(arg2);
    sprintf(immediate,"%s",immediateCalc(temp));
    //printf("%s,%s,%s,%s\n",code,rs,rt,immediate);
  }
  printf("%s%s%s%s\n",code,rs,rt,immediate);
}

void translateJType(char* instruction,int linec,const char* lables[],int numlines){
  //printf("J-instruction:%s\n",instruction);
  char *operation = strtok(instruction," ");
  char *code;
  char target[26];
  char* arg1 = strtok(NULL," \n");
  code = opcode(operation);
  int dest = lableline(lables,arg1,numlines);
  sprintf(target,"%s",jumpcalc(dest));
  printf("%s%s\n",code,target);
}

int main(int argc, char *argv[]){
  FILE *fp,*wp;
  char buff[255];

  fp = fopen(argv[1],"r");

//count number of lines
  int numlines = 0;
  while(fgets(buff,255,(FILE*)fp)){
    numlines++;
  }
  rewind((FILE*)fp);
  printf("number of lines including noninst lines :%d\n",numlines);
  const char* lables[numlines];
  //Initialize null for lables
  int init = 0;
  while(init < numlines){
    lables[init] = NULL;
    init++;
  }

  int linecounter = 0;
//Go through all lines, look for labels (PASS1)
  while(fgets(buff,255,(FILE*)fp)){
    //Check for non instruction line
    if(instructionLine(buff) == 0){
      //Cut off newline char, and any comment
      strtok(buff,"\n");
      strtok(buff,"#");
      //printf("instruction line found :%s, line :%d \n",buff,linecounter);
      //printf("Incrementing address\n");

      //Check for lable
      if(strstr(buff,":") != NULL){
        char* lable = strtok(buff,":");
        if(lable){
          //Trim whitespace from lable
          strtok(lable," ");
          printf("lable found: %s, line:%d\n",lable,linecounter);
          //Store lable in array (funky mem alloc stuff, label address is reused, cannot store)
          char* mem = (char*)malloc(32);
          strcpy(mem,lable);
          lables[linecounter] = mem;
          lable = NULL;
        }
      }
    }
    linecounter++;
  }
  printf("Labels complete\n");

  //Get insructions and begin to output binary (PASS2)
  int fclose(fp);
  fp = fopen(argv[1],"r");
  //rewind((FILE*) fp);

  linecounter = 0;
  //Open output file
  //wp = fopen("out.txt","w+");
  while(fgets(buff,255,(FILE*)fp)){
    //Check instruction line
    if(instructionLine(buff) == 0){
      strtok(buff,"#");
      char* line;
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
      line = strcpy(line, instruction);
      //printf("Snipped lable :%s",instruction);
      int instruction_type = instructionType(instruction);
      //printf("inst type:%d \n",instruction_type);
      //lableline(lables,"Fact",numlines);
      if(instruction_type == 1){
        translateRType(line);
      }
      else if(instruction_type == 2){
        translateIType(line,linecounter - 1,lables,numlines);
      }
      else if(instruction_type == 3){
        translateJType(line,linecounter - 1,lables,numlines);
      }
    }
  }
  //int fclose(wp);
  int fclose(fp);
}
