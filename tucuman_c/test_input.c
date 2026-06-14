// test_input.c — benchmark Tucuma completo

// Grupo A — offset constante == 1
uint16_t *p = (uint16_t*)(buf + 1);
uint32_t *p = (uint32_t*)(buf + 1);
uint64_t *p = (uint64_t*)(buf + 1);

// Grupo B — padding via (char*)&x
uint16_t *p = (uint16_t*)((char*)&x + 1);
uint32_t *p = (uint32_t*)((char*)&x + 1);
uint64_t *p = (uint64_t*)((char*)&x + 1);

// Grupo C — vetor
uint16_t *p = (uint16_t*)&vec[1];
uint32_t *p = (uint32_t*)&vec[1];
uint64_t *p = (uint64_t*)&vec[1];

// Grupo D — offsetof (caso correto)
uint16_t *p = (uint16_t*)(base + offsetof(struct S, b));
uint32_t *p = (uint32_t*)(base + offsetof(struct S, b));
uint64_t *p = (uint64_t*)(base + offsetof(struct S, b));

// Grupo E — offset simbolico
uint16_t *p = (uint16_t*)(base + i);
uint32_t *p = (uint32_t*)(base + i);
uint64_t *p = (uint64_t*)(base + i);

// Grupo F — offset via sizeof(char)
uint16_t *p = (uint16_t*)((char*)p + sizeof(char));
uint32_t *p = (uint32_t*)((char*)p + sizeof(char));
uint64_t *p = (uint64_t*)((char*)p + sizeof(char));

// Grupo G — offset impar arbitrario != 1
uint16_t *p = (uint16_t*)(buf + 3);
uint32_t *p = (uint32_t*)(buf + 5);
uint64_t *p = (uint64_t*)(buf + 7);

// Grupo H — campo struct sem packed (variavel s)
uint16_t *p = (uint16_t*)&s.b;
uint32_t *p = (uint32_t*)&s.b;
uint64_t *p = (uint64_t*)&s.b;

// Grupo H — campo struct com packed (variavel sp)
uint16_t *p = (uint16_t*)&sp.b;
uint32_t *p = (uint32_t*)&sp.b;
uint64_t *p = (uint64_t*)&sp.b;

// Grupo I — cast via void*
uint16_t *p = (uint16_t*)((void*)buf + 1);
uint32_t *p = (uint32_t*)((void*)buf + 1);
uint64_t *p = (uint64_t*)((void*)buf + 1);

// Grupo J — struct packed com ->
uint16_t *p = (uint16_t*)&((struct packed_s*)p)->b;
uint32_t *p = (uint32_t*)&((struct packed_s*)p)->b;
uint64_t *p = (uint64_t*)&((struct packed_s*)p)->b;