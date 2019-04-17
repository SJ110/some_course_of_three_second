fun sum ([]:int list) =0 
  | sum(x::L)=x+(sum L);
sum[1,2,3,4,5,6];


fun mult([]:int list):int=1 
  |mult(x::L)=x*(mult L);
mult[1,2,3,4];   

fun Mult([]:(int list) list):int = 1
  |Mult(r::R)= (mult r)*(Mult R);
  Mult[[2],[1,2,3],[4,5,6]];

fun mult' ([], a) = a
	  | mult' (x :: L, a) = mult' (L, x * a);
mult'([1,2,3],2);

fun Mult'([]:(int list) list,a):int=1
	| Mult'(r::R,a)=mult'(r,a)*(Mult'(R,a));
	Mult'([[1,2,3],[1,2]],2);

fun double (0 : int) : int = 0
    | double n = 2 + double (n - 1);
double(3);


fun square(n:int,0):int =0
    | square (n,a)=double(n) div 2+square(n,a-1) ;
    square(0,0);


fun divisiableByTree(n:int):bool=
   if n>=3 then divisiableByTree(n-3)
      else if n<=(~3) then divisiableByTree(n+3)
             else  if n=0 then true
                    else false;
 divisiableByTree(~7);


 fun oddp(0:int) :bool=false
    | oddp 1=true
    | oddp n=oddp(n-2);
    oddp(6);