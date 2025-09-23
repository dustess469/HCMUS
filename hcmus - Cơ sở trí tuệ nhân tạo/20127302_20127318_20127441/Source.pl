male(philip).
male(pharles).
male(william).
male(harry).
male(louis).
male(george).
male(archie_Harrison).
male(andrew).
male(edward).
male(mark_Phillips).
male(timothy_Laurence).
male(peter_Phillips).
male(mike_Tindall).
male(james).

female(queen_Elizabeth_II).
female(diana).
female(camilia_Parker_Bowles).
female(kate_Middleton).
female(meghan_Markle).
female(anne).
female(charlotte).
female(autumn_Phillips).
female(zara_Tindall).
female(sarah_Ferguson).
female(eugenie).
female(beatrice).
female(sophie_Rhys_Jones).
female(louis_Windsor).

parent(philip,charles).
parent(queen_Elizabeth_II,charles).
parent(philip,andrew).
parent(queen_Elizabeth_II,andrew).
parent(philip,anne).
parent(queen_Elizabeth_II,anne).
parent(philip,edward).
parent(queen_Elizabeth_II,edward).

parent(charles,william).
parent(diana,william).
parent(charles,harry).
parent(diana,harry).

parent(william, george).
parent(kate_Middleton, george).
parent(william, charlotte).
parent(kate_Middleton, charlotte).
parent(william,louis).
parent(kate_Middleton,louis).

parent(harry,archie_Harrison).
parent(meghan_Markle,archie_Harrison).

parent(andrew, eugenie).
parent(sarah_Ferguson ,eugenie).
parent(andrew, beatrice).
parent(sarah_Ferguson ,beatrice).

parent(mark_Phillips, peter_Phillips).
parent(anne, peter_Phillips).
parent(mark_Phillips, zara_Tindall).
parent(anne, zara_Tindall).

parent(edward, louis_indsor).
parent(sophie_Rhys_Jones,louis_Windsor).
parent(edward,james).
parent(sophie_Rhys_Jones,james).

married(queen_Elizabeth_II, philip).
married(philip,queen_Elizabeth_II).
married(charles, camilia_Parker_Bowles).
married(camilia_Parker_Bowles, charles).
married(william,kate_Middleton).
married(kate_Middleton, william).
married(harry, meghan_Markle).
married(meghan_Markle, harry).
married(andrew, sarah_Ferguson).
married(sarah_Ferguson, andrew).
married(timothy_Laurence, anne).
married(anne, timothy_Laurence).
married(peter_Phillips,autumn_Phillips).
married(autumn_Phillips, peter_Phillips).
married(mike_Tindall, zara_Tindall).
married(zara_Tindall, mike_Tindall).
married(edward, sophie_Rhys_Jones).
married(sophie_Rhys_Jones, edward).

divorced(charles, diana).
divorced(diana, charles).
divorced(mark_Phillips, anne).
divorced(anne, mark_Phillips).


father(X,Y) :- parent(X,Y), male(X).
mother(X,Y) :- parent(X,Y), female(X).
child(X,Y) :- parent(Y,X).
son(X,Y) :- parent(Y,X), male(X).
daughter(X,Y) :- parent(Y,X), female(X).

grandparent(X,Y) :- parent(X,Z), parent(Z,Y).
grandmother(X,Y) :- mother(X,Z), parent(Z,Y).
grandfather(X,Y) :- father(X,Z), parent(Z,Y).
grandchild(X,Y) :- grandparent(Y,X).
grandson(X,Y) :- grandparent(Y,X), male(X).
granddaughter(X,Y) :- grandparent(Y,X), female(X).
spouse(X,Y) :- married(X,Y), female(Y), male(X).
husband(X,Y) :- married(X,Y), male(X).
wife(X,Y) :- married(X,Y),female(X), male(Y).
sibling(X,Y) :- parent(Z,X), parent(Z,Y), X \== Y.
brother(X,Y) :- sibling(X,Y), male(X).
sister(X,Y) :- sibling(X,Y), female(X).
aunt(X,Y) :- sister(X,Z), parent(Z,Y).
uncle(X,Y) :- brother(X,Z), parent(Z,Y).
nephew(X,Y) :- sibling(Y,Z), parent(Z,X), male(X).
niece(X,Y) :- sibling(Y,Z), parent(Z,X), female(X).
firstCousin(X,Y) :- sibling(Z,T), parent(Z,X), parent(T,Y).
