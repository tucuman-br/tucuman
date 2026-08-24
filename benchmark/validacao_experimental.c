#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "esp_system.h"

void setup() {
  /* Inicializa a comunicação serial */
  Serial.begin(115200);
  while (!Serial) {
    ; // Aguarda a conexão da porta serial
  }
  
  delay(1000);

  /* =======================================================
   * Informações do Hardware e Arquitetura da CPU
   * ======================================================= */
  printf("=================================================\n");
  printf("Informacoes do Chip e Arquitetura\n");
  printf("=================================================\n");
  printf("Modelo do Chip : %s\n", ESP.getChipModel());
  printf("Revisao        : %d\n", ESP.getChipRevision());
  printf("Cores (CPUs)   : %d\n", ESP.getChipCores());
  printf("Frequencia     : %d MHz\n", ESP.getCpuFreqMHz());

#if defined(CONFIG_IDF_TARGET_ESP32)
  printf("Arquitetura    : Cadence Xtensa LX6 (32-bit)\n");
#elif defined(CONFIG_IDF_TARGET_ESP32S2)
  printf("Arquitetura    : Cadence Xtensa LX7 Single-Core (32-bit)\n");
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
  printf("Arquitetura    : Cadence Xtensa LX7 Dual-Core (32-bit com Extensoes de IA)\n");
#elif defined(CONFIG_IDF_TARGET_ESP32C3) || defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32C6)
  printf("Arquitetura    : RISC-V 32-bit (RV32IMC)\n");
#elif defined(CONFIG_IDF_TARGET_ESP32H2)
  printf("Arquitetura    : RISC-V 32-bit (RV32IMAC)\n");
#else
  printf("Arquitetura    : Desconhecida / Genérica\n");
#endif
  printf("=================================================\n\n");

  /* =======================================================
   * Validação de Acesso Desalinhado à Memória (DRAM)
   * ======================================================= */
  /* Buffer suficientemente grande para todos os testes */
  char buf[16] = {
      0x11, 0x22, 0x33, 0x44,
      0x55, 0x66, 0x77, (char)0x88,
      (char)0x99, (char)0xAA, (char)0xBB, (char)0xCC,
      (char)0xDD, (char)0xEE, (char)0xFF, 0x00
  };

  printf("=================================================\n");
  printf("Misaligned Memory Access Validation\n");
  printf("=================================================\n\n");

  /* Teste 1: uint16_t */
  {
      uint16_t *p = (uint16_t *)(buf + 1);
      uint16_t x = *p;

      printf("[16-bit]\n");
      printf("Address        : %p\n", (void *)p);
      printf("Alignment mod2 : %" PRIuPTR "\n",
             ((uintptr_t)p) % 2);
      printf("Value          : 0x%04" PRIX16 "\n\n", x);
  }

  /* Teste 2: uint32_t */
  {
      uint32_t *p = (uint32_t *)(buf + 1);
      uint32_t x = *p;

      printf("[32-bit]\n");
      printf("Address        : %p\n", (void *)p);
      printf("Alignment mod4 : %" PRIuPTR "\n",
             ((uintptr_t)p) % 4);
      printf("Value          : 0x%08" PRIX32 "\n\n", x);
  }

  /* Teste 3: uint64_t */
  {
      uint64_t *p = (uint64_t *)(buf + 1);
      uint64_t x = *p;

      printf("[64-bit]\n");
      printf("Address        : %p\n", (void *)p);
      printf("Alignment mod8 : %" PRIuPTR "\n",
             ((uintptr_t)p) % 8);
      printf("Value          : 0x%016" PRIX64 "\n\n", x);
  }
}

void loop() {
  delay(1000);
}
