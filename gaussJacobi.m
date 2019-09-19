function gaussJacobi(A, b, x0, epslon) 
  #Find g
  g = [];
  for i  = 1:length(b)
    g(i) = b(i)/A(i,i);
  endfor
  g = reshape(g, length(g), 1);
  display(g)
  
  #Find C
  C = [];
  for i  = 1:length(A) 
    divisor = A(i,i);
    for j  = 1:length(A)
      if(i != j)
        C(i,j) = -1*A(i,j)/divisor;
      else
        C(i,j) = 0;
      endif
    endfor
  endfor
  
  display(C)
  
  #Find x and k
  k = 0;
  do 
    x1 = C*x0 + g;
    x = x0;
    x0 = x1;
    k++;
  until max(abs(x1 - x))<epslon
  
  display(x1);
  display(k)
  
endfunction