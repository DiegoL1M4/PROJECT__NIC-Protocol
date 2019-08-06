#include <math.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Tempo Inicial de Simulação
  unsigned long tempoInit = millis();



  // Definição do Multi-hop em todos os setores
  float nodesSetor[18][6] = {{ 1, 8.85, 65.18, 0.0, 0, 0},
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
                            {99, 16.61, 83.47, 0.0, 0, 0}};
  // Modelo do node: (0)ID / (1) X / (2) Y / (3) Distância / (4) Setor intra-cluster / (5) Já foi CH
  
  float idCH[18];
  double tamModelosCH[18];
  
  for(int H = 0; H < 18; H++) {
    float CH[6] = {nodesSetor[H][0], nodesSetor[H][1], nodesSetor[H][2], nodesSetor[H][3], nodesSetor[H][4], nodesSetor[H][5]};
    float modelo[18][6];

    // Não calcula uma alternativa onde um node já foi CH
    if(CH[5] != 1) {
      // Zera as informações para o próximo teste de CH
      for(int k = 0; k < 18; k++) {
        nodesSetor[k][3] = 0.0;
        nodesSetor[k][4] = 0.0;
      }

      // Calcula as distâncias entre o CH e os outros
      float distanciasCH[18];
      for(int k = 0; k < 18; k++) {
        float distancia = sqrt( pow(CH[1]-nodesSetor[k][1], 2) + pow(CH[2]-nodesSetor[k][2], 2) );
        nodesSetor[k][3] = distancia;
        distanciasCH[k] = distancia;
      }
      
      // Definição dos setores dentro do CH
      float maior = distanciasCH[0];
      for(int k = 0; k < 18; k++) {
          if(maior < distanciasCH[k])
              maior = distanciasCH[k];
      }
    
      float menor = distanciasCH[0];
      for(int k = 0; k < 18; k++) {
          if(distanciasCH[k] < menor)
              menor = distanciasCH[k];
      }
  
      float valor = (maior - menor) / 8;
      
      for(int k = 0; k < 18; k++) {
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
      for(int k = 0; k < 18; k++) {
          float menor = nodesSetor[k][3];
  
          for(int z = 0; z < 18; z++)
              if(nodesSetor[z][0] != nodesSetor[k][0]) {
                  float dist = sqrt( pow(nodesSetor[k][1]-nodesSetor[z][1], 2) + pow(nodesSetor[k][2]-nodesSetor[z][2], 2) );
                  if(dist < menor && nodesSetor[z][4] < nodesSetor[k][4])
                      menor = dist;
              }
          nodesSetor[k][3] = menor;
      }

      
      // Soma o total das distâncias
      double total = 0;
      for(int k = 0; k < 18; k++) {
        total += nodesSetor[k][3];
      }

      // Registro das Informações
      idCH[H] = CH[0];
      tamModelosCH[H] = total;

      // Print de dados
      Serial.print("Total das Ditâncias para o CH ");
      Serial.print(CH[0]);
      Serial.print(": ");
      Serial.println(total);
    }
  }

  // Ordena em um vetor as melhores formações (menores distancias no total)
  for(int k = 0; k < 18; k++) {
    float menor = tamModelosCH[k];
    float idPosicao = 0;
    for(int k = 0; k < 18; k++) {
        if(tamModelosCH[k] < menor)
            menor = tamModelosCH[k];
            idPosicao = k;
    }
  }



  // Tempo Final de Simulação
  unsigned long tempoFim = millis();

  // Print do Resultado
  Serial.print("Tempo de execução (milisegundos): ");
  Serial.println(tempoFim-tempoInit);
  Serial.println();
  delay(1000000);

}
