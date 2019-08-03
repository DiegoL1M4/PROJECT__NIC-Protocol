# Bibliotecas
import matplotlib.pyplot as plt
import math

BS = [125,50]
rede = []

arq = open('nodes.txt', 'r')
for k in range(100):
    linha = arq.readline()
    linha = linha.split('/', 3)

    node = [int(linha[0]), float(linha[1]), float(linha[2]), 0, 0]
    rede.append(node)

distancias = []
for node in rede:
    distancias.append( [node[0], math.sqrt((BS[0]-node[1])**2 + (BS[1]-node[2])**2)] )

tamSector = 20
contNodes = 0
corNum = 0
for k in range(len(distancias)):
    menor = distancias[0]
    menorDT = distancias[0][1]
    for node in distancias:
        if(node[1] < menorDT):
            menor = node
            menorDT = node[1]

    rede[menor[0] - 1][4] = corNum
    contNodes += 1
    if(contNodes == tamSector):
        contNodes = 0
        corNum += 1

    distancias.remove(menor)

# Plot apenas para definir o label dos nodes no gráfico
plt.scatter(-50, -50, c = 'green',  marker=".", label='Node')

cores = ['green', 'black', 'red', 'gray','blue']
for node in rede:
    plt.scatter(node[1], node[2],  marker=".", c = cores[node[4]])

plt.scatter(125, 50, c = 'darkred', linewidth='2.0', marker="s",  label='Base Station')
plt.axis([-3, 145, -3, 103])
plt.grid(True)


plt.legend(loc='lower right')

# Configura as margens da imagem
plt.subplots_adjust(left=0.07, bottom=0.08, right=0.97, top=0.95, wspace=None, hspace=None)

plt.savefig('nodes.png')
plt.show()




input()







#
qtdNodes = 100
BS = [125,50]
#
# Função
def obterCoordenadas(index):
    lista = []
    arq = open('nodes.txt', 'r')
    linha = arq.readline()

    while(linha):
        node = linha.split(",")
        id = node[0].split("(")
        id = int(id[1])
        if(index == id):
            break
        linha = arq.readline()

    lista.append(float(node[2]))
    lista.append(float(node[3]))

    return lista

# Legendas do Gráficos
#plt.title('Grafico 1 - Dispersao de Nodes')
#plt.xlabel('X-coordinate')
#plt.ylabel('Y-coordinate')

# Vetores
cores = ['red','green','navy','gray','black','blue',
         'gold','orange','olive','maroon','silver',
         'crimson','cyan','teal','yellow','pink','violet']
chs = []

# Conjunto de CH de todos os Rounds
arq = open(nomeArq + '.txt', 'r')
linha = arq.readline()
roundList = []
Round = 1
while(linha):
    node = linha.split("/")
    if(Round != int(node[0])):
        chs.append(roundList)
        roundList = []
        Round = int(node[0])
    if(int(node[4]) == 1):
        roundList.append(int(node[1]))
    linha = arq.readline()
arq.close()

# Adição para último round
chs.append(roundList)

# Montagem da Dispersão
arq = open(nomeArq + '.txt', 'r')
linha = arq.readline()
Round = 1
while(linha):
    node = linha.split("/")

    if(Round != int(node[0])):
        plt.scatter(BS[0], BS[1], c = 'black')
        plt.axis([-3, 135, -3, 103])
        plt.grid(True)
        plt.savefig('Grafico_' + str(Round) + '.png')
        #plt.show()
        plt.clf()
        #plt.title('Grafico ' + node[0] + ' - Dispersao de Nodes')
        plt.xlabel('Eixo X')
        plt.ylabel('Eixo Y')
        Round = int(node[0])

    CH = int(node[5])

    if(int(node[4]) == 1):
        cor = 0
    else:
        cor = 1

    destino = obterCoordenadas(int(node[5]))
    if(node[4] == '0'):
        plt.plot([float(node[2]),destino[0]],[float(node[3]),destino[1]],'-', linewidth='0.7', c = 'gray', zorder=1)
    else:
        if(int(node[5]) == 0):
            plt.plot([float(node[2]),BS[0]],[float(node[3]),BS[1]],'b--', linewidth='0.9', c = 'navy', zorder=1)
        else:
            plt.plot([float(node[2]),destino[0]],[float(node[3]),destino[1]],'b--', linewidth='0.9', c = 'navy', zorder=1)

    if(int(node[4]) == 1):
        plt.scatter(float(node[2]), float(node[3]), linewidth='0.5', marker="H", c = 'black', zorder=3)
    else:
        plt.scatter(float(node[2]), float(node[3]),  marker=".", c = 'green', zorder=2)

    linha = arq.readline()

# Plot para marcar labels
plt.scatter(-50, -50, c = 'green', marker=".", label='Node')
plt.scatter(-50, -50, c = 'black', marker="H", label='Cluster-Head')

# Plot do último gráfico
plt.scatter(BS[0], BS[1], c = 'darkred', linewidth='2.0', marker="s", zorder=2, label='Base Station')
plt.axis([-3, 145, -3, 103])
plt.grid(True)

# Plots para marcar labels
plt.plot([-50,-50],[-50,-50],'-', linewidth='0.7', c = 'gray', label='Node Route')
plt.plot([-50,-50],[-50,-50],'--', linewidth='0.9', c = 'navy', label='CH Route')

plt.legend(loc='lower right')

# Configura as margens da imagem
plt.subplots_adjust(left=0.07, bottom=0.08, right=0.97, top=0.95, wspace=None, hspace=None)

plt.savefig('multi_' + nomeArq + '.png')
plt.show()
plt.clf()
