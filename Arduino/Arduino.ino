#include <math.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(D1, OUTPUT);
  Serial.begin(112000);
}

void loop() {
  // Tempo Inicial de Simulação
  unsigned long tempoInit = millis();



  // Definição do Multi-hop em todos os setores
  float nodesSetor[20][4] = {{ 1, 8.85, 65.18, 0.0},
                            {12, 7.15, 51.49, 0.0},
                            {22, 23.66, 64.9, 0.0},
                            {25, 15.46, 61.52, 0.0},
                            {31, 12.3, 86.55, 0.0},
                            {33, 14.72, 97.49, 0.0},
                            {50, 1.21, 70.18, 0.0},
                            {52, 5.2, 80.98, 0.0},
                            {65, 23.53, 61.98, 0.0},
                            {67, 19.01, 52.68, 0.0},
                            {71, 3.5, 99.35, 0.0},
                            {74, 3.86, 70.74, 0.0},
                            {77, 11.23, 53.57, 0.0},
                            {86, 16.18, 76.16, 0.0},
                            {89, 11.01, 71.13, 0.0},
                            {95, 18.95, 83.01, 0.0},
                            {97, 5.0, 52.75, 0.0},
                            {99, 16.61, 83.47, 0.0},
                            {101, 26.0, 72.0, 0.0},
                            {102, 27.0, 65.0, 0.0}};
  // Modelo do node: (0)ID / (1) X / (2) Y / (3) Distância
  
  float modelosCH[20][20][4];
  float tamModelosCH[20];
  
  for(int k = 0; k < 20; k++) {
    float CH[4] = {nodesSetor[k][0], nodesSetor[k][1], nodesSetor[k][2], nodesSetor[k][3]};
    float modelo[20][4];
    
    // Calcula as distâncias entre o CH e os outros
    float distanciasCH[20];
    for(int k = 0; k < 20; k++) {
      float distancia = sqrt( pow(CH[1]-nodesSetor[k][1], 2) + pow(CH[2]-nodesSetor[k][2], 2) );
      nodesSetor[k][3] = distancia;
      distanciasCH[k] = distancia;
    }
    /*
    for node in formacaoCluster:
        distancia = math.sqrt((CH[1]-node[1])**2 + (CH[2]-node[2])**2)
        node[6] = distancia
        distanciasSetor.append( distancia )

    // Definição dos setores dentro do CH
    for node in formacaoCluster:
        #Define o CH para envio
        node[5] = CH[0]
        # Calculo entre o menor e o maior

        maior = lista[0]
        for k in lista:
            if(maior < k):
                maior = k
        return maior
      
        menor = lista[0]
        for k in lista:
            if(k < menor):
                menor = k
        return menor
        
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
    */
    
    // Soma o total das distâncias
    int total = 0;
    for(int k = 0; k < 20; k++) {
      total += modelo[k][3];
    }
    tamModelosCH[k] = total;
    
  }



  // Tempo Final de Simulação
  unsigned long tempoFim = millis();

  // Print do Resultado
  Serial.print("Tempo de execução (milisegundos): ");
  Serial.println(tempoFim-tempoInit);
 /*
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

      # Escolher a melhor formação possível
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
                      totalContEnc = 0
                      for nodeSearch in rede:
                          if(nodeSearch[5] == node[0]):
                              totalContEnc += 1
                      node[9] -= 0.000000005*tamPacote*(totalContEnc + 1)
              break
  */
}
