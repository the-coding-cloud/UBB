; reverseList(l1,...,ln) =
; - [], if n=0
; - reverseList(l2,...,ln)Ul1, otherwise

(defun reverseList(l)
    (cond
        ((null l) nil)
        (t (append (reverseList (cdr l)) (list (car l))))))

(print (reverseList '(1 2 3 4)))

; multiplyNumber(l1,...,ln,carry,ct) =
; - carry, if carry>0, n=0
; - [], if carry=0, n=0
; - (l1*ct+carry)%10 U multiplyNumber(l2,...,ln,(l1*ct+carry)/10, ct)

(defun multiplyNumber(l carry ct)
    (cond
        ((and (> carry 0)(null l)) (list carry))
        ((and (= carry 0)(null l)) nil)
        (t (cons (mod (+ (* (car l)ct) carry) 10) (multiplyNumber (cdr l) (floor (/ (+ (* (car l)ct) carry) 10)) ct)))))

(print (multiplyNumber '(2 3 1) 0 2))

; main(l1,...,ln, ct) =
; reverseList(multiplyNumber((reverseList(l1,....,ln), 0, ct)))

(defun main (l ct)
    (reverseList(multiplyNumber (reverseList l) 0 ct)))

(print (main '(9 9) 2))

