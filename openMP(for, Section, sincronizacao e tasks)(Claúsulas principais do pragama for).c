/*
 Utilizacao dentro de uma regiaoparalela ou atraes de uma
 construcao combinada  parallel for

*Permite paralelismo laços de maneira automatica 
       * interação do laço são distribuidas e executada em 
         paralelo pelas threads da região paralela 
*/

// Exemplo(sequencial):
for (i = 0; i < 20; i++)
    c[i] = a[i] + b[i]; 

//Exemplo(paralelo):

#pragma omp parallel
#pragma omp for
for(i = 0; i < 20; i++)
    c[i] = a[i] + b[i];

/* 
 

Claúsula principais de #pragma omp for
- private(var)
Cada thread tem sua própria cópia da variável. Não é compartilhada entre os threads.

-firstprivate(var) 
Similar a private, mas a cópia inicial de cada thread é inicializada com o valor da variável original.

-lastprivate(var) 
A variável privada é atualizada ao final do loop com o valor da última iteração executada.

-shared(var) 
A variável é compartilhada entre todos os threads. Todos acessam a mesma instância.

-default(shared|none) 
Define o comportamento padrão das variáveis (compartilhadas ou não)

-reduction(op:var) 
Permite realizar reduções (soma, produto, mínimo, máximo etc.) de forma paralela e segura.

-schedule(kind[,chunk]) Controla como as iterações são distribuídas entre os threads:

       * static → blocos fixos de iterações.

       * dynamic → blocos atribuídos dinamicamente.

       * guided → blocos decrescentes.

       * auto → o compilador decide.

       * runtime → definido em tempo de execução

-ordered 
Permite executar certas partes do loop em ordem sequencial, mesmo que o loop esteja paralelizado.

-collapse(n) 
Combina vários loops aninhados em um só para paralelização

-nowait 
Remove a barreira implícita no final do loop, permitindo que os threads continuem sem esperar pelos demais.
*/
// EXEMPLO PRATICO:
#pragma omp parallel
{
      #pragma omp for private(i) reduction(+:sum) schedule(dynamic,4)
      for(int i = 0: i<100; i++) {
         sum +=i; 
      }
}
/* Neste exemplo:

    * Cada thread tem sua propria copia de i (private).
    * É feita uma redução com soma sobre sum.
    * AS iterações são distribuida dinamicamente em bloco de 4.
*/

