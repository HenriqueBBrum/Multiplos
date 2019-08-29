function msecante(f, x0, x1, epslon)
  i = 0;
  do
    x = (x0*f(x1)-x1*f(x0))/(f(x1)-f(x0));
    printf("Iteracao: %d,  x = %f, f(x) = %f\n", i, x, f(x));
    x0 = x1;
    x1 = x;
    i++;
  until(abs(f(x))<epslon) 
  
  printf("Final Iteracoes: %d,  raiz aproximada : %f\n", i, x);
  
  
endfunction