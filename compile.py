print("Hello")

filename = input("Enter a file name: ")

print(filename)

#Get length of file
i = 0
lables = {}
with open(filename,'r') as infile:
    for n,l in enumerate(infile):
        l = l.lstrip()
        #remove comments and noninstruction lines
        if(len(l) == 0 or l[0] == '#'):
            print("non instruction line found")
        else:
            l = l.split('#')[0]
            #lable finding
            if(l.find(':') != -1):
                lable = l[0:l.find(':')]
                print("Lable Found: " + lable + "at line: " + str(i))
                lables[lable] = i;
            i = i+1
        print(l)

print(lables)
