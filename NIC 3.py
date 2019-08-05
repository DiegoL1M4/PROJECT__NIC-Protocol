# Bibliotecas
import matplotlib.pyplot as plt
import math

# Variáveis
BS = [125,50]
rede = []
area = 100
tamSector = [25,50]

# Leitura do arquivo
arq = open('nodes.txt', 'r')
for k in range(100):
    linha = arq.readline()
    linha = linha.split('/', 3)
    # id / x / y / Setor CH / SetorRede / No receptor / Distancia até receptor / Já foi CH? / É CH
    node = [int(linha[0]), float(linha[1]), float(linha[2]), 0, 0, 0, 0.0, 0, 0]
    rede.append(node)




for round in range(20):
    # Criação dos setores
    totalX = int(area/tamSector[0])
    contX = 0
    totalY = int(area/tamSector[1])
    contY = 0
    limites = []

    count = 0
    for i in range(totalY):
        for j in range(totalX):
            count += 1
            limites.append([count, contX, contX+tamSector[0], contY, contY+tamSector[1]])
            contX += tamSector[0]
        contX = 0
        contY += tamSector[1]

    # Atribuição de dos setores nos nós
    for node in rede:
        for limite in limites:
            if((limite[1] < node[1] <= limite[2]) and (limite[3] < node[2] <= limite[4])):
                node[4] = limite[0]

    # Quantidade de nodes em cada setor e a Criação dos grupos dos setores
    totalNodesSector = []
    nodesSectors = []
    for k in range(count):
        totalNodesSector.append(0)
        nodesSectors.append([])
    for node in rede:
        totalNodesSector[node[4]-1] += 1
        nodesSectors[node[4]-1].append(node)
    print(totalNodesSector)
    print()

    # Definição do Multi-hop em todos os setores
    for setor in nodesSectors:
        # Análise de todos os nós (teste: somente para um setor)
        modelosCH = []
        tamModelosCH = []
        # Cada iteração é a escolha de um dos nodes do setor para ser o CH
        for CH in setor:
            # Cria uma cópia do objeto lista
            formacaoCluster = []
            for node in setor:
                formacaoCluster.append(node[:])

            # Calcula as distâncias entre o CH e os outros
            distanciasSetor = []
            for node in formacaoCluster:
                distancia = math.sqrt((CH[1]-node[1])**2 + (CH[2]-node[2])**2)
                node[6] = distancia
                distanciasSetor.append( distancia )

            # Definição dos setores dentro do CH
            for node in formacaoCluster:
                #Define o CH para envio
                node[5] = CH[0]
                # Calculo entre o menor e o maior
                menor = max(distanciasSetor)
                maior = min(distanciasSetor)

                valor = (maior - menor) / 8

                if(node[6] <= menor + 1*valor):
                    node[3] = 1
                elif(node[6] <= menor + 2*valor):
                    node[3] = 2
                elif(node[6] <= menor + 3*valor):
                    node[3] = 3
                elif(node[6] <= menor + 4*valor):
                    node[3] = 4
                elif(node[6] <= menor + 5*valor):
                    node[3] = 5
                elif(node[6] <= menor + 6*valor):
                    node[3] = 6
                elif(node[6] <= menor + 7*valor):
                    node[3] = 7
                else:
                    node[3] = 8

            # Escolha do destino
            for node in formacaoCluster:
                id = CH[0]
                menor = node[6]

                for nodeSearch in formacaoCluster:
                    if(nodeSearch[0] != node[0]):
                        dist = math.sqrt((node[1]-nodeSearch[1])**2 + (node[2]-nodeSearch[2])**2)
                        if(dist < menor and nodeSearch[3] < node[3]):
                            id = nodeSearch[0]
                            menor = dist
                node[5] = id
                node[6] = menor

            # Soma todas as Distâncias
            total = 0
            for node in formacaoCluster:
                total += node[6]

            # Registra as informações contruídas
            modelosCH.append([CH,formacaoCluster])
            tamModelosCH.append(total)

        # Ordena em um vetor as melhores formações (menores distancias no total)
        ordemMenorFormacoes = []
        for k in range(len(tamModelosCH)):
            menor = min(tamModelosCH)
            pos = tamModelosCH.index( menor )
            tamModelosCH[ pos ] = float('inf')
            ordemMenorFormacoes.append( pos )

        # Escolher a melhor formação possível e atualiza o vetor rede
        for formacao in ordemMenorFormacoes:
            if(modelosCH[ formacao ][0][7] == 0):
                for node in rede:
                    for nodeSubstituto in modelosCH[ formacao ][1]:
                        if(nodeSubstituto[0] == node[0]):
                            node[5] = nodeSubstituto[5]
                            node[6] = nodeSubstituto[6]
                            node[7] = nodeSubstituto[7]
                            node[8] = nodeSubstituto[8]
                    if(modelosCH[ formacao ][0][0] == node[0]):
                        node[7] = 1
                        node[8] = 1
                        node[6] = math.sqrt((node[1]-BS[0])**2 + (node[2]-BS[1])**2)
                break








    # Plot do Gráfico

    for node in rede:
        for nodeSearch in rede:
            if(node[5] == nodeSearch[0]):
                plt.plot([node[1],nodeSearch[1]],[node[2],nodeSearch[2]],'-', linewidth='0.7', c = 'gray', zorder=2)
                break

    # Print limites no Grafico ([x1,x2][y1,y2])
    ajuste = 1
    plt.plot([0-ajuste,100+ajuste],[100+ajuste,100+ajuste],'-', linewidth='1', c = 'black', zorder=1) #top
    plt.plot([0-ajuste,100+ajuste],[0-ajuste,0-ajuste],'-', linewidth='1', c = 'black', zorder=1) #bottom
    plt.plot([0-ajuste,0-ajuste],[100+ajuste,0-ajuste],'-', linewidth='1', c = 'black', zorder=1) #left
    plt.plot([100+ajuste,100+ajuste],[100+ajuste,0-ajuste],'-', linewidth='1', c = 'black', zorder=1) #right
    for k in range(1, totalX):
        plt.plot([0 + k*tamSector[0],0 + k*tamSector[0]],[100,0],'--', linewidth='0.7', c = 'black', zorder=1) #vertical
    for k in range(1, totalY):
        plt.plot([0,100],[0 + k*tamSector[1],0 + k*tamSector[1]],'--', linewidth='0.7', c = 'black', zorder=1) #horizontal

    cores = ['green', 'red', 'gray','blue','navy','maroon','silver','crimson','gold','orange','olive','cyan','teal','yellow','pink','violet','green', 'black', 'red', 'gray','blue','navy','gold','orange','olive','maroon','silver','crimson','cyan','teal','yellow','pink','violet']

    for node in rede:
        if(node[8] == 1):
            plt.scatter(node[1], node[2],  marker="H", c = 'black', zorder=3)
        else:
            plt.scatter(node[1], node[2],  marker=".", c = cores[node[4] - 1], zorder=3)



    # Plot para marcar labels
    plt.scatter(-50, -50, c = 'green', marker=".", label='Node')
    plt.scatter(-50, -50, c = 'black', marker="H", label='Cluster-Head')

    # Plots para marcar labels
    plt.plot([-50,-50],[-50,-50],'-', linewidth='0.7', c = 'gray', label='Node Route')
    plt.plot([-50,-50],[-50,-50],'--', linewidth='0.9', c = 'navy', label='CH Route')

    # Estação Base
    plt.scatter(125, 50, c = 'darkred', linewidth='2.0', marker="s",  label='Base Station')

    # Configuração
    plt.axis([-3, 145, -3, 103])
    #plt.grid(True)
    plt.legend(loc='lower right')

    # Configura as margens da imagem
    plt.subplots_adjust(left=0.07, bottom=0.08, right=0.97, top=0.95, wspace=None, hspace=None)

    plt.savefig('nodes.png')
    plt.show()
    plt.clf()

    # Reset nodes
    for node in rede:
        node[8] = 0
        node[5] = 0
        node[6] = 0.0

    for setor in nodesSectors:
        count = 0
        for node in setor:
            count += node[7]
        if(count == len(setor)):
            for node in setor:
                node[7] = 0
