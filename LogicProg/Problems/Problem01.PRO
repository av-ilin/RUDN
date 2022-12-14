/* Family relationship */
person(1, "Tom", male).
person(2, "Pam", female).
person(3, "Matt", male).
person(4, "Maggy", female).
person(5, "Julya", female).
person(6, "Daemon", male).
person(7, "Tony", male).

/* parent(Child, Parent) */
parent(3, 1).
parent(3, 2).
parent(4, 1).
parent(4, 2).
parent(1, 5).
parent(1, 6).
parent(2, 7).

/* String: father("Matt", "Tom") */
father(Child, Father) :- 
    person(ChildId, Child, _), 
    person(FatherId, Father, male), 
    parent(ChildId, FatherId).

/* String: mother("Matt", "Pam") */
mother(Child, Mother) :- 
    person(ChildId, Child, _), 
    person(MotherId, Mother, female), 
    parent(ChildId, MotherId).

/* String: gfather("Matt", "Daemon"), gfather("Matt", "Tony") */
gfather(GChild, GFather) :- 
    father(GChild, Father), father(Father, GFather);
    mother(GChild, Mother), father(Mother, GFather).

/* String: gmother("Matt", "Julya") */
gmother(GChild, GMother) :- 
    father(GChild, Father), mother(Father, GMother);
    mother(GChild, Mother), mother(Mother, GMother).

/* String: sister("Matt", "Julya") */
sister(Person, Sister) :-
    person(PersonId, Person, _),  person(SisterId, Sister, _), PersonId \= SisterId, 
    person(_, Sister, female),
    father(Person, Father), father(Sister, Father),
    mother(Person, Mother), mother(Sister, Mother).

/* String: brother("Julya", "Matt") */
brother(Person, Brother) :-
    person(PersonId, Person, _),  person(BrotherId, Brother, _), PersonId \= BrotherId, 
    person(_, Brother, male),
    father(Person, Father), father(Brother, Father),
    mother(Person, Mother), mother(Brother, Mother).

/* String: ancestor("Matt", "Daemon") */
ancestor(Person, Ancestor) :- 
    person(PersonId, Person, _), person(AncestorId, Ancestor, _),
    parent(PersonId, AncestorId);
    person(PersonId, Person, _), person(AncestorId, Ancestor, _),
    parent(PersonId, ParentId),
    person(ParentId, Parent, _),
    ancestor(Parent, Ancestor).
    
    