import sys

r_inst = { #inst $d,$s,$t
    "add" : "000000",
    "sub" : "000001",
    "slt" : "000101",
    "and" : "000111",
    "or" : "001000",
    "nor" : "001001",
    "xor" : "001010"
}

r_inst_mult = { #inst $s,$t
    "mult" : "000011",
    "div" : "000100"
}

r_inst_move = {
    "mfhi" : "001110",
    "mflo" : "001111"
}

r_inst_shift = { #inst $d
    "sll" : "010001",
    "srl" : "010010",
    "sra" : "010011"
}

r_inst_jr = { #inst $s
    "jr" : "011011"
}

i_inst_signed = { #inst $t,$s,C
    "addi" : "000010",
    "slti" : "000110",
}

i_inst_unsigned = { #inst $t,$s,C
    "andi" : "001011",
    "ori" : "001100",
    "xori" : "001101"
}


i_inst_mem = { #inst $t,C($s)
    "lw" : "010100",
    "lb" : "010101",
    "sw" : "010111",
    "sb" : "011000"
}

i_inst_branch = { #inst $s,$t,C
    "beq" : "011000",
    "bne" : "011001"
}

i_inst_lui = { #inst $t,C
    "lui" : "010000"
}

j_inst = { #inst C
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


f = open(sys.argv[1], 'r')
w = open(sys.argv[2], 'w')

labels = {}
count = 0
machines_lines = []

for line in f:
    line = line.lower()
    end = line.find('#')
    line = line[:end]
    line = line.replace(',', ' ')
    line = line.split()
    if not line:
        continue

    if line[0] not in r_inst.keys() and line[0] not in r_inst_mult.keys() \
            and line[0] not in r_inst_move.keys() and line[0] not in r_inst_shift.keys() \
            and line[0] not in r_inst_jr.keys() and line[0] not in i_inst_signed.keys() \
            and line[0] not in i_inst_unsigned.keys() and line[0] not in i_inst_lui.keys() \
            and line[0] not in i_inst_mem.keys() and line[0] not in i_inst_branch.keys() \
            and line[0] not in j_inst.keys():
        labels[line[0][:-1]] = count
        line = line[1:]

    machine_line = ""

    if line[0] in r_inst.keys():
        machine_line += r_inst[line[0]]
        machine_line += reg[line[2]]
        machine_line += reg[line[3]]
        machine_line += reg[line[1]]
        machine_line += format(0, "011")
    elif line[0] in r_inst_mult.keys():
        machine_line += r_inst_mult[line[0]]
        machine_line += reg[line[1]]
        machine_line += reg[line[2]]
        machine_line += format(0, "016")
    elif line[0] in r_inst_move.keys():
        machine_line += r_inst_move[line[0]]
        machine_line += format(0, "010")
        machine_line += reg[line[1]]
        machine_line += format(0, "011")
    elif line[0] in r_inst_shift.keys():
        machine_line += r_inst_shift[line[0]]
        machine_line += format(0, "05")
        machine_line += reg[line[2]]
        machine_line += reg[line[1]]
        machine_line += format(int(line[3]),"05b")
        machine_line += format(0, "06")
    elif line[0] in r_inst_jr.keys():
        machine_line += r_inst_jr[line[0]]
        machine_line += reg[line[1]]
        machine_line += format(0, "021")
    elif line[0] in i_inst_signed.keys():
        machine_line += i_inst_signed[line[0]]
        machine_line += reg[line[2]]
        machine_line += reg[line[1]]
        machine_line += format(int(line[3]) & 0b1111111111111111,"016b")
    elif line[0] in i_inst_unsigned.keys():
        machine_line += i_inst_unsigned[line[0]]
        machine_line += reg[line[2]]
        machine_line += reg[line[1]]
        machine_line += format(int(line[3]),"016b")
    elif line[0] in i_inst_mem.keys():
        machine_line += i_inst_mem[line[0]]
        offset_reg = line[2].replace(')', '').split('(')
        machine_line += reg[offset_reg[1]]
        machine_line += reg[line[1]]
        machine_line += format(int(offset_reg[0]) & 0b1111111111111111,"016b")
    elif line[0] in i_inst_branch.keys():
        machine_line += "bran"
        machine_line += i_inst_branch[line[0]]
        machine_line += reg[line[1]]
        machine_line += reg[line[2]]
        machine_line += line[3]
    elif line[0] in i_inst_lui.keys():
        machine_line += i_inst_lui[line[0]]
        machine_line += format(0, "05")
        machine_line += reg[line[1]]
        machine_line += format(int(line[2]),"016b")
    elif line[0] in j_inst.keys():
        machine_line += "jump"
        machine_line += j_inst[line[0]]
        machine_line += line[1]
    else:
        raise Exception("Instruction {} did not match any instruction in core set".format(count))


    machines_lines.append(machine_line + '\n')
    count += 4

for i, line in enumerate(machines_lines):
    for label in labels.keys():
        if label in line:
            if line[:4] == "bran":
                address = format(labels[label], "016b")
                machines_lines[i] = line.replace(label, address)[4:]
            else:
                address = format(labels[label], "026b")
                machines_lines[i] = line.replace(label, address)[4:]

w.writelines(machines_lines)
