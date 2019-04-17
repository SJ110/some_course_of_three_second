
(*++是Haskell中的concat运算符。在SML中它是@*)
fun reverse []:int list = []
  | reverse (h::tl) = reverse tl @ [h];
  reverse([1,2,3,4]);
  print("\n");


fun ins(x,[])=[x]
  | ins(x,y::L)=y::ins(x,L);

fun reverse' [] :int list =[]
  | reverse'(x::L) =reverse' L @ ins(x,[]); 
 reverse'[2,6,5,4];
 print("\n");

 fun interleave([],R)=R 
    | interleave(L,[])=L 
    | interleave(x::L,y::R)=[x,y]@interleave(L,R);
  interleave([1,2],[4,5,6]);
 print("\n");

datatype tree = Empty | Node of (tree * int * tree)   (* left  value  right *)

fun fullPreTrav Empty = "* "
  | fullPreTrav (Node (left, x, right)) = ((Int.toString x) ^ " " ^ (fullPreTrav left) ^ (fullPreTrav right))

fun treeToList_in Empty = []
  | treeToList_in (Node (left, x, right)) = ((treeToList_in left) @ x :: (treeToList_in right))

exception EmptyList

 fun split[] =raise EmptyList
  | split L=let val half =((List.length L) div 2)
            in  ((List.take (L, half)), (List.nth (L, half)), (List.drop (L, (half + 1))))
            end
            

            
  fun listToTree[]=Empty
    | listToTree L = let val (left, mid, right) = (split L) 
                     in (Node ((listToTree left), mid, (listToTree right)))
                   end
val tmp=listToTree([1,2,3,4,5]);
val R = (print ("   tmp = (listToTree [1, 2, 3, 4, 5]) = (preorder) "
      ^ (fullPreTrav tmp) ^ "\n"));
 print("\n");


fun revT Empty = Empty
  | revT (Node (left, x, right)) = (Node ((revT right), x, (revT left)))
 val tmp_tree_rev = (revT tmp);
val R = (print ("   tmp_tree_rev = (revT tmp) = (preorder) " ^ (fullPreTrav tmp_tree_rev) ^ "\n"));
val R = (print ("   ((treeToList_in tmp_tree_rev) = (reverse (treeToList_in tmp))) = "
              ^ (Bool.toString ((treeToList_in tmp_tree_rev) =
               (reverse (treeToList_in tmp)))) ^ "\n"));
print("\n");

fun binarySearch (Empty, int) = false
  | binarySearch ((Node (left, x, right)), y) =
        let val rst = (Int.compare (y, x)) in
          if rst = LESS
          then (binarySearch (left, y))
          else if rst = EQUAL
          then true
          else (binarySearch (right, y))
        end

val search_tree = (Node ((Node ((Node (Empty, 1, Empty)), 
2, (Node (Empty, 
3, (Node (Empty, 
4, Empty)))))), 
5, (Node (Empty, 
6, (Node (Node (Empty, 
7, Empty), 
8, Empty))))))

 val anser=binarySearch (search_tree, 7);
 val anser=binarySearch (search_tree, 12);
