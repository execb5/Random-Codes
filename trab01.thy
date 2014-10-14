theory trab01
imports Main
begin

datatype Nat = Z | suc Nat

primrec add::"Nat => Nat => Nat" where
  "add x Z = x" |
  "add x (suc y) = suc (add x y)"

value "add (len (cons 3 (cons -2 nil))) (len (cons 10 (cons 3( cons 4 nil))))"

primrec Nat2int::"Nat => int" where
  "Nat2int Z = 0" |
  "Nat2int (suc y) = Nat2int(y) + 1"

datatype 'a List = nil | cons 'a "'a List"

primrec len::"'a List => Nat" where
  "len nil = Z" |
  "len (cons y list) = suc (len list)"

value "len (cons (10::int) (cons 3 (cons -2 nil)))"
value "len (cons (10::int) (cons 3 (cons -2 nil)))"
value "len (cons (suc Z) (cons Z nil))"

primrec cat::"'a List => 'a List => 'a List" where
  cat01: "cat nil list= list" |
  cat02: "cat (cons e list1) list2 = (cons e (cat list1 list2))"

value "cat (cons (10::int) (cons 3 (cons -2 nil))) nil"
value "cat (cons (3::int) (cons -2 nil)) (cons 10 (cons 3( cons 4 nil)))"

primrec delete::"'a => 'a List => 'a List" where
  "delete x nil = nil" |
  "delete x (cons e L) = (if x = e then delete x L else cons e (delete x L))"

value "delete (3::int) (cons (3::int) (cons 3 (cons 2 (cons 3 nil))))"

primrec revert::"'a List => 'a List" where
  rev01: "revert nil = nil" |
  rev02: "revert (cons e L) = cat (revert L) (cons e nil)"

datatype 'a btree = leaf | br 'a "'a btree" "'a btree"

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

primrec inorder::"'a btree => 'a List" where
  in01: "inorder leaf = nil" |
  in02: "inorder (br x left right) = cat (inorder left) (cons x (inorder right))"

value "inorder (br (3::int) (br 4 (br 6 leaf leaf) leaf) (br 5 leaf leaf))"

primrec postorder::"'a btree => 'a List" where
  pos01: "postorder leaf = nil" |
  pos02: "postorder (br x left right) = cat (postorder left) (cat (postorder right) (cons x nil))"

value "postorder (br (3::int) (br 4 (br 6 leaf leaf) leaf) (br 5 leaf leaf))"

primrec preorder::"'a btree => 'a List" where
  pre01: "preorder leaf = nil" |
  pre02: "preorder (br x left right) = cons x (cat (preorder left) (preorder right))"

value "preorder (br (3::int) (br 4 (br 6 leaf leaf) leaf) (br 5 leaf leaf))"

primrec reflect::"'a btree => 'a btree" where
  re01: "reflect leaf = leaf" |
  re02: "reflect (br x left right) = (br x (reflect right) (reflect left))"

value "reflect (br (3::int) (br 4 leaf leaf) (br 5 leaf leaf))"

theorem catAssociativity: "\<forall> l2 l3. cat l (cat l2 l3) = cat (cat l l2) l3"
  proof (induction l)
    show "\<forall> (l2::'a List) l3. cat nil (cat l2 l3) = cat (cat nil l2) l3"
      proof (rule allI, rule allI)
        fix k::"'a List" and  m::"'a List"
        have         "cat nil (cat k m) = cat k m"           by (simp only:cat01)
        also have              "cat k m = cat (cat nil k) m" by (simp only:cat01)
        finally show "cat nil (cat k m) = cat (cat nil k) m" by this
      qed  
      next
        fix e0::'a and l0::"'a List"
        assume IH: "\<forall> l2 l3. cat l0 (cat l2 l3) = cat (cat l0 l2) l3"
        show "\<forall> l2 l3. cat (cons e0 l0) (cat l2 l3) = cat (cat (cons e0 l0) l2) l3"       
          proof (rule allI, rule allI)
            fix k and m
            have         "cat (cons e0 l0) (cat k m) = cons e0 (cat l0  (cat k m))" by (simp only:cat02)
            also have    "cons e0 (cat l0 (cat k m)) = cons e0 (cat (cat l0 k) m)"  by (simp only:IH)
            also have    "cons e0 (cat (cat l0 k) m) = cat (cons e0 (cat l0 k)) m"  by (simp only:cat02)
            also have    "cat (cons e0 (cat l0 k)) m = cat (cat (cons e0 l0) k) m"  by (simp only:cat02)
            finally show "cat (cons e0 l0) (cat k m) = cat (cat (cons e0 l0) k) m"  by simp
          qed  
      qed

