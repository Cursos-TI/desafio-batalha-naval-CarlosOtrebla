# 🚀 Batalha Naval - Ataques Especiais

## 🎯 Novos Tipos de Ataque Implementados!

Este projeto agora conta com 5 tipos diferentes de ataque:

### 1. 🎯 Ataque Simples
- Ataca apenas 1 posição
- Máxima precisão
- Ideal para ataques pontuais

### 2. 🎆 Ataque em Cone
- Formato triangular para baixo
- Ataca 6 posições no total:
  ```
      X     <- linha do alvo
    X X X  <- linha +1
  X X X X X <- linha +2
  ```
- Ótimo para áreas suspeitas

### 3. 🔶 Ataque Octaedro (Losango)
- Ataca 5 posições em formato losango
- Centro + 4 direções (cima, baixo, esquerda, direita)
  ```
    X
  X X X
    X
  ```
- Baseado no padrão do README original

### 4. ➕ Ataque em Cruz Estendida
- Formato cruz com linha horizontal extendida
- Ataca 7 posições no total:
  ```
      X
  X X X X X
      X
  ```
- Baseado no padrão do README original
- Eficaz para encontrar navios longos

### 5. 🔵 Ataque Circular
- Área 3x3 ao redor do alvo
- Ataca até 9 posições:
  ```
  X X X
  X X X
  X X X
  ```
- Máxima cobertura de área

## 🚀 Como Usar

1. **Posicione seus navios** (opção 1)
   - **NOVO**: Digite posição no formato **LinhaColuna** (ex: `5B`, `10A`, `3F`)
   - Muito mais rápido que antes!
   
2. **Escolha "Ataques especiais"** (opção 3)
3. **Selecione o tipo de ataque** desejado (1-5)
4. **Digite a posição** no formato **LinhaColuna** (ex: `5B`)
5. **Veja os resultados** com estatísticas detalhadas!

## ⚡ Interface Simplificada

### **ANTES** (complicado):
```
Linha (1-10): 5
Coluna (A-J): B
```

### **AGORA** (simples):
```
Posição: 5B
```

### **Exemplos válidos:**
- `1A`, `5B`, `10J` 
- `3F`, `7H`, `9C`
- Aceita maiúscula e minúscula
- Validação automática

## 📊 Funcionalidades

- ✅ **Validação inteligente**: Evita ataques fora do tabuleiro
- ✅ **Sistema de memória**: Não ataca a mesma posição duas vezes
- ✅ **Estatísticas em tempo real**: Taxa de acerto por ataque
- ✅ **Interface colorida**: Fácil visualização dos resultados
- ✅ **Feedback detalhado**: Informações sobre cada ataque realizado
- ✅ **Correção do buffer**: Não mais duplo Enter necessário!
- ✅ **Interface simplificada**: Digite apenas `5B` ao invés de linha e coluna separadas!

## 🛠️ Compilação

```bash
# Compilar
compile.bat

# Compilar e executar
compile.bat run
```

## 🎮 Navios Disponíveis

- **Destroyers**: 2 navios de 2 casas
- **Cruzadores**: 2 navios de 3 casas  
- **Navio de Guerra**: 1 navio de 4 casas
- **Porta-aviões**: 1 navio de 5 casas

## ⚡ Melhorias na Interface

- ✅ **Entrada simplificada**: `5B` em vez de linha e coluna separadas
- ✅ **Validação robusta**: Detecta formatos inválidos automaticamente
- ✅ **Mensagens claras**: Feedback específico para cada tipo de erro
- ✅ **Exemplos práticos**: Mostra como usar corretamente

---
**Desenvolvido por CarlosOtrebla**
*Versão com interface simplificada!* ⚡
