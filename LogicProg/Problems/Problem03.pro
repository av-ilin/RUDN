%    Пусть задан список фактов, содержащий числовые значения, например, s(<num>).
%    - Необходимо определить количество положительных и отрицательных элементов,
%    - количество элементов, превосходящих по модулю заданный
%    - среднее арифметическое положительных элементов

implement main
    open core, stdio

class facts
    s : (integer Value).

clauses
    s(1).
    s(2).
    s(-1).
    s(-10).
    s(0).
    s(0).
    s(18).
    s(3).

class predicates
    countpositivenum : (integer* List) -> integer Count.
clauses
    countpositivenum([]) = 0 :-
        !.
    countpositivenum([H | T]) = 1 + countpositivenum(T) :-
        H > 0,
        !.
    countpositivenum([_ | T]) = countpositivenum(T) :-
        !.
    countpositivenum(_) = -1.

class predicates
    countnegativenum : (integer* List) -> integer Count.
clauses
    countnegativenum([]) = 0 :-
        !.
    countnegativenum([H | T]) = 1 + countnegativenum(T) :-
        H < 0,
        !.
    countnegativenum([_ | T]) = countnegativenum(T) :-
        !.
    countnegativenum(_) = -1.

class predicates
    morethan : (integer* List, integer Num) -> integer Count.
clauses
    morethan([], _) = 0 :-
        !.
    morethan([H | T], Num) = 1 + morethan(T, Num) :-
        Num >= 0,
        H >= 0,
        H > Num,
        !.
    morethan([H | T], Num) = 1 + morethan(T, Num) :-
        Num < 0,
        H < 0,
        -H > -Num,
        !.
    morethan([H | T], Num) = 1 + morethan(T, Num) :-
        Num >= 0,
        H < 0,
        -H > Num,
        !.
    morethan([H | T], Num) = 1 + morethan(T, Num) :-
        Num < 0,
        H >= 0,
        H > -Num,
        !.
    morethan([_ | T], Num) = morethan(T, Num) :-
        !.
    morethan(_, _) = -1.

class predicates
    sumpositivenum : (integer* List) -> integer Sum.
    avarageposnum : (integer* List) -> real Average.

clauses
    sumpositivenum([]) = 0 :-
        !.
    sumpositivenum([H | T]) = H + sumpositivenum(T) :-
        H > 0,
        !.
    sumpositivenum([_ | T]) = sumpositivenum(T) :-
        !.
    sumpositivenum(_) = -1.

    avarageposnum(List) = sumpositivenum(List) / Count :-
        Count = countpositivenum(List),
        Count > 0,
        !.
    avarageposnum(_) = -1.

clauses
    run() :-
        List = [ Num || s(Num) ],
        writef("Count of positive numbers: %\n", countpositivenum(List)),
        writef("Count of negative numbers: %\n", countnegativenum(List)),
        Num = -10,
        writef("Count of numbers more than % on module: %\n", Num, morethan(List, Num)),
        writef("Avarage of positive numbers: %\n", avarageposnum(List)),
        fail.

    run().

end implement main

goal
    console::runUtf8(main::run).
