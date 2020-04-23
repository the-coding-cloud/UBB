; 3.
; a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.

; Mathematical model:
; insert(l1,...,ln, A, pos) =
;	- [], if n=0
;	- l1 U insert(l2,...,ln, A, pos+1), if pos%2=1
;	- {l1, A} U insert(l2,...,ln, A, pos+1), if pos%2=0

(defun insert (l e pos)
    (cond
        ((null l) nil)
        ((equal (mod pos 2) 1) (cons (car l) (insert (cdr l) e (+ pos 1))))
        (T (cons (car l) (cons e (insert (cdr l) e (+ pos 1)))))
    )
)

(defun main (l e)
    (insert l e 1)
)

(print (main '(1 2 3 4 5 6 A B) 9))


; b) Write a function to get from a given list the list of all atoms, on any
;  level, but reverse order. Example:
;  (((A B) C) (D E)) ==> (E D C B A)

; Mathematical model:
; get_all(l1,....,ln) =
;	- [], if n=0
;	- l1 U get_all(l2,...,ln), if l1 = atom
;	- get_all(l1) U get_all(l2,...,ln), if l1 = list

; reverse_linear(l1,...,ln) =
;	- [], if n=0
;	- reverse_linear U l1, otherwise

(defun getAll (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (cons (car l) (getAll (cdr l))))
    (T (append (getAll (car l)) (getAll (cdr l))))
  )
)

(defun reverseLiniar (l)
  (cond
    ((null l) nil)
    (T (append (reverseLiniar (cdr l)) (list (car l))))
  )
)

(defun reverseNonLiniar (l)
  (reverseLiniar (getAll l))
)

(print (reverseNonLiniar '(1 2 3 (4 5 (6 7 A)))))


; c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list.

; Mathematical model
; gcd(a, b) =
;  - nil, if a, b = not numbers
;	- a, if b - not number
;	- b, if a - not number
;	- b, if a = 0
;	- a, if b = 0
;	- gcd(b, a%b)

;  gcd_list(l1,...,ln) =
;	- l1, if l1 - atom, n=1
;	- gcd(l1, gcd_list(l2,...,ln)), if l1 = atom
;	- gcd(gcd_list(l1), gcd_list(l2,...,ln)), if l1 = list


(defun _gcd (a b)
    (cond
        ((and (not (numberp a)) (not (numberp b))) nil)
        ((not (numberp a)) b)
        ((not (numberp b)) a)
        ((equal a 0) b)
        ((equal b 0) a)
        (T (_gcd b (mod a b)))
    )
)

(defun gcd_list (l)
    (cond
        ((and (atom (car l)) (null (cdr l))) (car l))
        ((listp (car l)) (_gcd (gcd_list (car l)) (gcd_list (cdr l))))
        (T (_gcd (car l) (gcd_list (cdr l))))
    )
)

(print (gcd_list '(8 (12 (16 A 0)) 72)))


; d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.
; Mathematical model
;count_occurrences(l1,...,ln, e) =
;	- 0, if n=0
;	- count_occurences(l1, e) + count_occurences(l2,...,ln,e), if l1 - list
;	- 1 + count_occurences(l2,...,ln, e), if l1 = e
;   - 0 + count_occurences(l2,...,ln, e), if l1 != e

(defun count_occurences (l e)
    (cond
        ((null l) 0)
        ((and (atom (car l)) (equal (car l) e)) (+ 1 (count_occurences (cdr l) e)))
        ((atom (car l)) (+ 0 (count_occurences (cdr l) e)))
        (T (+ (count_occurences (car l) e) (count_occurences (cdr l) e)))
    )
)

(print (count_occurences '(1 (2 (3 4 5) (3 6)) 3 7) 8))
