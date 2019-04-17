fun thenAddOne(f,x)=((f x)+1)
 val it=thenAddOne(Int.abs,~5) ;    (*绝对值加1*)
 print("\n");


 fun maplist(f,[])=[]
    | maplist(f,y::L)=(f y)::maplist(f,L);
val it=maplist(Int.abs,[~1,~2,~3]);
print("\n");

fun maplist' f = fn L => 
            case L of
                []=>[]
            | x::R =>(f x):: (maplist' f R);

val it=maplist' Int.abs [~1,~2,~3];
print("\n");

fun findOdd ([])= NONE
    |findOdd(x::L) =
     let val it=x mod 2
     in
     if(it = 1)  then (SOME x)
     else findOdd(L)
     end
val it=findOdd([2,2,2]);
print("\n");


fun map f [] =[]
    |map f(x::R) =(f x)::(map f R);

fun sublist ([]) =[[]]
    | sublist (x::R) =
        let 
          val S= sublist R
          in 
          S @ map(fn A=>x::A) S
          end   
          (*val it=sublist [1,2,3];*)

fun sum [] =0
 | sum(x::R) =x+(sum R);
(*sum [1,2,3];*)  

fun uselist (a,x::R) = 
     if (sum x )= a then (SOME x)
     else if (R=[])  then NONE
          else uselist(a,R)

fun subsetSumOption(L,s) = 
    if(sum L) = s  
       then SOME L
    else 
        uselist(s,sublist(L))
    
    val subsetSumOption =  subsetSumOption([1,2,3],9);
    print("\n");


fun exists p [] = false
  | exists p (x::L) = 
   if (p x) then true
   else 
     (exists p L)

 val it = exists(fn x => x = 10) [1, 2, 3, 11];
 print("\n");

fun forall p [] = true
  | forall p (x::L) = 
  if (p x) = x then false
   else  (forall p L)

val it =  (forall op~ [1, 2, 3]) ;


datatype 'a tree = Null | Node of 'a tree * 'a * 'a tree

fun treeToString_pre (Null, xtostring) = "*"
  | treeToString_pre ((Node (left, x, right)), xtostring) =
        ((treeToString_pre (left, xtostring)) ^ " " ^ (xtostring x) ^ " " ^ (treeToString_pre (right, xtostring)))

fun optionToString (opt, toString) = if (Option.isSome opt) then (toString (Option.valOf opt)) else "x"

(* ('a -> bool) -> 'a tree -> 'a option tree *)
fun treeFilter p Null = Null
  | treeFilter p (Node (left, x, right)) =
        let val neo_x = if (p x) then (SOME x) else NONE in
          (Node ((treeFilter p left), neo_x, (treeFilter p right)))
        end
val search_tree = (Node ((Node ((Node (Null, 1, Null)), 
2, (Node (Null, 
3, (Node (Null, 
4, Null)))))), 
5, (Node (Null, 
6, (Node (Node (Null, 
7, Null), 
8, Null))))))

 val _ =  treeToString_pre (search_tree, Int.toString) 
 

 val it=   (treeToString_pre ((treeFilter (fn x => x < 7 andalso x > 3) search_tree), 
 (fn opt => (optionToString (opt, Int.toString))))) 