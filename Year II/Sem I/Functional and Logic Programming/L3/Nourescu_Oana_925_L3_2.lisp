; Write a function that returns the sum of numeric atoms in a list, at any level.
; Mathematical model:
; sum(l) =
; - l if l - number
; - 0 if l - atom
; - sum(l1)+...+sum(ln) if l - list

(defun sum(l)
    (cond
        ((numberp l) l)
        ((atom l) 0)
        (t (apply #'+ (mapcar #'sum l)))
    )
)

(print (sum '(1 2 3 (4 a (5 b) 6))))