theorem catLNil: "cat nil l = cat l nil"
  proof (induction l)
    show "cat nil nil = cat nil nil"
      proof -
        have         "cat nil nil = nil"         by (simp only: cat01)
        also have            "... = cat nil nil" by (simp only: cat01)
        finally show "cat nil nil = cat nil nil" by this
      qed
      next
        fix e::'a and l::"'a List"
        assume IH: "cat nil l = cat l nil"
        show "cat nil (cons e l) = cat (cons e l) nil"
          proof -
            have         "cat nil (cons e l) = cons e l"           by (simp only: cat01)
            also have                   "... = cons e (cat nil l)" by (simp only: cat01)
            also have                   "... = cons e (cat l nil)" by (simp only: IH)
            also have                   "... = cat (cons e l) nil" by (simp only: cat02)
            finally show "cat nil (cons e l) = cat (cons e l) nil" by this
          qed
      qed

theorem crazyRev: "\<forall> l2. revert (cat l l2) = cat (revert l2) (revert l)"
  proof (induction l)
    show "\<forall> l2. revert (cat nil l2) = cat (revert l2) (revert nil)"
      proof (rule allI)
        fix l::"'a List"
        have         "revert (cat nil l) = revert l"                    by (simp only: cat01)
        also have                   "... = cat nil (revert l)"          by (simp only: cat01)
        also have                   "... = cat (revert l) nil"          by (simp only: catLNil)
        also have                   "... = cat (revert l) (revert nil)" by (simp only: rev01)
        finally show "revert (cat nil l) = cat (revert l) (revert nil)" by this
      oops

theorem th01: "postorder (reflect x) = revert (preorder x)"
  proof (induction x)
    show "postorder (reflect leaf) = revert (preorder leaf)"
      proof -
        have         "postorder (reflect leaf) = postorder leaf"         by (simp only: re01)
        also have                         "... = nil"                    by (simp only: pos01)
        also have                         "... = revert nil"             by (simp only: rev01)
        also have                         "... = revert (preorder leaf)" by (simp only: pre01)
        finally show "postorder (reflect leaf) = revert (preorder leaf)" by this
      qed
      next
        fix x::'a and left::"'a btree" and right::"'a btree"
        assume IH1: "postorder (reflect left) = revert (preorder left)"
        assume IH2: "postorder (reflect right) = revert (preorder right)"
        show "postorder (reflect (br x left right)) = revert (preorder (br x left right))"
          proof -
            have "postorder (reflect (br x left right)) = postorder (br x (reflect right) (reflect left))"                               by (simp only: re02)
            also have                              "... = cat (postorder (reflect right)) (cat (postorder (reflect left)) (cons x nil))" by (simp only: pos02)
            also have                              "... = cat (revert (preorder right)) (cat (postorder (reflect left)) (cons x nil))"   by (simp only: IH2)
            also have                              "... = cat (revert (preorder right)) (cat (revert (preorder left)) (cons x nil))"     by (simp only: IH1)
            also have                              "... = cat (cat (revert (preorder right)) (revert (preorder left))) (cons x nil)"     by (simp only: catAssociativity)
          oops


end
