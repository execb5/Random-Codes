#int BinSearch(const int A[], int Prim, int Ult, int Valor)
#{
#   if (Prim > Ult)
#       return -1; // Valor não existe
#   else
#   { // Invariante: Se Valor existe em A,
#       // A[Prim]<=Valor<=A[Ult]
#       int Meio = (Prim + Ult)/2;
#       if (Valor == A[Meio])
#           return Meio; // Encontrou Valor em A[Meio]
#       else if (Valor<A[Meio])
#           return BinSearch(A, Prim, Meio-1, Valor);
#           // Recursão na metade inferior do vetor
#       else
#           return BinSearch(A, Meio+1, Ult, Valor);
#           // Recursão na metade superior do vetor
#   } // end else
#} // end BinSearch

        .text
        .globl main
main:   la      $a0, ARRAY          #
        la      $a1, FIRST          #
        lw      $a1, 0($a1)         #
        la      $a2, LAST           #Armazena as variaveis dos registradores a0 até a3 para chamar a funcao
        lw      $a2, 0($a2)         #
        la      $a3, VALUE          #
        lw      $a3, 0($a3)         #

        addiu   $sp, $sp, -4        #Salva na pilha o endereco de retorno
        sw      $ra, 0($sp)         #

        jal     BINSEA              #Chama a funcao

        lw      $ra, 0($sp)         #carrega no $ra o endereço de retorno anterior

        addiu   $sp, $sp, 4         #termina de esvaziar a pilha
        
        la	$t0, ANSWER	    #
        sw	$v0, 0($t0)	    #salva a resposta no label ANSWER

        addu    $a0, $v0, $zero     #prepara o $a0 com o resultado pra chamar o syscall

        li      $v0, 1              #carrega 1 em $v0 pra chamar o syscall
        syscall                     #

        jr      $ra                 #fim do programa

OUT:    li      $v0, -1		    #carrega a resposta por nao ter encontrado

        jr      $ra		    #comeca a retornar a recursao


BINSEA: bgt     $a1, $a2, OUT       #verificacao do A[Prim]<=Valor<=A[Ult]

        addu    $t0, $a1, $a2       #
        srl     $t0, $t0, 1         #cata o indice da metade to intervalo em questao
        sll     $t1, $t0, 2         #
        addu    $t1, $t1, $a0       #
        
        lw      $t1, 0($t1)         #carrega o valor da metade do intervalo
        
        bne     $t1, $a3, DIFF      #compara se o valor da metade do intervalo e diferente do valor procurado, se sim, pula pra DIFF

        addu    $v0, $t0, $zero     #
        jr      $ra                 #comeca a retornar a recursao

DIFF:   slt     $t3, $a3, $t1	    #compara se o valor procurado e menor que o valor da metade do intervalo

        beq     $t3, $zero, BIGGER  #se o valor procurado for maior, pula pra BIGGER

LESS:   addiu   $sp, $sp, -20	    #
        sw      $a0, 16($sp)	    #
        sw      $a1, 12($sp)	    #prepara para chamar a recursao
        sw      $a2, 8($sp)	    #
        sw      $a3, 4($sp)	    #
        sw      $ra, 0($sp)	    #
        
        sub     $a2, $t0, $t3       #modifica o argumento a ser passado
        
        jal     BINSEA		    #chama a recursao
        
        lw      $a0, 16($sp)	    #
        lw      $a1, 12($sp)	    #carrega os argumentos da recursao atual
        lw      $a2, 8($sp)	    #
        lw      $a3, 4($sp)	    #
        lw      $ra, 0($sp)	    #
        
        addiu   $sp, $sp, 20	    #esvazia a pilha
        
        jr      $ra		    #retorna

BIGGER: addiu   $sp, $sp, -20	    #
        sw      $a0, 16($sp)	    #
        sw      $a1, 12($sp)	    #prepara para chamar a recursao
        sw      $a2, 8($sp) 	    #
        sw      $a3, 4($sp)	    #
        sw      $ra, 0($sp)	    #
        
        addiu   $a1, $t0, 1         #modifica o argumento a ser passado
        
        jal     BINSEA		    #chama a recursao
        
        lw      $a0, 16($sp)	    #
        lw      $a1, 12($sp)	    #carrega os argumentos da recursao atual
        lw      $a2, 8($sp)	    #
        lw      $a3, 4($sp)	    #
        lw      $ra, 0($sp)	    #
        
        addiu   $sp, $sp, 20	    #esvazia a pilha
        
        jr      $ra		    #retorna

        .data
FIRST:  .word   0x00
LAST:   .word   0x0B
VALUE:  .word   0x11
ARRAY:  .word   0xFFFFFFFB, 0xFFFFFFFF, 0x05, 0x09, 0x0C, 0x0F, 0x15, 0x1D, 0x1F, 0x3A, 0xFA, 0x145
ANSWER:	.word	0x00