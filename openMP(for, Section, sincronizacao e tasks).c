/*
 Utilizacao dentro de uma regiaoparalela ou atraes de uma
 construcao combinada  parallel for

*Permite paralelismo laços de maneira automatica 
       * interação do laço são distribuidas e executada em 
         paralelo pelas threads da região paralela 


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

// Diretivas Sections
// ___________________________________________________________________________________
// Execução paralela de trecho de codigos 
// -----------------------------------------------------------------------------------
//====================================================================================
//-------------------------------------------------------------------------------------
/*
 * Ulizandoa dentro deum região paralela ou atravéis de ums
   construção com binada parallel sections

 *Permite dividir trechos de codigos (section) entre THREADS
      * Cada section é executada por uma thread 

 *Sicronização implicita no final (exceto com nowait)


#progma omp parallel
{
   #pragma omp sections
   {
     #pragma omp section
     a();
     #pragma omp section
     b();
     #pragma omp section
     c();
   }
} 

     #pragma omp sections [clauses]
     {
        [#pragma omp section]
         structured-block
        [#pragma omp section
          structured-block]
        ...
     }

  /* Clauses:
  private(list)
  firstprivate(list)
  lastprivate([lastprivate-modifier:] list )
  reduction(redution-identifier : list)
  allocate([allocator :] list)
  nowait
 */



// Diretivas Sicronização
// ___________________________________________________________________________________
// Sincronização entre threads em região paralela
// -----------------------------------------------------------------------------------
//====================================================================================
//--------------------------------------------------------------------------------------
/* 
 *  A diretiva single detemina que o codigo em uma região paralela
    seja exercutada por somente uma unica thread
 
 * as demais threads aguardam a exercução (excerto
   com nowait)



// Exemplo 
_________________________________________________________________________________________
 #pragma omp parallel
{
     printf("Threads %d: iniciada\n", omp_get_thread_num());
     #pragma omp single
     printf("Total de threads = %d\n", omp_num_threads());
}

/* saída (com 4 threds)
_________________________________________
Thread 2: iniciada
Thread 1: iniciada
Total de threads = 4
Thread 0: iniciada
Thread 3: iniciada
_________________________________________


// #pragama omp single [clauses]
  Clauses:
     private(list)
     firstprivate(list)
     copyprivate(list)
     allocate([Allocator :]list)
     nowait
_________________________________________

   #pragama omp critical[(name)]
 
* Funciona como um mecanismo de exclusão mútua 

* Toda as threads executam, porém, somente uma por vez

 // Exemplo
_______________________________________
 X = 0;

 #pragma omp parallel shared(x)
 {
   
    #pragma omp critical
    X++;
}
printf("X = %d\n", X);


 #pragma omp barrier

 * Sincronização todas as threds em uma barreira 

Exemplo:
____________________________________________________
 * Sincronização todas as threads em uma barreira 

----------------------------------------------------
#pragama omp parallel
{
  compute_a();
  #pragama_omp barrier
  computer_b();
}
_____________________________________________________

Diretiva task
-----------------------------------------------------
paralelismo com uso do conceito de tarefas
_____________________________________________________

* Permite paralelizar problemas irregulares
    * laços sem limites conhecidos
    * Algoritmo recursivo
     
    
* Tarefas são unidades independentes de trabalho    
    
    * são passadas para threads executrem imentiatamente ou posteriomente 


    *Exemplos: lista ligada de tarefa a serem processadas

    ___________________________________________________________
    #pragma omp parallel
    {
      #pragma omp single

      Node *n = list-> head;
      while (n) {
      #pragma omp task privat(n)
      compute(n);
      n = n ->next;
         }
       }
    }

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

* Exemplo: Fibonacci com tarefas

_______________________________________________________________________________
int main(int argc, char ** argv){
    int n = atoi(arqv[1]);
    long resultado;



    #pragma omp paralela
    {
         
           #pragma omp single nowait
           resultado = fib(n);
    }

    printf(" fibonnate(%d) = %ld\n", n, resultado);
}


 
    Exemplos: Fibonacci com tarefas
---------------------------------------------------------------------------
long fib(int n) {
long f1, f2, fn;
if(n == o || n == 1) return(n);
if(n < 20) return fib(n-1) + fib(n - 2);
else {
   #pragama omp task shared(f1)
   f1 = fib(n - 1);

   #pragma omp task shared(f2)
   f2 = fib(n - 2);

   #pragma omp taskwiait
   fn = f1 + f2;

   return fn;

}
   }   

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma omp task [clauses]

Clases:

      default(Shared | none)
      mergeable
      private(list)
      firstionprivate(list)
      shared(list)
      in_reduction(reduction-identifier : list)
      depend(dependence-type : locator-list)
      priority(priority-value)
      allocate([allocator :] list)




















}


*/










     





