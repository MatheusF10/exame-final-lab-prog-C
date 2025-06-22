# 🍽️ Gestão de Mesas de Restaurante em C

Este projeto simula um sistema de gestão de mesas para um restaurante, com o objetivo de **minimizar o tempo de espera** e **maximizar a ocupação eficiente das mesas**, de acordo com a dimensão dos grupos de clientes.

---

## 🎯 Objetivos do Projeto

- Estruturar um programa complexo utilizando **linguagem C**
- Aplicar o conceito de **modularidade**
- Promover a **reutilização de código**
- Desenvolver um sistema com **gestão dinâmica de memória** e uso de **estruturas**

---

## 📂 Formato dos Arquivos CSV

### 🪑 Ficheiro de Mesas

Cada linha representa uma mesa com:
- Número identificador
- Número de lugares
- Número de lugares ocupados

**Formato:**

Mesa,Lugares,Ocupação  
1,2,0  
2,6,5  
3,2,1  
4,8,0  
5,4,0  

### 👥 Ficheiro de Clientes

Cada linha representa um grupo de clientes, com:
- Letra identificadora do grupo (ordem alfabética == ordem de chegada)
- Número de pessoas

**Formato:**

Grupo,Pessoas  
A,2  
B,5  
C,7  
D,1  
E,4  

---

## ⚙️ Funcionalidades do Programa

- ✅ Carregar clientes e mesas a partir de ficheiros `.csv`
- ✅ Atribuir mesas a grupos de clientes com base em critérios otimizados
- ✅ Ver, editar ou remover mesas existentes por ID
- ✅ Limpar ocupação de uma mesa (grupo desocupa)
- ✅ Apresentar as mesas atribuídas a cada grupo
- ✅ Guardar alterações num novo ficheiro `.csv`
- ✅ Libertar memória e sair do programa com segurança

---

## 🧠 Regras de Atribuição de Mesas

1. Sentar o **maior número de grupos possível**
2. Respeitar a **ordem de chegada**, desde que não contradiga o critério 1

### Exemplo de saída:

Grupo A - mesa 1  
Grupo B - aguarda  
Grupo C - mesa 4  
Grupo D - aguarda  
Grupo E - mesa 5  

---

## 🛠️ Requisitos Técnicos

- Uso de **memória dinâmica**
- Definição de **estruturas (`struct`)** para modelar clientes e mesas
- Organização do código em **módulos**
- **Reutilização de funções**
- Implementação de **validações** (duplicados, arquivos inexistentes, dados inválidos)
- Planejamento de **testes unitários e de integração**

---

## 🚀 Como executar

1. Compile o programa:
   ```bash
   gcc prog.c prog.modules.c -o prog
   
2. Execute:
   ```bash
   ./prog  
