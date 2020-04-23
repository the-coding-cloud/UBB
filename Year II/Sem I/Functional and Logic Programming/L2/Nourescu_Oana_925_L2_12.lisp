; 12. Determine the list of nodes accesed in preorder in a tree of type (2).
; Mathematical model
; preorder(l1,...,ln) =
;       - [], if n = 0
;       - l1 U preorder(l2) U preorder(l3), otherwise

(defun preorder (l)
    (cond
    ((null l) nil)
    (T (append (list (car l)) (preorder (cadr l)) (preorder (caddr l))))
    )
)

(print (preorder '(1(2(4)(5))(3))))
(print (preorder '(A (B) (C (D) (E)))))
