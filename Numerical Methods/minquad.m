function minquad(x,y,g,x_til)
  n = length(g);
  m = length(x);
  
  A = zeros(n,n);
  for i = 1:n
    for j = 1:n
      A(i,j) = somatorio1(x,g,i,j);
    endfor
  endfor 
  
  display(A)
  
  for i = 1:n
    b(i) = somatorio2(x,y,g,i);
  endfor
  
  display(b)
  
  alfa = b*inv(A);
  display(alfa)
  
  y_til = [];
  for i =1:n
    y_til = somatorio3(alfa,g,x_til);
  endfor
  
  display(y_til)
  
  
endfunction


function sum = somatorio1(x,g,i,j)
  sum = 0;
  for k = 1:length(x)
    sum+= g{i}(x(k))*g{j}(x(k));
  endfor

endfunction

function sum = somatorio2(x,y,g,i)
  sum = 0;
  for k = 1:length(x)
    sum+= y(k)*g{i}(x(k));
  endfor

endfunction

function sum = somatorio3(alfa,g,x_til)
  sum = 0;
  for k = 1:length(g)
    sum+= alfa(k)*g{k}(x_til);
  endfor

endfunction
