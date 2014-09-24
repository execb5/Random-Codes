theory labPrimRec
imports Main
begin

text{* Exercício 01 *}

datatype Nat = Z | suc Nat

term "Z"
term "z"
term "suc (suc Z)"
term "Suc (Suc 0)"

primrec add::"Nat => Nat => Nat" where
  "add x Z = x" |
  "add x (suc y) = suc (add x y)"

value "add (suc (suc Z)) (suc (suc Z))"
value "add (suc (suc Z)) (suc Z)"

text{* Exercício 02 *}

primrec Nat2int::"Nat => int" where
  "Nat2int Z = 0" |
  "Nat2int (suc y) = Nat2int(y) + 1"

value "Nat2int (suc (suc (suc (suc Z))))"
value "Nat2int (suc (suc Z)) * Nat2int (suc (suc (suc Z)))"

text{* Exercício 03 *}

datatype 'a List = nil | cons 'a "'a List"

term "nil"
term "cons (10::int) (cons 3 (cons -2 nil))"
term "cons ''a'' (cons ''1'' (cons ''f'' nil))"
term "cons (suc Z) (cons Z nil)"

primrec len::"'a List => Nat" where
  "len nil = Z" |
  "len (cons y list) = suc (len list)"

value "len (cons (10::int) (cons 3 (cons -2 nil)))"
value "len (cons (10::int) (cons 3 (cons -2 nil)))"
value "len (cons (suc Z) (cons Z nil))"

primrec cat::"'a List => 'a List => 'a List" where
  "cat nil list= list" |
  "cat (cons e list1) list2 = (cons e (cat list1 list2))"

primrec delete::"'a => 'a List => 'a List" where
  "delete x nil = nil" |
  "delete x (cons e L) = (if x = e then delete x L else cons e (delete x L))"

value "delete (3::int) (cons (3::int) (cons 3 (cons 2 (cons 3 nil))))"

value "cat (cons (10::int) (cons 3 (cons -2 nil))) nil"
value "cat (cons (3::int) (cons -2 nil)) (cons 10 (cons 3( cons 4 nil)))"
value "add (len (cons 3 (cons -2 nil))) (len (cons 10 (cons 3( cons 4 nil))))"

text{* Exercício 04 *}

datatype 'a btree = leaf | br 'a "'a btree" "'a btree"

term "leaf"
term "br (1::nat) leaf leaf"
term "br (1::int) (br 2 leaf leaf) (br 3 leaf leaf)"

primrec numLeaf::"'a btree => Nat" where
  "numLeaf leaf = suc Z" |
  "numLeaf (br x left right) = add (numLeaf left) (numLeaf right)"

value "numLeaf (br 3 leaf leaf)"

primrec numNodos::"'a btree => Nat" where
  "numNodos leaf = Z" |
  "numNodos (br x left right) = suc (add (numNodos left) (numNodos right))"

value "numNodos (br 3 leaf leaf)"

primrec depth::"'a btree => int" where
  "depth leaf = 0" |
  "depth (br x left right) = (max (depth left) (depth right)) + 1"

value "depth (br 3 leaf leaf)"

text{* Exercício 05 *}

datatype boolex = Const bool | Var nat | Neg boolex | And boolex boolex

term "And (Var 0) (Neg (Var 1))"

text{* Exercício 06 *}

primrec "eval" :: "boolex => (nat => bool) => bool" where
  "eval (Const b) env = b" |
  "eval (Var x)   env = env x" |
  "eval (Neg b)   env = (\<not> eval b env)" |
  "eval (And b c) env = (eval b env \<and> eval c env)"

value "eval (And (Neg (Var 1)) (Var 2)) ((%x::nat. False)(2:=True))"

text{* Exercício 07 *}

datatype boolexa = Const bool | Var nat | Neg boolexa | And boolexa boolexa | Or boolexa boolexa | Implicate boolexa boolexa

primrec "evalu" :: "boolexa => (nat => bool) => bool" where
  "evalu (Const b)       env = b" |
  "evalu (Var x)         env = env x" |
  "evalu (Neg b)         env = (\<not> evalu b env)" |
  "evalu (And b c)       env = (evalu b env \<and> evalu c env)" |
  "evalu (Or b c)        env = (evalu b env \<or> evalu c env)" |
  "evalu (Implicate b c) env = (evalu b env \<longrightarrow> evalu c env)"

value "evalu (Implicate (Neg (Var 1)) (Var 2)) ((%x::nat. False)(2:=True))"

text{* Exercício 08 *}

text{* ... *}

lemma "P \<and> Q \<longrightarrow> R \<Longrightarrow> P \<longrightarrow> Q \<longrightarrow> R"
  apply (rule impI)
  apply (rule impI)
  apply (erule mp)
  apply (erule conjI)
  apply (assumption)
done

end
