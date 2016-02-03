/*******************************************/
/**    Your solution goes in this file    **/ 
/*******************************************/

/**************
(a) Find all courses with 3 or 4 credits (fc course).
**************/
fc_course(Name):- course(Name,List,Unit),(Unit=3;Unit=4).


/**************
(b) Find all courses whose immediate pre-requisite is ecs110 (prereq 110).
**************/
prereq_110(Name):- course(Name,List,Unit),(member(ecs110,List)).


/**************
(c) Find names of all students in ecs140a (ecs140a students).
**************/
ecs140a_students(Name):- student(Name,List),(member(ecs140a,List)).


/**************
(d) Find the names of all instructors who teach john’s courses (instructor names).
**************/
instructor_names(Name):- instructor(Name,_),teach_john(Name).
teach_john(Name):- instructor(Name,CI),student(john,CS),member(C,CI),member(C,CS),!.


/**************
(e) Find the names of all students who are in jim’s class (students).
**************/
students(Name):- student(Name,_),taught_jim(Name).
taught_jim(Name):- student(Name,CS),instructor(jim,CI),member(C,CI),member(C,CS),!.


/**************
(f) Find all pre-requisites of a course (allprereq). (This will involve finding not only the immediate
prerequisites of a course, but pre-requisite courses of pre-requisites and so on.)
**************/
allprereq(C,PS):- findall(CC,(course(CC,_,_),prereq(C,CC)),PS).
prereq(C,P):- course(C,List,Unit),member(P,List).
prereq(C,P):- course(C,List,Unit),member(X,List),prereq(X,P).


/**************
part2
**************/
all_length([],0).
all_length([[]|T],L):- all_length(T,Len),L is Len+1,!.
all_length([H|T],Len):- atom(H), all_length(T,LenT), Len is LenT + 1.
all_length([H|T],L):- all_length(H,Len), all_length(T,LenT), L is Len +LenT.


equal_a_b(L):- equal_help(L,Acount,Bcount),!, Acount = Bcount.
equal_help([], 0, 0).
equal_help([a|T],Acount,Bcount):- equal_help(T,Acount1,Bcount), Acount is Acount1 + 1.
equal_help([b|T],Acount,Bcount):- equal_help(T,Acount,Bcount1), Bcount is Bcount1 + 1.
equal_help([_|T],Acount,Bcount):- equal_help(T,Acount,Bcount).


swap_prefix_suffix(K,L,S):- append3(L1,K,L3,L), append3(L3,K,L1,S).
append3(L1,L2,L3,L):- append(L1,LL,L),append(L2,L3,LL).


palin(L):- my_reverse(L,LR), L = LR.
my_reverse([],[]).
my_reverse([H|T],LR):- my_reverse(T,TR),append(TR,[H],LR).


good(L):- isgood(L), !.
isgood([]).
isgood([0|T]):- isgood(T).
isgood([1|T]):- isgood2(T).
isgood2([0,0|T]):- isgood(T).
isgood2([0,1|T]):- isgood2(T).
isgood2([1|T]):- isgood2(T).




/* part 3 */
solve:- find(AllPaths),
        reverse(AllPaths,ModifiedPaths),
        converttomoves(ModifiedPaths,Moves),
        reverse(Moves,Sol),
        printlist(Sol),!.
        
initial(state(left,left,left,left)).
end(state(right,right,right,right)).

find(AllPaths):- initial(State),process(State,AllPaths).

process(State,AllPaths):- in_process(State,[],AllPaths).

in_process(State,Path,[State|Path]):- end(State).
in_process(State,Paths,AllPaths):- arc(State,State2), safe(State2), \+member(State2,Paths),
                                   in_process(State2,[State|Paths],AllPaths).

/* Farmer & Wolf */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Oppo,Goat,Cabbage)):- Farmer=Wolf,opposite(Farmer,Oppo).

/* Farmer & Cabbage */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Oppo)):- Farmer=Cabbage,opposite(Farmer,Oppo).

/* Farmer & Goat */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Oppo,Cabbage)):- Farmer=Goat,opposite(Farmer,Oppo).

/* Farmer alone */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Cabbage)):- opposite(Farmer,Oppo).


state(Farmer,Wolf,Goat,Cabbage).
take(Object,Bank1,Bank2).
unsafe(state(Farmer,Wolf,Goat,Cabbage)):- Goat=Wolf,opposite(Farmer,Goat),!.         /* Wolf eat Goat case */
unsafe(state(Farmer,Wolf,Goat,Cabbage)):- Goat=Cabbage,opposite(Farmer,Goat),!.      /* Goat eat Cabbage case */
safe(state(Farmer,Wolf,Goat,Cabbage)):-  \+unsafe(state(Farmer,Wolf,Goat,Cabbage)).
opposite(Bank1,Bank2):- (Bank1 = left,Bank2 = right);(Bank1 = right,Bank2 = left).

converttomoves([H|T],Moves):- initial(H),convert_process(H,T,[],Moves).
convert_process(H,[HH|T],Takes,Moves):- end(HH),generatetake(H,HH,Take),append([Take],Takes,Moves).
convert_process(H,[HH|T],Takes,Moves):- generatetake(H,HH,Take),convert_process(HH,T,[Take|Takes],Moves).

generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Oppo,Goat,Cabbage),take(wolf,Wolf,Oppo)):- Farmer=Wolf,opposite(Farmer,Oppo).
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Oppo),take(cabbage,Cabbage,Oppo)):- Farmer=Cabbage,opposite(Farmer,Oppo).
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Oppo,Cabbage),take(goat,Goat,Oppo)):- Farmer=Goat,opposite(Farmer,Oppo).        
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Cabbage),take(none,Farmer,Oppo)):- opposite(Farmer,Oppo).

printlist([]).
printlist([H|T]):- write(H),write('\n'),printlist(T).



