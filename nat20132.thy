theory nat20132
imports Main
begin
text{*
Tipos de dados recursivos são definidos com o comando datatype em
Isabelle. Isabelle normalmente usa identificadores em minúsculo para
os nomes dos tipos e nomes com o primeiro caracter em maísculo para
os construtores. Para evitar conflito, sugiro que utilizem o critério
inverso
*}
(* declare[[show_types]] *)
datatype Nat = "zero" | "suc" "Nat"
term "suc (suc zero)"
print_statement Nat.induct

primrec add::"Nat \<Rightarrow> Nat \<Rightarrow> Nat" where
  add01: "add x zero = x" |
  add02: "add x (suc y) = suc (add x y)"

thm add.simps
thm add.simps(1)
thm add01
thm add.simps(2)
thm add02

lemma "add (suc (suc zero)) (suc (suc zero)) =  suc(suc (suc (suc zero)))"
  using [[simp_trace = true]]
  apply (simp)
done

text{* teorema da associatividade na linguagem script e utilizando 
       automação na simplificação *}
theorem th01a: "\<forall>x. \<forall>y. add x (add y n) = add (add x y) n"
  apply (induction n)
  apply (simp) -- "simplifica caso base"
  apply (simp) -- "simplifica caso indutivo"
done

text{* teorema da associatividade na linguagem Isar e utilizando 
       automação na simplificação de vários passos *}

theorem th01b: "\<forall>x. \<forall>y. add x (add y n) = add (add x y) n"
   proof (induction n)
       show  "\<forall>x. \<forall>y. add x (add y zero) = add (add x y) zero" by simp
   next
      fix x0::Nat
      assume IH: "\<forall>x. \<forall>y. add x (add y x0) = add (add x y) x0"
      show "\<forall>x. \<forall>y. add x (add y (suc x0)) = add (add x y) (suc x0)" by (simp add:IH)
   qed

text{* teorema da associatividade na linguagem Isar e utilizando 
       automação apenas para  simplificações atômicas (uma regra de cada vez) *}

theorem th01c: "\<forall>x. \<forall>y. add x (add y n) = add (add x y) n"
   proof (induction n)
     show  "\<forall>x. \<forall>y. add x (add y zero) = add (add x y) zero"
       proof (rule allI, rule allI)
          fix x0::Nat and y0::Nat
          have "add x0 (add y0 zero) = add x0 y0" by (simp only:add01)
          also have "add x0 y0 = add (add x0 y0) zero" by (simp only:add01)
          finally show  "add x0 (add y0 zero) = add (add x0 y0) zero" by this
       qed
     next
       fix x0::Nat
       assume IH:"\<forall>x. \<forall>y. add x (add y x0) = add (add x y) x0"
       show "\<forall>x. \<forall>y. add x (add y (suc x0)) = add (add x y) (suc x0)"
         proof (rule allI, rule allI)
            fix x1::Nat and y1::Nat
            have "add x1 (add y1 (suc x0)) = add x1 (suc (add y1 x0))" by 
              (simp only:add02)
            also have "...= suc (add x1 (add y1 x0))" by (simp only:add02)
            also have "...= suc (add (add x1 y1) x0)" by (simp only:IH)
            also have "... = add (add x1 y1) (suc x0)" by (simp only:add02)
            finally show  "add x1 (add y1 (suc x0)) = add (add x1 y1) (suc x0)"
              by this
         qed
   qed

text{* lemma lem01 na linguagem script (procedural) e automação *}
lemma lem01:"add zero n = n"
    apply (induction n)
    apply (simp)
    using [[simp_trace=true]]
    apply (simp)
done

text{* lemma lem02 na linguagem script (procedural) e automação *}

lemma lem02: "\<forall>x. suc (add x n) = add (suc x) n"
    apply (induction n)
    apply (simp)
    apply (simp)
done

text{* teorema th02a na linguagem script (procedural) e automação *}

theorem th02a:"\<forall>x. add x n = add n x"
     apply (induction n)
     apply (simp add:lem01)
     apply (simp add:lem02)
done

text{* A prova do teorema cima *}
theorem shows "\<forall>x. add x n = add n x" 
  proof (induct n)
   show "\<forall>x. add x zero = add zero x"
     proof (rule allI)
       fix x0
       show "add x0 zero = add zero x0"
         proof -
            have "add x0 zero = x0" by (simp only:add01)
            also have "x0 = add zero x0" by (simp only:lem01)
            finally show ?thesis by this 
         qed
     qed
     next
       fix x0
       assume IH:"\<forall>x. add x x0 = add x0 x"
       show "\<forall>x. add x (suc x0) = add (suc x0) x"
         proof (rule allI)
           fix y0
           show "add y0 (suc x0) = add (suc x0) y0"
              proof -
                 have "add y0 (suc x0) = suc (add y0 x0)" by (simp only:add02)
                 also have "suc (add y0 x0) = suc (add x0 y0)" by (simp only:IH)
                 also have "suc (add x0 y0) = add (suc x0) y0" by (simp only:lem02)
                 finally show ?thesis by this
              qed
         qed
  qed

primrec mult::"Nat \<Rightarrow> Nat \<Rightarrow> Nat" where
  "mult x zero = zero" |
  "mult x (suc y)= add x (mult x y)"

value "mult (suc (suc zero)) (suc (suc (suc zero)))"

primrec equal::"Nat \<Rightarrow> Nat \<Rightarrow> bool" where
  "equal x zero = (case x of zero \<Rightarrow> True | suc k \<Rightarrow> False)" |
  "equal x (suc y) = (case x of zero \<Rightarrow> False | suc k \<Rightarrow> equal k y)"
 
primrec dec::"Nat\<Rightarrow>Nat" where
"dec zero = zero" |
"dec (suc x) = x"

primrec ifelseNat::"bool \<Rightarrow> Nat \<Rightarrow> Nat \<Rightarrow> Nat" where
  "ifelseNat True x y = x"|
  "ifelseNat False x y = y"

value "ifelseNat ((2::nat)=2) zero (suc (suc zero))"
primrec equal02::"Nat \<Rightarrow> Nat \<Rightarrow> bool" where
  "equal02 x zero = (if x = zero then True else False)" |
  "equal02 x (suc y) = (if x = zero then False else  equal02 (dec x) y)"
value "equal (suc (suc zero)) (suc zero)"
value "equal02 (suc (suc zero)) (suc zero)"
end

