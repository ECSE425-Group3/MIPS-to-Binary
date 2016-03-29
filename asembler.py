r_inst = {
    "add" : "000000",
    "sub" : "000001",
    "and" : "000111",
    "jr" : "011011",
    "nor" : "001001",
    "or" : "001000",
    "xor" : "001010",
    "slt" : "000101",
    "sll" : "010001",
    "srl" : "010010",
    "sra" : "010011",
    "mfhi" : "001110",
    "mflo" : "001111",
    "mult" : "000011",
    "div" : "000100"
}

i_inst = {
    "addi" : "000010",
    "andi" : "001011",
    "beq" : "011000",
    "bne" : "011001",
    "lb" : "010101",
    "lui" : "010000",
    "lw" : "010100",
    "ori" : "001100",
    "xori" : "001101",
    "slti" : "000110",
    "sb" : "011000",
    "sw" : "010111"
}

j_inst = {
    "j" : "011010",
    "jal" : "011100"
}

reg = {
    "$0" : "00000",
    "$1" : "00001",
    "$2" : "00010",
    "$3" : "00011",
    "$4" : "00100",
    "$5" : "00101",
    "$6" : "00110",
    "$7" : "00111",
    "$8" : "01000",
    "$9" : "01001",
    "$10" : "01010",
    "$11" : "01011",
    "$12" : "01100",
    "$13" : "01101",
    "$14" : "01110",
    "$15" : "01111",
    "$16" : "10000",
    "$17" : "10001",
    "$18" : "10010",
    "$19" : "10011",
    "$20" : "10100",
    "$21" : "10101",
    "$22" : "10110",
    "$23" : "10111",
    "$24" : "11000",
    "$25" : "11001",
    "$26" : "11010",
    "$27" : "11011",
    "$28" : "11100",
    "$29" : "11101",
    "$30" : "11110",
    "$31" : "11111",
}

f = open("fib.asm", 'r')
w = open("bytecode.txt", 'w')

labels = {}

for line in f:
    end = line.find('#')
    line = line[:end]
    line = line.replace(',', '')
    line = line.split()
    inst_type = 0
    if not line:
        continue

    if line[0] in r_inst.keys():
        inst_type = 'r'
        if line[0] == "sra" or line[0] == "srl" or line[0] == "sll":
            line[4] = format(int(line[4]),"05b")
        elif line[0]
        else:
            line.append("00000")
        line[0] = r_inst[line[0]]
        line[1] = reg[line[1]]
        line[2] = reg[line[2]]
        line[3] = reg[line[3]]
        line.append("000000")
    elif line[0] in i_inst.keys():
        inst_type = 'i'
        line[0] = i_inst[line[0]]
        line[1] = reg[line[1]]
        line[2] = reg[line[2]]
        line[3] = format(int(line[3]),"016b")
    elif line[0] in j_inst.keys():
        inst_type = 'j'
        line[0] = j_inst[line[0]]
    else:
        labels[line[0]] = line[0]


    print(line)
