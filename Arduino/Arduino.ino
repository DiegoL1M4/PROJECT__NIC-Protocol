#include <math.h>

void setup() {
  Serial.begin(112000);
}

void loop() {
  // Tempo Inicial de Simulação
  unsigned long tempoInit = millis();



  // Definição do Multi-hop em todos os setores
  float nodesSetor[20][6] = {{ 1, 8.85, 65.18, 0.0, 0, 0},
                            {12, 7.15, 51.49, 0.0, 0, 0},
                            {22, 23.66, 64.9, 0.0, 0, 0},
                            {25, 15.46, 61.52, 0.0, 0, 0},
                            {31, 12.3, 86.55, 0.0, 0, 0},
                            {33, 14.72, 97.49, 0.0, 0, 0},
                            {50, 1.21, 70.18, 0.0, 0, 0},
                            {52, 5.2, 80.98, 0.0, 0, 0},
                            {65, 23.53, 61.98, 0.0, 0, 0},
                            {67, 19.01, 52.68, 0.0, 0, 0},
                            {71, 3.5, 99.35, 0.0, 0, 0},
                            {74, 3.86, 70.74, 0.0, 0, 0},
                            {77, 11.23, 53.57, 0.0, 0, 0},
                            {86, 16.18, 76.16, 0.0, 0, 0},
                            {89, 11.01, 71.13, 0.0, 0, 0},
                            {95, 18.95, 83.01, 0.0, 0, 0},
                            {97, 5.0, 52.75, 0.0, 0, 0},
                            {99, 16.61, 83.47, 0.0, 0, 0},
                            {101, 26.0, 72.0, 0.0, 0, 0},
                            {102, 27.0, 65.0, 0.0, 0, 0}};
  // Modelo do node: (0)ID / (1) X / (2) Y / (3) Distância / (4) Setor intra-cluster / (5) Já foi CH
  
  float modelosCH[20][20][4];
  float tamModelosCH[20];
  
  for(int k = 0; k < 20; k++) {
    float CH[6] = {nodesSetor[k][0], nodesSetor[k][1], nodesSetor[k][2], nodesSetor[k][3], nodesSetor[k][4]};
    float modelo[20][4];

    // Não calcula uma alternativa onde um node já foi CH
    if(CH[6] != 1) {
      // Calcula as distâncias entre o CH e os outros
      float distanciasCH[20];
      for(int k = 0; k < 20; k++) {
        float distancia = sqrt( pow(CH[1]-nodesSetor[k][1], 2) + pow(CH[2]-nodesSetor[k][2], 2) );
        nodesSetor[k][3] = distancia;
        distanciasCH[k] = distancia;
  
        nodesSetor[k][3] = CH[0];
      }
      
      // Definição dos setores dentro do CH
      float maior = distanciasCH[0];
      for(int k = 0; k < 20; k++) {
          if(maior < distanciasCH[k])
              maior = distanciasCH[k];
      }
    
      float menor = distanciasCH[0];
      for(int k = 0; k < 20; k++) {
          if(distanciasCH[k] < menor)
              menor = distanciasCH[k];
      }
  
      float valor = (maior - menor) / 8;
      
      for(int k = 0; k < 20; k++) {
          if(nodesSetor[k][3] <= menor + 1*valor)
              nodesSetor[k][4] = 1;
          else if(nodesSetor[k][3] <= menor + 2*valor)
              nodesSetor[k][4] = 2;
          else if(nodesSetor[k][3] <= menor + 3*valor)
              nodesSetor[k][4] = 3;
          else if(nodesSetor[k][3] <= menor + 4*valor)
              nodesSetor[k][4] = 4;
          else if(nodesSetor[k][3] <= menor + 5*valor)
              nodesSetor[k][4] = 5;
          else if(nodesSetor[k][3] <= menor + 6*valor)
              nodesSetor[k][4] = 6;
          else if(nodesSetor[k][3] <= menor + 7*valor)
              nodesSetor[k][4] = 7;
          else
              nodesSetor[k][4] = 8;
      }
  
      // Escolhe um novo destino (multi-hop intra-cluster)
      for(int k = 0; k < 20; k++) {
          float menor = nodesSetor[k][4];
  
          for(int z = 0; z < 20; z++)
              if(nodesSetor[z][0] != nodesSetor[k][0]) {
                  float dist = sqrt( pow(nodesSetor[k][1]-nodesSetor[z][1], 2) + pow(nodesSetor[k][2]-nodesSetor[z][2], 2) );
                  if(dist < menor && nodesSetor[z][4] < nodesSetor[k][4])
                      menor = dist;
              }
                      
          nodesSetor[k][4] = menor;
      }
      
      // Soma o total das distâncias
      float total = 0;
      for(int k = 0; k < 20; k++) {
        total += modelo[k][3];
      }
      tamModelosCH[k] = total;
    }
  }

  // Ordena em um vetor as melhores formações (menores distancias no total)
  for(int k = 0; k < 20; k++) {
    float menor = tamModelosCH[k];
    for(int k = 0; k < 20; k++) {
        if(tamModelosCH[k] < menor)
            menor = tamModelosCH[k];
    }
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
