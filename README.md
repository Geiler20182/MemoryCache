# Memoria cache

## Requerimientos:

  1. Implementar memoria cache
  2. Implementar memoria principal (RAM) (TXT)

## A tomar en cuenta:

  1. El direccionamiento lo puede hacer con una función aleatoria
  2. La operación de lectura se puede hacer con una función aleatoria
  3. La operación de escritura se puede hacer con una función aleatoria
  4.  La capacidad de direccionamiento del sistema es de 2048 y el tamaño de palabra 1 byte.

## Características de la memoria cache:

  1. Tamaño de bloque 8 bytes
  2. Total de bloques en cache 16
  3. Después de la ejecución se debe mostrar cual fue la tasa de hits que
     obtuvo el sistema, al igual que el archivo txt y la memoria cache.

## MemoryCache
  FA WT LFU
  FA : Full Associative
  LRU : Least – Recently Used
  WT : Write-through: The information is written to both the block in the cache and to the block in
       the lower level of the memory hierarchy (main memory for a cache).
