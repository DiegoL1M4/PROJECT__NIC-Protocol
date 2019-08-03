
nodes = 20
maxCH = 2
total = 0

for inteiro in range(2**nodes):

    num = str( bin(inteiro) )
    num = num[2:]

    cont = num.count('1')

    if(cont == maxCH):
        total += 1
        #print(inteiro)
        '''for k in range(nodes - len(num)):
            num = '0' + num
        print(num)'''

print("Total: " + str(total))
