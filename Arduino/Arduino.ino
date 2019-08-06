#include <math.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  // Banco de nodes
  // Modelo do node: (0)ID / (1) X / (2) Y / (3) Distância / (4) Setor / (5) Já foi CH
  float banco[100][6] = {{1, 8.85, 65.18, 0.0, 0, 0},
                         {2, 43.74, 84.0, 0.0, 0, 0},
                         {3, 47.63, 26.33, 0.0, 0, 0},
                         {4, 15.25, 10.01, 0.0, 0, 0},
                         {5, 41.9, 98.81, 0.0, 0, 0},
                         {6, 83.63, 4.8, 0.0, 0, 0},
                         {7, 53.99, 14.5, 0.0, 0, 0},
                         {8, 30.43, 92.97, 0.0, 0, 0},
                         {9, 81.04, 90.06, 0.0, 0, 0},
                         {10, 31.46, 49.28, 0.0, 0, 0},
                         {11, 69.97, 96.12, 0.0, 0, 0},
                         {12, 7.15, 51.49, 0.0, 0, 0},
                         {13, 21.77, 15.06, 0.0, 0, 0},
                         {14, 46.37, 77.64, 0.0, 0, 0},
                         {15, 15.09, 14.26, 0.0, 0, 0},
                         {16, 49.56, 88.71, 0.0, 0, 0},
                         {17, 99.95, 13.15, 0.0, 0, 0},
                         {18, 89.5, 5.12, 0.0, 0, 0},
                         {19, 29.69, 10.07, 0.0, 0, 0},
                         {20, 73.6, 53.1, 0.0, 0, 0},
                         {21, 63.84, 37.57, 0.0, 0, 0},
                         {22, 23.66, 64.9, 0.0, 0, 0},
                         {23, 68.38, 15.72, 0.0, 0, 0},
                         {24, 30.73, 13.64, 0.0, 0, 0},
                         {25, 15.46, 61.52, 0.0, 0, 0},
                         {26, 39.82, 98.71, 0.0, 0, 0},
                         {27, 67.57, 44.94, 0.0, 0, 0},
                         {28, 54.17, 61.93, 0.0, 0, 0},
                         {29, 26.25, 17.49, 0.0, 0, 0},
                         {30, 77.28, 67.36, 0.0, 0, 0},
                         {31, 12.3, 86.55, 0.0, 0, 0},
                         {32, 57.18, 20.66, 0.0, 0, 0},
                         {33, 14.72, 97.49, 0.0, 0, 0},
                         {34, 61.9, 2.54, 0.0, 0, 0},
                         {35, 90.76, 61.65, 0.0, 0, 0},
                         {36, 10.33, 36.47, 0.0, 0, 0},
                         {37, 13.97, 37.29, 0.0, 0, 0},
                         {38, 78.25, 72.46, 0.0, 0, 0},
                         {39, 96.01, 69.52, 0.0, 0, 0},
                         {40, 27.79, 86.44, 0.0, 0, 0},
                         {41, 33.16, 88.58, 0.0, 0, 0},
                         {42, 93.64, 88.22, 0.0, 0, 0},
                         {43, 95.6, 44.23, 0.0, 0, 0},
                         {44, 22.81, 7.32, 0.0, 0, 0},
                         {45, 35.62, 44.63, 0.0, 0, 0},
                         {46, 74.01, 65.01, 0.0, 0, 0},
                         {47, 73.84, 92.56, 0.0, 0, 0},
                         {48, 84.25, 90.18, 0.0, 0, 0},
                         {49, 45.64, 90.95, 0.0, 0, 0},
                         {50, 1.21, 70.18, 0.0, 0, 0},
                         {51, 58.17, 71.64, 0.0, 0, 0},
                         {52, 5.2, 80.98, 0.0, 0, 0},
                         {53, 55.11, 10.99, 0.0, 0, 0},
                         {54, 69.57, 1.64, 0.0, 0, 0},
                         {55, 92.36, 6.59, 0.0, 0, 0},
                         {56, 62.27, 33.68, 0.0, 0, 0},
                         {57, 53.28, 19.86, 0.0, 0, 0},
                         {58, 66.61, 6.63, 0.0, 0, 0},
                         {59, 69.75, 64.55, 0.0, 0, 0},
                         {60, 56.65, 38.18, 0.0, 0, 0},
                         {61, 28.11, 64.96, 0.0, 0, 0},
                         {62, 4.04, 33.61, 0.0, 0, 0},
                         {63, 39.98, 1.54, 0.0, 0, 0},
                         {64, 27.51, 2.1, 0.0, 0, 0},
                         {65, 23.53, 61.98, 0.0, 0, 0},
                         {66, 68.85, 54.8, 0.0, 0, 0},
                         {67, 19.01, 52.68, 0.0, 0, 0},
                         {68, 50.91, 14.79, 0.0, 0, 0},
                         {69, 39.19, 74.0, 0.0, 0, 0},
                         {70, 68.0, 78.68, 0.0, 0, 0},
                         {71, 3.5, 99.35, 0.0, 0, 0},
                         {72, 96.9, 53.67, 0.0, 0, 0},
                         {73, 51.02, 38.83, 0.0, 0, 0},
                         {74, 3.86, 70.74, 0.0, 0, 0},
                         {75, 37.59, 65.77, 0.0, 0, 0},
                         {76, 72.34, 18.05, 0.0, 0, 0},
                         {77, 11.23, 53.57, 0.0, 0, 0},
                         {78, 6.74, 35.14, 0.0, 0, 0},
                         {79, 32.71, 89.16, 0.0, 0, 0},
                         {80, 71.3, 55.53, 0.0, 0, 0},
                         {81, 45.19, 37.62, 0.0, 0, 0},
                         {82, 26.87, 72.34, 0.0, 0, 0},
                         {83, 34.55, 30.22, 0.0, 0, 0},
                         {84, 38.32, 85.26, 0.0, 0, 0},
                         {85, 99.5, 38.27, 0.0, 0, 0},
                         {86, 16.18, 76.16, 0.0, 0, 0},
                         {87, 81.4, 67.55, 0.0, 0, 0},
                         {88, 33.11, 70.69, 0.0, 0, 0},
                         {89, 11.01, 71.13, 0.0, 0, 0},
                         {90, 57.8, 60.74, 0.0, 0, 0},
                         {91, 81.96, 36.6, 0.0, 0, 0},
                         {92, 4.77, 27.97, 0.0, 0, 0},
                         {93, 82.11, 89.35, 0.0, 0, 0},
                         {94, 79.46, 22.12, 0.0, 0, 0},
                         {95, 18.95, 83.01, 0.0, 0, 0},
                         {96, 16.47, 19.57, 0.0, 0, 0},
                         {97, 5.0, 52.75, 0.0, 0, 0},
                         {98, 44.88, 21.61, 0.0, 0, 0},
                         {99, 16.61, 83.47, 0.0, 0, 0},
                         {100, 59.75, 64.77, 0.0, 0, 0}};

  // Seleção dos nodes
  int totalNodes = 30;
  float nodesSetor[totalNodes][6];
  for(int k = 0; k < totalNodes; k++) {
    nodesSetor[k][0] = banco[k][0];
    nodesSetor[k][1] = banco[k][1];
    nodesSetor[k][2] = banco[k][2];
  }



  // Tempo Inicial de Simulação
  unsigned long tempoInit = millis();


  
  float idCH[totalNodes];
  double tamModelosCH[totalNodes];
  
  for(int H = 0; H < totalNodes; H++) {
    float CH[6] = {nodesSetor[H][0], nodesSetor[H][1], nodesSetor[H][2], nodesSetor[H][3], nodesSetor[H][4], nodesSetor[H][5]};
    float modelo[totalNodes][6];

    // Não calcula uma alternativa onde um node já foi CH
    if(CH[5] != 1) {
      // Zera as informações para o próximo teste de CH
      for(int k = 0; k < totalNodes; k++) {
        nodesSetor[k][3] = 0.0;
        nodesSetor[k][4] = 0.0;
      }

      // Calcula as distâncias entre o CH e os outros
      float distanciasCH[totalNodes];
      for(int k = 0; k < totalNodes; k++) {
        float distancia = sqrt( pow(CH[1]-nodesSetor[k][1], 2) + pow(CH[2]-nodesSetor[k][2], 2) );
        nodesSetor[k][3] = distancia;
        distanciasCH[k] = distancia;
      }
      
      // Definição dos setores dentro do CH
      float maior = distanciasCH[0];
      for(int k = 0; k < totalNodes; k++) {
          if(maior < distanciasCH[k])
              maior = distanciasCH[k];
      }
    
      float menor = distanciasCH[0];
      for(int k = 0; k < totalNodes; k++) {
          if(distanciasCH[k] < menor)
              menor = distanciasCH[k];
      }
  
      float valor = (maior - menor) / 8;
      
      for(int k = 0; k < totalNodes; k++) {
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
      for(int k = 0; k < totalNodes; k++) {
          float menor = nodesSetor[k][3];
  
          for(int z = 0; z < totalNodes; z++)
              if(nodesSetor[z][0] != nodesSetor[k][0]) {
                  float dist = sqrt( pow(nodesSetor[k][1]-nodesSetor[z][1], 2) + pow(nodesSetor[k][2]-nodesSetor[z][2], 2) );
                  if(dist < menor && nodesSetor[z][4] < nodesSetor[k][4])
                      menor = dist;
              }
          nodesSetor[k][3] = menor;
      }

      
      // Soma o total das distâncias
      double total = 0;
      for(int k = 0; k < totalNodes; k++) {
        total += nodesSetor[k][3];
      }

      // Registro das Informações
      idCH[H] = CH[0];
      tamModelosCH[H] = total;

      // Print de dados
      /*Serial.print("Total das Ditâncias para o CH ");
      Serial.print(CH[0]);
      Serial.print(": ");
      Serial.println(total);*/
    }
  }

  // Ordena em um vetor as melhores formações (menores distancias no total)
  for(int k = 0; k < totalNodes; k++) {
    float menor = tamModelosCH[k];
    float idPosicao = 0;
    for(int k = 0; k < totalNodes; k++) {
        if(tamModelosCH[k] < menor)
            menor = tamModelosCH[k];
            idPosicao = k;
    }
  }



  // Tempo Final de Simulação
  unsigned long tempoFim = millis();

  // Print do Resultado
  Serial.print("\nTempo de execução (milisegundos): ");
  Serial.println(tempoFim-tempoInit);
  Serial.println();
  delay(1000000);

}
